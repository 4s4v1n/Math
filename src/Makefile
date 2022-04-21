CC=gcc
CFLAGS=-c -Wall -Wextra -Werror
LDFLAGS=-L. -lcheck -lpthread -lrt -lsubunit -lm
HEADERS=my_math.h
SOURCES=my_math.c
TFILE=test.c
LIB=my_math.a

all: $(LIB)

$(LIB): $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	rm -rf $(OBJECTS)

$(OBJECTS): $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

clean:
	rm -rf *.o *.a
