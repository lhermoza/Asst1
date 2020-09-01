#include "mymalloc.h"

void printBlocks();

void * mymalloc(int size, char * file, int line) {
	// catching invalid number for malloc
	if (size<1) {
		printf("error at %s %d: request for <1 byte to be allocated\n", file, line);
		return NULL;
	}
	int memLeft = 4096;
	unsigned short magic = 45331;
	// checking memory size
	if (size>(memSize-sizeof(metadata))) {
		printf("error at %s %d: request larger than memory size\n", file, line);
		return NULL;
	}
	//checking for magic number
	metadata * magicCheck = (metadata *) &myblock[0];
	if (magicCheck->magicnum != magic) {
		metadata * newdata = (metadata *) &myblock[0];
		newdata->magicnum = 45331;
		newdata->inuse = 0;
		newdata->size = memLeft-sizeof(metadata);
		newdata->prev = NULL;
	}
	// finding block to allocate using first fit algorithm
	metadata * currnode = (metadata *) &myblock[memSize-memLeft];
	while (memLeft > 0) {
		//printf("%hu %hu\n", currnode->inuse, currnode->size);
		if (currnode->inuse == 0 && currnode->size >= size) {
			//printf("success!\n");
			//printf("%d\n", sizeof(metadata));
			currnode->inuse = 1;
			//printf("%hu\n", currnode->size);
			memLeft = memLeft-sizeof(metadata)-size;
			if (memLeft >= sizeof(metadata)+1) {
				metadata * fragmentptr = (metadata*) &myblock[memSize-memLeft];
				fragmentptr->magicnum = 45331;
				fragmentptr->size = memLeft-sizeof(metadata);
				fragmentptr->inuse = 0;
				fragmentptr->prev = currnode;
				currnode->size = size;
				//printf("%hu %hu\n", currnode->size, fragmentptr->size);
			}
			return ++currnode;
		}
		memLeft = memLeft-sizeof(metadata)-currnode->size;
		if (memLeft > 0) {
			currnode = (metadata *) &myblock[memSize-memLeft];
		}
	}
	printf("error at %s %d: insufficient space for allocation\n", file, line);
	return NULL;
};

void printBlocks() {
	metadata * currNode = (metadata *) &myblock[0];
	int memLeft = 4096;
	while (memLeft > 0) {
		printf("%hu %hu\t", currNode->size, currNode->inuse);
		memLeft = memLeft-sizeof(metadata)-currNode->size;
		if (memLeft > 0) {
			currNode = (metadata *) &myblock[memSize-memLeft];
		}
	}
	printf("\n");
};

void myfree(void * freeptr, char * file, int line) {
	if ((char *) freeptr > &myblock[0] && (char *) freeptr < &myblock[4095]) {
		metadata * freeBlock = (metadata *) freeptr;
		--freeBlock;
		int bs = freeBlock->size;
		if (freeBlock->inuse == 0) {
			printf("error at %s %d: address already freed\n", file, line);
			return;
		}
		if (freeBlock->magicnum != 45331) {
			printf("error at %s %d: invalid address\n", file, line);
			return;
		}
		freeBlock->inuse = 0;
		
		++freeBlock;
		char * nextBlock = (char *) freeBlock;
		nextBlock = nextBlock+bs;
		--freeBlock;

		metadata * temp = NULL;
		if (nextBlock <= &myblock[4095]) {
			metadata * next = (metadata *) nextBlock;
			if (next->inuse == 0) {
				freeBlock->size = freeBlock->size+sizeof(metadata)+next->size;
				char * findnext = (char *) next;
				findnext = findnext+sizeof(metadata)+next->size;
				if (findnext <= &myblock[4095]) {
					metadata * nextnext = (metadata *) findnext;
					nextnext->prev = freeBlock;
					temp = nextnext;
				}
			}
		}
		
		if (freeBlock->prev != NULL) {
			metadata * prev = freeBlock->prev;
			if (prev->inuse == 0) {
				prev->size = prev->size+sizeof(metadata)+freeBlock->size;
				if (temp != NULL) {
					temp->prev = prev;
				} else {
					if (nextBlock <= &myblock[4095]) {
						metadata * next = (metadata *) nextBlock;
						next->prev = freeBlock->prev;
					}
				}
			}
		}
	} else {
		printf("error at %s %d: address out of memory range\n", file, line);
	}
};
