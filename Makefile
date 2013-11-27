CC=     gcc
LD=     ld
# "override CFLAGS += ..." appends to any CFLAGS
# that were specified on the command line.
# note: to use sigaction, gnu99 is required instead of c99.
override CFLAGS += -W -Wall -Werror -std=gnu99 -g -lreadline
TARGET= vsh
CODE=   strings.c run.c builtins.c io.c
SRC=    $(TARGET).c $(CODE)
OBJ=    $(SRC:%.c=%.o)

$(TARGET): $(OBJ)
# note: on Linux Mint 15, the linker can't find the readline library if $(CFLAGS) put in front of $(OBJ).
	$(CC) -o $@ $(OBJ) $(CFLAGS)

expert:
	$(MAKE) $(TARGET) CFLAGS=-DEXPERT

.PHONY: $(TARGET)-solution.o expert
$(TARGET)-sol: $(subst $(TARGET),$(TARGET)-solution,$(OBJ))
	$(CC) -o $@ $^

$(TARGET)-solution.o:
	@test -f $(TARGET)-solution.c \
	|| { echo "Download solution tarball." >&2; false; }
	$(CC) $(CFLAGS) -c $(TARGET)-solution.c

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(TARGET) $(TARGET)-sol *.o
