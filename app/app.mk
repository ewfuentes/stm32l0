include app/various/various.mk
include app/lld/lld.mk
include app/display/display.mk
include app/tinyprintf/tinyprintf.mk

APPSRC =    $(VARIOUSSRC) \
            $(LLDSRC) \
            $(DISPLAYSRC) \
            $(TINYPRINTFSRC) \
            app/main.c

APPINC =    $(VARIOUSINC) \
            $(LLDINC) \
            $(DISPLAYINC) \
            $(TINYPRINTFINC)