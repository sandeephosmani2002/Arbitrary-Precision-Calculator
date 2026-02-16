/*                                                                                                                                                          Description : ***** Arbitrary Precision Calculator *****                                                                                                                                                                                                                                                                 -> This project is an Arbitrary Precision Calculator designed to perform mathematical operations on numbers of virtually unlimited size.                    -> Unlike standard calculators that are restricted by fixed data types, this APC can handle very large integers and high-precision decimal values without loss of accuracy.                                                                                                                                             -> It supports operations such as addition, subtraction, multiplication, division, and modulus on big numbers.                                              -> It also allows users to input extremely large numeric values and view the computed results with complete precision.                                      -> The APC ensures accurate calculations even for numbers that exceed the limits of built-in data types, making it useful for scientific computing, cryptography, and mathematical research.

*/

#include "apc.h"

Status Multiplication(Digit **head1, Digit **tail1, Digit **head2, Digit **tail2, Digit **headR, Digit **tailR)
{
    /* Definition goes here */
    Digit *temp2 = *tail2;
    int count = 0;

    *headR = NULL;
    *tailR = NULL;
    Digit *headR2=NULL;
    Digit *tailR2=NULL;

    while (temp2 != NULL)
    {
        int val1 = temp2->data;
        Digit *temp1 = *tail1;

        Digit *headR1 = NULL;
        Digit *tailR1 = NULL;

        int carry = 0;

        while (temp1 != NULL)
        {
            int val2 = temp1->data;
            int res = val1 * val2 + carry;

            int rem = res % 10;
            carry = res / 10;

            insert_at_first(&headR1, &tailR1, rem);

            temp1 = temp1->prev;
        }

        if (carry)
        {
            insert_at_first(&headR1, &tailR1, carry);
        }

        for (int i = 0; i < count; i++)
        {
            dl_insert_last(&headR1, &tailR1, 0);
        }
        if(*headR == NULL){
            *headR = headR1;
            *tailR = tailR1;
            headR1 = NULL;
            tailR1 = NULL;
        }
        else{
            Addition(headR,tailR,&headR1,&tailR1,&headR2,&tailR2);
            Delete_list(headR,tailR);
            *headR=headR2;
            *tailR=tailR2;
            Delete_list(&headR1,&tailR2);
            headR2=NULL;
            tailR2=NULL;
        }
        count++;
        temp2 = temp2->prev;
    }
    
    return SUCCESS;
}
