CC=				g++
CFLAGS=			-std=c++11
TARGETS=		studyND



studyND:		studyND.cpp
	@echo Compiling studyND program...
	@$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm studyND
