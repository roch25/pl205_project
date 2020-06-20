// implementation file

#include "phoneDirectory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int add_contact()
{
  int op, flag = 0;
  contact *new_contact;
  new_contact = (contact *)malloc(sizeof(contact));
  if (new_contact != NULL)
  {
    while (flag == 0)
    {
      printf("Enter phone number ");
      scanf("%s", new_contact->phone_number[0]);
      flag = validate_phone_number(new_contact->phone_number[0]);
      if (flag == 0)
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
  int length, i;
  char ch;
  length = strlen(value);
  if (length != 10)
  {
    return 0;
  }
  else
  {
    for (i = 0; i < 10; i++)
    {
      ch = value[i];
      if (!isdigit(ch))
      {
        return 0;
      }
    }
    return 1;
  }
}
