// implementation file

#include "phoneDirectory.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int add_contact(trie *root)
{
  int flag = 0;
  contact new_contact;
  printf("\nEnter name ");
  scanf(" %[^\n]", new_contact.name);
  int x;
  while (x = validate_name(new_contact.name))
  {
    switch (x)
    {
    case 1:
      printf(YELLOW "Length of name should be at least 3 characters " RESET);
      break;
    case 2:
      printf(YELLOW "Name should not begin with a apostrophe or a full point " RESET);
      break;
    case 3:
      printf(YELLOW "Name should not contain any numbers or special chracters other than an apostrophe(') and a full point(.) " RESET);
      break;
    case 4:
      printf(YELLOW "Invalid name " RESET);
    }
    printf(YELLOW "Please enter the name again\n" RESET);
    scanf("%s", new_contact.name);
  }
  printf("Enter phone number ");
  scanf(" %[^\n]", new_contact.phone_num);
  flag = validate_phone_number(new_contact.phone_num);
  while (flag == 0)
  {
    printf(YELLOW "INVALID PHONE NUMBER. PLEASE ENTER A VALID PHONE NUMBER\n" RESET);
    scanf("%s", new_contact.phone_num);
    flag = validate_phone_number(new_contact.phone_num);
  }

  if (insert(root, new_contact.name, new_contact.phone_num))
  {
    write_to_file(new_contact);
  }
  else
  {
    return -2;
  }
}

int insert(trie *root, char *name, char *phone_num)
{
  trie *curr = root;
  int sub;
  char ch;
  while (*name) //iterate over each character in the name to insert in the trie
  {
    ch = *name;
    sub = IS_UPPER_CASE(ch) ? 65 : (IS_LOWER_CASE(ch) ? 71 : (IS_SPACE(ch) ? -20 : IS_APOSTROPHE(ch) ? -14 : -8));
    if (curr->next[*name - sub] == NULL)
    {
      curr->next[*name - sub] = (trie *)malloc(sizeof(trie)); //set the node
      if (!curr->next[*name - sub])
        return 0;
      (curr->next[*name - sub])->isLeaf = 0;
      for (int i = 0; i < CHAR_SIZE; i++) //set all next nodes to NULL
        (curr->next[*name - sub])->next[i] = NULL;
    }
    curr = curr->next[*name - sub];
    name++; //move to next char in name
  }
  curr->isLeaf = 1; // indicates end
  strcpy(curr->phone_number[0], phone_num);
  return 1;
}

int modify_contact(trie *root)
{
}

void display(trie *root, char *str, int level)
{
  static int index = 0;
  if (root->isLeaf == 1)
  {
    str[level] = '\0';
    printf("%d %s %s\n", ++index, str, root->phone_number[0]);
  }
  int i, sub;
  char ch;
  for (i = 0; i < CHAR_SIZE; i++)
  {
    if (root->next[i])
    {
      sub = (i < 26) ? 65 : (i > 25 && i < 52) ? 71 : (i == 52 ? -20 : i == 53 ? -14 : -8);
      str[level] = i + sub;
      display(root->next[i], str, level + 1);
    }
  }
}

void write_to_file(contact new) //function to write phone number to a file
{
  FILE *fp;
  fp = fopen("phone_number.dat", "ab");
  if (fp == NULL)
  {
    printf(YELLOW "Cannot open file\n  " RESET);
    return;
  }
  int record_added = fwrite(&new, sizeof(new), 1, fp);
  if (record_added)
    printf(GREEN "\n\n Contact details added succesfully!\n" RESET);
  fclose(fp);
}
