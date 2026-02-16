/*                                                                                                                                                          Description : ***** Arbitrary Precision Calculator *****                                                                                                                                                                                                                                                                 -> This project is an Arbitrary Precision Calculator designed to perform mathematical operations on numbers of virtually unlimited size.                    -> Unlike standard calculators that are restricted by fixed data types, this APC can handle very large integers and high-precision decimal values without loss of accuracy.                                                                                                                                             -> It supports operations such as addition, subtraction, multiplication, division, and modulus on big numbers.                                              -> It also allows users to input extremely large numeric values and view the computed results with complete precision.                                      -> The APC ensures accurate calculations even for numbers that exceed the limits of built-in data types, making it useful for scientific computing, cryptography, and mathematical research.

*/


#include "apc.h"

extern int sign1 ;
extern int sign2 ;
extern int negative ;
Status Subtraction(Digit** head1,Digit** tail1,Digit** head2,Digit** tail2,Digit** res_head,Digit** res_tail)
{
     int cmp = compare(*head1,*head2);
     if(cmp == 0)
     {
       insert_at_first(res_head,res_tail,0);

       return SUCCESS;
     }

      if(cmp == -1)
     {
	     Digit *p = *tail1;
	     *tail1 = *tail2;
	     *tail2 = p;

	     Digit *q = *head1;
	     *head1 = *head2;
	     *head2 = q;
            
	     

     }
     

     int borrow = 0;
     while(*tail1 != NULL || *tail2 != NULL)
     {
             int num1 = *tail1 != NULL ? (*tail1)->data : 0;
             int num2 = *tail2 != NULL ? (*tail2)->data : 0;
             int sub = num1 - num2 - borrow;

             if(sub < 0)
	     {
		 sub+=10;
		 borrow=1;
	      }
	      else
	      {
		 borrow=0;
	      }

              dl_insert_first(res_head,res_tail,sub);

             if(*tail1 != NULL)
             {
                     *tail1 = (*tail1)->prev;
             }

             if(*tail2 != NULL)
             {
                     *tail2 = (*tail2)->prev;
             }
     
     }
      remove_leading_zeros(res_head);


}
