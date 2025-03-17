BIN := neander
OBJS := neander.o instructions.o
CCFLAGS := -Wall -Wextra

all: main.c $(OBJS)
	gcc $(CCFLAGS) -o $(BIN) main.c $(OBJS)

clean:
	rm $(BIN) $(OBJS) -f

%.o: %.c
	gcc $(CCFLAGS) -c $^
