#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

typedef struct Book
{
    char title[100];
    char author[100];
    char genre[50];
    int available;
} book;

// these are globals - if you're feeling up to it, use an array of pointers
// and practice your dynamic allocation instead!
book inventory[MAX_BOOKS];
int numBooks = 0;

int main()
{

    int choice;
    int len;

    while (1)
    {
        printf("\nBook Inventory Management System\n");
        printf("1. Add a new book\n");
        printf("2. Remove a book\n");
        printf("3. Display inventory\n");
        printf("4. Borrow a book\n");
        printf("5. Return a book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        // there will be a newline, so stripping it
        fgetc(stdin);

        switch (choice)
        {
        case 1:
            if (numBooks < MAX_BOOKS)
            {
                printf("Enter book title: ");
                fgets(inventory[numBooks].title, 100, stdin);
                // need to strip newlines
                len = strlen(inventory[numBooks].title);
                if (len > 0 && inventory[numBooks].title[len - 1] == '\n')
                {
                    inventory[numBooks].title[len - 1] = '\0';
                }

                printf("Enter book author: ");
                fgets(inventory[numBooks].author, 100, stdin);
                len = strlen(inventory[numBooks].author);
                if (len > 0 && inventory[numBooks].author[len - 1] == '\n')
                {
                    inventory[numBooks].author[len - 1] = '\0';
                }

                printf("Enter book genre: ");
                fgets(inventory[numBooks].genre, 50, stdin);
                len = strlen(inventory[numBooks].genre);
                if (len > 0 && inventory[numBooks].genre[len - 1] == '\n')
                {
                    inventory[numBooks].genre[len - 1] = '\0';
                }
                inventory[numBooks].available = 1;
                numBooks++;
            }
            else
            {
                printf("Maximum number of books reached!\n");
            }
            break;
        case 2:
            if (numBooks > 0)
            {
                char titleToRemove[100];
                printf("Enter the title of the book to remove: ");
                fgets(titleToRemove, 100, stdin);
                len = strlen(titleToRemove);
                if (len > 0 && titleToRemove[len - 1] == '\n')
                {
                    titleToRemove[len - 1] = '\0';
                }

                int found = 0;
                for (int i = 0; i < numBooks; i++)
                {
                    if (strcmp(inventory[i].title, titleToRemove) == 0)
                    {
                        for (int j = i; j < numBooks - 1; j++)
                        {
                            inventory[j] = inventory[j + 1];
                        }
                        numBooks--;
                        found = 1;
                        printf("Book removed successfully.\n");
                        break;
                    }
                }
                if (!found)
                {
                    printf("Book not found.\n");
                }
            }
            else
            {
                printf("Inventory is empty.\n");
            }
            break;
        case 3:
            printf("Inventory:\n");
            printf("Title\t\tAuthor\t\tGenre\t\tAvailable\n");
            for (int i = 0; i < numBooks; i++)
            {
                // using a ternary to print yes/no instead of 1/0
                // this is basically an if statement 'if inventory[i].available is 1, Yes, if 0, No
                printf("%s\t\t%s\t\t%s\t\t%s\n", inventory[i].title, inventory[i].author, inventory[i].genre,
                       inventory[i].available ? "Yes" : "No");
            }
            break;
        case 4:
        {
            char titleToBorrow[100];
            printf("Enter the title of the book to borrow: ");
            fgets(titleToBorrow, 100, stdin);
                len = strlen(titleToBorrow);
                if (len > 0 && titleToBorrow[len - 1] == '\n')
                {
                    titleToBorrow[len - 1] = '\0';
                }

            int found = 0;
            for (int i = 0; i < numBooks; i++)
            {
                if (strcmp(inventory[i].title, titleToBorrow) == 0)
                {
                    if (inventory[i].available)
                    {
                        inventory[i].available = 0;
                        printf("Book borrowed successfully.\n");
                    }
                    else
                    {
                        printf("Book is not available for borrowing.\n");
                    }
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                printf("Book not found.\n");
            }
            break;
        }
        case 5:
        {
            char titleToReturn[100];
            printf("Enter the title of the book to return: ");
            fgets(titleToReturn, 100, stdin);
                len = strlen(titleToReturn);
                if (len > 0 && titleToReturn[len - 1] == '\n')
                {
                    titleToReturn[len - 1] = '\0';
                }

            int found = 0;
            for (int i = 0; i < numBooks; i++)
            {
                if (strcmp(inventory[i].title, titleToReturn) == 0)
                {
                    if (!inventory[i].available)
                    {
                        inventory[i].available = 1;
                        printf("Book returned successfully.\n");
                    }
                    else
                    {
                        printf("Book is already available.\n");
                    }
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                printf("Book not found.\n");
            }
            break;
        }
        case 6:
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
