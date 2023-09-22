# Bank ATM System

This is a simple C++ program that simulates a bank ATM system. It allows users to log in, check their balance, deposit money, withdraw money, and view their transaction history. The program is organized into three classes: `BankAccount`, `transaction`, and `ATM`. 

## Usage

To run the program, you'll need a C++ compiler. Follow these steps:

1. Copy the code provided into a C++ source file (e.g., `main.cpp`).
2. Compile the code using your C++ compiler. For example, you can use g++ in the terminal:
   ```
   g++ main.cpp -o atm
   ```
3. Run the compiled executable:
   ```
   ./atm
   ```

## Classes

### 1. `BankAccount`

The `BankAccount` class represents a user's bank account. It includes functions for depositing, withdrawing, checking the balance, and viewing transaction history.

### 2. `transaction`

The `transaction` class represents individual financial transactions. It stores the date, type (deposit or withdrawal), and amount of each transaction.

### 3. `ATM`

The `ATM` class manages user interactions. It allows users to log in, perform various banking operations, and exit the program.

## Features

- Users can log in with an account number and password.
- Once logged in, users can:
  - Check their account balance.
  - Deposit money into their account.
  - Withdraw money from their account (with error handling).
  - View a list of their transactions.
- The program provides error messages for invalid actions or inputs.

## Default Accounts

The program initializes ten default accounts with the password "123" and an initial balance of $5000 each. You can modify the initialization in the `ATM` constructor if needed.

## Additional Information

This program demonstrates basic object-oriented programming principles in C++ and includes simple error handling for withdrawals. You can extend and enhance it further based on your requirements.

Enjoy using the Bank ATM System!
