CC=			g++
CFLAGS=			-std=c++11 -fPIC -g
TARGETS=		studyND
LD=       		g++
#LIBDIR=			$(shell locate libc.a | rev | cut -d/ -f2- | rev)/
#LDFLAGS=		-L/$(LIBDIR) -L.
LDFLAGS=  		-L/usr/lib/x86_64-redhat-linux5E/lib64 -L.
AR=       		ar
ARFLAGS=  		rcs

all: 			studyND test-room

test:
	@echo Testing memory and output...
	@./test_studyND.sh
	

bad: 			bad-studyND bad-test-room
	#This is the #include-tree method- NEVER USE THIS!!!!!

bad-studyND:		studyND.cpp
	@$(CC) $(CFLAGS) -o studyND $^

bad-test-room:		testRoom.cpp
	@$(CC) $(CFLAGS) -o test-room $^


test-room:		testRoom.o libroom.a
	@echo Linking $@
	@$(LD) $(LDFLAGS) -static -o $@ $^

testRoom.o:		testRoom.cpp
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

studyND:		studyND.o libroom.a
	@echo Linking $@
	@$(LD) $(LDFLAGS) -static -o $@ $^

studyND.o:		studyND.cpp
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

libroom.a:		roomMap.o circular_list.o
	@echo Creating $@...
	@$(AR) $(ARFLAGS) $@ $^

roomMap.o:		roomMap.cpp
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

circular_list.o: 	circular_linked_list.cpp
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -o $@ $^ -c

clean:
	@echo Cleaning studyND...
	@rm -f *.o *.a studyND test-room
