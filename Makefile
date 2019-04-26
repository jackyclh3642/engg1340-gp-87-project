OPTIONS = --pedantic-errors --std=c++11 -Iinclude

build/database.o: src/database.cpp include/database.h include/date.h include/variables.h
	g++ $(OPTIONS) -c $< -o $@

build/date.o: src/date.cpp include/date.h
	g++ $(OPTIONS) -c $< -o $@
	
build/main.o: src/main.cpp include/date.h
	g++ $(OPTIONS) -c $< -o $@
	
build/variables.o: src/variables.cpp include/variables.h
	g++ $(OPTIONS) -c $< -o $@
	
build: build/main.o build/date.o build/database.o build/variables.o
	g++ $(OPTIONS) $^ -o bin/engg1340-gp87-q4
	
clean:
	rm -f build/*.o
	rm -f build/*.out
	rm -f bin/engg1340-gp87-q4
	
.PHONY: clean