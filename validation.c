#include "phoneDirectory.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_dupilcate_contact_details(char *name, char *phone_num)
{
  int flag = 0;
  FILE *fp1;
  //open file stream
  contact c;
  while (fread(&c, sizeof(c), 1, fp1) == 1)
  {
    }
  fclose(fp1);
  return 0;
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
    return 1;
  }
}
