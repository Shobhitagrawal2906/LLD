#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Wallet
{
private:
    string account_number;
    double balance;
    double fd_amount;
    int fd_remaining_transactions;

public:
    Wallet(string acc_number, double initial_balance)
        : account_number(acc_number), balance(initial_balance), fd_amount(0), fd_remaining_transactions(0) {}

    string getAccountNumber() const
    {
        return account_number;
    }

    double getBalance() const
    {
        return balance;
    }

    double getFixedDepositAmount() const
    {
        return fd_amount;
    }

    int getRemainingFDTransactions() const
    {
        return fd_remaining_transactions;
    }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
    }

    bool withdraw(double amount)
    {
        if (amount > 0 && balance - amount >= 0)
        {
            balance -= amount;
            return true;
        }
        return false;
    }

    void createFixedDeposit(double amount, int num_transactions)
    {
        if (amount > 0)
        {
            fd_amount = amount;
            fd_remaining_transactions = num_transactions;
        }
    }

    bool transfer(Wallet &recipient, double amount)
    {
        if (amount >= 0.0001 && balance - amount >= 0)
        {
            balance -= amount;
            recipient.deposit(amount);

            if (balance == recipient.balance)
            {
                balance += 10;
                recipient.deposit(10);
            }
            return true;
        }
        return false;
    }

    void addInterest(double interest)
    {
        balance += interest;
    }
    void add(double amounttoadd)
    {
        balance += amounttoadd;
    }
};

class WalletSystem
{
private:
    vector<Wallet> wallets;

public:
    void createWallet(string account_number, double initial_balance)
    {
        for (auto &wallet : wallets)
        {
            if (wallet.getAccountNumber() == account_number)
            {
                cout<<"Account already exists!"<<endl;
                return;
            }
        }
        Wallet wallet(account_number, initial_balance);
        wallets.push_back(wallet);
        cout << "Wallet created successfully!" << endl;
    }

    Wallet *findWalletByAccountNumber(string account_number)
    {
        for (auto &wallet : wallets)
        {
            if (wallet.getAccountNumber() == account_number)
            {
                return &wallet;
            }
        }
        return nullptr;
    }

    void transferAmount(string sender_account_number, string receiver_account_number, double amount)
    {
        Wallet *sender_wallet = findWalletByAccountNumber(sender_account_number);
        Wallet *receiver_wallet = findWalletByAccountNumber(receiver_account_number);

        if (!sender_wallet || !receiver_wallet)
        {
            cout << "Invalid account numbers." << endl;
            return;
        }

        if (sender_wallet->transfer(*receiver_wallet, amount))
        {
            cout << "Amount transferred successfully!" << endl;
        }
        else
        {
            cout << "Transfer failed." << endl;
        }
    }

    void accountStatement(string account_number)
    {
        Wallet *wallet = findWalletByAccountNumber(account_number);

        if (!wallet)
        {
            cout << "Account not found." << endl;
            return;
        }

        cout << "Account statement for " << wallet->getAccountNumber() << ":" << endl;
        cout << "Balance: " << wallet->getBalance() << endl;
        cout << "Fixed deposit amount: " << wallet->getFixedDepositAmount() << endl;
        cout << "Remaining FD transactions: " << wallet->getRemainingFDTransactions() << endl;
    }

    void overview()
    {
        cout << "Overview of all accounts:" << endl;
        for (const Wallet &wallet : wallets)
        {
            cout << "Account number: " << wallet.getAccountNumber() << endl;
            cout << "Balance: " << wallet.getBalance() << endl;
            cout << "Fixed deposit amount: " << wallet.getFixedDepositAmount() << endl;
            cout << "Remaining FD transactions: " << wallet.getRemainingFDTransactions() << endl;
        }
    }

    void fixedDeposit(string account_number, double amount)
    {
        Wallet *wallet = findWalletByAccountNumber(account_number);

        if (!wallet)
        {
            cout << "Account not found." << endl;
            return;
        }

        if (amount < 0.0001)
        {
            cout << "The fixed deposit amount must be greater than 0.0001 F₹." << endl;
            return;
        }

        if (wallet->getFixedDepositAmount() > 0)
        {
            cout << "You already have a fixed deposit." << endl;
            return;
        }

        wallet->createFixedDeposit(amount, 5);
        cout << "Fixed deposit created successfully!" << endl;
    }

    void offer1()
    {
        for (Wallet &wallet : wallets)
        {
            if (wallet.getBalance() == wallet.getFixedDepositAmount())
            {
                wallet.addInterest(10);
            }
        }
    }

    void offer2()
    {
        vector<Wallet *> top3_customers;

        for (Wallet &wallet : wallets)
        {
            if (wallet.getRemainingFDTransactions() > 0)
            {
                top3_customers.push_back(&wallet);
            }
        }

        sort(top3_customers.begin(), top3_customers.end(),
             [](const Wallet *a, const Wallet *b)
             {
                 if (a->getBalance() > b->getBalance())
                 {
                     return true;
                 }
                 else if (a->getBalance() == b->getBalance())
                 {
                     if (a->getAccountNumber() < b->getAccountNumber())
                     {
                         return true;
                     }
                 }
                 return false;
             });

        for (int i = 0; i < 3 && i < top3_customers.size(); i++)
        {
            top3_customers[i]->addInterest(10);
        }
    }
    void addamount(string account_number, double amount)
    {
        Wallet *wallet = findWalletByAccountNumber(account_number);
        if (!wallet)
        {
            cout << "Account not found!" << endl;
            return;
        }
        wallet->add(amount);
        cout << "Added amount: " << amount << " successfully." << endl;
    }
};

int main()
{
    WalletSystem walletSystem;
    int choice;

    while (true)
    {
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1. Create wallet" << endl;
        cout << "2. Transfer amount" << endl;
        cout << "3. Account statement" << endl;
        cout << "4. Overview" << endl;
        cout << "5. Fixed deposit" << endl;
        cout << "6. Offer 1" << endl;
        cout << "7. Offer 2" << endl;
        cout << "8. Exit" << endl;
        cout << "9. Add amount" << endl;

        cout << endl;

        cin >> choice;

        string account_number, sender_account_number, receiver_account_number;
        double initial_balance, transfer_amount, fd_amount, add_amount;

        switch (choice)
        {
        case 1:
            cout << "Enter your account number: ";
            cin >> account_number;
            cout << "Enter your initial balance: ";
            cin >> initial_balance;
            walletSystem.createWallet(account_number, initial_balance);
            break;
        case 2:
            cout << "Enter the sender's account number: ";
            cin >> sender_account_number;
            cout << "Enter the receiver's account number: ";
            cin >> receiver_account_number;
            cout << "Enter the amount to transfer: ";
            cin >> transfer_amount;
            walletSystem.transferAmount(sender_account_number, receiver_account_number, transfer_amount);
            break;
        case 3:
            cout << "Enter the account number: ";
            cin >> account_number;
            walletSystem.accountStatement(account_number);
            break;
        case 4:
            walletSystem.overview();
            break;
        case 5:
            cout << "Enter the account number: ";
            cin >> account_number;
            cout << "Enter the fixed deposit amount: ";
            cin >> fd_amount;
            walletSystem.fixedDeposit(account_number, fd_amount);
            break;
        case 6:
            walletSystem.offer1();
            break;
        case 7:
            walletSystem.offer2();
            break;
        case 8:
            cout << "Exiting program." << endl;
            return 0;
        case 9:
            cout << "Enter Account Number: ";
            cin >> account_number;
            cout << "Enter Amount to be added: ";
            cin >> add_amount;
            walletSystem.addamount(account_number, add_amount);
            break;
        default:
            cout << "Invalid option." << endl;
        }
    }

    return 0;
}
