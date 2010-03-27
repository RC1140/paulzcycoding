CFLAGS=-O0 -g -Wall -fmessage-length=0 -DDEBUG
CXXFLAGS=$(CFLAGS)

TARGETS=p1050\
		p1159\
		p1207 p1298\
		p1316\
		p1401 p1458\
		p1503 p1517 p1519 p1528 p1565 p1579\
		p1657 p1658 p1663 p1664\
		p1799\
		p1969 p1979\
		p2000 p2013 p2017 p2039\
		p2105 p2136 p2140 p2141 p2195 p2196\
		p2262\
		p2301 p2309 p2350 p2352 p2388 p2390\
		p2509 p2521 p2549 p2551 p2575 p2578 p2583\
		p2636 p2656 p2665\
		p2924\
		p3030 p3062 p3067 p3094\
		p3173 p3176\
		p3325\
		p3650 p3673\
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