#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "uthash.h"

entry *hashtable = NULL;

int main(int argc, char* argv[]) {

	char * listfile = DEFAULT_LISTFILE;
	
	if (argc > 1) {
		listfile = argv[1];
	}
	
	FILE* fh = fopen(listfile, "r");
	if (fh == NULL) {
		perror("Error opening list");
		return EXIT_FAILURE;
	}
	
	char buffer[1024];
	while (fgets(buffer, sizeof buffer, fh) != NULL) {
		char *pos;
		if ((pos=strchr(buffer, '\n')) != NULL)
			*pos = '\0';
		add_entry(buffer);
	}
	if (!feof(fh)) {
		perror("Error reading file");
		fclose(fh);
		return EXIT_FAILURE;
	}
	
	fclose(fh);
	
	memset(buffer, 0, sizeof(buffer));
	
	while(scanf("%1023s", buffer) > 0) {
	
		char* input = calloc(strlen(buffer)+1, sizeof(char));
		strcpy(input, buffer);
		
		if (find_entry(input) == 1) {
			printf("OK\n");
		} else {
			printf("ERR\n");
		}
		fflush(stdout);

		free(input);
		memset(buffer, 0, sizeof(buffer));
	}
	
	return EXIT_SUCCESS;
}

unsigned long hashstr(char *str) {
	unsigned long hash = 5381;
	int c;

	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
}

void add_entry(char* str) {
	entry *e;
	e = calloc(1, sizeof(entry));
	e->hash = hashstr(str);
	e->str = calloc(strlen(str)+1, sizeof(char));
	strcpy(e->str, str);
	
	HASH_ADD_INT(hashtable, hash, e);
}
unsigned char find_entry(char* str) {
	unsigned long hash = hashstr(str);
	
	entry *e = NULL;
	HASH_FIND_INT(hashtable, &hash, e);
	
	if (e == NULL) {
		return 0;
	} else {
		if (strcmp(str, e->str) == 0) {
			return 1;
		} else {
			return 0;
		}
	}
}