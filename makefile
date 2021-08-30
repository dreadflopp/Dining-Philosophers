#   File:	makefile
#   Builds:	Lab7
#   Date:	jan 2019
						
CCX = g++

CCFLAGS		=   -ansi -pedantic -std=c++11
#LDFLAGS		=
LDFLAGS	=  -pthread

PROGS		= lab7
OBJS		= main.o Philosopher.o Table.o
HDRS		= Philosopher.h Table.h

.cc.o:
	@echo "Compiling " $<
	$(CCX) -c $(CCFLAGS) $<
	@echo $@ "done"

all:	$(PROGS)


lab7:	$(OBJS) 
	@echo "Linking " $@
	$(CCX)  -o $@ $(OBJS) $(LDFLAGS)
	@echo $@ "done"

clean:
	$(RM) $(PROGS) $(OBJS) core *~
