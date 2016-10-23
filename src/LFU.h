#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int repeat=0;

struct Node {
	struct Node* next;
	int sizeList;
	struct Page* p;

};
struct LFU {
	struct Page* tail;
	struct Page* head;
	int size;
};

struct Page {
	int time;
	int isDirty;
	int idPage;
	int freq;
	struct Page* next;
	struct Page* prev;
	struct LFU* lfu;
	struct Node* list;
	char* content;
};
struct Page *users = NULL;
void read_file(struct Page* x, int BYTES);
void write_file(struct Page* x, int BYTES);

FILE *file;
void startFILE() {
	file = fopen("file.txt", "r+");
}

void read_file(struct Page* x, int BYTES) {

	char * xs = (char*) malloc(BYTES);
	fseek(file, (x->idPage / 100000) * BYTES, SEEK_SET);
	fread(xs, sizeof(char), BYTES, file);
	x->content = xs;

}
void write_file(struct Page* x, int BYTES) {
	fseek(file, (x->idPage / 100000) * BYTES, SEEK_SET);
	fwrite(x->content, sizeof(char), BYTES, file);
}

void insereListFrequecies(struct Page* page) {

	page->freq++;

	if(repeat==0){
	list->next = page;
	list->sizeList++;

	}else{
		//obs: prestar atenção nesse trecho de cod n sei se funci
		while(list != NULL){
			if(list->p->idPage==page->idPage){
				list->p->next=NULL;
				list->p=NULL;
				list->next=page;
			}

			list=list->next;
		}
	}
}


void verificTime() {
	struct Page* aux = lfu->head;
		while (aux != NULL) {
			aux->time++;
			aux=aux->next;
		}
}
void insereLFU(struct LFU* lfu, struct Page* page) {
	struct Page* aux = lfu->head;

	if (page != NULL) {

		if (0 < lfu->size < 4) {
			//verificar se vai inserir repetidos...
			while(aux!=NULL){
				if(aux->idPage==page->idPage){
					repeat=1;
					insereListFrequecies(page);
				}
				aux=aux->next;
			}
			lfu->tail->next = page;
			page->prev = lfu->tail;
			lfu->tail = page;
			insereListFrequecies(page);

		}

	} else {
		lfu->head = page;
		lfu->tail = page;
		insereListFrequecies(page);
	}
	lfu->size++;
	verificTime();
}
void deletaLFU(struct LFU* lfu, struct Page* page) {
//remover a com maior frequencia caso nao haja remover a mais antiga
	//obs remover a pagina n esquecer de zerar a frequencia
	struct Page* aux = page->next;

	while (aux != NULL) {
		if (aux->freq >= aux->next->freq) {

		} else {
			break;
		}

		aux = aux->next;
	}
	//remove a mais antiga
	while (aux != NULL) {

	}

}
