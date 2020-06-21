// implementation file

#include "phoneDirectory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
  new_contact = (contact *)malloc(sizeof(contact));

  if (new_contact != NULL)
  {
    char name[25];
    printf("\n Enter name ");
    scanf("%s", name);
    while (validate_name(name))
    {
      printf("Invalid name. Lenghth of name should be at least 3 characters. also Name should not contain any numbers or special chracters other than an apostrophe(') and a full point(.) Please enter the name again\n");
      scanf("%s", name);
    }
    //insert in trie, here

    printf("Enter phone number ");
    scanf("%s", new_contact->phone_number[0]);
    flag = validate_phone_number(new_contact->phone_number[0]);
    while (flag == 0)
    {
      printf("INVALID PHONE NUMBER. PLEASE ENTER A VALID PHONE NUMBER\n");
      scanf("%s", new_contact->phone_number[0]);
      flag = validate_phone_number(new_contact->phone_number[0]);
    }
    write_to_file(new_contact);
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

int write_to_file(contact *new) //function to write phone number to a file
{
  FILE *fp;
  fp = fopen("phone_number.txt", "a+");
  if (fp == NULL)
  {
    printf("Cannot open file\n  ");
    exit(0);
  }
  else
  {
    fprintf(fp, "%s\n", new->phone_number[0]);
  }
  fclose(fp);
}
