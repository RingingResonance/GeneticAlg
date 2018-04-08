GA: gt.o rg.o
	g++ -std=c++11 -pthread -o GT GeneticTest.o rget.o ../GeneticAlg/gga.o

gt.o: GeneticTest.cpp ../GeneticAlg/gga.h GeneticTest.h
	g++ -std=c++11 -pthread -c GeneticTest.cpp

rg.o: rget.cpp ../GeneticAlg/gga.h
	g++ -std=c++11 -pthread -c rget.cpp

clean:
	rm *.o
