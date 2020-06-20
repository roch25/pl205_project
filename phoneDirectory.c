// implementation file

#include "phoneDirectory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_contact()
{
  int op,int flag=0;
  contact *new_contact;
  new_contact = (contact*)malloc(sizeof(contact));
  if(new_contact != NULL)
  {
    // to-do: name
    while(flag==0)
    {
    // phone number
    printf("Enter phone number ");
    scanf("%s", new_contact->phone_number[0]);
    
    //validation function call
    flag=validate_phone_number(new_contact->phone_number);
     if(flag==0)
     {
         printf("INVALID PHONE NUMBER. PLEASE ENTER A VALID PHONE NUMBER\n");
     }
    }
  }
  else
  {
    return -1; // memory could not be allocated
  }
}

int validate_phone_number(char value[])
{
  int length;
  length=strlen(value);
  if(length != 10)
  {
    return 0;
  }
  else
  {
      return 1;
  }
}
