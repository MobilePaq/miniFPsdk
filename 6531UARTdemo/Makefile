NAME = 6531UARTdemo
TWO_STAGE = 0
#LIBC_SDIO = 3

IMAGE_START = 0x3ae000

SYS_EXTRA = sdio microfat sfc

APP_SRCS = main
APP_OBJS1 += $(APP_SRCS:%=$(OBJDIR)/app/%.o)
APP_OBJS2 =

include ../buildinc.make

#CFLAGS += -DSDIO_VERBOSE=2

APP_CFLAGS += -std=c11
APP_CFLAGS += -I$(SYSDIR)
