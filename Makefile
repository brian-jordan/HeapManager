# You can compile with either gcc or g++
# CC = g++
CC = gcc
CFLAGS = -g -I. -Wall -lm -DNDEBUG
# disable the -DNDEBUG flag for the printing the freelist
OPTFLAG = -O2

all: dmm.o test_basic test_coalesce test_dmalloc test_general test_stress

dmm.o: dmm.c
	$(CC) $(CFLAGS) -c dmm.c 
test_basic: test_basic.c dmm.o
	$(CC) $(CFLAGS) -o test_basic test_basic.c dmm.o
test_coalesce: test_coalesce.c dmm.o
	$(CC) $(CFLAGS) -o test_coalesce test_coalesce.c dmm.o
test_dmalloc: test_dmalloc.c dmm.o
	$(CC) $(CFLAGS) -o test_dmalloc test_dmalloc.c dmm.o
test_general: test_general.c dmm.o
	$(CC) $(CFLAGS) -o test_general test_general.c dmm.o
test_stress: test_stress.c dmm.o
	$(CC) $(CFLAGS) -o test_stress test_stress.c dmm.o
clean:
	rm -f *.o test_basic test_coalesce test_dmalloc test_general test_stress
	rm -rf *.dSYM

