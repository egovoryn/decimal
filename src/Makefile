CC = gcc
GCOV=-coverage
REPORTDIR = gcovdir
FILE_LIB = decimal
FILE = decimal_test
OS = $(shell uname)
ifeq ($(OS), Darwin)
  CHECKFLAGS=-lcheck
else
  CHECKFLAGS=-lcheck -lpthread -lrt -lm -lsubunit
endif

all: clean $(FILE_LIB).a

$(FILE_LIB).a: $(FILE_LIB).c
	$(CC) -c $(FILE_LIB).c -o $(FILE_LIB).o 
	ar rcs $(FILE_LIB).a $(FILE_LIB).o

test: clean $(FILE_LIB).a
	$(CC) -c $(FILE).c -o $(FILE).o 
	$(CC) $(FILE).o $(FILE_LIB).o $(CHECKFLAGS) -o $(FILE)

	./$(FILE)

gcov_report: $(FILE_LIB).a
	$(CC) $(GCOV) -c decimal.c 
	$(CC) -c decimal_test.c $(CHECKFLAGS)
	$(CC) $(GCOV) -o decimal_test decimal_test.o decimal.o $(CHECKFLAGS)
	./decimal_test

	lcov -t "Unit-tests of $(FILE_LIB)" -o $(FILE_LIB).info -c -d .
	genhtml -o $(REPORTDIR) $(FILE_LIB).info

clean:
	rm -rf *.o *.a *.out *.gcno *.gcda *.gcov *.info $(REPORTDIR) $(FILE) $(FILE_LIB)

leaks: test
ifeq ($(UNAME), Linux)
	CK_FORK=no valgrind --tool=memcheck --leak-check=full ./decimal_test
else
	CK_FORK=no leaks --atExit -- ./decimal_test
endif

check:
	cppcheck *.c *.h
