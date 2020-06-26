#include "phoneDirectory.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_dupilcate_contact_name(char *name)
{
  int str = 0;
  FILE *fp2;
  fp2 = fopen("phone_number.dat", "rb+");
  if (fp2 == NULL)
  {
    printf("Cannot open file\n  ");
    exit(0);
  }

  contact c;
  while (fread(&c, sizeof(c), 1, fp2) == 1)
  {

    str = strcmp(c.name, name);
    if (str == 0)
    {
      return 0;
    }
  }
  fclose(fp2);
  return 1;
}

int check_dupilcate_contact_number(char number[])
{

  FILE *fp1;
  contact c;
  int str;
  // open file here
  fp1 = fopen("phone_number.dat", "rb+");
  if (fp1 == NULL)
  {
    printf("Cannot open file\n  ");
    exit(0);
  }

  while (fread(&c, sizeof(c), 1, fp1) == 1)
  {
    str = strcmp(c.phone_num, number);
    if (str == 0)
    {
      return 0;
    }
  }
  return 1;
  fclose(fp1);
}

int validate_name(char name[25])
{
  int i = 0, c;
  char ch, next;
  if (strlen(name) < 3) // length validation
    return 1;
  ch = name[0];
  if (IS_SPACE(ch) || IS_APOSTROPHE(ch) || IS_FULLPOINT(ch)) // first character validation
    return 2;
  while (i < strlen(name)) //if it contains numbers or special charcters other than a full point or apostrophe
  {
    ch = name[i];
    c = IS_UPPER_CASE(ch) || IS_LOWER_CASE(ch) || IS_SPACE(ch) || IS_APOSTROPHE(ch) || IS_FULLPOINT(ch);
    if (!c)
      return 3;
    if ((i - 1) >= 0)
    {
      next = name[i - 1];
      if ((IS_APOSTROPHE(ch) && IS_APOSTROPHE(next)) || (IS_FULLPOINT(ch) && IS_FULLPOINT(next) || ((IS_SPACE(ch) && IS_SPACE(next)))))
        return 4;
    }
    i++;
  }
  if (check_dupilcate_contact_name(name) == 0)
  {
    return 5;
  }

  return 0; //if valid
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
  }
  if (check_dupilcate_contact_number(value) == 0)
  {
    return 0;
  }
  return 1;
}
