#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>
#include <iomanip>
using namespace std;

// Cross checking => error message in code => cross verify 

string getCurrentDateTime();

class transaction{
    public:
        string date;
        
        string type;
        double amount; 
        transaction(string d, string t , double a){
            date = d;
            type = t;
            amount = a;
        } 

};

class BankAccount {
private:
    static int nextAccountNo;
    int account_no;
    int password;

    double balance;
    vector<transaction> transactions;

public:
    BankAccount(int pw, double initialBalance = 5000); // Default initial balance is $5000

    void deposit(double amount);

    bool withdraw(double amount);

    double getBalance();

    int getAccountNo();

    vector<transaction> getTransactions();

    int getPassword();
};

int BankAccount::nextAccountNo = 1;

BankAccount::BankAccount(int pw, double initialBalance) : account_no(nextAccountNo++), password(pw), balance(initialBalance) {
    
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        transactions.push_back(transaction(getCurrentDateTime(), "Deposit", amount));
    }
}

bool BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        transactions.push_back(transaction(getCurrentDateTime(), "Withdrawal", amount));
        return true;
    }
    return false;
}

double BankAccount::getBalance() {
    return balance;
}

int BankAccount::getAccountNo() {
    return account_no;
}

vector<transaction> BankAccount::getTransactions() {
    return transactions;
}

int BankAccount::getPassword() {
    return password;
}

string getCurrentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %b %d %H:%M:%S %Y", &tstruct);
    return buf;
}

class ATM {
private:
    vector<BankAccount> accounts;

public:
    ATM();

    void start();

private:
    void login();

    void displayAccountMenu(BankAccount &account);

    void showBalance(BankAccount &account);

    void deposit(BankAccount &account);

    bool withdraw(BankAccount &account);

    void showTransactions(BankAccount &account);

    void waitForEnterToContinue();
};

ATM::ATM() {
    // Initialize accounts with default passwords (123) and $5000 initial balance
    for (int i = 0; i < 10; ++i) {
        accounts.push_back(BankAccount(123));
    }
}

void ATM::start() {
    do {
        login();
    } while (true);
}

void ATM::login() {
    int account_no;
    int password;
    cout << "Login Window\n";
    cout << "============\n";
    cout << "Enter your account no: ";
    cin >> account_no;
    cout << "Enter your password: ";
    cin >> password;

    for (BankAccount &account : accounts) {
        if (account.getAccountNo() == account_no && account.getPassword() == password) {
            displayAccountMenu(account);
            return;
        }
    }
    cout << "Login failed. Invalid account number or password.\n";
}

// Inside ATM::displayAccountMenu(BankAccount &account)
void ATM::displayAccountMenu(BankAccount &account) {
    int choice;
    do {
        cout << "Main Window\n";
        cout << "============\n";
        cout << "1. Show Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Show Transactions\n";
        cout << "Enter your choice: ";
        
        cin >> choice;

        switch (choice) {
            case 1:
                showBalance(account);
                break;
            case 2:
                deposit(account);
                break;
            case 3:
                if (withdraw(account)) {
                    cout << "Withdrawal successful\n";
                } else {
                    cout << "Withdrawal failed\n";
                }
                waitForEnterToContinue();
                break;
            case 4:
                showTransactions(account);
                break;
            default:
                cout << "Invalid choice\n";
                waitForEnterToContinue();
                break;
        }
    } while (true);
    cout << "Logging out\n";
}


void ATM::showBalance(BankAccount &account) {
    cout << "Main Window --> Show Balance"  << endl;
    cout << "================================================================"  << endl;
    cout << "Your balance is $" << account.getBalance() << endl;
    cout << "----------------------------------------------------------------"  << endl;
    cout << "Press enter to go back to the Main Window"  << endl;
    waitForEnterToContinue();
}

void ATM::deposit(BankAccount &account) {
    double amount;
    cout << "Main Window --> Deposit(Enter the Following Information)"  << endl;
    cout << "================================================================"  << endl;
    cout << "The amount you want to deposit: $" << endl;
    cin >> amount;
    cout << "----------------------------------------------------------------"  << endl;
    
    account.deposit(amount);
    cout << "Well done. This was added to your balance successsfully...Press enter to go back to the Main Window\n";
    waitForEnterToContinue();
}
//Error Messages will be covered in upcoming / method overriding
bool ATM::withdraw(BankAccount &account) {
    double amount;
    cout << "Main Window --> Withdraw (Enter the Following Information)" << endl;
    cout << "================================================================" << endl;
    cout << "The amount you want to withdraw: $";
    cin >> amount;
    cout << "----------------------------------------------------------------" << endl;

    if (amount <= 0) {
        cout << "Invalid amount. Please enter a positive amount." << endl;
        waitForEnterToContinue();
        return false;
    }

    if (amount > account.getBalance()) {
        cout << "Insufficient balance. You cannot withdraw more than your account balance." << endl;
        waitForEnterToContinue();
        return false;
    }

    // Withdrawal is valid, update the account balance
    if (account.withdraw(amount)) {
        cout << "Please take your money...Press enter to go back to the Main Window" << endl;
        waitForEnterToContinue();
        return true;
    }

    // Withdrawal failed for some reason
    cout << "Withdrawal failed. Please try again." << endl;
    waitForEnterToContinue();
    return false;
}

void ATM::showTransactions(BankAccount &account) {
    //Formating
    cout << "Main Window --> Show All Transactions :\n";
    cout << "================================================================" << endl;
    cout << "Account no: " << account.getAccountNo() << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << left << setw(24) << "Date" << setw(25) << "Type" << setw(10) << "Amount" << endl;
    cout << "----------------------------------------------------------------" << endl;
    vector<transaction> transactions = account.getTransactions();
    for (int i = 0; i < transactions.size(); ++i) {
        // Split the transaction into date, type, and amount
        string date = transactions[i].date;
        string type = transactions[i].type;
        double amount = transactions[i].amount;

        // Convert the amount to a double and format it
        cout << setw(24) << left << setw(25) << date << setw(10) << type << fixed << setprecision(2) << amount << endl;
    }

    cout << "================================================================" << endl;
    waitForEnterToContinue();
}



void ATM::waitForEnterToContinue() {
    cout << "Press Enter to continue\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    ATM atm;
    atm.start();
    return 0;
}
