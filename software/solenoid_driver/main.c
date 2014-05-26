#include <propeller.h>
#include <stdint.h>
#include <sys/thread.h>

#include "solenoid.h"

struct solenoid_mailbox cogdata[7];

// configuration set over the wire by the master control board
HUBDATA volatile uint32_t initial_pulse_time_min[MAX_SOL];
HUBDATA volatile uint32_t initial_pulse_time_max[MAX_SOL];
HUBDATA volatile uint32_t pulse_pause_time[MAX_SOL];
HUBDATA volatile uint32_t pulse_hold_time[MAX_SOL];

// These change each time coils fire
HUBDATA volatile uint32_t state[MAX_SOL];
HUBDATA volatile uint32_t power_on_ms[MAX_SOL];
HUBDATA volatile uint32_t cnt_start[MAX_SOL];

// each cog gets its own variable so we can go lockless
HUBDATA volatile uint32_t solenoid_pins0;
HUBDATA volatile uint32_t solenoid_pins1;
HUBDATA volatile uint32_t solenoid_pins2;
HUBDATA volatile uint32_t solenoid_pins3;
HUBDATA volatile uint32_t solenoid_pins4;
HUBDATA volatile uint32_t solenoid_pins5;
HUBDATA volatile uint32_t solenoid_pins6;


/* cause all internal data state to reset */
#define CMD_RESET			0x01

/* This takes 4 bytes of 8bit data to setup */
#define CMD_SETUP_SOL		0x02

/* this takes 4x8bit data for 32 switch inputs */
#define CMD_SWITCHES		0x03


/*
 * These pins map as written in the data sheet.
 */

// direct message communication
#define COMMS_D1			0
#define COMMS_D2			1
#define COMMS_D3			2
#define COMMS_D4			3
#define COMMS_D5			4
#define COMMS_D6			5
#define COMMS_D7			6
#define COMMS_D8			7

#define COMMS_D9			8
#define COMMS_D10			9
#define COMMS_D11			10
#define COMMS_D12			11
#define COMMS_D13			12
#define COMMS_D14			13
#define COMMS_D15			14
#define COMMS_D16			15

#define RCV_PIN				27
#define RCV_OK				26

// solenoid outputs
#define HC595_CLK			16
#define HC595_DATA			17
#define HC595_LATCH			18
#define WATCHDOG			19

#define PIN_HIGH(a)		(OUTA |= (1 << (a)))
#define PIN_LOW(a)		(OUTA &= ~(1 << (a)))
#define READ_PIN(a)		(INA & (1 << (a)) )

/* Reads 16bits of data from PIC32 command.
 *
 * @blocking zero will wait until data arrives.
 */
static uint32_t read_command_word (int blocking)
{
	uint32_t data;

	// wait for rcv to go high for data is ready
	while (READ_PIN(RCV_PIN) == 0)
	{
		if (blocking != 0)
			return 0;
	}

	// get 16 bits and say we got it
	data = ((INA >> COMMS_D1) & 0xFFFF);
	PIN_HIGH(RCV_OK);

	// wait for RCV to go low
	while (READ_PIN(RCV_PIN) == 1)
		;

	// put OK low so we are ready for next communication
	PIN_LOW(RCV_OK);

	return data;
}

/* Resets all solenoid out data pins, and all internal data structures
 */
static void reset_data (void)
{
	int i;

	// set all pins to 0
	solenoid_pins0 = 0;
	solenoid_pins1 = 0;
	solenoid_pins2 = 0;
	solenoid_pins3 = 0;
	solenoid_pins4 = 0;
	solenoid_pins5 = 0;
	solenoid_pins6 = 0;

	// kill config
	for (i = 0; i < MAX_SOL; i++)
	{
		initial_pulse_time_min[i] = 0;
		initial_pulse_time_max[i] = 0;
		pulse_pause_time[i] = 0;
		pulse_hold_time[i] = 0;
		state[i] = STATE_NOTHING;
	}


}

/* Output all active solenoid state bits to the
 * 74HC595 chips.
 */
static void hc595_out_solenoids (void)
{
	int i;

	// preload so the cogs can write to it while we out it..
	uint32_t x = solenoid_pins0 | solenoid_pins1 | solenoid_pins2 | solenoid_pins3 | solenoid_pins4 | solenoid_pins5 | solenoid_pins6;

	// latch low so we dont SEE the data change.
	PIN_LOW(HC595_LATCH);

	for (i = 0; i < 32; i++)
	{
		if ((x & 0x80000000) == 0)
			PIN_LOW(HC595_DATA);
		else
			PIN_HIGH(HC595_DATA);

		// Pulse clock input to write next bit.
		PIN_LOW(HC595_CLK);
		PIN_HIGH(HC595_CLK);

		x = x << 1;
	}

	// latch high so data is seen!
	PIN_HIGH(HC595_LATCH);
}

int main (int argc, char *argv[])
{
	uint32_t c1;
	uint32_t switches;
	uint32_t old_switches;

	OUTA = 0;

	// inputs + outputs
#define XXOUT	(1 << RCV_OK) \
				| (1 << HC595_CLK) \
				| (1 << HC595_DATA) \
				| (1 << HC595_LATCH) \
				| (1 << WATCHDOG)


#define XXIN	(1 << RCV_PIN) \
				| (1 << COMMS_D1) \
				| (1 << COMMS_D2) \
				| (1 << COMMS_D3) \
				| (1 << COMMS_D4) \
				| (1 << COMMS_D5) \
				| (1 << COMMS_D6) \
				| (1 << COMMS_D7) \
				| (1 << COMMS_D8) \
				| (1 << COMMS_D9) \
				| (1 << COMMS_D10) \
				| (1 << COMMS_D11) \
				| (1 << COMMS_D12) \
				| (1 << COMMS_D13) \
				| (1 << COMMS_D14) \
				| (1 << COMMS_D15) \
				| (1 << COMMS_D16)

	// all output pins as 1's.
	DIRA = XXOUT;

	cognew(_load_start_sol1_cog, (void *) &cogdata[0]);
	cognew(_load_start_sol2_cog, (void *) &cogdata[1]);
	cognew(_load_start_sol3_cog, (void *) &cogdata[2]);
	cognew(_load_start_sol4_cog, (void *) &cogdata[3]);
	cognew(_load_start_sol5_cog, (void *) &cogdata[4]);
	cognew(_load_start_sol6_cog, (void *) &cogdata[5]);
	cognew(_load_start_sol7_cog, (void *) &cogdata[6]);


	// Do a reset on startup.
	c1 = CMD_RESET;
	old_switches = 0;
	switches = 0;

	while (1)
	{
		//***********************************************************************
		// heartbeat to watchdog chip transition from a high to low state.
		// We have 62ms in order to toggle the pin before reset!
		// **********************************************************************
		PIN_HIGH(WATCHDOG);
		PIN_LOW(WATCHDOG);

		switch (c1)
		{
			case CMD_RESET:
				reset_data();
				old_switches = 0;
				hc595_out_solenoids();
				// wait 2 seconds
				waitcnt(ONE_SEC * 2);
				break;

			case CMD_SETUP_SOL:
				c1 = read_command_word(0); // solenoid in 16bits

				initial_pulse_time_min[c1] = ONE_MS * read_command_word(0);
				initial_pulse_time_max[c1] = ONE_MS * read_command_word(0);
				pulse_pause_time[c1] = ONE_MS * read_command_word(0);
				pulse_hold_time[c1] = ONE_MS * read_command_word(0);
				break;

			case CMD_SWITCHES:
				switches = (read_command_word(0) << 16) | (read_command_word(0));
				break;

				// traps the non message command for non blocking (-1)
			default:
				switches = old_switches;
				break;
		}

		// output the current soelnoid state for on/off
		hc595_out_solenoids();

		// need to compare it against last trigger?? if difference
		// if it its, KAPOW BLAM
		for (c1 = 0; c1 < 32; c1++)
		{
			// SWITCH is ON = FIRE
			if ((switches & (1 << c1)) != 0)
			{
				// previous switch was OFF so FIRE
				if ((old_switches & (1 << c1)) == 0)
				{
					state[c1] = STATE_FIRE;
				}
				else
				{
					// previous switch was on, its still pressed. dont change
				}
			}
			else
			{
				// switch is now off
				state[c1] = STATE_NOTHING;
			}
		}

		// store the old info
		old_switches = switches;

		//waitcnt(ONE_MS);

		// look for a command, non blocking!
		// if no command, put current switch set now in old_d1 back into d1
		c1 = read_command_word(1);
	}
}

