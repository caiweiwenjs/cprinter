TARGET=lp_cups
CC=gcc
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
CFLAGS=`cups-config --cflags` -g
LIBS=`cups-config --libs`


$(TARGET): $(OBJS)
	$(CC) -o $@ $^  $(LIBS)

.PHONY: clean
clean:
	-rm -rf $(OBJS) $(TARGET)
