// implementation file

#include "phoneDirectory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VALID(x) ((x > 64 && x < 91) || (x > 96 && x < 123) || x == 39 || x == 32 || x == 46)
//65-90(A-Z) 97-122(a-z) 32(space) 39(') 46(.)

int validate_name(char name[25])
{
  int i = 0, c;
  if (strlen(name) < 3)
    return 1; //if length is too short
  while (i < strlen(name))
  {
    c = VALID(name[i]);
    if (!c)
      return 2; //if it contains numbers or special charcters other than a full point or apostrophe
    i++;
  }
  return 0; //if valid
}
int add_contact()
{
  int op, flag = 0;
  contact *new_contact;
  // contact *c_name; //(contact name)
  new_contact = (contact *)malloc(sizeof(contact));
  // c_name=(contact*)malloc(strlen(c_name)*sizeof(contact));

  if (new_contact != NULL)
  {
    // to-do: name
    int c;
    char name[25];
    printf("\n Enter name ");
    scanf("%s", name);

    //validation function call
    c = validate_name(name);
    if (c == 1)
      printf("\n Length of name too small. Please enter your name again\n ");
    else if (c == 2)
      printf("\n Name should not contain any numbers or special chracters other than an apostrophe(') and a full point(.)\n ");
    else
    { // name is valid
      strcpy(new_contact->name, name);
    }

    {
      // phone number
      printf("Enter phone number ");
      scanf("%s", new_contact->phone_number[0]);

      //validation function call
      flag = validate_phone_number(new_contact->phone_number);
      if (flag == 0)
      {
        printf("INVALID PHONE NUMBER. PLEASE ENTER A VALID 10 DIGITS PHONE NUMBER\n");
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
  length = strlen(value);
  if (length != 10)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}