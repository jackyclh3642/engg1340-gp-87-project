OPTIONS = --pedantic-errors --std=c++11 -Iinclude

build/calender.o: src/calender.cpp include/calender.h
	g++ $(OPTIONS) -c $< -o $@
	
build/debug.o: src/debug.cpp include/calender.h
	g++ $(OPTIONS) -c $< -o $@
	
debug: build/debug.o build/calender.o
	g++ $^ -o build/debug.out