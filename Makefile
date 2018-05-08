CC=				g++
CFLAGS=			-std=c++11 -fPIC -g
TARGETS=		studyND


all: 			studyND


test:			studyND.cpp studyND
	@echo Testing memory and output...
	@./scripts/test_studyND.sh
	

studyND:		studyND.cpp
	@echo Compiling and linking studyND...
	@$(CC) $(CFLAGS) -o studyND $^


clean:
	@echo Cleaning studyND and test-room...
	@rm -f *.o *.a studyND test-room
