#ifndef MYMALLOC_H
#define MYMALLOC_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)
#define memSize 4096

void * mymalloc(int, char *, int);
void myfree(void *, char *, int);

static char myblock[memSize];

typedef struct _metadata metadata;
struct _metadata {
	unsigned short magicnum;
	char inuse;
	unsigned short size;
	metadata * prev;
};

#endif
