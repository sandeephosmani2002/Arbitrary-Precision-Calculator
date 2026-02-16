/*NAME:sandeep hosmani
  DATE:10/12/2025
  DESCRIPTION: ***** Arbitrary Precision Calculator *****
-> This project is an Arbitrary Precision Calculator designed to perform mathematical operations on numbers of virtually unlimited size.
-> Unlike standard calculators that are restricted by fixed data types, this APC can handle very large integers and high-precision
   decimal values without loss of accuracy.
-> It supports operations such as addition, subtraction, multiplication, division, and modulus on big numbers.
-> It also allows users to input extremely large numeric values and view the computed results with complete precision.
-> The APC ensures accurate calculations even for numbers that exceed the limits of built-in data types, making it useful for 
   scientific computing, cryptography, and mathematical research.*/


#include "apc.h"
extern int sign1 ;
extern int sign2 ;
extern int negative ;
/*
int division(Digit **head1, Digit **tail1,
             Digit **head2, Digit **tail2,
             Digit **Q_head, Digit **Q_tail)
{

    printf("hi\n");
    negative = (sign1 != sign2);
    printf("bye\n");

    remove_leading_zeros_full(head1,tail1);
    remove_leading_zeros_full(head2,tail2);
    printf("bye\n");

    if (*head2 == NULL)
    {
        printf("Error : Division by Zero\n");
        return FAILURE;
    }

    printf("hi\n");

    if (compare(*head1, *head2) < 0)
    {
        insert_at_first(Q_head, Q_tail, 0);
        return SUCCESS;
    }

    printf("bye\n");

    Digit *dividend_h = NULL, *dividend_t = NULL;
    Digit *divisor_h  = NULL, *divisor_t  = NULL;

    copy_list(*head1, &dividend_h, &dividend_t);
    copy_list(*head2, &divisor_h,  &divisor_t);

    printf("hhiiii\n");

    *Q_head = NULL;
    *Q_tail = NULL;

    while (dividend_h && compare(dividend_h, divisor_h) >= 0)
    {
        Digit *temp_div_h = NULL, *temp_div_t = NULL;
        copy_list(divisor_h, &temp_div_h, &temp_div_t);

        Digit *temp_mul_h = NULL, *temp_mul_t = NULL;
        insert_at_first(&temp_mul_h, &temp_mul_t, 1);

        while (1)
        {
            Digit *next_h = NULL, *next_t = NULL;
            copy_list(temp_div_h, &next_h, &next_t);
            multiply_by_2(&next_h, &next_t);

            if (compare(next_h, dividend_h) > 0)
            {
                Delete_list(&next_h, &next_t);
                break;
            }

            Delete_list(&temp_div_h, &temp_div_t);
            temp_div_h = next_h;
            temp_div_t = next_t;

            multiply_by_2(&temp_mul_h, &temp_mul_t);
        }

        Digit *res_h = NULL, *res_t = NULL;
        subtract_abs(dividend_h, dividend_t,
                     temp_div_h, temp_div_t,
                     &res_h, &res_t);

        Delete_list(&dividend_h, &dividend_t);
        dividend_h = res_h;
        dividend_t = res_t;

        Digit *new_q_h = NULL, *new_q_t = NULL;
        safe_addition(*Q_head, *Q_tail,
                 temp_mul_h,temp_mul_t,
                 &new_q_h, &new_q_t);

        Delete_list(Q_head, Q_tail);
        *Q_head = new_q_h;
        *Q_tail = new_q_t;

        Delete_list(&temp_div_h, &temp_div_t);
        Delete_list(&temp_mul_h, &temp_mul_t);
    }

    printf("hiiiiiiiii\n");

    remove_leading_zeros_full(Q_head,Q_tail);
    
    return SUCCESS;
}
*/
int division(Digit **head1, Digit **tail1,
             Digit **head2, Digit **tail2,
             Digit **Q_head, Digit **Q_tail)
{
    Digit *dividend_h = NULL, *dividend_t = NULL;
    Digit *divisor_h  = NULL, *divisor_t  = NULL;

    negative = (sign1 != sign2);

    remove_leading_zeros_full(head1, tail1);
    remove_leading_zeros_full(head2, tail2);

    if (*head2 == NULL)
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    if (*head1 == NULL || compare(*head1, *head2) < 0)
    {
        insert_at_first(Q_head, Q_tail, 0);
        return SUCCESS;
    }

    copy_list(*head1, &dividend_h, &dividend_t);
    copy_list(*head2, &divisor_h, &divisor_t);

    *Q_head = NULL;
    *Q_tail = NULL;

    while (compare(dividend_h, divisor_h) >= 0)
    {
        Digit *res_h = NULL, *res_t = NULL;

        subtract_abs(dividend_h, dividend_t,
                     divisor_h, divisor_t,
                     &res_h, &res_t);

        Delete_list(&dividend_h, &dividend_t);

        dividend_h = res_h;
        dividend_t = res_t;

        /* 🔥 THIS IS THE FIX 🔥 */
        remove_leading_zeros_full(&dividend_h, &dividend_t);

        /* quotient++ */
        if (*Q_head == NULL)
        {
            insert_at_first(Q_head, Q_tail, 1);
        }
        else
        {
            Digit *one_h = NULL, *one_t = NULL;
            insert_at_first(&one_h, &one_t, 1);

            Digit *new_q_h = NULL, *new_q_t = NULL;
            safe_addition(*Q_head, *Q_tail,
                          one_h, one_t,
                          &new_q_h, &new_q_t);

            Delete_list(Q_head, Q_tail);
            Delete_list(&one_h, &one_t);

            *Q_head = new_q_h;
            *Q_tail = new_q_t;
        }
    }

    remove_leading_zeros_full(Q_head, Q_tail);

    Delete_list(&dividend_h, &dividend_t);
    Delete_list(&divisor_h, &divisor_t);

    return SUCCESS;
}




Status subtract_abs(Digit *head1, Digit *tail1,Digit *head2, Digit *tail2,Digit **res_head, Digit **res_tail)
{
    int borrow = 0;

    *res_head = NULL;
    *res_tail = NULL;

    while (tail1 || tail2)
    {
        int num1 = tail1 ? tail1->data : 0;
        int num2 = tail2 ? tail2->data : 0;

        int sub = num1 - num2 - borrow;

        if (sub < 0)
        {
            sub += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        dl_insert_first(res_head, res_tail, sub);

        if (tail1) tail1 = tail1->prev;
        if (tail2) tail2 = tail2->prev;
    }

    remove_leading_zeros_full(res_head,res_tail);
    return SUCCESS;
}

void multiply_by_2(Digit **head, Digit **tail)
{
    if (*head == NULL)
        return;

    Digit *temp = *tail;
    int carry = 0;

    /* Traverse from LSB to MSB */
    while (temp != NULL)
    {
        int val = (temp->data * 2) + carry;
        temp->data = val % 10;
        carry = val / 10;
        temp = temp->prev;
    }

    /* If carry remains, insert at beginning */
    if (carry)
    {
        insert_at_first(head, tail, carry);
    }
}

void remove_leading_zeros_full(Digit **head, Digit **tail)
{
    while (*head && (*head)->data == 0 && (*head)->next)
    {
        Digit *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }

    /* Fix tail */
    if (*head == NULL)
        *tail = NULL;
    else
    {
        Digit *t = *head;
        while (t->next)
            t = t->next;
        *tail = t;
    }
}

