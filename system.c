//this was made by: Paulo
//github: Paulo-Henrique-Silva 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int menu();

enum menuoperationtions 
{
    newRent = 1, RemoveRent, ShowRent,
    newAccounts, RemoveAccounts, ShowAccounts,
    newBooks, RemoveBooks, ShowBooks,
    ChangePassword, ExitProgram
};

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