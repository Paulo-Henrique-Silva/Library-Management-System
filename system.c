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
#define MAX_PWDSIZE 6

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

enum menuoperationtions 
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

int main() 
{
    int operation;
    char infile[10];

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

void changePwd(void)
{
    FILE *pTemp;
    const char TEMPF_PATH[] = "temp.tmp";

    char 
    currentPwd[1024], newPwd1[1024], 
    newPwd2[1024], pwdIn_file[MAX_PWDSIZE];

    system("cls");
    printf("\n\t\t\t\t    CHANGING PASSWORD");
    printf("\n\t\t\t---------------------------------------");

    printf("\nType your Current Password: ");
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

    printf("\nPassword Successfuly Changed!");
}

/*
Checks files situation. Returns:
    -1 if the files were deleted 
    0 if the files are empty
    1 if the files are ok
*/
int checkFiles(void)
{
    char buffer[1024];

    if 
    (
        //checks if they were deleted
        (pAdmin = fopen(ADMIN_FPATH, "r")) == NULL ||
        (pRents = fopen(RENTS_FPATH, "r")) == NULL ||
        (pAccounts = fopen(ACCOUNTS_FPATH, "r")) == NULL ||
        (pBooks = fopen(BOOKS_FPATH, "r")) == NULL 
    )
    {
        fclose(pAdmin);
        fclose(pRents);
        fclose(pAccounts);
        fclose(pBooks);

        pAdmin = fopen(ADMIN_FPATH, "w");
        fprintf(pAdmin, DEFAULT_PWD); //writes the default password

        pRents = fopen(RENTS_FPATH, "w");
        pAccounts = fopen(ACCOUNTS_FPATH, "w");
        pBooks = fopen(BOOKS_FPATH, "w"); 

        fclose(pAdmin);
        fclose(pRents);
        fclose(pAccounts);
        fclose(pBooks);

        return -1;
    }
    else if
    (
        //if they are empty
        fgets(buffer, 1024, pAdmin) == NULL ||
        fgets(buffer, 1024, pRents) == NULL ||
        fgets(buffer, 1024, pAccounts) == NULL ||
        fgets(buffer, 1024, pBooks) == NULL 
    )
    {
        fclose(pAdmin);
        fclose(pRents);
        fclose(pAccounts);
        fclose(pBooks);
        return 0;
    }
    else
    {
        fclose(pAdmin);
        fclose(pRents);
        fclose(pAccounts);
        fclose(pBooks);
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

    //how it is justing cmping, there is no need to block the program
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