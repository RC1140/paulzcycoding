CFLAGS=-O0 -g -Wall -fmessage-length=0 -DDEBUG
CXXFLAGS=$(CFLAGS)

TARGETS=p1050\
		p1159\
		p1207 p1298\
		p1316\
		p1401 p1458\
		p1503 p1517 p1519 p1565\
		p1657 p1658 p1664\
		p2000 p2013 p2017\
		p2105 p2136 p2140 p2195\
		p2262\
		p2301 p2350 p2352 p2388 p2390\
		p2509 p2521 p2549\
		p2636 p2656 p2665\
		p3030 p3062 p3067 p3094\
		p3673\
		p3740 

all: $(TARGETS:=.exe)

%.exe: ../src/%/main.cpp
#	cmd /c IF NOT EXIST $* mkdir $*
	$(CXX) $(CXXFLAGS) -o $@ $?

%.exe: ../src/%/main.c
#	cmd /c IF NOT EXIST $* mkdir $*
	$(CC) $(CFLAGS) -o $@ $?

clean:
	-del *.exe