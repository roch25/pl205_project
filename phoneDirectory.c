// implementation file

#include "phoneDirectory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define IS_UPPER_CASE(x) (x > 64 && x < 91)
#define IS_LOWER_CASE(x) (x > 96 && x < 123)
#define IS_APOSTROPHE(x) x == 39
#define IS_SPACE(x) x == 32
#define IS_FULLPOINT(x) x == 46

int add_contact(trie *root)
{
  int op, flag = 0;
  if (root != NULL)
  {
    char name[25];
    printf("\nEnter name ");
    scanf(" %[^\n]", name);
    int x;
    while (x = validate_name(name))
    {
      switch (x)
      {
      case 1:
        printf("Length of name should be at least 3 characters");
      case 2:
        printf("Name should not begin with a apostrophe or a full point");
        break;
      case 3:
        printf("Name should not contain any numbers or special chracters other than an apostrophe(') and a full point(.) ");
      }
      printf("Please enter the name again\n");
      scanf("%s", name);
    }
    char phone_num[12];
    printf("Enter phone number ");
    scanf("%s", phone_num);
    flag = validate_phone_number(phone_num);
    while (flag == 0)
    {
      printf("INVALID PHONE NUMBER. PLEASE ENTER A VALID PHONE NUMBER\n");
      scanf("%s", phone_num);
      flag = validate_phone_number(phone_num);
    }
    insert(root, name, phone_num);
  }
  else
  {
    return -1; // memory could not be allocated
  }
}

void write_to_file(trie *new) //function to write phone number to a file
{
  FILE *fp;
  fp = fopen("phone_number.dat", "ab");
  if (fp == NULL)
  {
    printf("Cannot open file\n  ");
    return;
  }
  int record_added = fwrite(&new, sizeof(new), 1, fp);
  if (record_added)
    printf("\n\n Contact details added succesfully!\n");
  fclose(fp);
}

int insert(trie *root, char *name, char *phone_num)
{
  trie *curr = root;
  int sub;
  char ch;
  while (*name) //iterate over each character in the name to insert in the trie
  {
    ch = *name;
    sub = IS_UPPER_CASE(ch) ? 65 : (IS_LOWER_CASE(ch) ? 70 : (IS_SPACE(ch) ? -21 : IS_APOSTROPHE(ch) ? -15 : -9));
    if (curr->next[*name - sub] == NULL)
    {
      curr->next[*name - sub] = (trie *)malloc(sizeof(trie)); //set the node
      (curr->next[*name - sub])->isLeaf = 0;
      for (int i = 0; i < CHAR_SIZE; i++) //set all next nodes to NULL
        (curr->next[*name - sub])->next[i] = NULL;
    }
    curr = curr->next[*name - sub];
    name++; //move to next char in name
  }
  curr->isLeaf = 1; // indicates end
  strcpy(curr->phone_number[0], phone_num);
}

int check_phone_number(char *phone_num) //function to check if phone number is identical
{
  int flag = 0;
  FILE *fp1;
  fp1 = fopen("phone_number.txt", "r");
  if (fp1 == NULL)
  {
    printf("Cannot open file\n");
    exit(0);
  }
  else
  {
  }

  fclose(fp1);
}

void display(trie *root, char *str, int level)
{
  if (root->isLeaf == 1)
  {
    str[level] = '\0';
    printf("%s %s\n", str, root->phone_number[0]);
  }
  int i, sub;
  char ch;
  for (i = 0; i < CHAR_SIZE; i++)
  {
    if (root->next[i])
    {
      sub = (i < 26) ? 65 : (i > 25 && i < 53) ? 70 : (i == 53 ? -21 : i == 54 ? -15 : -9);
      str[level] = i + sub;
      display(root->next[i], str, level + 1);
    }
  }
}

int validate_name(char name[25])
{
  int i = 0, c;
  char ch;
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