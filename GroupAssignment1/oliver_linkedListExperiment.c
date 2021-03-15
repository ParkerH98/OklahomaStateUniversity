#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

struct testStructure{
    char name[50];
};

struct linkedList{
    struct testStructure* entry;
    struct linkedList* last;
    struct linkedList* next;
};

int main(){
    struct linkedList* head;
    head = malloc(sizeof(struct linkedList));
    head->entry = malloc(sizeof(struct testStructure));
    strcpy(head->entry->name,"Hello");
    printf("%s",head->entry->name);
}