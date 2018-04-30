CC=			g++
CFLAGS=			-std=c++11 -fPIC -g
TARGETS=		studyND
LD=       		g++
LDFLAGS=  		-L/usr/lib/x86_64-redhat-linux5E/lib64/ -L./
AR=       		ar
ARFLAGS=  		rcs

all: 			studyND test-room

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
	rm *.o *.a studyND
