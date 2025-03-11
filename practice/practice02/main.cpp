#include <iostream>
#include <fstream>
#include <string>


int posInput()
{
    int inputVal{};
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

void deposit(int& balance)
{
    std::cout << "How much would you like to deposit?" << std::endl;
    int depositAmount = posInput();
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
    std::cout << "Your balance is now $" << balance << "." << std::endl;
}

void withdraw(int& balance)
{
    std::cout << "How much would you like to withdraw?" << std::endl;
    int withdrawAmount = posInput();
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
    std::cout << "Your balance is now $" << balance << "." << std::endl;
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
    int currentBalance{};
    fin >> currentBalance;

    while (true)
    {
    std::cout << "Your current balance is: $" << currentBalance << std::endl;
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
    else
    {
        break;
    }
    }


    return 0;
}