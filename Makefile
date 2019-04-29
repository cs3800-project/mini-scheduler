main: main.cpp
	g++ -std=c++11 main.cpp scheduler.cpp sys.cpp \
	    -o scheduler

.PHONY: clean
clean:
	rm scheduler
