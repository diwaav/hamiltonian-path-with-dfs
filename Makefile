CC = clang
CFLAGS = -Werror -Wall -Wextra -Wpedantic
TARGET = tsp
LFLAGS = -lm

OBJECTS = tsp.o graph.o stack.o path.o 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) -f $(TARGET) *.o

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make
