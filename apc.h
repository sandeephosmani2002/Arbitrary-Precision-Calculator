#ifndef APC_H
#define APC_H

#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	struct node* prev;
	int data;
	struct node* next;

}Digit;

typedef enum
{
	FAILURE,
	SUCCESS
}Status;

Status read_and_validate(char* argv[],int argc,char* operator);
Status Addition(Digit** head1,Digit** tail1,Digit** head2,Digit** tail2,Digit** res_head,Digit** res_tail); 
Status Subtraction(Digit** head1,Digit** tail1,Digit** head2,Digit** tail2,Digit** res_head,Digit** res_tail); 
Status Multiplication(Digit** head1,Digit** tail1,Digit** head2,Digit** tail2,Digit** res_head,Digit** res_tail); 
int division(Digit **head1, Digit **tail1, Digit **head2, Digit **tail2, Digit **Q_head, Digit **Q_tail);
void copy_list(Digit *src_head, Digit **dest_head, Digit **dest_tail);
Digit *create_node(int data);
void remove_leading_zeros(Digit **head);

Status load_first_number(char* num,Digit** head,Digit** tail,int* sign1);
Status dl_insert_last(Digit **head1, Digit **tail1, int data);
void print_list(Digit *head1);
Status load_second_number(char* num,Digit** head2,Digit** tail2,int* sign2);

Status dl_insert_first(Digit **head, Digit **tail, int data);

void opretion_validation(char *operator, Digit **head1 , Digit **head2);
Status compare(Digit *head1,Digit *head2);

int Delete_list(Digit **head, Digit **tail);
int insert_at_first(Digit **head,Digit **tail,int data);
void multiply_by_2(Digit **head, Digit **tail);

Status subtract_abs(Digit *head1, Digit *tail1,Digit *head2, Digit *tail2,Digit **res_head, Digit **res_tail);
Status safe_addition(Digit *h1, Digit *t1,Digit *h2, Digit *t2,Digit **res_h, Digit **res_t);
void remove_leading_zeros_full(Digit **head, Digit **tail);
#endif
