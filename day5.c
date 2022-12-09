#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack_t {
    char *data;
    stack *next;
} typedef stack;

void insert(stack *head, char data) {
    stack *temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = (stack*) malloc(sizeof(stack));
    temp->next->data = data;
    temp->next->next = NULL;
}

stack* create(char data) {
    stack *new = malloc(sizeof(stack));
    new->data = data;
    new->next = NULL;

    return new;
}

char pop(stack *head)
{
   char head_value; //variable for value at the top
   stack *temp; //temporary pointer

   temp = head;
   head_value = head->data;
   head = head->next;
   free(temp); //free temporary pointer value
   return head_value;
}

char peek(stack *head) {
    return head->data;
}

void part1() {
    stack *stacks[9];
    char databuffer[9];

    memset(stacks, 0, sizeof(stack*) * 9);

    char buffer[40];
    memset(buffer, 0, 40);

    FILE *fp;

    fp = fopen("day5.txt", "r");

    while(!buffer[1] == '1') {
        fgets(buffer, 40, fp);

        sscanf(buffer, "");
    }
}