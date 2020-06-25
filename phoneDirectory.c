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
  if (root)
  {
    contact *new_contact = (contact *)malloc(sizeof(contact));
    if (new_contact)
    {
      printf("\nEnter name ");
      scanf(" %[^\n]", new_contact->name);
      int x;
      while (x = validate_name(new_contact->name))
      {
        switch (x)
        {
        case 1:
          printf("Length of name should be at least 3 characters ");
          break;
        case 2:
          printf("Name should not begin with a apostrophe or a full point ");
          break;
        case 3:
          printf("Name should not contain any numbers or special chracters other than an apostrophe(') and a full point(.) ");
          break;
        case 4:
          printf("Invalid name ");
        }
        printf("Please enter the name again\n");
        scanf("%s", new_contact->name);
      }
      printf("Enter phone number ");
      scanf(" %[^\n]", new_contact->phone_num);
      flag = validate_phone_number(new_contact->phone_num);
      while (flag == 0)
      {
        printf("INVALID PHONE NUMBER. PLEASE ENTER A VALID PHONE NUMBER\n");
        scanf("%s", new_contact->phone_num);
        flag = validate_phone_number(new_contact->phone_num);
      }
      if (insert(root, new_contact->name, new_contact->phone_num))
      {
        write_to_file(new_contact);
      }
      else
      {
        return -2;
      }
    }
  }
  else
  {
    return -1; // memory could not be allocated
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

int check_dupilcate_contact_details(char *name, char *phone_num)
{
  int flag = 0;
  FILE *fp1;
  // open file here
  contact c;

  while (fread(&c, sizeof(c), 1, fp1) == 1)
  {
    // 	read each entry from the file to that contact ds, save in the trie[use the insert function already written]
  }
  /* Steps: make a function call
      open file and read from it
			create contact data structure
			check if any entry matches name and phone_num, if yes return and write apppropriate message in calling funtion

	*/
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
      sub = (i < 26) ? 65 : (i > 25 && i < 52) ? 71 : (i == 52 ? -20 : i == 53 ? -14 : -8);
      str[level] = i + sub;
      display(root->next[i], str, level + 1);
    }
  }
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

void write_to_file(contact *new) //function to write phone number to a file
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
