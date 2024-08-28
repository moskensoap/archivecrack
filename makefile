cc = gcc
CFLAGS = -Wall -g -O3 -s

target = archivecrack

all: $(target)

$(target): archivecrack.c
	$(cc) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf $(target)
