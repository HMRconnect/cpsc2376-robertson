#include <iostream>
#include <string>
#include <list>

int intInputValid()
{
	int num{};
	while (true)
	{
		std::cin >> num;
		if (std::cin.fail())
		{
			std::cout << "Invalid. ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}
	return num;
}

void addTask(std::list<std::string>& stringList)
{
	std::cout << "Enter a task to add. " << std::endl;
	std::string task{};
	std::cin.ignore();
	std::getline(std::cin, task);
	stringList.push_back(task);
	std::cout << "Task added. \n" << std::endl;
}

void removeTask(std::list<std::string>& stringList)
{
	std::cout << "Which task should be removed? " << std::endl;
	int taskNumber = intInputValid() -1;
	if (taskNumber > stringList.size())
	{
		std::cout << "There is no task with that number!" << std::endl;
		return;
	}
	auto taskLocation{ next(stringList.begin(), taskNumber) };
	stringList.erase(taskLocation);
	std::cout << "Task erased.\n" << std::endl; 
}

void showTasks(const std::list<std::string>& stringList)
{
	if (stringList.size() == 0)
	{
		std::cout << "There are currently no tasks.\n" << std::endl;
		return;
	}
	int spot{ 1 };
	for (auto i = stringList.begin(); i != stringList.end(); i++)
	{
		std::cout << spot << ". " << *i << std::endl;
		spot++;
	}
	std::cout << std::endl;
}

int main()
{
	std::list<std::string> stringList{};
	while (true)
	{
		std::cout << "1. Add a Task to the Task List\n"
			<< "2. Remove a Task from the Task List\n"
			<< "3. View the Task List\n"
			<< "4. Quit\n" << std::endl;
		int choice = intInputValid();
		switch (choice)
		{
		case 1:
			addTask(stringList);
			break;
		case 2:
			removeTask(stringList);
			break;
		case 3:
			showTasks(stringList);
			break;
		case 4: 
			std::cout << "Quitting..." << std::endl;
			return 0;
		default:
			continue;
		}
	}
	

	return 0;
}