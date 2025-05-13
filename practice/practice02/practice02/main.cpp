#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cmath>

double posInput()
{
    double inputVal{};
    while (inputVal <= 0)
    {
        std::cin >> inputVal;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (inputVal <= 0)
        {
            std::cout << "invalid" << std::endl;
        }
    }
    return inputVal;
}

void checkForFile()
{
    std::ifstream fin{ "account_balance.txt" };
    if (!fin)
    {
        fin.close();
        std::cout << "No account found, making new account." << std::endl;
        std::ofstream fout{ "account_balance.txt" };
        if (!fout)
        {
            std::cerr << "Error creating file.\n";
            return;
        }
        fout << 100;
        fout.close();
    }
    fin.close();
}

void deposit(double& balance)
{
    std::cout << "How much would you like to deposit?" << std::endl;
    double depositAmount = posInput();
    balance += depositAmount;
    std::ofstream fout{ "account_balance.txt" };
    if (!fout)
    {
        std::cerr << "Error opening file\n";
        return;
    }
    fout << balance;
    fout.close();

    std::cout << "$" << depositAmount << " deposited." << std::endl;
}

void withdraw(double& balance)
{
    std::cout << "How much would you like to withdraw?" << std::endl;
    double withdrawAmount = posInput();
    if (withdrawAmount > balance)
    {
        std::cout << "You cannot withdraw more than you have stored. You have $" << balance << "." << std::endl;
        return;
    }
    balance -= withdrawAmount;
    std::ofstream fout{ "account_balance.txt" };
    if (!fout)
    {
        std::cerr << "Error opening file\n";
        return;
    }
    fout << balance;
    fout.close();
    std::cout << "$" << withdrawAmount << " withdrawn." << std::endl;
}

void printCurrentBalance(double balance)
{
    double centAmt = balance - floor(balance);
    if (centAmt != 0)
    {
        std::cout << "Your current balance is: $" << balance << std::endl;
    }
    else
    {
        std::cout << "Your current balance is: $" << balance << ".00" << std::endl;
    }
}

int main()
{
    checkForFile();
    std::ifstream fin{ "account_balance.txt" };
    if (!fin)
    {
        std::cerr << "Error opening file\n";
        return 1;
    }
    double currentBalance{};
    fin >> currentBalance;

    while (true)
    {
        printCurrentBalance(currentBalance);
        std::cout << "\nWould you like to: \n"
            << "1. Deposit Money? \n"
            << "2. Withdraw Money? \n"
            << "3. Quit?\n" << std::endl;
        int userChoice = posInput();
        if (userChoice == 1)
        {
            deposit(currentBalance);
        }
        else if (userChoice == 2)
        {
            withdraw(currentBalance);
        }
        else if (userChoice == 3)
        {
            std::cout << "Exiting program." << std::endl;
            break;
        }
        else
        {
            std::cout << "invalid option." << std::endl;
            continue;
        }
    }


    return 0;
}