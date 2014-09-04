PROJECT = test

OUTDIR = build/
OBJDIR = $(OUTDIR)obj/
LSTDIR = $(OUTDIR)lst/

include lib/lib.mk
include app/app.mk

SRCS = $(APPSRC) $(LIBSRC)
INCS = $(APPINC) $(LIBINC)
ASSRCS = $(LIBAS)

TARGET = arm-none-eabi-
CC = $(TARGET)gcc
LD = $(TARGET)gcc
AS = $(TARGET)gcc -x assembler-with-cpp
OD = $(TARGET)objdump
CP = $(TARGET)objcopy
SZ = $(TARGET)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary

CFLAGS = -O0 -g3 -Wall -Wextra -mlittle-endian -mthumb
CFLAGS += -mcpu=cortex-m0plus -mthumb-interwork -DSTM32L053xx

ASFLAGS = -mcpu=cortex-m0plus -mthumb -mthumb-interwork

LDFLAGS = -mcpu=cortex-m0 -nostartfiles -T$(LDSCRIPT)
LDFLAGS += -Wl,-Map=$(OUTDIR)/$(PROJECT).map,--cref,--no-warn-mismatch,--gc-sections
LDFLAGS += -mthumb-interwork -mthumb --specs=nano.specs

OBJS = $(addprefix $(OBJDIR),$(notdir $(SRCS:.c=.o)) $(notdir $(ASSRCS:.s=.o)))

OUTFILES = 	$(OUTDIR)$(PROJECT).elf $(OUTDIR)$(PROJECT).hex \
			$(OUTDIR)$(PROJECT).bin $(OUTDIR)$(PROJECT).dmp

IINC = $(patsubst %,-I% ,$(INCS))

SRCPATHS = $(sort $(dir $(SRCS)) $(dir $(ASSRCS)))

VPATH = $(SRCPATHS)

all: $(OBJS) $(OUTFILES) size

$(OBJS): | buildDir

$(OBJDIR)%.o: %.c Makefile
	@echo Compiling $<
	@$(CC) -c $(CFLAGS) $(IINC) $< -o $@

$(OBJDIR)%.o: %.s Makefile
	@echo Compiling $<
	@$(AS) -c $(ASFLAGS) $(IINC) $< -o $@

%.elf: $(OBJS) $(LDSCRIPT)
	@echo Linking $@ using $(LDSCRIPT)
	@$(LD) $(OBJS) $(LDFLAGS) -o $@

%.hex: %.elf $(OBJS) $(LDSCRIPT)
	@echo Creating $@
	@$(HEX) $< $@

%.bin: %.elf $(OBJS) $(LDSCRIPT)
	@echo Creating $@
	@$(BIN) $< $@

%.dmp: %.elf $(LDSCRIPT)
	@echo Creating $@
	@$(OD) -x --syms $< > $@

buildDir:
	@mkdir -p $(OUTDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(LSTDIR)

clean: 
	@echo Cleaning...
	rm -rf $(OUTDIR) .dep
	@echo Done

size: $(OUTFILES)
	@$(SZ) $(OUTDIR)$(PROJECT).hex $(OUTDIR)$(PROJECT).elf