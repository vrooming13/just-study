#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data_field;
    struct node * next_field;
}NODE;

NODE * L_head;

void InsertFront(NODE *head, int data){

    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode ->next_field = head->next_field;
    newNode ->data_field = data;

    head->next_field = newNode;
}

void DeleteNode(int data){
    NODE *searchNode = (NODE*)malloc(sizeof(NODE)); // 탐색 노드
    NODE *delNode = (NODE*)malloc(sizeof(NODE)); // 탐색 노드의 앞 노드, 삭제할 노드

    searchNode = L_head -> next_field;
    delNode = searchNode -> next_field;

    if(searchNode -> data_field == data){
        L_head -> next_field = searchNode -> next_field;
        free(searchNode);
        printf("DELETE!\n");
        return;
    }

    while(delNode -> data_field != data){
        searchNode = searchNode -> next_field;
        delNode = searchNode ->next_field;
        if(searchNode -> next_field == NULL){
            printf("해당 데이터는 리스트에 있지 않습니다.\n");
            return;
        } 
    }

    if(delNode -> data_field == data){
        searchNode -> next_field = delNode -> next_field;
        free(delNode);
        printf("DELETE!\n");
        return;
    }
}

int main(void){

    int del;

    L_head = (NODE *)malloc(sizeof(NODE));
    NODE *n1 = (NODE *)malloc(sizeof(NODE));
    
    L_head -> next_field = n1;
    n1 -> data_field = 10;

    NODE *n2 = (NODE *)malloc(sizeof(NODE));
    n1 -> next_field = n2;
    n2 -> data_field = 20;

    NODE *n3 = (NODE *)malloc(sizeof(NODE));
    n2 -> next_field = n3;
    n3 -> data_field = 30;

    NODE *n4 = (NODE *)malloc(sizeof(NODE));
    n3 -> next_field = n4;
    n4 -> data_field = 40;

    NODE *n5 = (NODE *)malloc(sizeof(NODE));
    n4 -> next_field = n5;
    n5 -> data_field = 50;
    n5 -> next_field = NULL;

    
    NODE *curr = L_head ->next_field;

    while(curr != NULL){
        printf("%d\n", curr ->data_field);
        curr = curr ->next_field;
    }
    
    printf("Enter Delete Node\n");
    scanf("%d",&del);

    DeleteNode(del);

    curr = L_head -> next_field;

    while(curr != NULL){
        printf("%d\n", curr ->data_field);
        curr = curr ->next_field;
    }


    free(n5);
    free(n4);
    free(n3);
    free(n2);
    free(n1);

    free(L_head);

    return 0;
}
