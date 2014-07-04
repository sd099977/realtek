##############################################
# Tool Chain
##############################################
CC   = gcc 
CXX  = g++
AR   = ar 
RM   = rm -vf
MAKEFLAGS = --no-print-directory	
# for GDB debug
#CFLAGS = $(DEBUGFLAG)
#SHOW_COMMAND ?=@
##############################################

MYPROG  = r2modm
MYLIB   = 

##############################################
# Environment
##############################################
SUBDIRS    = 
VPATH      = 
#CFLAGS    += -Wall -g
CFLAGS    += $(INC_DEF)
OBJS      += main.o

LIBS      += -lssl -lcrypto 
LDFLAGS   += -L /usr/local/ssl/lib $(LIBS) 



##############################################
# Make
##############################################
all : clean $(MYPROG)			
	
$(MYPROG) : $(OBJS)
	$(SHOW_COMMAND)$(CXX) -static $(OBJS) $(MYLIB) $(LDFLAGS) -o $(MYPROG) 		
	
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@
	
clean:	
	@$(RM)  $(MYPROG) *~ *.bak *.o			
	
