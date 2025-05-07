#include <iostream>
#include <vector>
#include <memory>
#include <numeric>


class Observer {
public:
    virtual void update(int newGrade) = 0;
    virtual ~Observer() = default;
};


class GradeBook 
{
private:
    std::vector<Observer*> observers;
    std::vector<int> grades;

public:
    void attach(Observer* observer) 
    {
        observers.push_back(observer);
    }

    void addGrade(int grade) 
    {
        grades.push_back(grade);
        notify(grade);
    }

    void setGrade(int index, int newGrade) 
    {
        if (index < 0 || index >= grades.size()) 
        {
            std::cout << "Invalid index." << std::endl;
            return;
        }
        grades[index] = newGrade;
        notify(newGrade);
    }

    const std::vector<int>& getGrades() const 
    {
        return grades;
    }

private:
    void notify(int newGrade) 
    {
        for (auto observer : observers) 
        {
            observer->update(newGrade);
        }
    }
};


class Averager : public Observer {
private:
    std::vector<int> gradeHistory;

public:
    void update(int newGrade) override 
    {
        gradeHistory.push_back(newGrade);
        double avg = std::accumulate(gradeHistory.begin(), gradeHistory.end(), 0.0) / gradeHistory.size();
        std::cout << "New Average: " << avg << "%" << std::endl;
    }
};

class Notifier : public Observer 
{
public:
    void update(int newGrade) override 
    {
        if (newGrade < 60) 
        {
            std::cout << "Grade notification email sent to student@example.com." << std::endl;
        }
    }
};

int main() 
{
    GradeBook gradeBook;
    Averager averager;
    Notifier notifier;

    gradeBook.attach(&averager);
    gradeBook.attach(&notifier);

    gradeBook.addGrade(85);  
    gradeBook.addGrade(75);
    gradeBook.addGrade(55);  
    gradeBook.setGrade(1, 50);  


    return 0;
}