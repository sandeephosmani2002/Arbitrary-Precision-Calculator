/*
Description : ***** Arbitrary Precision Calculator *****

 -> This project is an Arbitrary Precision Calculator designed to perform mathematical operations on numbers of virtually unlimited size.    
 -> Unlike standard calculators that are restricted by fixed data types, this APC can handle very large integers and high-precision decimal values without loss of accuracy.
 -> It supports operations such as addition, subtraction, multiplication, division, and modulus on big numbers.
 -> It also allows users to input extremely large numeric values and view the computed results with complete precision.
 -> The APC ensures accurate calculations even for numbers that exceed the limits of built-in data types, making it useful for scientific computing, cryptography, and mathematical research.

*/


#include "apc.h"

int sign1 = 1;
int sign2 = 1;
int negative ;

int main(int argc,char* argv[])
{
     Digit *head1 = NULL;
     Digit *tail1 = NULL;
     Digit *head2 = NULL;
     Digit *tail2 = NULL;
     Digit *res_head = NULL;
     Digit *res_tail = NULL;

  
     char operator;
    
     if(argc == 4)
     {
     	if(read_and_validate(argv,argc,&operator) == SUCCESS)
     	{
		if(load_first_number(argv[1],&head1,&tail1,&sign1) == FAILURE)
		{
                   printf("1st number is not copied\n");
		}
		if(load_second_number(argv[3],&head2,&tail2,&sign2) ==  FAILURE)
		{
                   printf("2nd number is not copied\n");
		}


     	}

        operator = argv[2][0];	
	printf("DEBUG operator after validation = %c\n", operator);
	opretion_validation(&operator,&head1 ,&head2);
	 
        printf("DEBUG operator after validation = %c\n", operator);
	
	switch(operator)
	{
           case '+':
                   Addition(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);
		   print_list(res_head);
		   break;
	   case '-':
                   Subtraction(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);
		   print_list(res_head);

		   break;
	   case 'x':
                   Multiplication(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);
		   print_list(res_head);
		   break;
	   case '/':
		    res_head = NULL;
                    res_tail = NULL;
                   division(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);
		   print_list(res_head);
		   break;
	   default:
		   printf("Invalid operator\n");
	}
     }
     else
     {
	     printf("Error:");
     }
}
