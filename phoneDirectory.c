// implementation file

#include "phoneDirectory.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int delete_by_number(char *number);
trie *delete_by_name(char *number, trie *);

int add_contact(trie *root)
{
  int flag = 0;
  contact new_contact;
  printf("\nEnter name :- ");
  scanf(" %[^\n]", new_contact.name);
  int x;
  while (x = validate_name(new_contact.name))
  {
    switch (x)
    {
    case 1:
      printf(YELLOW "Length of name should be at least 3 characters. " RESET);
      break;
    case 2:
      printf(YELLOW "Name should not begin with a apostrophe or a full point. " RESET);
      break;
    case 3:
      printf(YELLOW "Name should not contain any numbers or special chracters other than an apostrophe(') and a full point(.). " RESET);
      break;
    case 4:
      printf(YELLOW "Invalid name. " RESET);
      break;
    case 5:
      printf(YELLOW "Name already exists. \n" RESET);
    }
    printf(YELLOW "Please enter the name again :- " RESET);
    scanf("%s", new_contact.name);
  }
  printf("Enter phone number :- ");
  scanf(" %[^\n]", new_contact.phone_num);
  flag = validate_phone_number(new_contact.phone_num);
  while (flag == 0)
  {
    printf(YELLOW "INVALID PHONE NUMBER. PLEASE ENTER A VALID PHONE NUMBER :- " RESET);
    scanf("%s", new_contact.phone_num);
    flag = validate_phone_number(new_contact.phone_num);
  }
  if (insert_to_trie(root, new_contact.name, new_contact.phone_num))
  {
    if (write_to_file(new_contact) == 0)
      return 0; //success
  }
  else
  {
    return -1;
  }
}

int insert_to_trie(trie *root, char *name, char *phone_num)
{
  trie *curr = root;
  int sub;
  char ch;
  while (*name) //iterate over each character in the name to insert in the trie
  {
    ch = *name;
    sub = IS_UPPER_CASE(ch) ? 65 : (IS_LOWER_CASE(ch) ? 71 : (IS_SPACE(ch) ? -20 : IS_APOSTROPHE(ch) ? -14 : -8));
    if (curr->next[ch - sub] == NULL)
    {
      curr->next[ch - sub] = (trie *)malloc(sizeof(trie)); //set the node
      if (!curr->next[ch - sub])
        return 0;
      (curr->next[ch - sub])->isLeaf = 0;
      for (int i = 0; i < CHAR_SIZE; i++) //set all next nodes to NULL
        (curr->next[ch - sub])->next[i] = NULL;
    }
    curr = curr->next[ch - sub];
    name++; //move to next char in name
  }
  curr->isLeaf = 1; // indicates end
  strcpy(curr->phone_number[0], phone_num);
  return 1;
}

int modify_contact(trie *root)
{
  //todo
}

trie *delete_contact(trie *phone_book)
{
  trie *temp;
  int option, found = 0;
  char number[10], name[50];
  do
  {
    printf("\n\tCHOOSE OPTION FROM MENU\t\n");
    printf("\n1 - DELETE BY NUMBER\n2 - DELETE BY NAME\n3 - EXIT\nENTER THE CHOICE\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      printf("ENTER THE CONTACT NUMBER YOU WANT TO DELETE\n");
      scanf("%s", number);
      if (delete_by_number(number) == 0)
        printf("\nCONTACT DELETED SUCCESSFULY\n");
      break;

    case 2:
      printf("ENTER THE CONTACT NAME YOU WANT TO DELETE\n");
      scanf("%s", name);
      if (temp = delete_by_name(name, phone_book))
        printf("\nCONTACT DELETED SUCCESSFULY\n");
      break;

    case 3:
      // menu();
      break;

    default:
      printf(YELLOW "INVALID CHOICE\nPLEASE ENTER A VALID CHOICE FROM ABOVE MENU\n" RESET);
      break;
    }

  } while (option != 3);
  return temp;
}

int search_contact(trie *phone_book, char *search_str)
{
  int sub;
  char ch, temp[20];
  strcpy(temp, search_str);
  if (phone_book == NULL) //if trie is empty
    return 0;
  trie *curr = phone_book;
  while (*search_str)
  {
    ch = *search_str;
    sub = IS_UPPER_CASE(ch) ? 65 : (IS_LOWER_CASE(ch) ? 71 : (IS_SPACE(ch) ? -20 : IS_APOSTROPHE(ch) ? -14 : -8));
    curr = curr->next[*search_str - sub]; // go to next node
    if (curr == NULL)                     //if string is invalid
      return 0;
    search_str++; //move to next character
  }
  display(curr, temp, strlen(temp)); // temp holds the value of search string, display function makes a call using the last pointer in the search string
  return 1;                          //if current node is leaf & we have reached the end of the string, return 1
}

void display(trie *root, char *str, int level)
{
  if (root->isLeaf == 1)
  {
    str[level] = '\0';
    printf("\n%-25s %-10s", str, root->phone_number[0]);
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

int write_to_file(contact new) //function to write phone number to a file
{
  int flag = 1;
  FILE *fp;
  fp = fopen("phone_number.dat", "ab");
  if (fp == NULL)
  {
    printf(YELLOW "Cannot open file\n  " RESET);
    return flag;
  }
  int record_added = fwrite(&new, sizeof(new), 1, fp);
  if (record_added)
    flag = 0;
  fclose(fp);
  return flag;
}

int delete_by_number(char *number)
{
  trie *phone_book;
  printf("num=%s", number);
  FILE *fp, *fp1;
  fp = fopen("phone_number.dat", "rb+");
  if (fp == NULL)
  {
    printf(YELLOW "\n File cannot be opened\n" RESET);
    exit(0);
  }

  fp1 = fopen("dumy.dat", "wb");
  if (fp1 == NULL)
  {
    printf(YELLOW "\n File cannot be opened\n" RESET);
    exit(0);
  }

  contact c;
  while (fread(&c, sizeof(c), 1, fp) == 1)
  {
    printf("%s\t%s\n", c.name, c.phone_num);
    if (strcmp(number, c.phone_num) != 0)
    {
      fwrite(&c, sizeof(c), 1, fp1);
    }
  }

  fclose(fp);
  fclose(fp1);
  fp1 = fopen("dumy.dat", "rb");
  if (fp1 == NULL)
  {
    printf(YELLOW "\n File cannot be opened\n" RESET);
    exit(0);
  }

  fp = fopen("phone_number.dat", "wb+");
  if (fp == NULL)
  {
    printf(YELLOW "\n File cannot be opened\n" RESET);
    exit(0);
  }

  while (fread(&c, sizeof(c), 1, fp1) == 1)
  {
    printf("in while dumy\n");
    printf("%s\t%s\n", c.name, c.phone_num);
    fwrite(&c, sizeof(c), 1, fp);
  }
  fclose(fp);
  fclose(fp1);
}

trie *delete_by_name(char *name, trie *phone_book)
{
  FILE *fp, *fp1;
  fp = fopen("phone_number.dat", "rb+");
  if (fp == NULL)
  {
    printf(YELLOW "\n File cannot be opened\n" RESET);
    exit(0);
  }

  fp1 = fopen("dumy.dat", "wb");
  if (fp1 == NULL)
  {
    printf(YELLOW "\n File cannot be opened\n" RESET);
    exit(0);
  }

  contact c;
  while (fread(&c, sizeof(c), 1, fp) == 1)
  {
    if (strcmp(name, c.name) != 0)
    {
      fwrite(&c, sizeof(c), 1, fp1);
    }
  }

  fclose(fp);
  fclose(fp1);
  fp1 = fopen("dumy.dat", "rb");
  if (fp1 == NULL)
  {
    printf(YELLOW "\n File cannot be opened\n" RESET);
    exit(0);
  }

  fp = fopen("phone_number.dat", "wb+");
  if (fp == NULL)
  {
    printf(YELLOW "\n File cannot be opened\n" RESET);
    exit(0);
  }

  while (fread(&c, sizeof(c), 1, fp1) == 1)
  {
    // printf("in while dumy\n");
    // printf("%s\t%s\n", c.name, c.phone_num);
    fwrite(&c, sizeof(c), 1, fp);
  }

  phone_book = (trie *)malloc(sizeof(trie));
  (phone_book)->isLeaf = 0;
  for (int i = 0; i < CHAR_SIZE; i++)
    (phone_book)->next[i] = NULL;
  fclose(fp);
  fclose(fp1);
  return phone_book;
}

void read_from_file(trie *root) //stores the existing (older) contacts to the trie
{
  FILE *fp;
  fp = fopen("phone_number.dat", "rb+");
  if (fp == NULL)
  {
    printf(YELLOW "\n File cannot be opened\n" RESET);
    return;
  }
  contact c;
  while (fread(&c, sizeof(c), 1, fp) == 1)
  {
    insert_to_trie(root, c.name, c.phone_num);
  }
  fclose(fp);
}