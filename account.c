/******************************************************************************
 * Project       : ATM Simulation System
 * File Name     : account.c
 * Author        : Siva Prasad Reddy
 * Date          : 20-09-2025
 *
 * Description   :
 *  This program simulates a basic ATM system with the following features:
 *   - Account Creation (with validation of account number, name, PIN)
 *   - Deposit / Withdraw (with minimum balance rules)
 *   - Transaction History (with timestamp logging)
 *   - Mini Statement (last 5 transactions)
 *   - Change PIN (with old PIN verification + confirmation)
 *   - Money Transfer (between two valid accounts, dual transaction logging)
 *   - Admin Access:
 *        -> View all accounts
 *        -> Reset PIN for users
 *        -> (Extendable: Delete accounts, sort by balance, etc.)
 *
 * Implementation Notes:
 *   - Account data is stored in a master file "account.txt"
 *   - Each account has a separate transaction history file:
 *         tx_<account_number>.txt
 *   - Timestamps are formatted using strftime: "%Y-%m-%d %H:%M:%S"
 *   - Input is validated for account numbers, names, and PINs
 *
 * Compilation:
 *   gcc account.c -o atm
 *
 * Usage:
 *   ./atm
 ******************************************************************************/

#include<stdio.h>
#include "account.h"
#include<string.h>
#include<ctype.h>
#include<time.h>
//load the all account details in structure
void load_account(Account* Bank)
{
    FILE* fp=fopen("account.txt","r");//open file in read mode
    if(fp==NULL)
    {
       printf("Error opening file for reading!\n"); 
        return; //No account loaded
    }
     fscanf(fp,"#%d\n",&Bank->Account_count); //read the count of account
     for(int i=0;i<Bank->Account_count;i++) //read the all account details 
     {
        fscanf(fp,"%[^,],%[^,],%[^,],%f\n",
            Bank->Atm[i].account_number,
            Bank->Atm[i].name,
            Bank->Atm[i].pin,
            &Bank->Atm[i].balance
        );
     }
     fclose(fp); //close the file
}
//check the account number present in the list or not
int check_account_number(Account*Bank,char* number)
{
    int j=1;
    while(j)
    {
        scanf(" %s",number); //read the account number
        j=0;
        
    for(int i=0;i<Bank->Account_count;i++)
    {
        if(strcmp(Bank->Atm[i].account_number,number)==0)  //search the account number are present or not
        {
            return i; //account number present return the index value
        }
     }
        j=1;
        printf("Wrong Account number.Try again\n"); 
        //account number are not present again ask to enter the number
     
    }
    return -1;
}
//check for authenticate of account number and PIN
int authenticate(Account *Bank, char* number,char *pin)
{
    int j=3;
    do
    {
        //read the PIN number
        scanf(" %s",pin);
    for(int i=0;i<Bank->Account_count;i++)
    {
        if(strcmp(Bank->Atm[i].account_number,number)==0) //search for account number
        {
            if(strcmp(Bank->Atm[i].pin,pin)==0) //check for PIN number is correct or wrong
            {
                return i;//PIN correct return the index value
            }
            else
            {
                j--;
                if(j==0)
                {
                    return -1; //PIN number is wrong for 3 times return the value
                }
                printf("Wrong PIN. You have %d chance(s). Try again.\n",j);
            }
        }
    }
  }while(j>0);
}
//download the ministatement for last 5 transection 
void ministatement(Account* Bank)
{
    char filename[50]; //read the filename in stdin
    char Account_num[20];//read the account number
    printf("Enter the Account Number:\n");
     int res=check_account_number(Bank,Account_num); //check for account number is present or not in file
     if(res == -1)
    {
        printf("Invalid Account Number!\n");
        return;//if not present return the function
    }
    printf("Account Number is valid. Enter the PIN\n");
    char pin[10];//account number present read the PIN and check for authentication
    int index=authenticate(Bank,Account_num,pin);
    if(index!=-1) //if PIN is correct download the statement
    {
        sprintf(filename, "tx_%s.txt", Bank->Atm[index].account_number);
        FILE* fp=fopen(filename,"r");//copy the account number in filename of file and open the file in read mode
        if(fp == NULL)
        {
            printf("No transaction history found for this account!\n");
             return;//no filename return the function
        }
       char line[200];
       char transection[50][100];
       int count=0;
       while(fgets(line,sizeof(line),fp)) //copy the data in file to stdout 
       {
           strcpy(transection[count],line);
            count++;
       }
       int start= (count>5)?count-5:0; //check for last 5 transection 
       printf("\n-------------- Mini Statement ------------------------------\n");
       for(int i=start;i<count;i++)
       {
            printf("%s",transection[i]); //print the last 5 transection
       }
       printf("---------------------------------------------------------------\n");
       printf("\n");
       fclose(fp); //close the file
    }
    else
    {
        printf("Wrong PIN entered multiple times. Account is Blocked!\n"); 
    }

}
//check for account number is valid or not
void valid_account_number(Account* Bank,char* number)
{
    int dupilicate=1;
    do
    {
        dupilicate=0;
        int n=1;
        do
        {
            n=0;
           scanf(" %s",number); //read the account number
           if(strlen(number)!=10)//check account number is 10 digit or not
           {
               printf("Account Number should be 10 digit.Check and Try Again\n");
               n=1;
            }
         
            for(int k=0;number[k]!='\0';k++)//check account number is only digit or not
            {     
               if(!isdigit(number[k]))
               {
                  printf("Account Number must contain only numbers. Try again.\n");
                  n=1;
                  break;
                } 
            }
        }while(n);
        for(int j=0;j<Bank->Account_count;j++)//check for same account number present or not 
        {
            if(strcmp(Bank->Atm[j].account_number,number)==0)
            {
                printf("This account number already exist.Check Account number and Try again\n");
                dupilicate=1;
                break;//if same account number present ask again to enter valid account number
            }
        }
    }while(dupilicate);
}
//check  for name is valid or not
void valid_name(char* name)
{
    int duplicate=1;
    do
    {
        duplicate=0;
        scanf(" %[^\n]",name);//read the name 
        if(!isalpha(name[0])) //first letter is alphabet or not
        {
        printf("First letter must be an alphabet.Try again\n");
        duplicate=1;
      }
    for(int i=0;name[i]!='\0';i++)//check name contain only alphabets and spaces
    {
             if(!isalpha(name[i])&&name[i]!=' ')
             {
                  printf("The name must contain only alphabets and spaces.Try again\n");
                  duplicate=1;
                  break;
            }
    }
 } while (duplicate);
}
//check for PIN is valid or not
void valid_pin(char* pin)
{
    int i=1;
    do
    {
        scanf(" %s",pin);//read the PIN
       i=0;
       if(strlen(pin)!=4)//check PIN is only 4 digit
       {
          printf("PIN contain 4 digit only.try again\n");
          i=1;
       }
        for(int j=0;pin[j]!='\0';j++)
        {
            if(!isdigit(pin[j]))//check PIN contain only digit
            {
                printf("PIN contain only numbers>Try again\n");
                i=1;
                break;
            }
        }
    } while (i);
    
}
//to store the transection histroy of each account number in seperate file with account number 
void transection_histroy(Account* Bank,int index,float money,int flag)
{
        char filename[50];//read account number is file name
        sprintf(filename, "tx_%s.txt", Bank->Atm[index].account_number);
        FILE* fp=fopen(filename,"a");//open file in append mode
        if(fp == NULL)
        {
             printf("Error opening transaction file!\n");
             return;//no transection histroy 
        }
        //to store with time and data 
        time_t t; 
        time(&t);//read the current time
        struct tm *current;
        char buffer[100];
        current=localtime(&t);//change into local time and date by using struct
        strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",current);//store in buffer
        if(flag==1)//if flag 1 means to deposit transection
        {
            fprintf(fp, "Deposit: %.2f  | Balance: %.2f | Time: %s\n", 
                money, Bank->Atm[index].balance, buffer);//update the file with deposite and time
        }
        else//flag 0 means withdraw transection and store in the file
        {
            fprintf(fp, "withdraw: %.2f | Balance: %.2f | Time: %s\n", 
                money, Bank->Atm[index].balance, buffer);
        }
        fclose(fp);//close the file

}
//create new account for atm transection
void Create_Account(Account* Bank)
{
     int index=Bank->Account_count;
        char act_num[15];
         printf("Enter the Account Number: \n");
         valid_account_number(Bank,act_num);//read the account number and valid it and copy in structure
         strcpy(Bank->Atm[index].account_number,act_num);
         char name[50];
         printf("Enter the Account Holder Name: \n");
         valid_name(name);//read the account holder name and valid it and copy in structure
         strcpy(Bank->Atm[index].name,name);
         char num[10];
         printf("Enter the New PIN (4 digits only): \n");
         valid_pin(num);//read the PIN and valid it and copy in structure
        strcpy(Bank->Atm[index].pin,num);
        Bank->Atm[index].balance=1000;//minimum balance for each account
        char filename[50];//creat a logbook file for each account number to store transection histroy
        sprintf(filename, "tx_%s.txt", Bank->Atm[index].account_number);
        FILE* fp=fopen(filename,"w");//open in write mode
        if(fp == NULL)
        {
             printf("Error opening transaction file!\n");
             return;
        }
        fprintf(fp, "Account Number: %s\nName: %s\nInitial Balance: %.2f\n",
                Bank->Atm[index].account_number,
                Bank->Atm[index].name,
                Bank->Atm[index].balance);//store the account number,name and balance in logbook 
        fprintf(fp,"--------------------------------------------------------------\n");
        Bank->Account_count++;
        printf("Your ATM account has been successfully registered!\n");
        printf("\nAccount Number : %s\nName           : %s\nBalance        : %.2f\n",
           Bank->Atm[index].account_number,
           Bank->Atm[index].name,
           Bank->Atm[index].balance);//print the register successfull with name and account number 
           fclose(fp);//close the file
        
}
//check the balance in there account
void getBalance(Account* Bank)
{
    char number[15];//read the account number and check it present or not in file
    printf("Enter the Account number: \n");
    int res=check_account_number(Bank,number);
    if(res == -1)//if not present 
    {
        printf("Invalid Account Number!\n");
        return;
    }
    printf("Account Number is valid. Enter the PIN\n");
    char pin[10];//if present read the PIN and check authentication
    int index=authenticate(Bank,number,pin);
    if(index!= -1)//if PIN present take the index value and display the balance and name
    {
        printf("Account Holder Name: %s\nBalance: %.2f",Bank->Atm[index].name,Bank->Atm[index].balance);
    }
    else
    {
        printf("Wrong PIN entered multiple times. Account is Blocked!\n");
    }
}
//deposite the money in there account
void deposite(Account* Bank)
{
    char number[15];//read the account number and check account number present in file or not 
    printf("Enter the Account Number: \n");
     int res=check_account_number(Bank,number);//if present return there index
    if(res == -1)
    {
        printf("Invalid Account Number!\n");
        return;//if not present
    }
    printf("Account Number is valid. Enter the PIN\n");
    char pin[10];//if account number present read the PIN and check for authenticate
    int index=authenticate(Bank,number,pin);
    if(index!=-1)//if PIN is correct 
    {
        printf("Enter the Deposite Amount: \n");
        float deposite;//read the deposite money
        scanf("%f",&deposite);
        if(deposite<=0)//chek deposite is lessthan 0 or not
        {
            printf("Invalid amount! Deposit must be greater than 0.\n");
            return ;
        }
        Bank->Atm[index].balance+=deposite;//update the balance by adding the deposite money
        transection_histroy(Bank,index,deposite,1);//enter in the logbook file
         printf("Deposit successful!\n");
        printf("Updated Account Info:\n");
        printf("Account Holder Name: %s\nBalance: %.2f\n",
            Bank->Atm[index].name,
            Bank->Atm[index].balance);//display the update balance
    }
     else
    {
        printf("Wrong PIN entered multiple times. Account is Blocked!\n");
    }

}
//withdraw the money for there account 
void withdraw(Account* Bank)
{
     char number[15];//read the account number and check account numer is present or not in file
    printf("Enter the Account Number: \n");
     int res=check_account_number(Bank,number);
    if(res == -1)//if not present return the function
    {
        printf("Invalid Account Number!\n");
        return;
    }
    printf("Account Number is valid. Enter the PIN\n");
    char pin[10];//if present read the PIN and check for authentication 
    int index=authenticate(Bank,number,pin);
    if(index!=-1)//if pin is present
    {
        printf("Enter the Withdraw Amount: \n");
        float withdraw;//read the withdraw money 
        scanf("%f",&withdraw);
        if(withdraw<=0)//check withdraw money is not lessthan 0  
        {
            printf("Invalid amount! Withdraw must be greater than 0.\n");
            return ;
        }
        if (withdraw > (Bank->Atm[index].balance - 1000.0))//check wihdraw money morethan the balance in there account
        {
            printf("Inseficeinet Balance in your Account!\n");
            return ;
        }
        Bank->Atm[index].balance-=withdraw;//update the money 
        transection_histroy(Bank,index,withdraw,0);//enter the transection in logbook
       printf("Withdraw Successful!\n");
        printf("Please collect your cash.\n");
         printf("Updated Account Info:\n");//display the balance
        printf("Account Holder Name: %s\nBalance: %.2f\n",
            Bank->Atm[index].name,
            Bank->Atm[index].balance);
    }
    else
    {
        printf("Wrong PIN entered multiple times. Account is Blocked!\n");
    }
   
}
//account holder to change there pin for account
void changePin(Account* Bank)
{
     char number[15];//read the account number and check it is present or not in file
    printf("Enter the Account Number: \n");
     int res=check_account_number(Bank,number);
    if(res == -1)// account number not present 
    {
        printf("Invalid Account Number!\n");
        return;
    }
    printf("Account Number is valid. Enter the Old PIN\n");
    char pin[10];//account number is present read the old PIN and check for authentication
    int index=authenticate(Bank,number,pin);
    if(index!=-1)//if PIN is correct
    {
        char newpin[10];
        char confirmpin[10];
        do
        {
         printf("Enter the New PIN (4 digits only): \n");
         valid_pin(newpin);//read the new pin and valid it and compare the new pin and old pin are same or not
        if (strcmp(newpin, Bank->Atm[index].pin) == 0)
        {
            printf("New PIN cannot be the same as the old PIN. Try again.\n");
            continue;
        }
        printf("Confirm the New PIN: \n");
        valid_pin(confirmpin);//read new pin again to confirm the pin
        if (strcmp(newpin, confirmpin) != 0)//compare new pin and confirm pin same or not
        {
            printf("PINs do not match. Try again.\n");
        }
        else
        {
            strcpy(Bank->Atm[index].pin, newpin);//both are same copy the new pin 
            printf("PIN changed successfully!\n");
            break;
        }
    }while(1);
    }
    else
    {
        printf("Wrong PIN entered multiple times. Account is Blocked!\n");
    }
}
//store the account in alphabet order 
void sort(Account* Bank)
{
    for(int i=0;i<Bank->Account_count-1;i++)
    {
        for(int j=i+1;j<Bank->Account_count;j++)
        {
            if(strcasecmp(Bank->Atm[i].name,Bank->Atm[j].name)>0)
            {
                struct Account_details temp=Bank->Atm[i];
                Bank->Atm[i]=Bank->Atm[j];
                Bank->Atm[j]=temp;
            }
        }
    }
}
//money transfer for account to account
void moneytransfer(Account* Bank)
{
    char number[15];//read the account number of sender and check is present or not
    printf("Enter the your Account Number: \n");
     int res=check_account_number(Bank,number);
    if(res == -1)//not present
    {
        printf("Invalid Account Number!\n");
        return;
    }
    printf("Account Number is valid. Enter the PIN\n");
    char pin[10];//present enter the PIN and cehck for authenticate 
    int index=authenticate(Bank,number,pin);
    if(index!=-1)//PIN is correct
    { 
             char num[15];//read the account number of reciver and check is present or not in file
             printf("Enter the Recevier Account Number: \n");
             int r=check_account_number(Bank,num);
            if(r == -1)//not present
            {
                printf("Invalid Account Number!\n");
                return;
            }
             printf("Account Holder Name: %s\n", Bank->Atm[r].name);//if present display the recievre name
            float transfermoney;
            printf("Enter the transfermoney:\n");//read the money for sender
            scanf("%f",&transfermoney);
            if(transfermoney<=0)//check transfermoney is there in sender account 
            {
                 printf("Invalid amount! Withdraw must be greater than 0.\n");
                 return ;
            }
            if (transfermoney > (Bank->Atm[index].balance - 1000.0))
            {
               printf("Inseficeinet Balance in your Account!\n");
               return ;
            }
            Bank->Atm[index].balance-=transfermoney;//remove the money in sender account
            transection_histroy(Bank,index,transfermoney,0);//enter the logbook
            Bank->Atm[r].balance+=transfermoney;//add the money in reciver acount
            transection_histroy(Bank,r,transfermoney,1);//enter the logbook
            printf("Transfer Successful!\n");
            printf("Updated Account Info:\n");
            printf("Account Holder Name: %s\nBalance: %.2f\n",
            Bank->Atm[index].name,
            Bank->Atm[index].balance);//display update balance in sender account
    }
    else
    {
        printf("Wrong PIN entered multiple times. Account is Blocked!\n");
    }
}
//view all account for admin to access
void view_all_account(Account* Bank)
{
    printf("\n%-15s %-20s %-10s\n", "Account Number", "Name", "Balance");
    for(int i=0; i<Bank->Account_count; i++)
    {
        printf("%-15s %-20s %.2f\n", 
               Bank->Atm[i].account_number,
               Bank->Atm[i].name,
               Bank->Atm[i].balance);
    }
}
//rest the pin by admin for account holder 
void reset_pin(Account* Bank)
{
    char act_num[20];
    printf("Enter the Account Number to reset PIN: ");
    //read the account number and check 
    int index = check_account_number(Bank, act_num);
    if(index == -1)
    {
        printf("Invalid Account Number!\n");
        return;
    }
    //reaet the pin 
    char new_pin[10];
    printf("Enter New PIN (4 digits only): ");
    valid_pin(new_pin);
    strcpy(Bank->Atm[index].pin, new_pin);

    printf("PIN reset successful for Account: %s\n", Bank->Atm[index].account_number);
}
//for admin login to change in account
void admin_login(Account* Bank)
{
    int i=1;
    while(i)
    {
    char name[30];//read the username and check
    printf("Enter the Username:\n");
    scanf(" %[^\n]",name);
    char username[30]={"siva prasad"};
    if(strcmp(name,username)!=0)
    {
        printf("Invalid username\n");
        continue;
    }
    char posword[20];//read the posword and check
    printf("Enter the posword:\n");
    scanf(" %s",posword);
    char pos[20]={"Ksiva@123"};
    if(strcmp(pos,posword)!=0)
    {
        printf("Invalid posword.\n");
        continue;
    }
     printf("Login Successful\n");

    i=0;
}
   int j=1;
   while(j)
   {
    printf("1.view all accounts\n2.Reset User PIN\n");
    printf("selecet one opition\n");
    int opt;//to access the all account and reset the oin
    scanf("%d",&opt);
     switch(opt)
    {
            case 1:
                    view_all_account(Bank);
                    break;
            case 2:
                    reset_pin(Bank);
                    break;
            default:
                    printf("invalid input\n");
                    break;    
     }
     printf("Do you want to continue (1-Yes/0-No)\n");
     scanf("%d",&j);
     if(j==0)
     {
        printf("Logout Successuful!\n");
     }
    }

}
//save the all account in file 
void save_account(Account* Bank)
{
    sort(Bank);
    FILE* fp=fopen("account.txt","w");//open in write mode
    if(fp==NULL)
    {
         printf("Error opening file for saving!\n");
        return;
    }
    fprintf(fp,"#%d\n",Bank->Account_count);//sotre the all account details i file
    int index=Bank->Account_count;
    for(int i=0;i<index;i++)
    {
        fprintf(fp,"%s,%s,%s,%.2f\n",
         Bank->Atm[i].account_number,
                Bank->Atm[i].name,
                Bank->Atm[i].pin,
                Bank->Atm[i].balance);
    }
    fclose(fp);//close the file
}