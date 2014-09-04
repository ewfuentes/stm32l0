include app/various/various.mk
include app/lld/lld.mk
include app/display/display.mk

APPSRC =    $(VARIOUSSRC) \
            $(LLDSRC) \
            $(DISPLAYSRC) \
            app/main.c

APPINC =    $(VARIOUSINC) \
            $(LLDINC) \
            $(DISPLAYINC)