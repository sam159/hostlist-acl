#ifndef LIST_H
#define LIST_H

#include "uthash.h"

#define DEFAULT_LISTFILE "/etc/blocklist.txt"

typedef struct entry entry;

struct entry {
	unsigned long hash;
	char* str;
	UT_hash_handle hh;
};

int main(int argc, char* argv[]);
unsigned long hashstr(char *str);
void add_entry(char* str);
unsigned char find_entry(char* str);

#endif
