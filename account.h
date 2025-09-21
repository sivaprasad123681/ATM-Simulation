#ifndef ACCOUNT_H
#define ACCOUNT_H
//struct for account details
 struct Account_details {
    char account_number[15];
    char name[50];
    char pin[5];
    float balance;
};
struct Account
{
    struct Account_details Atm[100];
    int Account_count;
};
typedef struct Account Account;

// Function prototypes
void Create_Account(Account*);
void valid_account_number(Account* ,char*);
void valid_name(char*);
void valid_pin(char*);
void save_account(Account*);
void load_account(Account*);
int authenticate(Account *,char*,char*);
void getBalance(Account *);
int check_account_number(Account*,char*);
void deposite(Account *);
void withdraw(Account *);
void changePin(Account *);
void sort(Account*);
void ministatement(Account*);
void transection_histroy(Account*,int,float,int);
void moneytransfer(Account*);
void admin_login(Account*);
void view_all_account(Account*);
void reset_pin(Account*);
#endif
