CC 			:= gcc
SRCPATH 	:= src
INCPATH 	:= include
TESTPATH 	:= test
BINPATH 	:= bin
CFLAGS		:= -Wall -Wextra -I $(INCPATH)
LDFLAGS		:= -lm

SRCFILES_RAW := simulator.c barrier.c reader.c

SRCFILES	:= $(patsubst %, $(SRCPATH)/%, $(SRCFILES_RAW))

TESTSRC := $(TESTPATH)/assets.c

test_barriers: $(TESTPATH)/test_barriers.c $(SRCFILES) $(TESTSRC)
	$(CC) $(CFLAGS) $(TESTPATH)/test_barriers.c $(TESTSRC) $(SRCFILES) -o $(BINPATH)/test_barriers $(LDFLAGS)
	./$(BINPATH)/test_barriers

test_scan: $(TESTPATH)/test_scan.c $(SRCFILES) $(TESTSRC)
	$(CC) $(CFLAGS) $(TESTPATH)/test_scan.c $(TESTSRC) $(SRCFILES) -o $(BINPATH)/test_scan $(LDFLAGS)
	./$(BINPATH)/test_scan

test_reading: $(TESTPATH)/test_reading.c $(SRCFILES) $(TESTSRC)
	$(CC) $(CFLAGS) $(TESTPATH)/test_reading.c $(TESTSRC) $(SRCFILES) -o $(BINPATH)/test_reading $(LDFLAGS)
	./$(BINPATH)/test_reading

test: test_barriers test_reading test_scan


test_mock_scan: $(TESTPATH)/test_mock_scan.c $(SRCFILES) $(TESTSRC)
	$(CC) $(CFLAGS) $(TESTPATH)/test_mock_scan.c $(TESTSRC) $(SRCFILES) -o $(BINPATH)/test_mock_scan $(LDFLAGS)
	./$(BINPATH)/test_mock_scan

debug_mock_scan:$(TESTPATH)/test_mock_scan.c $(SRCFILES) $(TESTSRC)
	$(CC) $(CFLAGS) -g $(TESTPATH)/test_mock_scan.c $(TESTSRC) $(SRCFILES) -o $(BINPATH)/test_mock_scan $(LDFLAGS)
	gdb ./$(BINPATH)/test_mock_scan


debug_reading:$(TESTPATH)/test_reading.c $(SRCFILES) $(TESTSRC)
	$(CC) $(CFLAGS) -g $(TESTPATH)/test_reading.c $(TESTSRC) $(SRCFILES) -o $(BINPATH)/test_reading $(LDFLAGS)
	gdb ./$(BINPATH)/test_reading


test_mock_move: $(TESTPATH)/test_mock_move.c $(SRCFILES) $(TESTSRC)
	$(CC) $(CFLAGS) -g $(TESTPATH)/test_mock_move.c $(TESTSRC) $(SRCFILES) -o $(BINPATH)/test_mock_move $(LDFLAGS)
	./$(BINPATH)/test_mock_move

debug_mock_move: $(TESTPATH)/test_mock_move.c $(SRCFILES) $(TESTSRC)
	$(CC) $(CFLAGS) -g $(TESTPATH)/test_mock_move.c $(TESTSRC) $(SRCFILES) -o $(BINPATH)/test_mock_move $(LDFLAGS)
	gdb ./$(BINPATH)/test_mock_move