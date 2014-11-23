CC=gcc
CFLAGS=-W -Wall -Wextra -Ofast -fstack-protector-all
DFLAGS=-D_FORTIFY_SOURCE=1
LDFLAGS=-Wl,-z,relro,-z,now -lcurl -lsqlite3

urlminer: urlminer.c 
	$(CC) $(CFLAGS) $(DFLAGS) -c *.c
	$(CC) -o urlminer *.o $(LDFLAGS)

clean:
	rm -f *.o urlminer
