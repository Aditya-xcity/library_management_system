#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define MAX_USERS 50
#define FILENAME_BOOKS "library_books.txt"
#define FILENAME_USERS "library_users.txt"
#define FILENAME_ISSUES "book_issues.txt"

typedef struct {
    int id;
    char title[100];
    char author[50];
    int quantity;
    int available;
} Book;

typedef struct {
    int id;
    char name[50];
    char email[50];
} User;

typedef struct {
    int book_id;
    int user_id;
    char issue_date[20];
    char return_date[20];
} BookIssue;

Book books[MAX_BOOKS];
User users[MAX_USERS];
BookIssue issues[MAX_BOOKS];

int book_count = 0;
int user_count = 0;
int issue_count = 0;

void load_data();
void save_data();
void main_menu();
void book_management();
void user_management();
void issue_management();
void add_book();
void view_books();
void search_book();
void update_book();
void delete_book();
void add_user();
void view_users();
void issue_book();
void return_book();
void view_issues();

int main() {
    /* Aditya Bhardwaj - main start */
    load_data();
    main_menu();
    return 0;
    /* Aditya Bhardwaj - main end */
}

void load_data() {
    /* Aditya Bhardwaj - load_data start */
    FILE *file = fopen(FILENAME_BOOKS, "r");
    if (file != NULL) {
        while (fscanf(file, "%d,%[^,],%[^,],%d,%d\n", 
                      &books[book_count].id, books[book_count].title, 
                      books[book_count].author, &books[book_count].quantity, 
                      &books[book_count].available) != EOF) {
            book_count++;
        }
        fclose(file);
    }

    file = fopen(FILENAME_USERS, "r");
    if (file != NULL) {
        while (fscanf(file, "%d,%[^,],%[^\n]\n", 
                      &users[user_count].id, users[user_count].name, 
                      users[user_count].email) != EOF) {
            user_count++;
        }
        fclose(file);
    }

    file = fopen(FILENAME_ISSUES, "r");
    if (file != NULL) {
        while (fscanf(file, "%d,%d,%[^,],%[^\n]\n", 
                      &issues[issue_count].book_id, &issues[issue_count].user_id, 
                      issues[issue_count].issue_date, issues[issue_count].return_date) != EOF) {
            issue_count++;
        }
        fclose(file);
    }
    /* Aditya Bhardwaj - load_data end */
}

void save_data() {
    /* Aditya Bhardwaj - save_data start */
    FILE *file = fopen(FILENAME_BOOKS, "w");
    if (file != NULL) {
        for (int i = 0; i < book_count; i++) {
            fprintf(file, "%d,%s,%s,%d,%d\n", 
                    books[i].id, books[i].title, books[i].author, 
                    books[i].quantity, books[i].available);
        }
        fclose(file);
    }

    file = fopen(FILENAME_USERS, "w");
    if (file != NULL) {
        for (int i = 0; i < user_count; i++) {
            fprintf(file, "%d,%s,%s\n", 
                    users[i].id, users[i].name, users[i].email);
        }
        fclose(file);
    }

    file = fopen(FILENAME_ISSUES, "w");
    if (file != NULL) {
        for (int i = 0; i < issue_count; i++) {
            fprintf(file, "%d,%d,%s,%s\n", 
                    issues[i].book_id, issues[i].user_id, 
                    issues[i].issue_date, issues[i].return_date);
        }
        fclose(file);
    }
    /* Aditya Bhardwaj - save_data end */
}

void main_menu() {
    /* Aditya Bhardwaj - main_menu start */
    int choice;
    do {
        printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
        printf("1. Book Management\n");
        printf("2. User Management\n");
        printf("3. Issue/Return Management\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                book_management();
                break;
            case 2:
                user_management();
                break;
            case 3:
                issue_management();
                break;
            case 4:
                save_data();
                printf("Data saved successfully. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    /* Aditya Bhardwaj - main_menu end */
}

void book_management() {
    /* Aditya Bhardwaj - book_management start */
    int choice;
    do {
        printf("\n===== BOOK MANAGEMENT =====\n");
        printf("1. Add Book\n");
        printf("2. View All Books\n");
        printf("3. Search Book\n");
        printf("4. Update Book\n");
        printf("5. Delete Book\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                view_books();
                break;
            case 3:
                search_book();
                break;
            case 4:
                update_book();
                break;
            case 5:
                delete_book();
                break;
            case 6:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    /* Aditya Bhardwaj - book_management end */
}

void add_book() {
    /* Aditya Bhardwaj - add_book start */
    if (book_count >= MAX_BOOKS) {
        printf("Maximum book capacity reached!\n");
        return;
    }
    
    Book new_book;
    printf("\nEnter Book ID: ");
    scanf("%d", &new_book.id);
    
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == new_book.id) {
            printf("Book ID already exists!\n");
            return;
        }
    }
    
    printf("Enter Book Title: ");
    scanf(" %[^\n]", new_book.title);
    printf("Enter Author: ");
    scanf(" %[^\n]", new_book.author);
    printf("Enter Quantity: ");
    scanf("%d", &new_book.quantity);
    new_book.available = new_book.quantity;
    
    books[book_count++] = new_book;
    printf("Book added successfully!\n");
    save_data();
    /* Aditya Bhardwaj - add_book end */
}

void view_books() {
    /* Aditya Bhardwaj - view_books start */
    if (book_count == 0) {
        printf("No books available in the library.\n");
        return;
    }
    
    printf("\n===== BOOK LIST =====\n");
    printf("%-5s %-30s %-20s %-10s %-10s\n", "ID", "Title", "Author", "Quantity", "Available");
    for (int i = 0; i < book_count; i++) {
        printf("%-5d %-30s %-20s %-10d %-10d\n", 
               books[i].id, books[i].title, books[i].author, 
               books[i].quantity, books[i].available);
    }
    /* Aditya Bhardwaj - view_books end */
}

void search_book() {
    /* Aditya Bhardwaj - search_book start */
    if (book_count == 0) {
        printf("No books available in the library.\n");
        return;
    }
    
    int choice;
    printf("\n===== SEARCH BOOK =====\n");
    printf("1. Search by ID\n");
    printf("2. Search by Title\n");
    printf("3. Search by Author\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        int id;
        printf("Enter Book ID: ");
        scanf("%d", &id);
        
        for (int i = 0; i < book_count; i++) {
            if (books[i].id == id) {
                printf("\nBook Found:\n");
                printf("ID: %d\n", books[i].id);
                printf("Title: %s\n", books[i].title);
                printf("Author: %s\n", books[i].author);
                printf("Quantity: %d\n", books[i].quantity);
                printf("Available: %d\n", books[i].available);
                return;
            }
        }
        printf("Book not found with ID %d\n", id);
    } 
    else if (choice == 2) {
        char title[100];
        printf("Enter Book Title: ");
        scanf(" %[^\n]", title);
        
        printf("\nSearch Results:\n");
        int found = 0;
        for (int i = 0; i < book_count; i++) {
            if (strstr(books[i].title, title) != NULL) {
                printf("%d. %s by %s (Available: %d)\n", 
                       books[i].id, books[i].title, books[i].author, books[i].available);
                found = 1;
            }
        }
        if (!found) {
            printf("No books found with title containing '%s'\n", title);
        }
    } 
    else if (choice == 3) {
        char author[50];
        printf("Enter Author Name: ");
        scanf(" %[^\n]", author);
        
        printf("\nSearch Results:\n");
        int found = 0;
        for (int i = 0; i < book_count; i++) {
            if (strstr(books[i].author, author) != NULL) {
                printf("%d. %s by %s (Available: %d)\n", 
                       books[i].id, books[i].title, books[i].author, books[i].available);
                found = 1;
            }
        }
        if (!found) {
            printf("No books found by author '%s'\n", author);
        }
    } 
    else {
        printf("Invalid choice.\n");
    }
    /* Aditya Bhardwaj - search_book end */
}

void update_book() {
    /* Aditya Bhardwaj - update_book start */
    if (book_count == 0) {
        printf("No books available to update.\n");
        return;
    }
    
    int id;
    printf("Enter Book ID to update: ");
    scanf("%d", &id);
    
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            printf("\nCurrent Book Details:\n");
            printf("ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Quantity: %d\n", books[i].quantity);
            printf("Available: %d\n", books[i].available);
            
            printf("\nEnter new details (leave blank to keep current):\n");
            
            char new_title[100];
            printf("New Title: ");
            scanf(" %[^\n]", new_title);
            if (strlen(new_title) > 0) {
                strcpy(books[i].title, new_title);
            }
            
            char new_author[50];
            printf("New Author: ");
            scanf(" %[^\n]", new_author);
            if (strlen(new_author) > 0) {
                strcpy(books[i].author, new_author);
            }
            
            char quantity_str[10];
            printf("New Quantity: ");
            scanf(" %[^\n]", quantity_str);
            if (strlen(quantity_str) > 0) {
                int new_quantity = atoi(quantity_str);
                int difference = new_quantity - books[i].quantity;
                books[i].quantity = new_quantity;
                books[i].available += difference;
            }
            
            printf("Book updated successfully!\n");
            save_data();
            return;
        }
    }
    printf("Book not found with ID %d\n", id);
    /* Aditya Bhardwaj - update_book end */
}

void delete_book() {
    /* Aditya Bhardwaj - delete_book start */
    if (book_count == 0) {
        printf("No books available to delete.\n");
        return;
    }
    
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);
    
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            if (books[i].available < books[i].quantity) {
                printf("Cannot delete book. Some copies are still issued.\n");
                return;
            }
            
            for (int j = i; j < book_count - 1; j++) {
                books[j] = books[j + 1];
            }
            book_count--;
            printf("Book deleted successfully!\n");
            save_data();
            return;
        }
    }
    printf("Book not found with ID %d\n", id);
    /* Aditya Bhardwaj - delete_book end */
}

void user_management() {
    /* Aditya Bhardwaj - user_management start */
    int choice;
    do {
        printf("\n===== USER MANAGEMENT =====\n");
        printf("1. Add User\n");
        printf("2. View All Users\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_user();
                break;
            case 2:
                view_users();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    /* Aditya Bhardwaj - user_management end */
}

void add_user() {
    /* Aditya Bhardwaj - add_user start */
    if (user_count >= MAX_USERS) {
        printf("Maximum user capacity reached!\n");
        return;
    }
    
    User new_user;
    printf("\nEnter User ID: ");
    scanf("%d", &new_user.id);
    
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == new_user.id) {
            printf("User ID already exists!\n");
            return;
        }
    }
    
    printf("Enter User Name: ");
    scanf(" %[^\n]", new_user.name);
    printf("Enter Email: ");
    scanf(" %[^\n]", new_user.email);
    
    users[user_count++] = new_user;
    printf("User added successfully!\n");
    save_data();
    /* Aditya Bhardwaj - add_user end */
}

void view_users() {
    /* Aditya Bhardwaj - view_users start */
    if (user_count == 0) {
        printf("No users registered.\n");
        return;
    }
    
    printf("\n===== USER LIST =====\n");
    printf("%-5s %-20s %-30s\n", "ID", "Name", "Email");
    for (int i = 0; i < user_count; i++) {
        printf("%-5d %-20s %-30s\n", users[i].id, users[i].name, users[i].email);
    }
    /* Aditya Bhardwaj - view_users end */
}

void issue_management() {
    /* Aditya Bhardwaj - issue_management start */
    int choice;
    do {
        printf("\n===== ISSUE/RETURN MANAGEMENT =====\n");
        printf("1. Issue Book\n");
        printf("2. Return Book\n");
        printf("3. View All Issues\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                issue_book();
                break;
            case 2:
                return_book();
                break;
            case 3:
                view_issues();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    /* Aditya Bhardwaj - issue_management end */
}

void issue_book() {
    /* Aditya Bhardwaj - issue_book start */
    if (book_count == 0 || user_count == 0) {
        printf("Cannot issue books. Either no books or no users available.\n");
        return;
    }
    
    int book_id, user_id;
    printf("\nEnter Book ID to issue: ");
    scanf("%d", &book_id);
    
    int book_index = -1;
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == book_id) {
            book_index = i;
            break;
        }
    }
    
    if (book_index == -1) {
        printf("Book not found with ID %d\n", book_id);
        return;
    }
    
    if (books[book_index].available <= 0) {
        printf("No copies of this book are currently available.\n");
        return;
    }
    
    printf("Enter User ID: ");
    scanf("%d", &user_id);
    
    int user_index = -1;
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == user_id) {
            user_index = i;
            break;
        }
    }
    
    if (user_index == -1) {
        printf("User not found with ID %d\n", user_id);
        return;
    }
    
    for (int i = 0; i < issue_count; i++) {
        if (issues[i].book_id == book_id && issues[i].user_id == user_id && 
            strcmp(issues[i].return_date, "Not Returned") == 0) {
            printf("This user already has this book issued.\n");
            return;
        }
    }
    
    char issue_date[20];
    printf("Enter Issue Date (DD-MM-YYYY): ");
    scanf("%s", issue_date);
    
    issues[issue_count].book_id = book_id;
    issues[issue_count].user_id = user_id;
    strcpy(issues[issue_count].issue_date, issue_date);
    strcpy(issues[issue_count].return_date, "Not Returned");
    issue_count++;
    
    books[book_index].available--;
    
    printf("Book issued successfully!\n");
    save_data();
    /* Aditya Bhardwaj - issue_book end */
}

void return_book() {
    /* Aditya Bhardwaj - return_book start */
    if (issue_count == 0) {
        printf("No books currently issued.\n");
        return;
    }
    
    int book_id, user_id;
    printf("\nEnter Book ID to return: ");
    scanf("%d", &book_id);
    printf("Enter User ID: ");
    scanf("%d", &user_id);
    
    int issue_index = -1;
    for (int i = 0; i < issue_count; i++) {
        if (issues[i].book_id == book_id && issues[i].user_id == user_id && 
            strcmp(issues[i].return_date, "Not Returned") == 0) {
            issue_index = i;
            break;
        }
    }
    
    if (issue_index == -1) {
        printf("No active issue found for this book and user.\n");
        return;
    }
    
    char return_date[20];
    printf("Enter Return Date (DD-MM-YYYY): ");
    scanf("%s", return_date);
    
    strcpy(issues[issue_index].return_date, return_date);
    
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == book_id) {
            books[i].available++;
            break;
        }
    }
    
    printf("Book returned successfully!\n");
    save_data();
    /* Aditya Bhardwaj - return_book end */
}

void view_issues() {
    /* Aditya Bhardwaj - view_issues start */
    if (issue_count == 0) {
        printf("No book issues recorded.\n");
        return;
    }
    
    printf("\n===== BOOK ISSUES =====\n");
    printf("%-5s %-30s %-20s %-15s %-15s\n", 
           "ID", "Book Title", "User Name", "Issue Date", "Return Date");
    
    for (int i = 0; i < issue_count; i++) {
        char book_title[100] = "Unknown";
        for (int j = 0; j < book_count; j++) {
            if (books[j].id == issues[i].book_id) {
                strcpy(book_title, books[j].title);
                break;
            }
        }
        
        char user_name[50] = "Unknown";
        for (int j = 0; j < user_count; j++) {
            if (users[j].id == issues[i].user_id) {
                strcpy(user_name, users[j].name);
                break;
            }
        }
        
        printf("%-5d %-30s %-20s %-15s %-15s\n", 
               i+1, book_title, user_name, 
               issues[i].issue_date, issues[i].return_date);
    }
    /* Aditya Bhardwaj - view_issues end */
}