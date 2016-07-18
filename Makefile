CC = gcc
CFLAGS = -g -Wall
CHMOD := $(shell which chmod)
SETCAP := $(shell which setcap)
USER := $(shell whoami)

all: daemon

daemon: main.o json.o mysql.o login.o connection.o curl.o time.o
	$(CC) $(CFLAGS) $^ -lssh -lutil -ljansson -lcurl -lmysqlclient -L/usr/lib64/mysql/ -lz -o $@

main.o: main.c config.h struct.h
	$(CC) $(CFLAGS) -I /usr/include/mysql -c main.c

json.o: json.c config.h struct.h
		$(CC) $(CFLAGS)  -I /usr/include/mysql -c json.c

login.o: login.c config.h struct.h
		$(CC) $(CFLAGS)  -I /usr/include/mysql -c login.c

connection.o: connection.c config.h struct.h
		$(CC) $(CFLAGS)  -I /usr/include/mysql -c connection.c

mysql.o: mysql.c config.h struct.h
		$(CC) $(CFLAGS)  -I /usr/include/mysql -c mysql.c

curl.o: curl.c config.h struct.h
		$(CC) $(CFLAGS)  -I /usr/include/mysql -c curl.c

time.o: time.c config.h struct.h
			$(CC) $(CFLAGS) -I /usr/include/mysql -c time.c

clean:
	\/bin/rm -f *.o
