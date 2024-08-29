cc = gcc
CFLAGS = -Wall -g -O3 -s

target = archivecrack

all: $(target)

$(target): archivecrack.c
	$(cc) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf $(target)

.PHONY: windows
windows: archivecrack-windows.c
	/ucrt64/bin/gcc -Wall -g -O3 -s -o archivecrack-windows.exe archivecrack-windows.c