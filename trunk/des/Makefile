logic:	logic.cpp algorithm.h logicpolynomial/logic.h sboxfunction.h
	g++ -o logic logic.cpp

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
	
tovtest:	tovtest.cpp algorithm.h sboxfunction.h
	g++ -o tovtest tovtest.cpp

vttest:	vttest.cpp algorithm.h sboxfunction.h
	g++ -o vttest vttest.cpp

.PHONY: clean
clean:
	rm -f des sboxgent sboxres sboxmat sboxinvmat matmulti sboxfun sr sboxfunction.h tovtest vttest logic
