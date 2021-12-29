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

typedef struct rentsInfo
{
    char
    name[40],
    ic[10],
    title[40];

    int amountOf_daysRented; 

    float totalTo_pay;
} rent;

typedef struct accountsInfo
{
    char
    name[40],
    ic[10];

    int amountOf_rents;

    float moneyTo_pay;
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
                addRent();
                break;

            case RemoveRent:
                removeRent();
                break;

            case ShowRent:
                showRent();
                break;

            case newAccounts:
                addAccounts();
                break;

            case RemoveAccounts:
                removeAccounts();
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
    FILE *pTemp;
    const char TEMPF_PATH[] = "temp.tmp";

    rent newRent;
    account accountList;
    book bookList;

    int lineCounter = 0, accountNum_toRent = 0, bookNum_toRent = 0;
    char numInput[1024] = {'\0'};

    if(login() == 0) return;

    //Choosing the Account
    system("cls");
    printf("\n\t\t\t\t\tCHOOSE AN ACCOUNT");
    printf("\n\t\t\t------------------------------------------------");

    if //checks the amount of Accounts and Books
    (
        checkFile(pAccounts, ACCOUNTS_FPATH) != 1 || 
        checkFile(pBooks, BOOKS_FPATH) != 1 
    )
    {
        printf("\n\nSorry, it needs at least 1 Account and 1 Book in System to Rent a Book :/");
        return;
    }

    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    while //reads and prints the account infos
    (
        fscanf(pAccounts, "%s %s %d %f", &accountList.name, &accountList.ic, 
        &accountList.amountOf_rents, &accountList.moneyTo_pay) != EOF
    )
    {
        lineCounter++; //shows accounts num
        printf("\n\n\t\t\t\t%d) Name: %s - Ic: %s", lineCounter, accountList.name, 
        accountList.ic);
    }
    fclose(pAccounts);

    //gets as a str and converts to an integer
    printf("\n\nType Person Account Number that wants to Rent a Book: "); 
    fgets(numInput, 1024, stdin);
    if((accountNum_toRent = atoi(numInput)) == 0 || accountNum_toRent > lineCounter)
    {
        printf("\nInvalid Input!");
        return;
    }

    //Choosing the Book
    system("cls");
    printf("\n\t\t\t\t\tCHOOSE A BOOK");
    printf("\n\t\t\t------------------------------------------------");

    if(checkFile(pBooks, BOOKS_FPATH) != 1)
    {
        printf("\nError, it is not Possible to continue.");
        return;
    }

    pBooks = fopen(BOOKS_FPATH, "r");
    lineCounter = 0;
    while //reads books and prints it
    (
        fscanf(pBooks, "%s %s %s %s %f", &bookList.title, &bookList.author, 
        &bookList.genres, &bookList.date, &bookList.rentValue_perDay) != EOF
    )
    {
        lineCounter++; //shows books num        
        printf("\n\n\t\t%d) Title: %s - Author: %s - Price: R$%.2f", 
        lineCounter, bookList.title, bookList.author, bookList.rentValue_perDay);    
    }    
    fclose(pBooks);

    printf("\n\nType the Book Number to be Rented: "); 
    fgets(numInput, 1024, stdin);
    if((bookNum_toRent = atoi(numInput)) == 0 || bookNum_toRent > lineCounter)
    {
        printf("\nInvalid Input!");
        return;
    }

    //amount of days
    system("cls");
    printf("\n\t\t\t\t\tAMOUNT OF DAYS");
    printf("\n\t\t\t------------------------------------------------");

    printf("\n\nType the Amount of Days to rent: ");
    fgets(numInput, 1024, stdin);
    if((newRent.amountOf_daysRented = atoi(numInput)) == 0)
    {
        printf("\nInvalid Input!");
        return;
    }

    //gets new rent info
    if //checks the amount of Accounts and Books
    (
        checkFile(pAccounts, ACCOUNTS_FPATH) != 1 || 
        checkFile(pBooks, BOOKS_FPATH) != 1 
    )
    {
        printf("\n\nError, it is not possible to Continue.");
        return;
    }

    //gets the name and the ic
    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    lineCounter = 0; //reset line counter
    while //scans the files and copy the info to new rent
    (
        fscanf(pAccounts, "%s %s %d %f", &accountList.name, &accountList.ic, 
        &accountList.amountOf_rents, &accountList.moneyTo_pay) != EOF
    )
    {
        lineCounter++; 

        if(lineCounter == accountNum_toRent)
        {
            strcpy(newRent.name, accountList.name);
            strcpy(newRent.ic, accountList.ic);
        }
    }
    fclose(pAccounts);

    //gets the book title and the rent to calculate
    pBooks = fopen(BOOKS_FPATH, "r");
    lineCounter = 0;
    while ///scans books list to new rent info
    (
        fscanf(pBooks, "%s %s %s %s %f", &bookList.title, &bookList.author, 
        &bookList.genres, &bookList.date, &bookList.rentValue_perDay) != EOF
    )
    {
        lineCounter++;      
        //the total to pay will be the amount of days times the price per day
        if(lineCounter == bookNum_toRent)
        {
            strcpy(newRent.title, bookList.title);
            newRent.totalTo_pay = bookList.rentValue_perDay * newRent.amountOf_daysRented;
        }  
    }    
    fclose(pBooks);

    //adding to file
    //how it is adding, there is no need to block the program
    checkFile(pRents, RENTS_FPATH); 

    pRents = fopen(RENTS_FPATH, "a");
    fprintf(pRents, "%s %s %s %d %.2f\n", newRent.name, newRent.ic, newRent.title, 
    newRent.amountOf_daysRented, newRent.totalTo_pay);
    fclose(pRents);

    //update account infos
    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    pTemp = fopen(TEMPF_PATH, "w"); //creates a temp file to update
    lineCounter = 0; 

    while 
    (
        fscanf(pAccounts, "%s %s %d %f", &accountList.name, &accountList.ic, 
        &accountList.amountOf_rents, &accountList.moneyTo_pay) != EOF
    )
    {
        lineCounter++; 

        //add one rent to the account total and add the new amount to pay
        //for other accounts, just copy and paste
        if(lineCounter == accountNum_toRent)
        {
            fprintf(pTemp, "%s %s %d %.2f\n", accountList.name, accountList.ic, 
            accountList.amountOf_rents + 1, accountList.moneyTo_pay + newRent.totalTo_pay);
        }
        else
        {
            fprintf(pTemp, "%s %s %d %.2f\n", accountList.name, accountList.ic, 
            accountList.amountOf_rents, accountList.moneyTo_pay);
        }
    }

    fclose(pAccounts);
    fclose(pTemp);

    //remove the old file and renames the new one with the updates infos
    remove(ACCOUNTS_FPATH);
    rename(TEMPF_PATH, ACCOUNTS_FPATH);

    printf("\nThe total will be: R$%.2f", newRent.totalTo_pay);
    printf("\nNew Rent Sucessfully Added!");
}

void removeRent(void)
{
    FILE *pTemp;
    const char TEMPF_PATH[] = "temp.tmp";

    rent inFile;
    account accountIn_file;

    int lineCounter = 0, rentNum_toDelete = 0;
    char numInput[1024] = {'\0'}, accountIc_toUpdte[10] = {'\0'};
    float accountMoney_toUpdte = 0; 

    if(login() == 0) return;

    system("cls");
    printf("\n\t\t\t\t\t   REMOVE A RENT");
    printf("\n\t\t\t------------------------------------------------");

    if(checkFile(pRents, RENTS_FPATH) != 1)
    {
        printf("\nSorry, it seems it does not have a Rent yet :/");
        return;
    }

    pRents = fopen(RENTS_FPATH, "r");
    while //scans and prints the file rent info
    (
        fscanf(pRents, "%s %s %s %d %f", &inFile.name, &inFile.ic, &inFile.title, 
        &inFile.amountOf_daysRented, &inFile.totalTo_pay) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t\t%d) Name: %s - IC: %s - Title: %s", lineCounter, inFile.name, 
        inFile.ic, inFile.title);
    }
    fclose(pRents);

    printf("\n\nType the Rent Number to Delete it: ");
    fgets(numInput, 1024, stdin);
    if((rentNum_toDelete = atoi(numInput)) == 0 || rentNum_toDelete > lineCounter)
    {
        printf("\nInvalid Input!");
        return;
    }

    if(checkFile(pRents, RENTS_FPATH) != 1)
    {
        printf("\nError, it is not possible to continue.");
        return;
    }

    //creates a temp file
    pRents = fopen(RENTS_FPATH, "r");
    pTemp = fopen(TEMPF_PATH, "w");
    lineCounter = 0; 

    while
    (
        fscanf(pRents, "%s %s %s %d %f", &inFile.name, &inFile.ic, &inFile.title, 
        &inFile.amountOf_daysRented, &inFile.totalTo_pay) != EOF
    )
    {
        lineCounter++; 
        
        //print in the temp file, except for the rent that the user wants to delete
        if(lineCounter != rentNum_toDelete)       
        {   
            fprintf(pTemp, "%s %s %s %d %.2f\n", inFile.name, inFile.ic, inFile.title, 
            inFile.amountOf_daysRented, inFile.totalTo_pay);
        }
        else //saves the accounts info to update it later
        {
            strcpy(accountIc_toUpdte, inFile.ic);
            accountMoney_toUpdte = inFile.totalTo_pay;
        }
    }    

    fclose(pRents);
    fclose(pTemp);

    //deletes the old and renames the new one without that rent
    remove(RENTS_FPATH);
    rename(TEMPF_PATH, RENTS_FPATH);

    //update account info
    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    pTemp = fopen(TEMPF_PATH, "w");

    while //reads and prints the account infos
    (
        fscanf(pAccounts, "%s %s %d %f", &accountIn_file.name, &accountIn_file.ic, 
        &accountIn_file.amountOf_rents, &accountIn_file.moneyTo_pay) != EOF
    )
    {
        //updates the account info, removing the old data
        if(strcmp(accountIc_toUpdte, accountIn_file.ic) == 0)
        {
            fprintf(pTemp, "%s %s %d %.2f\n", accountIn_file.name, accountIn_file.ic, 
            accountIn_file.amountOf_rents - 1, 
            accountIn_file.moneyTo_pay - accountMoney_toUpdte);
        }
        else
        {
            fprintf(pTemp, "%s %s %d %.2f\n", accountIn_file.name, accountIn_file.ic, 
            accountIn_file.amountOf_rents, accountIn_file.moneyTo_pay);
        }
    }

    fclose(pAccounts);
    fclose(pTemp);

    remove(ACCOUNTS_FPATH);
    rename(TEMPF_PATH, ACCOUNTS_FPATH);

    printf("\nRent Successfully Removed!");
}

void showRent(void)
{
    rent inFile;
    int lineCounter = 0;

    if(login() == 0) return;

    system("cls");
    printf("\n\t\t\t\t\t       RENTS");
    printf("\n\t\t\t------------------------------------------------");

    if(checkFile(pRents, RENTS_FPATH) != 1)
    {
        printf("\nSorry, it seems it does not have a Rent yet :/");
        return;
    }

    pRents = fopen(RENTS_FPATH, "r");
    while //scans and prints the file rent info
    (
        fscanf(pRents, "%s %s %s %d %f", &inFile.name, &inFile.ic, &inFile.title, 
        &inFile.amountOf_daysRented, &inFile.totalTo_pay) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t%d) Name: %s - IC: %s - Title: %s - Days: %d - Total: R$%.2f",
        lineCounter, inFile.name, inFile.ic, inFile.title, inFile.amountOf_daysRented, 
        inFile.totalTo_pay);
    }
    fclose(pRents);

    printf("\n\nType Anything to continue.");
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
    newAccount.moneyTo_pay = 0;

    //how it is adding, there is no need to block the program
    checkFile(pAccounts, ACCOUNTS_FPATH); 

    pAccounts = fopen(ACCOUNTS_FPATH, "a");
    fprintf(pAccounts, "%s %s %d %.2f\n", newAccount.name, newAccount.ic, 
    newAccount.amountOf_rents, newAccount.moneyTo_pay);
    fclose(pAccounts);

    printf("\nNew Account Successfully Added");
}

void removeAccounts(void)
{
    FILE *pTemp;
    const char TEMPF_PATH[] = "temp.tmp";

    account inFile;
    char numInput[1024] = {'\0'};
    int lineCounter = 0, accountNum_toDelete = 0;

    if(login() == 0) return;

    system("cls");
    printf("\n\t\t\t\t\tREMOVE AN ACCOUNT");
    printf("\n\t\t\t------------------------------------------------");

    if(checkFile(pAccounts, ACCOUNTS_FPATH) != 1)
    {
        printf("\n\nIt seems it does not have an Account yet :/");
        return;
    }

    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    while //reads and prints the account infos
    (
        fscanf(pAccounts, "%s %s %d %f", &inFile.name, &inFile.ic, 
        &inFile.amountOf_rents, &inFile.moneyTo_pay) != EOF
    )
    {
        lineCounter++; //shows accounts num
        printf("\n\n\t\t\t\t%d) Name: %s - Ic: %s", lineCounter, inFile.name, inFile.ic);
    }
    fclose(pAccounts);

    //gets the input as a string and converts to an integer
    printf("\n\nType the Account Number to Delete it: ");
    fgets(numInput, 1024, stdin);
    if((accountNum_toDelete = atoi(numInput)) == 0 || accountNum_toDelete > lineCounter)
    {
        printf("\nInvalid Input!");
        return;
    }
    
    if(checkFile(pAccounts, ACCOUNTS_FPATH) != 1)
    {
        printf("\nError, it is not possible to continue.");
        return;
    }

    //creates a temp file to transfer the data
    pTemp = fopen(TEMPF_PATH, "w");
    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    lineCounter = 0; //resets line counter

    while //reads and prints the account infos
    (
        fscanf(pAccounts, "%s %s %d %f", &inFile.name, &inFile.ic, 
        &inFile.amountOf_rents, &inFile.moneyTo_pay) != EOF
    )
    {
        lineCounter++;

        //copy and paste all accounts, except for the account that the user wants to delete
        if(lineCounter != accountNum_toDelete)
        {
            fprintf(pTemp, "%s %s %d %.2f\n", inFile.name, inFile.ic, 
            inFile.amountOf_rents, inFile.moneyTo_pay);
        }
        //to avoid errors, it needs to delete all the Accounts rents before delete the Account
        else if(inFile.amountOf_rents != 0)
        {
            printf("\nSorry, it is not Possible to remove this Account.");
            printf("\nRemove all the Accounts Rents before delete it.");
            
            fclose(pAccounts);
            fclose(pTemp);

            remove(TEMPF_PATH);
            return;
        }
    }

    fclose(pAccounts);
    fclose(pTemp); 

    //remove the old file and renames the new one without that account
    remove(ACCOUNTS_FPATH);
    rename(TEMPF_PATH, ACCOUNTS_FPATH);

    printf("\nAccount Successfully Deleted!");
}

void showAccounts(void)
{
    account inFile;
    int lineCounter = 0;

    if(login() == 0) return;

    system("cls");
    printf("\n\t\t\t\t\t    ACCOUNTS");
    printf("\n\t\t\t------------------------------------------------");

    if(checkFile(pAccounts, ACCOUNTS_FPATH) != 1)
    {
        printf("\n\nIt seems it does not have an Account yet :/");
        return;
    }

    pAccounts = fopen(ACCOUNTS_FPATH, "r");
    while //reads and prints the account infos
    (
        fscanf(pAccounts, "%s %s %d %f", &inFile.name, &inFile.ic, 
        &inFile.amountOf_rents, &inFile.moneyTo_pay) != EOF
    )
    {
        lineCounter++;

        printf("\n\n\t\t%d) Name: %s - Ic: %s - Rents: %d - Money to Pay: R$%.2f", 
        lineCounter, inFile.name, inFile.ic, inFile.amountOf_rents, inFile.moneyTo_pay);
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

    printf("\n\nType the Book Number to Delete it: ");    
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