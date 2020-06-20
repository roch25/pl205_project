// implementation file

#include "phoneDirectory.h"
#include <stdio.h>
#include <stdlib.h>

int add_contact()
{
  int op;
  contact *new_contact;
  //allocate space ...
  new_contact = (contact*)malloc(sizeof(contact));
  if(new_contact != NULL)
  {
    printf("Enter phone number");
    scanf("%s", new_contact->phone_number[0]);
  }
  else
  {
    op = -1; // memory could not be allocated
  }
  printf("%s",  new_contact->phone_number[0]);

}
