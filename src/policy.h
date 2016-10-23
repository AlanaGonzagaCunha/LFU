#include "LFU.h"
#define max(a, b) ( (a) > (b) ? (a) : (b) )
#define min(a, b) ( (a) < (b) ? (a) : (b) )

int CAPACITY = 0;
int OPERATION_COUNTER = 0;
int READ_COUNTER = 0;
int WRITE_COUNTER = 0;
int MISS_COUNTER = 0;
int HIT_COUNTER = 0;
int SECONDARY_MEDIA_COUNTER = 0;
int BYTES;
int p = 0;
int STATE;

struct LFU * lfu;
struct Node* list;

struct Page * create_New_Page(int id);
struct Page *_seek(int id);




void setOperation(struct Page *x, char operation) {
	if (operation == 'W') {
		x->isDirty = 1;
		WRITE_COUNTER++;
	} else {
		READ_COUNTER++;
	}
}

struct Page* flush(struct Page *x) {
	if (x != NULL) {
		if (x->isDirty == 1) {
			write_file(x, BYTES);
			SECONDARY_MEDIA_COUNTER++;

		}
		free(x->content);
		x->content = NULL;
	}
	return x;
}




int _insert_LRU(int id, char operation) {

	OPERATION_COUNTER++;
	struct Node * x = _seek(id);

	if (x != NULL) {

		setOperation(x, operation);

		HIT_COUNTER++;
		STATE = 1;

		//insert_list(lru,remove_list(lru,x));

	} else {

		STATE = -1;

		MISS_COUNTER++;
		x = create_New_Page(id);
		setOperation(x, operation);

		if(lfu->size == CAPACITY){
			struct Node* removed = remove_list(lfu,lfu->tail);
			free(flush(removed));
			removed = NULL;
		}

		insert_list(lfu,x);


	}

	return STATE;
}

struct Page *_seek(int id) {
	struct Node * x = NULL;
	x = seek_list(lfu, id);
	if (x != NULL)

		return x;
	return x;
}



struct Page * create_New_Page(int id) {
	struct Page * newPage = (struct Page*) malloc(sizeof(struct Page));
	newPage->idPage = id;
	newPage->isDirty = 0;
	newPage->lfu = NULL;
	newPage->next = NULL;
	newPage->prev = NULL;
	newPage->freq = 0;
	newPage->time=0;
	read_file(newPage, BYTES);
	return newPage;
}

void _print_report() {

	printf("\nCapacity: %d", CAPACITY);
	printf("\nOperation Counter: %d", OPERATION_COUNTER);

	printf("\nSecondary Media Counter: %d", SECONDARY_MEDIA_COUNTER);
	float aux1 = 100 * ((float) MISS_COUNTER / (float) OPERATION_COUNTER);
	float aux2 = 100 * (float) HIT_COUNTER / (float) OPERATION_COUNTER;
	printf("\nHit:    \t %d, %.1f percent \nMiss:     \t %d, %.1f percent",
			HIT_COUNTER, aux2, MISS_COUNTER, aux1);
	aux1 = 100 * ((float) READ_COUNTER / (float) OPERATION_COUNTER);
	aux2 = 100 * ((float) WRITE_COUNTER / (float) OPERATION_COUNTER);
	printf("\nREAD:\t %d, %.1f percent \nWRITE:\t %d, %.1f percent",
			READ_COUNTER, aux1, WRITE_COUNTER, aux2);
	printf("\n ");
}


void _printLRU(){

	struct P * x = lfu->head;
	while(x != NULL){
		printf("[%d]",x->id);
		x = x->next;
	}

}

void _initialize_(int capacity, int bytes) {
	startFILE();
	STATE = 0;
	p = 0;
	CAPACITY = capacity;
	BYTES = bytes;

	lfu = (struct Page*) malloc(sizeof(struct List));

	lfu->head = NULL;
	lfu->tail = NULL;
	lfu->size = 0;

	list= (struct Node*) malloc(sizeof(struct Node));
	list->next = NULL;
	list->sizeList=0;

}
