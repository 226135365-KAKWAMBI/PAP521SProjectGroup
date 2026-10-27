CC     = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
SRC    = main.c employees.c budget.c suppliers.c assets.c reports.c utils.c

mfms: $(SRC)
	$(CC) $(CFLAGS) -o mfms $(SRC)

clean:
	rm -f mfms mfms.exe
