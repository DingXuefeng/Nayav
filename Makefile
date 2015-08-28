# Makefile for demo
# Author: Ding Xuefeng dingxf@ihep.ac.cn
# History:
#   2013.08.04 ver 1.0

TARGET:= TPoker

HEAD := ./include 
HEADFILES := $(wildcard ${HEAD}/*.h)
SRC := ./src
TEST := ./test
SRCFILES := $(wildcard ${SRC}/*.cc)
SRCFILES += $(wildcard ${SRC}/*.C)
TMP := ./tmp
OBJFILES := $(patsubst ${SRC}/%.cc,${TMP}/%.o,$(patsubst ${SRC}/%.C,${TMP}/%.o,${SRCFILES}))

TESTFILES := $(wildcard ${TEST}/*.cc)
TESTFILES += $(wildcard ${TEST}/*.C)
TESTOBJFILES := $(patsubst ${TEST}/%.cc,${TMP}/%.o,$(patsubst ${SRC}/%.C,${TMP}/%.o,${TESTFILES}))

CC := g++
CPPFLAGS := -I$(HEAD) -Ipublic_interface -pipe -Wall -O2

# for ROOT
#CPPFLAGS += $(shell root-config --cflags)
#LDLIBS += $(shell root-config --glibs --libs) 

# for LegendOfNeutrino
#CPPFLAGS += $(shell LegendOfNeutrino-config --cflags)
#LDLIBS += $(shell LegendOfNeutrino-config --libs)


.PHONY: makeFileTut all clean test

all:$(TARGET)

test:Test

clean:
	-@rm $(TARGET)
	-@rm tmp/*
	-@rm include/*~ include/.*~ include/.*.sw*
	-@rm src/*~ src/.*~ src/.*.sw*
	-@rm *~ .*~ .*.sw*
	-@rm public_interface/*~ public_interface/.*~ public_interface/.*.sw*
	@echo "Cleaning done."

makeFileTut:
	echo ${CPPFLAGS}
	echo ${SRCFILES}
	echo ${OBJFILES}

$(TMP)/%.o : $(SRC)/%.cc $(HEADFILES)
	$(CC) -o $@ -c $< $(CPPFLAGS)

$(TMP)/%.o : $(SRC)/%.C $(HEADFILES)
	$(CC) -o $@ -c $< $(CPPFLAGS)

tmp/main.o : main.cc $(HEADFILES)
	$(CC) -o $@ -c $< $(CPPFLAGS)

$(TARGET) : tmp/main.o $(OBJFILES)
	$(CC) -o $@ $^ $(LDLIBS)

$(TMP)/%.o : $(TEST)/%.cc $(HEADFILES)
	$(CC) -o $@ -c $< $(CPPFLAGS) $(G4CPPFLAGS)

$(TMP)/%.o : $(TEST)/%.C $(HEADFILES)
	$(CC) -o $@ -c $< $(CPPFLAGS) $(G4CPPFLAGS)

Test : $(TESTOBJFILES) $(OBJFILES)
	$(CC) -o $@ $^ $(LDLIBS) $(G4LDLIBS)
