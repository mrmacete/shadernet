INCLUDES=-I../common -I../building_block -I./
#COMMON_OBJECTS=../common/log.o ../common/set.o ../common/sn_memory.o
COMMON_OBJECTS=../common/*.o ../building_block/block*.o ../building_block/building_block.o
COMPILE_FLAGS=-Werror -Wall -ansi -pedantic -ggdb
LINK_FLAGS=-ggdb

all: code_chunk.o parsed_couple.o parsing_bookmark.o bookmark_set.o parsed_building_block.o block_net.o

code_chunk.o: code_chunk.h code_chunk.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c code_chunk.c

parsed_couple.o: parsed_couple.h parsed_couple.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c parsed_couple.c

parsed_building_block.o: parsed_building_block.h parsed_building_block.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c parsed_building_block.c

parsing_bookmark.o: parsing_bookmark.h parsing_bookmark.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c parsing_bookmark.c

bookmark_set.o: bookmark_set.h bookmark_set.c parsing_bookmark.h
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c bookmark_set.c

block_net.o: block_net.h block_net.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c block_net.c

tests: all test_code_chunk test_parsed_couple test_bookmark_set test_parsed_building_block test_block_net
	valgrind ./test_code_chunk
	valgrind ./test_parsed_couple
	valgrind ./test_bookmark_set
	valgrind ./test_parsed_building_block
	valgrind ./test_block_net

test_code_chunk: test_code_chunk.o 
	gcc $(LINK_FLAGS) -o test_code_chunk test_code_chunk.o code_chunk.o $(COMMON_OBJECTS)

test_code_chunk.o: test_code_chunk.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c test_code_chunk.c

test_parsed_couple: test_parsed_couple.o 
	gcc $(LINK_FLAGS) -o test_parsed_couple test_parsed_couple.o parsed_couple.o code_chunk.o $(COMMON_OBJECTS)

test_parsed_couple.o: test_parsed_couple.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c test_parsed_couple.c

test_bookmark_set: test_bookmark_set.o 
	gcc $(LINK_FLAGS) -o test_bookmark_set test_bookmark_set.o bookmark_set.o parsing_bookmark.o parsed_couple.o code_chunk.o $(COMMON_OBJECTS)

test_bookmark_set.o: test_bookmark_set.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c test_bookmark_set.c

test_parsed_building_block: test_parsed_building_block.o 
	gcc $(LINK_FLAGS) -o test_parsed_building_block test_parsed_building_block.o bookmark_set.o parsed_building_block.o parsing_bookmark.o parsed_couple.o code_chunk.o $(COMMON_OBJECTS)

test_block_net: test_block_net.o 
	gcc $(LINK_FLAGS) -o test_block_net test_block_net.o block_net.o bookmark_set.o parsed_building_block.o parsing_bookmark.o parsed_couple.o code_chunk.o $(COMMON_OBJECTS)

test_parsed_building_block.o: test_parsed_building_block.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c test_parsed_building_block.c

test_block_net.o: test_block_net.c
	gcc $(COMPILE_FLAGS) $(INCLUDES) -c test_block_net.c

clean:
	rm -f *.o
	rm -f test_code_chunk
	rm -f test_parsed_couple
	rm -f test_bookmark_set
	rm -f test_parsed_building_block
	rm -f test_block_net
