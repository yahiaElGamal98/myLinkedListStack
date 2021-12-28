#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"STD_types.h"
#pragma warning(disable:4996)

/******MACROS******/
#define EMPTY_STACK 0 
#define FULL_STACK 30

/******TYPEDEFS******/
typedef struct Node_t node;
typedef struct Node_t
{
   uint8_t data;
   node* next;
}node;

/******Function prototypes******/
void push(uint8_t  u8_val);      //push new element to stack
uint8_t pull(void);     //pull element out of stack
void printStack(void);     //pop and print element by element of stack (used for debugging only)
uint8_t* balancedParentheses(uint8_t* expression);    //function to check parentheses balance


/******Global Variables******/
uint8_t gu8_stackTop = EMPTY_STACK;    //number of elements in stack
node* gpstr_head = NULL;    //head node of stack

/*****Main Function******/
int main(void)
{
   uint8_t u8arr_test[30];    //array for custom test cases
   printf("First test case : { 1+( 2/5 )+2 }\n\n");
   printf("%s\n", balancedParentheses("{1+(2/5)+2}"));
   printf("Second Test case : (2*3 + ( 5/2 + ( 4*3 )))\n\n");
   printf("%s\n", balancedParentheses("(2*3 + ( 5/2 + ( 4*3 ))) "));
   printf("Third test case : { ( { 2+10 } }*11 }\n\n");
   printf("%s\n", balancedParentheses("{ ( { 2+10 } }*11 }"));
   printf("custom test case : ");
   scanf("%[^\n]", u8arr_test);     //user's test case input
   printf("%s\n", balancedParentheses(u8arr_test));
   system("PAUSE");
  }

/******Function implemetation*******/
void push(uint8_t  u8_val)
{
   node* pnode_temp;    //temporary pointer to exchange new node's next address with address of head
   node* pstr_newNode = (node*)malloc(sizeof(node));    //assigning new node
   if (NULL==gpstr_head)    //If stack is empty
   {
      gpstr_head = pstr_newNode;    //head points to the new node
      pstr_newNode->data = u8_val;    
      pstr_newNode->next = NULL;      //new node points to NULL (no elements next)
      gu8_stackTop++;      //increment stack elements count
   }
   else if (FULL_STACK <= gu8_stackTop)      //stack overflow protection
   {
      printf("Stack overflow!\n");
   }
   else      //else if stack already has atleast one element
   {
      pnode_temp = gpstr_head;    //temp takes address of first node from head
      gpstr_head = pstr_newNode;    //head takes address of new node
      pstr_newNode->data = u8_val; 
      pstr_newNode->next = pnode_temp;   //new node points to temp(the previous first node)
      gu8_stackTop++;   //increment stack elements
   }
}


uint8_t pull(void)
{
   node* pstr_temp;     //temporary pointer to exchange deleted node's next address with address of head
   uint8_t u8_val;      //popped value
   if (NULL==gpstr_head)   //no elements in stack
   {
      printf("Stack empty, Nothing to pull!\n");
      return NULL;
   }
   else 
   {
      pstr_temp = gpstr_head;
      gpstr_head = pstr_temp->next;
      u8_val = pstr_temp->data;
      free(pstr_temp);     
      gu8_stackTop--;   //decrement number of elements in stack
      return u8_val;
   }
}


void printStack(void)
{
   while(gpstr_head!=NULL)    //while head not equal null (didn't pull all elements)
   {
      printf("%c ", pull());  //pull and print
   }
}


uint8_t* balancedParentheses(uint8_t* str)
{
   uint8_t u8_strIndex     //array index
      ,u8_temp=0     //variable to return pulled elements in
      ,u8_countCurlyOpen=0    //variable to count open curly braces
      ,u8_countCurlyClosed=0    //variable to count closed curly braces
      ,u8_countRoundOpen=0    //variable to count open round braces
      ,u8_countRoundClosed=0   //variable to count closed round braces
      ,u8_prevElement=0
      ,u8_parenFlag=0;   
   for (u8_strIndex = 0; str[u8_strIndex]!='\0'; u8_strIndex++)
   {
      push(str[u8_strIndex]);    //push element by element into stack
   }
   while (gpstr_head != NULL)    //pull element by element 
   {
      u8_temp = pull();    //store each element in temp variable
      if ('{' == u8_temp)     //check which braces type it holds if any
      {
         u8_countCurlyOpen++;
         if (u8_prevElement == ')')
         {
            u8_parenFlag=1;
         }
         else
         {
            u8_prevElement = 0;
         }
      }
      else if ('}' == u8_temp)
      {
         u8_countCurlyClosed++;
         u8_prevElement = u8_temp;
      }
      else if ('(' == u8_temp)
      {
         u8_countRoundOpen++;
         if (u8_prevElement == '}')
         {
            u8_parenFlag=1;
         }
         else
         {
            u8_prevElement = 0;
         }
      }
      else if (')' == u8_temp)
      {
         u8_countRoundClosed++;
         u8_prevElement = u8_temp;
      }
   }
   if ((u8_countCurlyClosed == u8_countCurlyOpen)     // a balanced parenthesis must have as many open braces of each type as there are closed 
      && (u8_countRoundClosed == u8_countRoundOpen)
      &&(!u8_parenFlag)
      &&(NULL==gpstr_head))      // and we check we already searched for all of braces by assuring we popped all stack elements
   {
      return "Balanced Parentheses\n";
   }
   else
   {
      return "Unbalanced Parentheses\n";
   }
}
