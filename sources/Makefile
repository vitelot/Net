LIBGSL = -lgsl -lgslcblas # to be commented out if no GSL are installed
#LIBLAPACK = -llapack -lblas # to be commented out if no LAPACK are installed

CDEFINE = -DGSL #-DLAPACK

SHELL=/bin/tcsh

SYSTEM  = $(shell uname)

BINDIR  = ../bin
OBJDIR  = ../objs
QTDIR1   = ../Qt

OUT     =  $(BINDIR)/Net.$(SYSTEM)
QT	=  $(QTDIR1)/NetIni

ifeq "$(SYSTEM)" "HP-UX"
CC 	= cc -Aa
FC	= f77
LFLAGS	= -lm -lC.ansi -lcl
endif

ifeq "$(SYSTEM)" "Linux"
CC 	= gcc
FC	= gcc #g77
LFLAGS	= -lm $(LIBGSL) $(LIBLAPACK)
endif

ifeq "$(SYSTEM)" "Darwin"
CC      = gcc
FC      = gcc
LFLAGS  = -lm $(LIBGSL) $(LIBLAPACK)
endif

# Remember: -g with -O not allowed 
CFLAGS  = -O -Wno-unused-result
FFLAGS  = -O

CSOURCES = $(wildcard *.c)
SOURCES  = $(CSOURCES)
ALLH     = $(wildcard *.h)

COBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(CSOURCES))

OBJS = $(COBJS)

all: $(OUT) $(QT)

# use $(FC) instead of $(CC) because of lapack anomaly 
$(OUT): $(OBJS)
	$(FC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@;
	etags *.[ch];
	ctags *.[ch];
	./Store

$(OBJS): $(ALLH) Makefile

$(QT): NetIni.pro

# compiling procedures
$(COBJS): $(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CDEFINE) $< -o $@

NetIni.pro:
	( cd $(QTDIR1) && qmake NetIni.pro && $(MAKE) )
	cp -u $(QT) $(BINDIR)/
	./Store

.PHONY: clean

clean:
	rm $(OBJS) $(OUT)
