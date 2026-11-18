#include <stdio.h>
#include <string.h>

#define MAX 100

struct Book
{
    int id;
    char name[50];
    char author[50];
    char category[30];
    float price;
    int issued;
};

struct Book books[MAX];
int count = 0;

// Add New Book
void addBook()
{
    if(count >= MAX)
    {
        printf("Library is full!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &books[count].id);

    for(int i = 0; i < count; i++)
    {
        if(books[i].id == books[count].id)
        {
            printf("Book ID already exists!\n");
            return;
        }
    }

    printf("Enter Book Name: ");
    scanf(" %[^\n]", books[count].name);

    printf("Enter Author Name: ");
    scanf(" %[^\n]", books[count].author);

    printf("Enter Category: ");
    scanf(" %[^\n]", books[count].category);

    printf("Enter Price: ");
    scanf("%f", &books[count].price);

    books[count].issued = 0;

    count++;

    printf("Book added successfully!\n");
}

// Display All Books
void displayBooks()
{
    if(count == 0)
    {
        printf("No books available!\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        printf("\nBook ID: %d", books[i].id);
        printf("\nBook Name: %s", books[i].name);
        printf("\nAuthor: %s", books[i].author);
        printf("\nCategory: %s", books[i].category);
        printf("\nPrice: %.2f", books[i].price);

        if(books[i].issued == 1)
            printf("\nStatus: Issued\n");
        else
            printf("\nStatus: Available\n");
    }
}

// Search Book by ID
void searchByID()
{
    int id, found = 0;

    printf("Enter Book ID: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(books[i].id == id)
        {
            printf("\nBook Name: %s", books[i].name);
            printf("\nAuthor: %s", books[i].author);
            printf("\nCategory: %s\n", books[i].category);
            found = 1;
            break;
        }
    }

    if(found == 0)
        printf("Book not found!\n");
}

// Search Book by Name
void searchByName()
{
    char name[50];
    int found = 0;

    printf("Enter Book Name: ");
    scanf(" %[^\n]", name);

    for(int i = 0; i < count; i++)
    {
        if(strstr(books[i].name, name) != NULL)
        {
            printf("\nBook ID: %d", books[i].id);
            printf("\nBook Name: %s", books[i].name);
            printf("\nAuthor: %s\n", books[i].author);
            found = 1;
        }
    }

    if(found == 0)
        printf("Book not found!\n");
}

// Issue Book
void issueBook()
{
    int id, found = 0;

    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(books[i].id == id)
        {
            found = 1;

            if(books[i].issued == 0)
            {
                books[i].issued = 1;
                printf("Book issued successfully!\n");
            }
            else
            {
                printf("Book is already issued!\n");
            }
            break;
        }
    }

    if(found == 0)
        printf("Book not found!\n");
}

// Return Book
void returnBook()
{
    int id, found = 0;

    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(books[i].id == id)
        {
            found = 1;

            if(books[i].issued == 1)
            {
                books[i].issued = 0;
                printf("Book returned successfully!\n");
            }
            else
            {
                printf("Book was not issued!\n");
            }
            break;
        }
    }

    if(found == 0)
        printf("Book not found!\n");
}

// Update Book Details
void updateBook()
{
    int id, found = 0;

    printf("Enter Book ID to update: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(books[i].id == id)
        {
            printf("Enter New Book Name: ");
            scanf(" %[^\n]", books[i].name);

            printf("Enter New Author Name: ");
            scanf(" %[^\n]", books[i].author);

            printf("Enter New Category: ");
            scanf(" %[^\n]", books[i].category);

            printf("Enter New Price: ");
            scanf("%f", &books[i].price);

            printf("Book details updated successfully!\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
        printf("Book not found!\n");
}

// Count Total Books
void countBooks()
{
    printf("Total Books: %d\n", count);
}

// Display Available Books
void availableBooks()
{
    int found = 0;

    printf("\nAvailable Books:\n");

    for(int i = 0; i < count; i++)
    {
        if(books[i].issued == 0)
        {
            printf("\nBook ID: %d", books[i].id);
            printf("\nBook Name: %s\n", books[i].name);
            found = 1;
        }
    }

    if(found == 0)
        printf("No available books!\n");
}

// Main Function
int main()
{
    int choice;

    do
    {
        printf("\n========== LIBRARY MANAGEMENT SYSTEM ==========\n");

        printf("\n1. Add New Book");
        printf("\n2. Display All Books");
        printf("\n3. Search Book by ID");
        printf("\n4. Search Book by Name");
        printf("\n5. Issue Book");
        printf("\n6. Return Book");
        printf("\n7. Update Book Details");
        printf("\n8. Count Total Books");
        printf("\n9. Display Available Books");
        printf("\n10. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchByID();
                break;

            case 4:
                searchByName();
                break;

            case 5:
                issueBook();
                break;

            case 6:
                returnBook();
                break;

            case 7:
                updateBook();
                break;

            case 8:
                countBooks();
                break;

            case 9:
                availableBooks();
                break;

            case 10:
                printf("Thank you for using Library Management System!\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while(choice != 10);

    return 0;
}