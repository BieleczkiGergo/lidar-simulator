CC 			:= gcc
SRCPATH 	:= src
INCPATH 	:= include
TESTPATH 	:= test
BINPATH 	:= bin
CFLAGS		:= -Wall -Wextra -I $(INCPATH) -lmath

SRCFILES_RAW := simulator.c barrier.c

SRCFILES	:= $(patsubst %, $(SRCPATH)/%, $(SRCFILES_RAW))

test_barriers: $(TESTPATH)/test_barriers.c $(SRCFILES)
	$(CC) $(CFLAGS) $(TESTPATH)/test_barriers.c $(SRCFILES) -o $(BINPATH)/test_barriers
	./$(BINPATH)/test_barriers

test: test_barriers