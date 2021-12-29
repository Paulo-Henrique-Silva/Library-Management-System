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

int checkFile(FILE *pFile, char fPath[]);
int login(void);
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

typedef struct accountsInfo
{
    char
    name[40],
    ic[10];

    int amountOf_rents;

    float moneyTo_play;
} account;

typedef struct booksInfo
{
    char 
    title[40], 
    author[40],
    genres[15],
    date[12];

    float rentValue_perDay;
} book;

int main() 
{
    int operation = 0;

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
                addAccounts();
                break;

            case RemoveAccounts:
                break;

            case ShowAccounts:
                showAccounts();
                break;

            case newBooks:
                addBooks();
                break;

            case RemoveBooks:
                removeBooks();
                break;

            case ShowBooks:
                showBooks();
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
    char input[1024] = {'\0'};

    system("cls"); //cleans screen
    printf("\t\t\t\tLIBRARY MANAGEMENT SYSTEM\n");
    printf("\n\t\t\t\t[1] - Add a New Rent");
    printf("\n\t\t\t\t[2] - Remove an Existing Rent");
    printf("\n\t\t\t\t[3] - Show Rents Details");
    printf("\n\t\t\t\t[4] - Add a New Account");
    printf("\n\t\t\t\t[5] - Remove an Existing Account");
    printf("\n\t\t\t\t[6] - Show Accounts Details");
    printf("\n\t\t\t\t[7] - Add a new Book");
    printf("\n\t\t\t\t[8] - Remove an Existing Book");
    printf("\n\t\t\t\t[9] - Show Books Details");
    printf("\n\t\t\t\t[10] - Change Admin PassWord");
    printf("\n\t\t\t\t[11] - Exit");

    printf("\n\nType the Operation: ");
    fgets(input, 1024, stdin); //takes as a str and convets to an integer to avoid errors

    return atoi(input);
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
    account newAccount;

    if(login() == 0) return;

    system("cls");
    printf("\n\t\t\t\t\t  ADDING ACCOUNTS");
    printf("\n\t\t\t------------------------------------------------");

    printf("\n\nType the New Account Name: ");
    fgets(newAccount.name, sizeof(newAccount.name), stdin);
    strcpy(newAccount.name, removeSpecial_chars(newAccount.name));
    strupr(newAccount.name);

    printf("\nType the New Account Indentification code: ");
    fgets(newAccount.ic, sizeof(newAccount.ic), stdin);
    strcpy(newAccount.ic, removeSpecial_chars(newAccount.ic));
    strupr(newAccount.ic);

    //assign zero because it's a new account
    newAccount.amountOf_rents = 0; 
    newAccount.moneyTo_play = 0;

    //how it is adding, there is no need to block the program
    checkFile(pAccounts, ACCOUNTS_FPATH); 

    pAccounts = fopen(ACCOUNTS_FPATH, "a");
    fprintf(pAccounts, "%s %s %d %.2f\n", newAccount.name, newAccount.ic, 
    newAccount.amountOf_rents, newAccount.moneyTo_play);
    fclose(pAccounts);

    printf("\nNew Account Successfully Added");
}
void removeAccounts(void)
{

}

void showAccounts(void)
{
    account inFile;
    int lineCounter = 0;

    if(login() == 0) return;

    system("cls");
    printf("\n\t\t\t\t\t      ACCOUNTS");
    printf("\n\t\t\t------------------------------------------------");

    if(checkFile(pAccounts, ACCOUNTS_FPATH) != 1)
    {
        printf("\n\nIt seems it does not have an Account yet :/");
        return;
    }

    pAccounts = fopen(ACCOUNTS_FPATH, "r");

    while
    (
        fscanf(pAccounts, "%s %s %d %f", &inFile.name, &inFile.ic, 
        &inFile.amountOf_rents, &inFile.moneyTo_play) != EOF
    )
    {
        lineCounter++;

        printf("\n\n\t\t%d) Name: %s - Ic: %s - Rents: %d - Money to Pay: R$%.2f", 
        lineCounter, inFile.name, inFile.ic, inFile.amountOf_rents, inFile.moneyTo_play);
    }

    fclose(pAccounts);

    printf("\n\nType anything to Continue.");
}

void addBooks(void)
{
    book newBook_toAdd;
    char inputStr[1024] = {'\0'};

    if(login() == 0) return; //asks password to the user

    system("cls");
    printf("\n\t\t\t\t\t  ADDING BOOKS");
    printf("\n\t\t\t------------------------------------------------");

    printf("\n\nType the New Book Title: ");
    fgets(newBook_toAdd.title, sizeof(newBook_toAdd.title), stdin);
    strcpy(newBook_toAdd.title, removeSpecial_chars(newBook_toAdd.title));
    strupr(newBook_toAdd.title); //lower case to uppercase

    printf("\nType the New Book Author: ");
    fgets(newBook_toAdd.author, sizeof(newBook_toAdd.author), stdin);
    strcpy(newBook_toAdd.author, removeSpecial_chars(newBook_toAdd.author));
    strupr(newBook_toAdd.author);
    
    printf("\nType the New Book Genres: ");
    fgets(newBook_toAdd.genres, sizeof(newBook_toAdd.genres), stdin);
    strcpy(newBook_toAdd.genres, removeSpecial_chars(newBook_toAdd.genres));
    strupr(newBook_toAdd.genres);

    printf("\nType the New Book Release Date(dd/mm/yyy): ");
    fgets(newBook_toAdd.date, sizeof(newBook_toAdd.date), stdin);
    strcpy(newBook_toAdd.date, removeSpecial_chars(newBook_toAdd.date));
    strupr(newBook_toAdd.date);

    printf("\nType the New Book Rent Price per Day: R$");
    fgets(inputStr, 1024, stdin);
    if((newBook_toAdd.rentValue_perDay = atof(inputStr)) <= 0)
    {
        printf("\nInvalid Input!");
        return;
    }

    //how it is adding, there is no need to block the program
    checkFile(pBooks, BOOKS_FPATH); 

    pBooks = fopen(BOOKS_FPATH, "a");
    fprintf(pBooks, "%s %s %s %s %.2f\n", newBook_toAdd.title, newBook_toAdd.author, 
    newBook_toAdd.genres, newBook_toAdd.date, newBook_toAdd.rentValue_perDay);
    fclose(pBooks);

    printf("\nNew Book Successfully Added!");
}

void removeBooks(void)
{
    FILE *pTemp;
    const char TEMPF_PATH[] = "temp.tmp";

    book inFile;
    char numInput[1024] = {'\0'};
    int lineCounter = 0, bookNum_toDelete = 0;

    if(login() == 0) return;

    system("cls");
    printf("\n\t\t\t\t\t  DELETE A BOOK");
    printf("\n\t\t\t------------------------------------------------");

    if(checkFile(pBooks, BOOKS_FPATH) != 1) //checks if there is, at least, a book
    {
        printf("\nIt seems it does not have a Book yet. :/");
        return;
    }

    pBooks = fopen(BOOKS_FPATH, "r");

    while
    (
        fscanf(pBooks, "%s %s %s %s %f", &inFile.title, &inFile.author, 
        &inFile.genres, &inFile.date, &inFile.rentValue_perDay) != EOF
    )
    {
        lineCounter++; //shows the books num        
        printf("\n\n\t\t\t%d) Title: %s - Author: %s", lineCounter, inFile.title, inFile.author);    
    }    

    fclose(pBooks);

    printf("\n\nType the Book Number to Delete: ");    
    fgets(numInput, 1024, stdin);
    if((bookNum_toDelete = atoi(numInput)) == 0 || bookNum_toDelete > lineCounter)
    {        
        printf("\nInvalid Input!");        
        return;    
    }

    if(checkFile(pBooks, BOOKS_FPATH) != 1)
    {
        printf("\nError, it is not possible to continue.");
        return;
    }

    //creates a temp file
    pBooks = fopen(BOOKS_FPATH, "r");
    pTemp = fopen(TEMPF_PATH, "w");
    lineCounter = 0; //resets line counter

    while
    (
        fscanf(pBooks, "%s %s %s %s %f", &inFile.title, &inFile.author, 
        &inFile.genres, &inFile.date, &inFile.rentValue_perDay) != EOF
    )
    {
        lineCounter++; 
        
        //print in the temp file, except for the book that the user wants to delete
        if(lineCounter != bookNum_toDelete)       
        {   
            fprintf(pTemp, "%s %s %s %s %.2f\n",  inFile.title, inFile.author, 
            inFile.genres, inFile.date, inFile.rentValue_perDay);
        }
    }    

    fclose(pBooks);
    fclose(pTemp);

    //deletes the old and renames the new one without that book
    remove(BOOKS_FPATH);
    rename(TEMPF_PATH, BOOKS_FPATH);

    printf("\nBook Sucessfully Removed!");
}

void showBooks(void)
{
    book inFile;
    int lineCounter = 0;

    if(login() == 0) return;

    system("cls");
    printf("\n\t\t\t\t\t     BOOKS");
    printf("\n\t\t\t------------------------------------------------");

    if(checkFile(pBooks, BOOKS_FPATH) != 1) //checks if the file is ok
    {
        printf("\n\nIt seems It does not have a Book Yet :/");
        return;
    }

    pBooks = fopen(BOOKS_FPATH, "r");

    while //scans and prints the nums
    (
        fscanf(pBooks, "%s %s %s %s %f", &inFile.title, &inFile.author, 
        &inFile.genres, &inFile.date, &inFile.rentValue_perDay) != EOF
    )
    {
        lineCounter++;
        printf("\n\n%d) Title: %s - Author: %s - Genre: %s - Date: %s - Rent: R$%.2f", 
        lineCounter, inFile.title, inFile.author, inFile.genres, inFile.date, 
        inFile.rentValue_perDay);
    }

    fclose(pBooks);

    printf("\n\nPress Anything to Continue.");
}

void changePwd(void)
{
    FILE *pTemp;
    const char TEMPF_PATH[] = "temp.tmp";

    char newPwd1[1024], newPwd2[1024];

    if(login() == 0) return;

    system("cls");
    printf("\n\t\t\t\t\tCHANGING PASSWORD");
    printf("\n\t\t\t------------------------------------------------");

    printf("\n\nType the New PassWord - MAX %d Characters: ", MAX_PWDSIZE - 1); 
    fgets(newPwd1, 1024, stdin);
    printf("\nType the New PassWord again: ");
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
Checks file situation. Returns:
    -1 if the file was deleted 
    0 if the file is empty
    1 if the file is ok
*/
int checkFile(FILE *pFile, char fPath[])
{
    char buffer[1024] = {'\0'};
    char *firstLine; 

    pFile = fopen(fPath, "r");
    firstLine = fgets(buffer, 1024, pFile); 
    fclose(pFile);

    if(pFile == NULL) //if it does not exist
    {
        pFile = fopen(fPath, "w"); 
        fclose(pFile);

        return -1;
    }
    else if(firstLine == NULL) //if it is empty
    {
        return 0; 
    }
    else 
    {
        return 1;
    }
}

/*
To login, it needs the admin password
Checks if the input is equal to the password admin in file
- Returns 1 if it is equal
- Else, returns 0
*/
int login(void)
{
    char 
    inputPwd[1024] = {'\0'}, pwdIn_file[1024] = {'\0'};

    printf("\nType the Admin PassWord: ");
    fgets(inputPwd, 1024, stdin);

    if //if the file does not exist or are empty, it creates it again
    (
        (pAdmin = fopen(ADMIN_FPATH, "r")) == NULL ||
        fgets(pwdIn_file, 1024, pAdmin) == NULL
    ) 
    {
        fclose(pAdmin);

        pAdmin = fopen(ADMIN_FPATH, "w");
        fprintf(pAdmin, DEFAULT_PWD); //writes the default password
    }

    fclose(pAdmin);

    //compares the strings
    pAdmin = fopen(ADMIN_FPATH, "r");
    fgets(pwdIn_file, 1024, pAdmin);

    if(strcmp(pwdIn_file, inputPwd) != 0)
    {
        printf("\nIncorret Password!");
        fclose(pAdmin);
        return 0;
    } 

    fclose(pAdmin);
    return 1; //if the passwords are not equal
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