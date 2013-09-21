export ENERGIADIR=/opt/energia
export ENERGIABOARD=lpmsp430g2553
#SOURCES := main.cc other.cc
SOURCES := $(wildcard $(addprefix src/, *.c))
#LIBRARIES := include
INCLUDE := include
ASM_SRC = src/ws2811_hs.S
ASM_OBJ = $(ASM_SRC:.S=.o)
%.o: %.S
	echo "Compiling $<"
	$(CC) -D_GNU_ASSEMBLER_ -c $(ASFLAGS) $(CPPFLAGS) $(INCLUDES) -o $@ $<
include energia.mk
