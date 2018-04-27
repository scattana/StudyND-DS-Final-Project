CC=				g++
CFLAGS=			-std=c++11
TARGETS=		studyND

all: 			studyND

studyND:		studyND.cpp
	@echo Compiling $@...
	@$(CC) $(CFLAGS) $^ -o $@


roomMap.o:			roomMap.cpp
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c $^ -o $@
	
circular_linked_list.o:		circular_linked_list.cpp
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm *.o studyND
