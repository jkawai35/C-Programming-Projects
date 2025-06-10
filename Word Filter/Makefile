EXECBIN = banhammer
CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic $(OPTFLAG)

OPTFLAG = -O2

.PHONY: all clean spotless format

SOURCES = banhammer.c bv.c bf.c node.c ll.c ht.c city.c parser.c

OBJECTS = $(SOURCES:%.c=%.o)

$(EXECBIN): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBFLAGS)

all: $(EXECBIN)

clean:
	rm -f $(EXECBIN) $(OBJECTS)

spotless:
	rm -f banhammer

format:
	clang-format -i -style=file *.[c]
