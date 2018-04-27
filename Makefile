CC=				g++
CFLAGS=			-std=c++11
TARGETS=		studyND

all: 			studyND

studyND:		studyND.o roomMap.o circular_linked_list.p
	@$(CC) $^ -o $@


%.o:			%.cpp
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c $^ -o $@
	
clean:
	rm *.o studyND
