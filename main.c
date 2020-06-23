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

int main()
{
	printf("\n PHONE DIRECTORY\n");
	trie *phone_book;
	phone_book = (trie *)malloc(sizeof(trie));
	(phone_book)->isLeaf = 0;
	for (int i = 0; i < CHAR_SIZE; i++)
		(phone_book)->next[i] = NULL;
	menu(phone_book);
	return 0;
}

void menu(trie *phone_book)
{
	char str[20];
	int choice;
	do
	{
		printf("\n1 - ADD CONTACT\n2 - MODIFY CONTACT\n3 - DELETE CONTACT\n4 - SEARCH CONTACT\n5 - VIEW ALL CONTACTS\n6 - EXIT \n");
		printf("\nENTER YOUR CHOICE\n");
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
			break;
		case 6:

			display(phone_book, str, 0);
			printf("\nExiting...");
			break;
		default:
			printf("INVALID CHOICE\nPLEASE ENTER A VALID CHOICE FROM ABOVE MENU\n");
			break;
		}
	} while (choice != 6);
}