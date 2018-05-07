CC=			g++
CFLAGS=			-std=c++11 -fPIC -g
TARGETS=		studyND
LD=       		g++
#LIBDIR=			$(shell locate libc.a | rev | cut -d/ -f2- | rev)/
#LDFLAGS=		-L/$(LIBDIR) -L.
LDFLAGS=  		-L/usr/lib/x86_64-redhat-linux5E/lib64 -L.
AR=       		ar
ARFLAGS=  		rcs


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
