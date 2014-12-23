# $Id: Makefile,v 1.2 2013-03-22 01:32:57 ist173701 Exp $
#---------------------------------------------------------------
#             CONFIGURE THESE VARIABLES IF NEEDED
#---------------------------------------------------------------

ROOT =
CDK_INC_DIR = $(ROOT)/usr/include
CDK_LIB_DIR = $(ROOT)/usr/lib64

L_NAME=MFScanner
Y_NAME=MFParser

#---------------------------------------------------------------
#    PROBABLY, NO NEED TO CHANGE ANYTHING BEYOND THIS POINT
#---------------------------------------------------------------

LFLAGS   = 
YFLAGS   = -dtv
CXXFLAGS = -std=c++11 -DYYDEBUG=1 -Wall -O3 -ggdb -Isemantics -I. -I$(CDK_INC_DIR) -I$(CDK_INC_DIR)/cdk
LDFLAGS  = -L$(CDK_LIB_DIR) -lcdk
COMPILER = mayfly

SRC_CPP = $(wildcard nodes/**/*.cpp) $(wildcard semantics/*.cpp) $(wildcard ./*.cpp)
OFILES  = $(SRC_CPP:%.cpp=%.o)

#---------------------------------------------------------------
#                DO NOT CHANGE AFTER THIS LINE
#---------------------------------------------------------------

all: nodes/all.h $(COMPILER)

%.tab.o:: %.tab.c
	$(CXX) $(CXXFLAGS) -DYYDEBUG -c $< -o $@

%.o:: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o:: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.tab.c:: %.y
	 byacc -dtv -b $* $<

%.tab.h:: %.y
	 byacc -dtv -b $* $<

$(L_NAME).cpp: $(L_NAME).l
	flex $(LFLAGS) $<

$(Y_NAME).tab.c: $(Y_NAME).y
$(Y_NAME).tab.h: $(Y_NAME).y

# this is needed to force byacc to run
$(L_NAME).o: $(L_NAME).cpp $(Y_NAME).tab.h

.PHONY: ./mknodedecls.pl
nodes/all.h: ./mknodedecls.pl
	./mknodedecls.pl > nodes/all.h

$(COMPILER): $(L_NAME).o $(Y_NAME).tab.o $(OFILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) *.tab.[ch] *.o $(OFILES) $(L_NAME).cpp $(Y_NAME).output $(COMPILER)

depend: nodes/all.h
	$(CXX) $(CXXFLAGS) -MM $(SRC_CPP) > .makedeps

-include .makedeps

#---------------------------------------------------------------
#                           THE END
#---------------------------------------------------------------
# $Log: Makefile,v $
# Revision 1.2  2013-03-22 01:32:57  ist173701
# *** empty log message ***
#
# Revision 1.1  2013-02-16 16:10:15  ist13500
# This is a base mayfly version.
# This is just Compact with the names changed.
#
# 
#
