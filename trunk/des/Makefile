logic:	logic.cpp algorithm.h logic.h sboxfunction.h
	g++ -o logic logic.cpp -O3

des:	des.cpp algorithm.h sboxfunction.h logic.h
	g++ -o des des.cpp

sboxmat:	sboxgent
	./sboxgent > sboxmat

sboxinvmat:	sboxmat invsbox.m
	matlab -nojvm -r invsbox 

sboxres:	sboxdata.h sboxres.cpp
	g++ -o sboxres sboxres.cpp

sr:	sboxres sboxinvmat matmulti
	./sboxres | ./matmulti > sr

sboxfunction.h:	sr sboxfun
	./sboxfun > sboxfunction.h < sr
	
.PHONY: clean
clean:
	rm -f des sboxgent sboxres sboxmat sboxinvmat matmulti sboxfun sr testlogic sboxfunction.h tovtest vttest logic

testlogic:	logic.h testlogic.cpp
	g++ -o testlogic testlogic.cpp

tovtest:	tovtest.cpp algorithm.h sboxfunction.h
	g++ -o tovtest tovtest.cpp

vttest:	vttest.cpp algorithm.h sboxfunction.h
	g++ -o vttest vttest.cpp
