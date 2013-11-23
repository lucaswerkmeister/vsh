CC=     gcc
LD=     ld
CFLAGS= -W -Wall -Werror -std=c99 -g
TARGET= shell
CODE=   strings.c run.c
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
