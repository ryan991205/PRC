CFLAGS=-Wall -Werror -Wextra -pedantic -O0 -ggdb -fopenmp -std=c++98 -Icode
LDDFLAGS=-lmyhash -lmyfilestructure -lpthread

MAIN_SOURCES=$(wildcard code/*.cpp)
MAIN_LIBS=-Llib

TEST_LIBS=-lgtest -lgtest_main -lpthread

CC=g++

.phony: all clean install submit

sort: $(MAIN_OBJECTS) Makefile code/FileStructure.h
	@$(CC) $(CFLAGS) $(MAIN_LIBS) $(MAIN_SOURCES) -o $@ $(LDDFLAGS)
	
all: sort

clean:
	@rm -rf sort code/*.o test/*.o *.bin

install:
	@chmod 750 lib/install.sh
	@lib/install.sh lib/

submit:
	@chmod 750 submit.sh
	@./submit.sh
