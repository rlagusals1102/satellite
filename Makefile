CC		= gcc
CFLAGS	= -Wall -std=c17 -pedantic
LIBS	= -lm -lhackrf

TARGET	= satellite
SRCS	= main.c rf.c
OBJS	:= $(SRCS:%.c=%.o)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)


all:
	$(TARGET)


clean:
	rm -f $(TARGET) $(OBJS) *~


main.o: main.c main.h
rf.o: rf.c rf.h
