#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
   float *m;
	
   struct node *next;
   struct node *prev;
}typeNode;

//this link always point to first Link 
struct node *head = NULL;

//this link always point to last Link 
struct node *last = NULL;

struct node *current = NULL;

//is list empty
bool isEmpty(){
   return head == NULL;
}

int length(){
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) length++;
	
   return length;
}

//display the list in from first to last
void displayForward(){

   //start from the beginning
   struct node *ptr = head;
	
   //navigate till the end of the list
   printf("\n[ ");
	
   while(ptr != NULL){        
      printf("(%d,%d) ",ptr->m);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

//insert link at the first location
void insertFirst(float *v){

   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
   link->m[16] = *v;

   if(isEmpty()){
      //make it the last link
      last = link;
   }else {
      //update first prev link
      head->prev = link;
   }

   //point it to old first link
   link->next = head;
   //link->prev = NULL;
	
   //point first to new first link
   head = link;
}

//delete first item
struct node* deleteFirst(){

   //save reference to first link
   struct node *tempLink = head;
	
   //if only one link
   if(head->next == NULL){
      last = NULL;
   }else {
      head->next->prev = NULL;
   }
	
   head = head->next;
   //return the deleted link
   return tempLink;
}
