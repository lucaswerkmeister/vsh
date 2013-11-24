CC=     gcc
LD=     ld
# "override CFLAGS += ..." appends to any CFLAGS
# that were specified on the command line.
# note: to use sigaction, gnu99 is required instead of c99.
override CFLAGS += -W -Wall -Werror -std=gnu99 -g
TARGET= shell
CODE=   strings.c run.c builtins.c
SRC=    $(TARGET).c $(CODE)
OBJ=    $(SRC:%.c=%.o)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ)

.PHONY: $(TARGET)-solution.o
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
