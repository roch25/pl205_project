// implementation file

#include "phoneDirectory.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

trie *delete_by(char *name, trie *phone_book, char *value);

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
    return -1; // probelem inserting in trie
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

trie *modify_contact(trie *phone_book)
{
  trie *temp = NULL;
  int option, found = 0, token, search_res;
  char number[12], name[25];
  do
  {
    printf("\n\nCHOOSE OPTION FROM MENU\t\n");
    printf("\n1 - Modify by name\n2 - Modify by phone number \n3 - Go back \nEnter the choice:- \n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      token = 0;
      printf("Enter the contact name you want to modify in phonebook:- \n");
      scanf(" %[^\n]", name);
      search_res = search_contact(phone_book, name);
      while (search_res > 1)
      {
        printf("\nENTER THE CONTACT NAME YOU WANT TO MODIFY\n");
        scanf(" %[^\n]", name);
        search_res = search_contact(phone_book, name);
      }
      temp = delete_by(name, phone_book, "name");
      if (temp != NULL)
      {
        printf(GREEN "\nName exists!! Kindly re-enter the details to modify the contact:- \n" RESET);
        if (add_contact(phone_book) == 0)
          printf(GREEN "\nContact details updated succesfully!\n" RESET);
        else
          printf(YELLOW "There was a problem updating the contact to the directory" RESET);
      }
      else
        printf(YELLOW "Sorry! Contact with this name does not exist. Please try again.\n" RESET);
      break;

    case 2:
      printf("Enter the contact number you want to modify in phonebook:- \n");
      scanf(" %[^\n]", number);
      temp = delete_by(number, phone_book, "number");
      if (temp != NULL)
      {
        printf(GREEN "Phone number exists!! Kindly re-enter the details to modify the contact:- \n" RESET);
        if (add_contact(phone_book) == 0)
          printf(GREEN "\nContact details updated succesfully!\n" RESET);
        else
          printf(YELLOW "There was a problem updating the contact to the directory" RESET);
      }
      else
        printf(YELLOW "Sorry! Contact with this phone number does not exist. Please try again.\n" RESET);
      break;
    case 3:
      if (temp == NULL)
        temp = phone_book;
      break;
    default:
      printf(YELLOW "INVALID CHOICE\nPLEASE ENTER A VALID CHOICE FROM ABOVE MENU\n" RESET);
      break;
    }
  } while (option != 3);
  return temp;
}

trie *delete_contact(trie *phone_book)
{
  trie *temp = NULL;
  int option, found = 0, token, search_res;
  char number[12], name[25];
  do
  {
    printf("\n\nCHOOSE OPTION FROM MENU\t\n");
    printf("\n1 - DELETE BY NAME\n2 - DELETE BY NUMBER\n3 - GO BACK\nENTER THE CHOICE\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      token = 0;
      printf("ENTER THE CONTACT NAME YOU WANT TO DELETE\n");
      scanf(" %[^\n]", name);
      search_res = search_contact(phone_book, name);
      while (search_res > 1)
      {
        printf("\nENTER THE CONTACT NAME YOU WANT TO DELETE\n");
        scanf(" %[^\n]", name);
        search_res = search_contact(phone_book, name);
      }
      temp = delete_by(name, phone_book, "name");
      if (temp != NULL)
        printf(GREEN "\n\nCONTACT DELETED SUCCESSFULY\n" RESET);
      else
        printf(YELLOW "CONTACT NOT FOUND" RESET);
      break;
    case 2:
      printf("ENTER THE CONTACT NUMBER YOU WANT TO DELETE\n");
      scanf(" %[^\n]", number);
      temp = delete_by(number, phone_book, "number");
      if (temp != NULL)
        printf(GREEN "\nCONTACT DELETED SUCCESSFULY\n" RESET);
      else
        printf(YELLOW "CONTACT NOT FOUND" RESET);
      break;
    case 3:
      if (temp == NULL)
        temp = phone_book;
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
  int sub, token = 0;
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
      return -1;
    search_str++; //move to next character
  }
  display(curr, temp, strlen(temp), &token); // temp holds the value of search string, display function makes a call using the last pointer in the search string
  return token;                              //if current node is leaf & we have reached the end of the string, return 1
}

void display(trie *root, char *str, int level, int *token)
{
  if (root->isLeaf == 1)
  {
    (*token)++;
    str[level] = '\0';
    printf("\n%-25s %-10s", str, root->phone_number[0]);
  }
  int i, sub;
  char ch;
  for (i = 0; i < CHAR_SIZE; i++)
    if (root->next[i])
    {
      sub = (i < 26) ? 65 : (i > 25 && i < 52) ? 71 : (i == 52 ? -20 : i == 53 ? -14 : -8);
      str[level] = i + sub;
      display(root->next[i], str, level + 1, token);
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

trie *delete_by(char *name, trie *phone_book, char *value)
{
  FILE *fp, *fp1;
  int flag = 0;
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
    if (!strcmp(value, "name"))
    {
      if (strcmp(name, c.name) != 0)
        fwrite(&c, sizeof(c), 1, fp1);
      else
        flag = 1;
    }
    else
    {
      if (strcmp(name, c.phone_num) != 0)
        fwrite(&c, sizeof(c), 1, fp1);
      else
        flag = 1;
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
    fwrite(&c, sizeof(c), 1, fp);
  }
  if (flag)
  {
    phone_book = (trie *)malloc(sizeof(trie));
    (phone_book)->isLeaf = 0;
    for (int i = 0; i < CHAR_SIZE; i++)
      (phone_book)->next[i] = NULL;
  }
  else
    phone_book = NULL;
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
