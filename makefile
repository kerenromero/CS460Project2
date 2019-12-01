P2.out : Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P2.out Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project2.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm [SP]*.o P2.out *.gch *.lst *.p1 *.dbg *.ss.p2 *~

submit : Project2.cpp LexicalAnalyzer.h SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf denimP2
	mkdir denimP2
	cp Project2.cpp denimP2
	cp SyntacticalAnalyzer.h denimP2
	cp SyntacticalAnalyzer.cpp denimP2
	cp makefile denimP2
	cp README.txt denimP2
	tar cfvz denimP2.tgz denimP2
	cp denimP2.tgz ~tiawatts/cs460drop
