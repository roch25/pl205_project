// implementation file

#include "phoneDirectory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_contact()
{
  int op;
  contact *new_contact;
  new_contact = (contact*)malloc(sizeof(contact));
  if(new_contact != NULL)
  {
    // to-do: name
    // phone number
    printf("Enter phone number ");
    scanf("%s", new_contact->phone_number[0]);
    //validation function call
  }
  else
  {
    return -1; // memory could not be allocated
  }
}
