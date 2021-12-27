//this was made by: Paulo
//github: Paulo-Henrique-Silva 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define DEFAULT_PWD "2021"
#define ADMIN_FPATH "adm.bin"

int menu();

void addRent();
void removeRent();
void showRent();
void addAccounts();
void removeAccounts();
void showAccounts();
void addBooks();
void removeBooks();
void showBooks();
void changePwd();

int checkFiles();

enum menuoperationtions 
{
    newRent = 1, RemoveRent, ShowRent,
    newAccounts, RemoveAccounts, ShowAccounts,
    newBooks, RemoveBooks, ShowBooks,
    ChangePassword, ExitProgram
};

FILE *pAdmin; 

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
int menu()
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

/*
Checks files situation. Returns:
    -1 if the files were deleted
    0 if the files are empty
    1 if the files are ok
*/
int checkFiles()
{
    char infile[1024];

    if((pAdmin = fopen(ADMIN_FPATH, "rb")) == NULL)
    {
        fclose(pAdmin);

        pAdmin = fopen(ADMIN_FPATH, "wb");
        fwrite(DEFAULT_PWD, sizeof(char), 1, pAdmin);
        fclose(pAdmin);

        return -1;
    }
    else if(fread(&infile, sizeof(char), 1, pAdmin) == EOF)
    {
        fclose(pAdmin);
        return 0;
    }
    else
    {
        fclose(pAdmin);
        return 1;
    }
}