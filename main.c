/* PL205 project
  Authors: 1904 Shruti  Dalvi
           1929   Chetana Marathe
           1930  Rochelle Martins
 Description: Phone directory using Trie data structure.
*/

#include <stdio.h>
#include "phone_directory.h"
int main()
{
        printf("\n PHONE DIRECTORY\n");

        int choice;

        do
        {
                printf("1 - ADD CONTACT\n2 - MODIFY CONTACT\n3 - DELETE CONTACT\n4 - SEARCH CONTACT\n5 - VIEW ALL CONTACTS\n6 - EXIT \n");

                printf("\nENTER YOUR CHOICE\n");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
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
                        break;

                default:
                        printf("INVALID CHOICE\nPLEASE ENTER A VALID CHOICE FROM ABOVE MENU\n");
                        break;
                }
        } while (choice != 6);
        return 0;
}
