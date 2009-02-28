COMPILE_FLAGS=-Wall -Werror -ansi -pedantic -ggdb
OBJECTS=testing.o

all: set.o log.o sn_memory.o testing.o sn_math.o glsl_types.o sn_hash.o sn_string.o

set.o: set.c set.h
	gcc $(COMPILE_FLAGS) -c set.c

sn_hash.o: sn_hash.c sn_hash.h set.h set.c
	gcc $(COMPILE_FLAGS) -c sn_hash.c

log.o: log.c log.h
	gcc $(COMPILE_FLAGS) -c log.c

sn_memory.o: sn_memory.c sn_memory.h
	gcc $(COMPILE_FLAGS) -c sn_memory.c

sn_math.o: sn_math.c sn_math.h
	gcc $(COMPILE_FLAGS) -c sn_math.c

sn_string.o: sn_string.c sn_string.h
	gcc $(COMPILE_FLAGS) -c sn_string.c

testing.o: testing.c testing.h
	gcc $(COMPILE_FLAGS) -c testing.c

glsl_types.o: glsl_types.c glsl_types.h
	gcc $(COMPILE_FLAGS) -c glsl_types.c

tests: test_sn_math test_set test_hash all
	valgrind ./test_sn_math
	valgrind ./test_set
	valgrind ./test_string
	valgrind ./test_hash

test_set: test_set.c set.o testing.o sn_memory.o log.o
	gcc -ggdb -o test_set test_set.c testing.o set.o sn_memory.o log.o

test_hash: test_hash.c sn_hash.o set.o testing.o sn_memory.o log.o
	gcc -ggdb -o test_hash test_hash.c testing.o set.o sn_memory.o log.o sn_hash.o sn_string.o

test_string: test_string.c sn_string.o testing.o sn_memory.o log.o
	gcc -ggdb -o test_string test_string.c testing.o sn_memory.o log.o sn_string.o

test_sn_math: test_sn_math.c sn_math.o testing.o sn_memory.o
	gcc -o test_sn_math test_sn_math.c testing.o sn_math.o sn_memory.o
clean:
	rm -f *.o
	rm -f test_set
	rm -f test_hash
	rm -f test_sn_math
