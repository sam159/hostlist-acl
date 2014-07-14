CC=gcc
#OPTS=-ggdb
OPTS=-O2
CFLAGS=${OPTS} -Wall -isystem ./lib

all: list

list: list.c list.h
	$(CC) $(CFLAGS) list.c -o list

install: all
	install -T list /usr/lib/squid3/hostlist_acl
	install -m=0644 -T blocklist.txt /etc/blocklist.txt

update:
	rm -f hosts.txt
	wget http://winhelp2002.mvps.org/hosts.txt
	sed 's/\r$$//' hosts.txt | grep -v ^# | cut -d " " -f 2 | sed '/^$$/d' | sort -d > blocklist.txt
	install -m=0644 -T blocklist.txt /etc/blocklist.txt

clean:
	rm -f list
