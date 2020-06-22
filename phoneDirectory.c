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
    printf("\nEnter name ");
    fseek(stdin, 0, SEEK_END);
    scanf(" %[^\n]", name);
    while (validate_name(name))
    {
      printf("Invalid name. Length of name should be at least 3 characters and should not contain any numbers or special chracters other than an apostrophe(') and a full point(.) Please enter the name again\n");
      scanf("%s", name);
    }

    //insert in trie, here
    new_contact->name = (trie *)malloc(sizeof(trie));
    (new_contact->name)->isLeaf = 0;
    for (int i = 0; i < CHAR_SIZE; i++)
      (new_contact->name)->next[i] = NULL;
    insert((new_contact->name), name);

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
    	 check_phone_number(value);
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

int insert(trie *root, char *name)
{
  trie *curr = root;
  int sub;
  while (*name) //iterate over each character in the name to insert in the trie
  {
    // if (*name > 65 && *name < 92)
    //   sub = 70;
    // else if (*name > 65 && *name < 92)
    //   sub = 65;
    // else if (*name == 32)
    //   sub = -21; // map to 53
    // else if (*name == 39)
    //   sub = -14;
    // else
    //   sub = -9;
    // next line is equivalent to the commented code above
    sub = (*name > 64 && *name < 92) ? 65 : ((*name > 96 && *name < 123) ? 70 : ((*name == 32) ? -21 : (*name == 39) ? -15 : -9));
    if (curr->next[*name - sub] == NULL)
      curr->next[*name - sub] = (trie *)malloc(sizeof(trie)); //set the node
    (curr->next[*name - sub])->isLeaf = 0;
    for (int i = 0; i < CHAR_SIZE; i++) //set all next nodes to NULL
      (curr->next[*name - sub])->next[i] = NULL;
    curr = curr->next[*name - sub];
    name++; //move to next char in name
  }
  curr->isLeaf = 1; // indicates end
}

int check_phone_number(contact *new)            //function to check if phone number is identical
{
	int flag=0;
	FILE *fp1;
	fp1 = fopen("phone_number.txt","r");
	if (fp1 == NULL)
	{
	  printf("Cannot open file\n");
	  exit(0);
	}
	else
	{
	int val;
	while(fscanf(fp1,"%s \n",new->phone_number[0])!=EOF)
	{
	val=strcmp(new->phone_number[0],new);
		if(val==0)
		{	 printf("PHONE NUMBER ALREADY EXIST. PLEASE ENTER A VALID PHONE NUMBER\n");
			while (flag == 0)
			{
			     
			      scanf("%s", new->phone_number[0]);
			      flag = validate_phone_number(new->phone_number[0]);
			      write_to_file(new);
			}
		}
		
	}
	}

	fclose(fp1);
}
