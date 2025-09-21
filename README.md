# ATM-Simulation
A C-based ATM Simulation project with account management, transactions, and file handling.

🏦 ATM Simulation System (C Project)
Author: Siva Prasad Reddy

📅 Date: September 2025
📖 Description

This project is a C-based ATM Simulation System that simulates the core functionalities of an Automated Teller Machine (ATM).
It allows users to securely manage their bank accounts, perform transactions, and keep track of their transaction history.

The project demonstrates the use of:

  -> C structures and arrays for account management

  -> File handling (fopen, fgets, fprintf, etc.) to store account details and transaction history
  
  -> String and input validation for account numbers, PINs, and names

  -> Sorting, searching, and authentication mechanisms
  
  -> Date and time logging using <time.h>
  
It is designed as a console-based project for learning purposes and can be extended to real-world banking simulations.

✨ Features

👤 User Features

  -> Create a new account (auto-generates transaction file)
  
  -> Deposit money (minimum balance validation)
  
  -> Withdraw money (with insufficient balance check)
  
  -> Money transfer between accounts
  
  -> View account balance
  
  -> Change ATM PIN (old PIN validation + new PIN confirmation)
  
  -> Mini Statement (last 5 transactions with date & time)

🔑 Admin Features

  -> Admin login with username & password
  
  -> View all registered accounts
  
  -> Sort accounts by name
  
  -> Reset user PIN if forgotten
  
  -> Delete an account (future enhancement)

ATM-Simulation/

    │── main.c            # Main driver program (menu system)
    │── account.c         # Implementation of ATM functionalities
    │── account.h         # Header file with structures & function prototypes
    │── account.txt       # Stores all account details (account_number, name, pin, balance)
    │── tx_<account>.txt  # Transaction history files for each account
    │── README.md         # Project documentation

⚙️ How It Works

1.Account Creation

  -> User enters account number, name, and PIN
  
  -> balance set to 1000
  
  -> A transaction file (tx_<account>.txt) is created
  
2.Deposits/Withdrawals

   -> Updates balance in memory
   
  -> Logs each transaction into respective file with date and time
  
3.Mini Statement

  ->Reads last 5 lines of the transaction file using fgets()
  
4.Money Transfer

  ->Validates sender & receiver accounts
  
  ->Deducts from sender, adds to receiver
  
  ->Updates both transaction history files
  
5.Admin Module

  ->Admin logs in with username & password
  
  ->Can view all accounts, reset PINs, and manage system

🛠️ Technologies Used

Language: C

Compiler: GCC (Linux/Windows)

Concepts:

  Structures & arrays
  ,Pointers
  ,File handling
 ,String manipulation
 ,Validation & authentication
  ,Date & Time (time.h)
          
📜 Sample Transaction Log

Example tx_6305983532.txt

Account Number: 6305983532

Name: Sandeep

Initial Balance: 1000.00

--------------------------------------------------------------

Deposit: 1500.00  | Balance: 2500.00 | Time: 2025-09-20 12:48:52

Withdraw: 500.00  | Balance: 2000.00 | Time: 2025-09-20 13:10:25


👨‍💻 Author

Siva Prasad Reddy

📅 September 2025
