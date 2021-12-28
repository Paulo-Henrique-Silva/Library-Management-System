//this was made by: Paulo
//github: Paulo-Henrique-Silva 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_PWD "2021\n"
#define ADMIN_FPATH "adm.txt"
#define RENTS_FPATH "rents.txt"
#define ACCOUNTS_FPATH "account.txt"
#define BOOKS_FPATH "books.txt"
#define MAX_PWDSIZE sizeof(DEFAULT_PWD)

int menu();

void addRent(void);
void removeRent(void);
void showRent(void);
void addAccounts(void);
void removeAccounts(void);
void showAccounts(void);
void addBooks(void);
void removeBooks(void);
void showBooks(void);
void changePwd(void);

int checkFiles(void);
int checkPwd(char strTo_cmp[]);
char *removeSpecial_chars(char string[]);

enum menuOperations
{
    newRent = 1, RemoveRent, ShowRent,
    newAccounts, RemoveAccounts, ShowAccounts,
    newBooks, RemoveBooks, ShowBooks,
    ChangePassword, ExitProgram
};

FILE 
*pAdmin, 
*pRents,
*pAccounts,
*pBooks; 

typedef struct booksInfo
{
    char 
    title[40], 
    author[40],
    genres[15],
    date[12];

    float rentValue_perDay;
} booksData;

int main() 
{
    int operation;

    do
    {  
        switch(operation = menu())
        {
            case newRent:
                break;

            case RemoveRent:
                break;

            case ShowRent:
                break;

            case newAccounts:
                break;

            case RemoveAccounts:
                break;

            case ShowAccounts:
                break;

            case newBooks:
                addBooks();
                break;

            case RemoveBooks:
                break;

            case ShowBooks:
                break;

            case ChangePassword:
                changePwd();
                break;

            case ExitProgram:
                printf("\nExiting...");
                break;
            
            default:
                printf("\nInvalid Input");
                break;
        }

        getch(); //stops before closes it
    } 
    while(operation != ExitProgram);

    return 0;
}

//shows the menu and takes the user input
int menu(void)
{
    char input[1024];
    int op;

    system("cls"); //cleans screen
    printf("\t\t\t\tLIBRARY MANAGEMENT SYSTEM\n");
    printf("\n\t\t\t\t[1] - Add a New Rent");
    printf("\n\t\t\t\t[2] - Remove an Existing Rent");
    printf("\n\t\t\t\t[3] - Show Rents");
    printf("\n\t\t\t\t[4] - Add a New Account");
    printf("\n\t\t\t\t[5] - Remove an Existing Account");
    printf("\n\t\t\t\t[6] - Show Accounts");
    printf("\n\t\t\t\t[7] - Add a new Book");
    printf("\n\t\t\t\t[8] - Remove an Existing Book");
    printf("\n\t\t\t\t[9] - Show Books");
    printf("\n\t\t\t\t[10] - Change Admin PassWord");
    printf("\n\t\t\t\t[11] - Exit");

    printf("\n\nType the Operation: ");
    fgets(input, 1024, stdin); //takes as a str and convets to an integer to avoid errors

    return op = atoi(input);
}

void addRent(void)
{

}
void removeRent(void)
{

}
void showRent(void)
{

}
void addAccounts(void)
{

}
void removeAccounts(void)
{

}
void showAccounts(void)
{

}
void addBooks(void)
{
    booksData newBook_toAdd;
    char inputStr[1024];

    system("cls");
    printf("\n\t\t\t\t\t  ADDING BOOKS");
    printf("\n\t\t\t------------------------------------------------");

    printf("\n\nType the New Book's Title: ");
    fgets(newBook_toAdd.title, sizeof(newBook_toAdd.title), stdin);
    strcpy(newBook_toAdd.title, removeSpecial_chars(newBook_toAdd.title));
    strupr(newBook_toAdd.title); //lower case to uppercase

    printf("\nType the New Book's Author: ");
    fgets(newBook_toAdd.author, sizeof(newBook_toAdd.author), stdin);
    strcpy(newBook_toAdd.author, removeSpecial_chars(newBook_toAdd.author));
    strupr(newBook_toAdd.author);
    
    printf("\nType the New Book's Genres: ");
    fgets(newBook_toAdd.genres, sizeof(newBook_toAdd.genres), stdin);
    strcpy(newBook_toAdd.genres, removeSpecial_chars(newBook_toAdd.genres));
    strupr(newBook_toAdd.genres);

    printf("\nType the New Book's Lauch Date(dd/mm/yyy): ");
    fgets(newBook_toAdd.date, sizeof(newBook_toAdd.date), stdin);
    strcpy(newBook_toAdd.date, removeSpecial_chars(newBook_toAdd.date));
    strupr(newBook_toAdd.date);

    printf("\nType the New Book's Rent Price per Day: R$");
    fgets(inputStr, 1024, stdin);
    if((newBook_toAdd.rentValue_perDay = atof(inputStr)) <= 0)
    {
        printf("\nInvalid Input!");
        return;
    }

    //how it is adding, there is no need to block the program
    checkFiles(); 

    pBooks = fopen(BOOKS_FPATH, "a");
    fprintf(pBooks, "%s %s %s %s %.2f\n", newBook_toAdd.title, newBook_toAdd.author, 
    newBook_toAdd.genres, newBook_toAdd.date, newBook_toAdd.rentValue_perDay);
    fclose(pBooks);

    printf("\nNew Book Successfully Added!");
}
void removeBooks(void)
{

}
void showBooks(void)
{
    
}

void changePwd(void)
{
    FILE *pTemp;
    const char TEMPF_PATH[] = "temp.tmp";

    char 
    currentPwd[1024], newPwd1[1024], 
    newPwd2[1024], pwdIn_file[MAX_PWDSIZE];

    system("cls");
    printf("\n\t\t\t\t\tCHANGING PASSWORD");
    printf("\n\t\t\t------------------------------------------------");

    printf("\n\nType your Current Password: ");
    fgets(currentPwd, 1024, stdin);

    if(checkPwd(currentPwd) == 0)
    {
        printf("\nInvalid PassWord!");
        return;
    }
    
    printf("\nType your New PassWord - MAX %d Characters: ", MAX_PWDSIZE - 1); 
    fgets(newPwd1, 1024, stdin);
    printf("\nType your New PassWord again: ");
    fgets(newPwd2, 1024, stdin);

    if //if they are diferent or bigger
    (
        strlen(newPwd1) >= MAX_PWDSIZE || 
        strlen(newPwd2) >= MAX_PWDSIZE || 
        strcmp(newPwd1, newPwd2) != 0
    )
    {
        printf("\nInvalid Input!");
        return;
    }

    //creates a temp file with the new password
    pTemp = fopen(TEMPF_PATH, "w");
    fprintf(pTemp, newPwd1);
    fclose(pTemp);
    
    //removes the old files and creates a new one with the new password
    remove(ADMIN_FPATH);
    rename(TEMPF_PATH, ADMIN_FPATH);

    printf("\nPassword Successfully Changed!");
}

/*
Checks files situation. Returns:
    -1 if the files were deleted 
    0 if the files are empty
    1 if the files are ok
*/
int checkFiles(void)
{
    char buffer[4][1024];

    pAdmin = fopen(ADMIN_FPATH, "r"); 
    pRents = fopen(RENTS_FPATH, "r"); 
    pAccounts = fopen(ACCOUNTS_FPATH, "r"); 
    pBooks = fopen(BOOKS_FPATH, "r");

    //reads the first line of each file
    fgets(buffer[0], 1024, pAdmin); 
    fgets(buffer[1], 1024, pRents); 
    fgets(buffer[2], 1024, pAccounts); 
    fgets(buffer[3], 1024, pBooks); 

    fclose(pAdmin);
    fclose(pRents);
    fclose(pAccounts);
    fclose(pBooks);

    //checks if they were deleted
    if(pAdmin  == NULL || pRents == NULL || pAccounts  == NULL || pBooks == NULL)
    {
        pAdmin = fopen(ADMIN_FPATH, "w");
        pRents = fopen(RENTS_FPATH, "w");
        pAccounts = fopen(ACCOUNTS_FPATH, "w");
        pBooks = fopen(BOOKS_FPATH, "w"); 

        fprintf(pAdmin, DEFAULT_PWD); //writes the default password

        fclose(pAdmin);
        fclose(pRents);
        fclose(pAccounts);
        fclose(pBooks);

        return -1;
    }
    else if  //if they are empty
    (
        buffer[0] == NULL || buffer[1] == NULL || 
        buffer[2] == NULL || buffer[3] == NULL
    )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*
Checks if the string is equal to the password admin in file
- Returns 1 if it is equal
- Else, returns 0
*/
int checkPwd(char strTo_cmp[])
{
    char pwdIn_file[MAX_PWDSIZE];

    checkFiles(); 

    pAdmin = fopen(ADMIN_FPATH, "r");

    if(strcmp(fgets(pwdIn_file, MAX_PWDSIZE, pAdmin), strTo_cmp) == 0)
    {
        fclose(pAdmin);
        return 1;
    }

    fclose(pAdmin);

    return 0; //if the passwords are not equal
}
/*
This Function avoid extra chars being getting by others fgets, 
removes the \n in last char and removes the blank spaces
*/
char *removeSpecial_chars(char string[])
{
    if(strchr(string, '\n') == NULL) //if the string is full or out of limits
    {
        char extraChar;
        
        //reads(removes) the extra chars
        while((extraChar = fgetc(stdin)) != '\n' && extraChar != EOF);
    }

    //removes blank spaces
    for(int i = 0; i < strlen(string) - 1; i++)
    {
        if(string[i] == ' ')
            string[i] = '-';
    }

    //add the null char
    string[strlen(string) - 1] = '\0';

    return string;
}