
/*                                                                                                                                                          Description : ***** Arbitrary Precision Calculator *****                                                                                                                                                                                                                                                                 -> This project is an Arbitrary Precision Calculator designed to perform mathematical operations on numbers of virtually unlimited size.                    -> Unlike standard calculators that are restricted by fixed data types, this APC can handle very large integers and high-precision decimal values without loss of accuracy.                                                                                                                                             -> It supports operations such as addition, subtraction, multiplication, division, and modulus on big numbers.                                              -> It also allows users to input extremely large numeric values and view the computed results with complete precision.                                      -> The APC ensures accurate calculations even for numbers that exceed the limits of built-in data types, making it useful for scientific computing, cryptography, and mathematical research.

*/

#include "apc.h"


extern int sign1 ;
extern int sign2 ;
extern int negative ;

Status read_and_validate(char* argv[],int argc,char* operator)
{
       
           int i=0;
	   while(argv[1][i] != '\0')
	   {
                 if(!((argv[1][i] >= '0' && argv[1][i] <= '9') || argv[1][0] == '-' || argv[1][0] == '+'))
		 {
	             printf("Enter the 1st argument as number:  \n");
                     return FAILURE;
		 }
		 i++;

	   }

	   if(!(argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == 'x' || argv[2][0] == '/'))
	   {
		   printf("operator is not suited of this :\n");
		   return FAILURE;
	   }
	   *operator = argv[2][0];

	   int j=0;
           while(argv[3][j] != '\0')
           {
                 if(!((argv[3][j] >= '0' && argv[3][j] <= '9') || argv[3][0] == '-' || argv[3][0] == '+'))
                 {
                     printf("Enter the 2nd argument as number: \n");
                     return FAILURE;
                 }
                 j++;

           }

       
       return SUCCESS;
}

Status load_first_number(char* num,Digit** head1,Digit** tail1,int* sign1)
{
	int i=0;
	if(num[i] == '+')
	{
		*sign1 = 1;//1
		i++;
	}
	else if(num[i] == '-')
	{
		*sign1 = -1;//-1
		i++;
	}
	while(num[i]!='\0')
	{
		int data = num[i]-'0';
                dl_insert_last(head1,tail1,data);
		i++;
	}
	
	return SUCCESS;


}

Status load_second_number(char* num,Digit** head2,Digit** tail2,int* sign2)
{

        int j=0;
	if(num[j] == '+')
        {
                *sign2 = 1;//1
                j++;
        }
        else if(num[j] == '-')
        {
                *sign2 = -1;//-1
                j++;
        }

        while(num[j]!='\0')
        {
                int data1 = num[j]-'0';
                dl_insert_last(head2,tail2,data1);
                j++;
        }
        
	return SUCCESS;
}


Status dl_insert_last(Digit **head, Digit **tail, int data)
{
     Digit *new = malloc(sizeof(Digit));
     if(new == NULL)
     {
         return FAILURE;
     }
     new->data = data;
     new->prev = *tail;
     new->next = NULL;
     if(*head == NULL)
     {
         *head = new;
         *tail = new;
         return SUCCESS;
     }
     (*tail)->next = new;
     *tail = new;
     return SUCCESS;
}

void print_list(Digit *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    printf("Result -> ");
	    if(negative == 1)
	    {
		    printf("-");
	    }
	    while (head)
	    {
		    /* Printing the list */
		    printf("%d", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
		   
	    }
	    printf("\n");
    }
}


Status compare(Digit *head1,Digit *head2)
{
        int len1 = 0, len2 = 0;
        Digit *temp1 = head1;
        Digit *temp2 = head2;

        /* Count length of both lists */
        while (temp1)
        {
                len1++;
                temp1 = temp1->next;
        }
        while (temp2)
        {
                len2++;
                temp2 = temp2->next;
        }

        /* Compare by length */
        if (len1 > len2)
                return 1;
        else if (len1 < len2)
                return -1;


        temp1 = head1;
        temp2 = head2;
        while (temp1 && temp2)
        {
                if (temp1->data > temp2->data)
                        return 1;
                else if (temp1->data < temp2->data)
                        return -1;

                temp1 = temp1->next;
                temp2 = temp2->next;
        }
        return 0;
}
void opretion_validation(char *operator, Digit **head1, Digit **head2)
{
    int bigger;  // stores compare result

    // Case: Addition
    if (*operator == '+')
    {
        if (sign1 == sign2)
        {
            // -a + -b or +a + +b
            negative = (sign1 == -1);
            *operator = '+';
        }
        else
        {
            // +a + -b or -a + +b --> becomes subtraction
            *operator = '-';

            bigger = compare(*head1, *head2);

            if (bigger == 0)
            {
                // same magnitude → result is 0
                negative = 0;
                return;
            }

            if (sign1 == 1 && sign2 == -1)  // +a + -b = a - b
                negative = (bigger < 0);    // if b bigger, result negative
            else                            // -a + +b = b - a
                negative = (bigger > 0);    // if a bigger, result negative
        }
    }

    // Case: Subtraction
    else if (*operator == '-')
    {
        if (sign1 != sign2)
        {
            // +a - (-b) = a + b
            // -a - (+b) = -(a + b)
            *operator = '+';
            negative = (sign1 == -1);
        }
        else
        {
            // +a - +b OR -a - -b → subtraction
            bigger = compare(*head1, *head2);

            if (bigger == 0)
            {
                negative = 0;
                return;
            }

            if (sign1 == 1)
                negative = (bigger < 0);
            else
                negative = (bigger > 0);

            *operator = '-';
        }
    }

    // Case: Multiplication or Division
   /* else if (*operator == 'x' || *operator == '/')
    {
        negative = (sign1 != sign2);  // XOR
    }*/

    else if (*operator == '/' || *operator == 'x')
    {
        if ((sign1 == 1 && sign2 == 1) || (sign1 == -1 && sign2 == -1))
        {
            negative = 0;
        }
        else
        {
            negative = 1;
        }
    }
}

int Delete_list(Digit **head, Digit **tail)
{
    Digit *temp = *head;

    while (temp)
    {
        Digit *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
    *tail = NULL;

    return SUCCESS;
}

int insert_at_first(Digit **head,Digit **tail,int data)
{
	Digit *new=malloc(sizeof(Digit));
	if(new == NULL)	return FAILURE;
	new->data=data;
	new->prev=NULL;
	new->next=NULL;
	if((*head == NULL)|| (*tail == NULL)){
		*head=new;
		*tail=new;
		return SUCCESS;
	}
	else
	{
		(*head)->prev=new;    
		new->next=*head;
		*head=new;
	}
	return SUCCESS;
}

/* Function to copy one list to another list */
/*
void copy_list(Digit *src_head, Digit **dest_head, Digit **dest_tail)
{
    while (src_head != NULL)
    {
        Digit *new = create_node(src_head -> data);

        if (*dest_head == NULL)
        {
            *dest_head = new;
            *dest_tail = new;
        }
        else
        {
            (*dest_tail) -> next = new;
            new -> prev = *dest_tail;  // maintain prev link
            *dest_tail = new;
        }

        src_head = src_head -> next;
    }
}*/
void copy_list(Digit *src_head, Digit **dest_head, Digit **dest_tail)
{
    *dest_head = NULL;
    *dest_tail = NULL;

    while (src_head)
    {
        Digit *new = create_node(src_head->data);

        if (*dest_head == NULL)
        {
            *dest_head = new;
            *dest_tail = new;
        }
        else
        {
            (*dest_tail)->next = new;
            new->prev = *dest_tail;
            *dest_tail = new;
        }
        src_head = src_head->next;
    }
}


/*Function to create node */
Digit *create_node(int data)
{
    Digit *new = malloc(sizeof(Digit));
    if(new == NULL)
            return NULL;
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;
    return new;
}

/* Function to remove the leading zeros */
void remove_leading_zeros(Digit **head)
{
        while (*head && ((*head) -> data == 0) && ((*head) -> next) != NULL)
        {
                Digit *temp = *head;
                *head = (*head) -> next;
                if (*head)
                        (*head) -> prev = NULL;
                free(temp);
        }
}

Status safe_addition(Digit *h1, Digit *t1,Digit *h2, Digit *t2,Digit **res_h, Digit **res_t)
{
    Digit *t1_copy = t1;
    Digit *t2_copy = t2;

    return Addition(&h1, &t1_copy,
                    &h2, &t2_copy,
                    res_h, res_t);
}

