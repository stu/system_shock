CC=propeller-elf-gcc
CPP=propeller-elf-g++
MEM=cog
CFLAGS=-Os -m$(MEM) -I. -fno-exceptions -Wl,-Map,output.map
CPPFLAGS=-Os -m$(MEM) -I. -fno-exceptions
COGFLAGS=-Os -r -mcog -I. -fno-exceptions
DUMP=propeller-elf-objdump
COPY=propeller-elf-objcopy
LOAD=propeller-load
LOAD_DIR=/opt/propgcc/propeller-load/
TYPE=sparkfun
DEST=/dev/ttyUSB0
OUT=main.prop
OBJS=main.o sol1.cog sol2.cog sol3.cog sol4.cog sol5.cog sol6.cog sol7.cog

CLEANUP_TRIGGER := .makefile
BASE_MAKEFILE := Makefile solenoid.h

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

all: $(CLEANUP_TRIGGER) main.prop


$(CLEANUP_TRIGGER): $(BASE_MAKEFILE)
	if [ -f $(CLEANUP_TRIGGER) ]; then $(MAKE) clean; fi
	touch $@


$(OUT): Makefile $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	$(DUMP) -h $@

sol1.cog: solenoid.cogc
	$(CC) -DXCOGX=cog1 -DXCOGX_IDX=0 $(COGFLAGS) -xc solenoid.cogc -o $@
	$(COPY) --localize-text --rename-section .text=$@ $@

sol2.cog: solenoid.cogc
	$(CC) -DXCOGX=cog2 -DXCOGX_IDX=1 $(COGFLAGS) -xc solenoid.cogc -o $@
	$(COPY) --localize-text --rename-section .text=$@ $@

sol3.cog: solenoid.cogc
	$(CC) -DXCOGX=cog3 -DXCOGX_IDX=2 $(COGFLAGS) -xc solenoid.cogc -o $@
	$(COPY) --localize-text --rename-section .text=$@ $@

sol4.cog: solenoid.cogc
	$(CC) -DXCOGX=cog4 -DXCOGX_IDX=3 $(COGFLAGS) -xc solenoid.cogc -o $@
	$(COPY) --localize-text --rename-section .text=$@ $@

sol5.cog: solenoid.cogc
	$(CC) -DXCOGX=cog5 -DXCOGX_IDX=4 $(COGFLAGS) -xc solenoid.cogc -o $@
	$(COPY) --localize-text --rename-section .text=$@ $@

sol6.cog: solenoid.cogc
	$(CC) -DXCOGX=cog6 -DXCOGX_IDX=5 $(COGFLAGS) -xc solenoid.cogc -o $@
	$(COPY) --localize-text --rename-section .text=$@ $@

sol7.cog: solenoid.cogc
	$(CC) -DXCOGX=cog7 -DXCOGX_IDX=6 $(COGFLAGS) -xc solenoid.cogc -o $@
	$(COPY) --localize-text --rename-section .text=$@ $@

load_run: clean $(OUT)
	$(LOAD) -I$(LOAD_DIR) -b $(TYPE) -p $(DEST) $(OUT) -r -v

load_eeprom: clean $(OUT)
	$(LOAD) -I$(LOAD_DIR) -b $(TYPE) -p $(DEST) $(OUT) -r -e -v

clean:
	touch main.o main.prop main.cog output.map
	rm -f *.o *.prop *.cog output.map
	rm -f $(CLEANUP_TRIGGER)

.PHONY: all clean


