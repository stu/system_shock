#ifndef SOLENOID_H
#define SOLENOID_H

#ifdef __cplusplus
extern "C"{
#endif

#define STATE_NOTHING		0
#define STATE_FIRE			1
#define STATE_FIRING		2
#define STATE_PULSE_PAUSE	3
#define STATE_PULSE_FIRE	4
#define STATE_DONE			5

// multiple of 7! as we have 7 cogs running at once, for 35. last cog is capped at 32.
#define SOLS_PER_COG		5

#define ONE_MS          (CLKFREQ / 1000)
#define ONE_SEC			(ONE_MS * 1000)

#define MAX_SOL		32
#define STACK_SIZE	64

struct solenoid_mailbox
{
	uint32_t stack[STACK_SIZE];
	uint32_t action;
};

// configuration data
extern HUBDATA volatile uint32_t initial_pulse_time_min[MAX_SOL];
extern HUBDATA volatile uint32_t initial_pulse_time_max[MAX_SOL];
extern HUBDATA volatile uint32_t pulse_pause_time[MAX_SOL];
extern HUBDATA volatile uint32_t pulse_hold_time[MAX_SOL];

// our runtime changing data
extern HUBDATA volatile uint32_t state[MAX_SOL];
extern HUBDATA volatile uint32_t power_on_ms[MAX_SOL];
extern HUBDATA volatile uint32_t cnt_start[MAX_SOL];

// 7 cogs worth of data
extern HUBDATA volatile uint32_t solenoid_pins0;
extern HUBDATA volatile uint32_t solenoid_pins1;
extern HUBDATA volatile uint32_t solenoid_pins2;
extern HUBDATA volatile uint32_t solenoid_pins3;
extern HUBDATA volatile uint32_t solenoid_pins4;
extern HUBDATA volatile uint32_t solenoid_pins5;
extern HUBDATA volatile uint32_t solenoid_pins6;


extern _load_start_sol1_cog;
extern _load_start_sol2_cog;
extern _load_start_sol3_cog;
extern _load_start_sol4_cog;
extern _load_start_sol5_cog;
extern _load_start_sol6_cog;
extern _load_start_sol7_cog;


#ifdef __cplusplus
};
#endif
#endif

