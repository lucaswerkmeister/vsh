CC=     gcc
LD=     ld
# "override CFLAGS += ..." appends to any CFLAGS
# that were specified on the command line.
override CFLAGS += -W -Wall -Werror -std=c99 -g -lreadline
TARGET= vsh
CODE=   strings.c run.c builtins.c io.c
SRC=    $(TARGET).c $(CODE)
OBJ=    $(SRC:%.c=%.o)

$(TARGET): $(OBJ)
# note: on Linux Mint 15, the linker can't find the readline library if $(CFLAGS) put in front of $(OBJ).
	$(CC) -o $@ $(OBJ) $(CFLAGS)

expert:
	$(MAKE) $(TARGET) CFLAGS=-DEXPERT

.PHONY: expert clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(TARGET) *.o
