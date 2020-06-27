/* PL205 Lab Project
	Contributors:
		1904, Shruti Dalvi
		1929, Chetana Marathe
		1930, Rochelle Martins
	Description: Phone directory using Trie data structure.
*/

#include <stdio.h>
#include <stdlib.h>
#include "phoneDirectory.h"

void menu(trie *);
void read_from_file(trie *);

int main()
{
	printf(" -------------------------------");
	printf("\n|\tPHONE DIRECTORY         |\n");
	printf(" -------------------------------");

	trie *phone_book;
	phone_book = (trie *)malloc(sizeof(trie));
	(phone_book)->isLeaf = 0;
	for (int i = 0; i < CHAR_SIZE; i++)
		(phone_book)->next[i] = NULL;
	read_from_file(phone_book);

	menu(phone_book);
	return 0;
}

void menu(trie *phone_book)
{
	char str[20], search_str[12];
	int choice;
	do
	{
		printf("\n\n1 - ADD CONTACT\n2 - MODIFY CONTACT\n3 - DELETE CONTACT\n4 - SEARCH CONTACT\n5 - VIEW ALL CONTACTS\n6 - EXIT \n");
		printf("\nENTER YOUR CHOICE :\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			if (add_contact(phone_book) == 0)
				printf(GREEN "\n\nContact details added succesfully!\n" RESET);
			else
				printf(YELLOW "There was a problem adding the contact to the directory" RESET);
			break;
		case 2:
			modify_contact(phone_book);
			break;
		case 3:
			delete_contact(phone_book);
			break;
		case 4:
			printf("Enter name of the contact you want to search:- ");
			scanf(" %[^\n]", search_str);
			search_contact(phone_book, search_str);
			break;
		case 5:
			printf("--------------Contacts-----------------\n");
			printf("%-25s %-10s\n", "Name", "Phone Number");
			printf("---------------------------------------\n");
			display(phone_book, str, 0);
			break;
		case 6:
			printf("\nExiting...");
			break;
		default:
			printf(YELLOW "INVALID CHOICE\nPLEASE ENTER A VALID CHOICE FROM ABOVE MENU\n" RESET);
			break;
		}
	} while (choice != 6);
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
