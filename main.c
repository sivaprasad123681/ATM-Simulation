/******************************************************************************
 * Project       : ATM Simulation System
 * File Name     : main.c
 * Author        : Siva Prasad Reddy
 * Date          : 20-09-2025
 *
 * Description   :
 *  ATM system implementation supporting:
 *   - Account creation
 *   - Deposit / Withdraw
 *   - Mini statement
 *   - PIN change and reset
 *   - Transaction history
 *   - Admin features
 *
 ******************************************************************************/

#include<stdio.h>
#include"account.h"
int main()
{
    Account Bank;
    Bank.Account_count=0;
    int i=1;
     printf(".....Welcome to the SIVA Bank......\n");
     int opt;
     load_account(&Bank);
    while(i)
    {
        //display the menu 
        printf("\n----------- MENU -----------\n");
        printf("1. Create New Account\n");
        printf("2. Check Balance\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Pin Change\n");
        printf("6. Mini statement\n");
        printf("7. Money Transfer Account_to_Account\n");
        printf("8. Exit\n");
        printf("----------------------------\n");
        //select option
        printf("Select one option: ");
        scanf("%d", &opt);
        switch(opt)
        {
            case 1://create account
                    Create_Account(&Bank);
                    break;
            case 2://check balance
                    getBalance(&Bank);
                    break;
            case 3://deposite
                    deposite(&Bank);
                    break;
            case 4://withdraw
                    withdraw(&Bank);
                    break;
            case 5://pin change
                    changePin(&Bank);
                    break;
            case 6://ministatement
                    ministatement(&Bank);
                    break;
            case 7://money transfer 
                    moneytransfer(&Bank);
                    break;
            case 8://exit
                     save_account(&Bank);
                     printf("Thank you! Visit again\n");
                     i = 0;
                     break;
            case 9://admin login
                    admin_login(&Bank);
                    break;
            default :
                        printf("invalid option\n");
                        return 0 ;
                    
        }
        save_account(&Bank);//save account detailes 
        if (i != 0) {
            printf("\nDo you want to continue (1-yes/0-no): ");
            scanf("%d", &i);
            if (i == 0) { 
                printf("Thank you! Visit again\n");
            }
        }
    }
}