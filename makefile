P2.out : Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P2.out Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project2.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm [SP]*.o P2.out *.gch

submit : Project2.cpp LexicalAnalyzer.h SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf DenimP2
	mkdir DenimP2
	cp Project2.cpp DenimP2
	cp SyntacticalAnalyzer.h DenimP2
	cp SyntacticalAnalyzer.cpp DenimP2
	cp makefile DenimP2
	cp README.txt DenimP2
	tar cfvz DenimP2.tgz DenimP2
	cp DenimP2.tgz ~tiawatts/cs460drop
