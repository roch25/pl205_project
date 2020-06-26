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
#define RED "\x1b[31m"		//Error messages
#define RESET "\x1b[0m"		//reset to white
#define BLUE "\x1b[37m"		//Normal messages
#define YELLOW "\x1b[33m" //warring messages

void menu(trie *);
void read_from_file(trie *);

int main()
{
	printf("\n PHONE DIRECTORY\n");
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
	char str[20];
	int choice;
	do
	{
		printf(BLUE "\n1 - ADD CONTACT\n2 - MODIFY CONTACT\n3 - DELETE CONTACT\n4 - SEARCH CONTACT\n5 - VIEW ALL CONTACTS\n6 - EXIT \n" RESET);
		printf(BLUE "\nENTER YOUR CHOICE\n" RESET);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			add_contact(phone_book);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			display(phone_book, str, 0);
			break;
		case 6:
			printf(YELLOW "\nExiting..." RESET);
			break;
		default:
			printf(RED "INVALID CHOICE\nPLEASE ENTER A VALID CHOICE FROM ABOVE MENU\n" RESET);
			break;
		}
	} while (choice != 6);
}

void read_from_file(trie *root)
{
	FILE *fp;
	// do this+ open file
	fp = fopen("phone_number.dat", "rb+");
	if (fp == NULL)
	{
		printf(RED "\n File cannot be opened\n" RESET);
		exit(0);
	}
	contact c;
	// while (fread(&c, sizeof(c), 1, fp) == 1)
	// {
	// 	// 	read each entry from the file to that contact ds, save in the trie[use the insert function already written]
	// }
}
