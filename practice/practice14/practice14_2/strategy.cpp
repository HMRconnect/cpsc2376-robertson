#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <cctype>
#include <vector>


class TextFilterStrategy 
{
public:
    virtual std::string apply(const std::string& input) = 0;
    virtual ~TextFilterStrategy() = default;
};


class ReverseFilter : public TextFilterStrategy {
public:
    std::string apply(const std::string& input) override 
    {
        std::string reversed = input;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }
};


class UppercaseFilter : public TextFilterStrategy 
{
public:
    std::string apply(const std::string& input) override 
    {
        std::string upper = input;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return upper;
    }
};


class RemoveVowelsFilter : public TextFilterStrategy 
{
public:
    std::string apply(const std::string& input) override 
    {
        std::string result;
        for (char ch : input) {
            if (std::string("aeiouAEIOU").find(ch) == std::string::npos) 
            {
                result += ch;
            }
        }
        return result;
    }
};


class CensorFilter : public TextFilterStrategy 
{
private:
    std::vector<std::string> badWords = { "fuck", "shit", "ass", "bitch"};

    std::string censorWord(const std::string& word) 
    {
        for (const auto& bad : badWords) 
        {

            if (word == bad) 
            {
                return std::string(word.length(), '*');
            }
        }
        return word;
    }

public:
    std::string apply(const std::string& input) override 
    {
        std::string result;
        std::string word;
        for (char ch : input) 
        {
            if (std::isspace(ch)) 
            {
                result += censorWord(word) + ch;
                word.clear();
            }
            else 
            {
                word += ch;
            }
        }
        result += censorWord(word);
        return result;
    }
};

class TextProcessor 
{
private:
    std::unique_ptr<TextFilterStrategy> strategy;

public:
    void setStrategy(std::unique_ptr<TextFilterStrategy> newStrategy) 
    {
        strategy = std::move(newStrategy);
    }

    std::string process(const std::string& text) 
    {
        if (strategy) 
        {
            return strategy->apply(text);
        }
        return text;
    }
};



int main() 
{
    TextProcessor processor;
    std::string input;

    

    int choice;
    while (true)
    {
        std::cout << "Enter a sentence: ";
        std::getline(std::cin, input);
        std::cout << "\nSelect a how to filter:\n"
            << "1. Reverse\n"
            << "2. Uppercase\n"
            << "3. Remove vowels\n"
            << "4. Censor bad words\n"
            << "5. Exit\n" << std::endl;
        std::cin >> choice;
        std::cin.ignore();  

        switch (choice) 
        {
        case 1:
            processor.setStrategy(std::make_unique<ReverseFilter>());
            break;
        case 2:
            processor.setStrategy(std::make_unique<UppercaseFilter>());
            break;
        case 3:
            processor.setStrategy(std::make_unique<RemoveVowelsFilter>());
            break;
        case 4:
            processor.setStrategy(std::make_unique<CensorFilter>());
            break;
        case 5:
            return 0;
        default:
            std::cout << "Invalid choice.\n";
            continue;
        }

        if (choice >= 1 && choice <= 4) 
        {
            std::string result = processor.process(input);
            std::cout << "Filtered text: " << result << "\n";
        }

    } 

    return 0;
}