OPTIONS = --pedantic-errors --std=c++11 -Iinclude

build/date.o: src/date.cpp include/date.h
	g++ $(OPTIONS) -c $< -o $@
	
build/debug.o: src/debug.cpp include/date.h
	g++ $(OPTIONS) -c $< -o $@
	
debug: build/debug.o build/date.o
	g++ $(OPTIONS) $^ -o build/debug.out
	./build/debug.out
	
clean:
	rm -f build/*.o
	rm -f build/*.out
	
.PHONY: clean