OPTIONS = --pedantic-errors --std=c++11 -Iinclude

build/database.o: src/database.cpp include/database.h include/calendar.h
	g++ $(OPTIONS) -c $< -o $@

build/calender.o: src/calender.cpp include/calendar.h
	g++ $(OPTIONS) -c $< -o $@
	
build/debug.o: src/debug.cpp include/calendar.h
	g++ $(OPTIONS) -c $< -o $@
	
debug: build/debug.o build/calender.o build/database.o
	g++ $^ -o build/debug.out
	./build/debug.out
	
clean:
	rm -f build/*.o
	rm -f build/*.out
	
.PHONY: clean