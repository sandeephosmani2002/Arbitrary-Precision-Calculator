/*                                                                                                                                                          Description : ***** Arbitrary Precision Calculator *****                                                                                                                                                                                                                                                                 -> This project is an Arbitrary Precision Calculator designed to perform mathematical operations on numbers of virtually unlimited size.                    -> Unlike standard calculators that are restricted by fixed data types, this APC can handle very large integers and high-precision decimal values without loss of accuracy.                                                                                                                                             -> It supports operations such as addition, subtraction, multiplication, division, and modulus on big numbers.                                              -> It also allows users to input extremely large numeric values and view the computed results with complete precision.                                      -> The APC ensures accurate calculations even for numbers that exceed the limits of built-in data types, making it useful for scientific computing, cryptography, and mathematical research.

*/




#include "apc.h"

Status Addition(Digit** head1,Digit** tail1,Digit** head2,Digit** tail2,Digit** res_head,Digit** res_tail)
{
     int carry = 0;
     while(*tail1 != NULL || *tail2 != NULL)
     {
	     int num1 = *tail1 != NULL ? (*tail1)->data : 0;
	     int num2 = *tail2 != NULL ? (*tail2)->data : 0;
	     int sum = num1 + num2 + carry;

	     if(sum > 9)
	     {
		     carry = 1;
	     }
	     else
	     {
		     carry = 0;
	     }

	      dl_insert_first(res_head,res_tail,sum%10);
	     
	     if(*tail1 != NULL)
	     {
		     *tail1 = (*tail1)->prev;
	     }

	     if(*tail2 != NULL)
	     {
		     *tail2 = (*tail2)->prev;
	     }
     }

     if(carry)
     {
	     dl_insert_first(res_head,res_tail,carry);
     }
}


Status dl_insert_first(Digit **head, Digit **tail, int data)
{
     Digit *new = malloc(sizeof(Digit));
     if(new == NULL)
     {
         return FAILURE;
     }
     new->data = data;
     new->prev = NULL;
     new->next = *head;
     if(*head == NULL)
     {
         *head = new;
         *tail = new;
         return SUCCESS;
     }
     (*head)->prev = new;
     *head = new;
     return SUCCESS;
}
