include app/various/various.mk
include app/lld/lld.mk
include app/display/display.mk
include app/usb/usb.mk

APPSRC =    $(VARIOUSSRC) \
            $(LLDSRC) \
            $(DISPLAYSRC) \
            $(USBSRC) \
            app/main.c

APPINC =    $(VARIOUSINC) \
            $(LLDINC) \
            $(USBINC) \
            $(DISPLAYINC)