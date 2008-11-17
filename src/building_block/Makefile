INCLUDES=-I../common -I../code_generator
#COMMON_OBJECTS=../common/log.o ../common/set.o ../common/sn_memory.o
COMMON_OBJECTS=../common/*.o ../code_generator/code_chunk.o
COMPILE_FLAGS=-Werror -Wall -ansi -pedantic -ggdb
LINK_FLAGS=-ggdb

all: block_parameter_set.o block_pin_set.o block_parameter.o block_pin.o building_block.o 

block_parameter_set.o: block_parameter_set.c block_parameter_set.h 
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c block_parameter_set.c

block_pin_set.o: block_pin_set.c block_pin_set.h
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c block_pin_set.c
	
block_pin.o: block_pin.c block_pin.h
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c block_pin.c

block_parameter.o: block_parameter.c block_parameter.h
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c block_parameter.c

building_block.o: building_block.h building_block.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c building_block.c

tests: all test_block_pin test_block_pin_set test_building_block test_block_parameter
	valgrind ./test_block_pin
	valgrind ./test_block_pin_set
	valgrind ./test_building_block	
	valgrind ./test_block_parameter	

test_block_pin: test_block_pin.o 
	gcc $(LINK_FLAGS) -o test_block_pin test_block_pin.o block_pin.o $(COMMON_OBJECTS)

test_block_pin_set: test_block_pin_set.o 
	gcc $(LINK_FLAGS) -o test_block_pin_set test_block_pin_set.o block_pin_set.o block_pin.o $(COMMON_OBJECTS)

test_block_parameter: test_block_parameter.o 
	gcc $(LINK_FLAGS) -o test_block_parameter test_block_parameter.o block_parameter.o $(COMMON_OBJECTS)

test_building_block: test_building_block.o 
	gcc $(LINK_FLAGS) -o test_building_block test_building_block.o block_pin_set.o block_pin.o block_parameter_set.o block_parameter.o building_block.o $(COMMON_OBJECTS)

test_block_pin.o: test_block_pin.c 
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c test_block_pin.c

test_block_pin_set.o: test_block_pin_set.c 
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c test_block_pin_set.c

test_building_block.o: test_building_block.c 
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c test_building_block.c

test_block_parameter.o: test_block_parameter.c block_parameter.c block_parameter.h
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c test_block_parameter.c

clean:
	rm -f *.o
	rm -f test_block_pin
	rm -f test_block_pin_set
	rm -f test_building_block
	rm -f test_block_parameter
