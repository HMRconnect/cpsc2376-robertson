#include <iostream>
#include <fstream>
#include <vector>

class Employee
{
protected:
	std::string name{};
	int id{};
public:
	Employee(std::string name, int id) : name{ name }, id{ id } {};
	virtual double calculateSalary() const = 0;
	virtual void displayInfo() const
	{
		std::cout << "\nName: " << name
			<< "\nID: " << id << std::endl;
	}
	virtual ~Employee() {}
};

class SalariedEmployee : public Employee
{
protected:
	double monthlySalary{};
public:
	SalariedEmployee(std::string name, int id, double monthly)
		: Employee{ name, id }, monthlySalary{ monthly } {};
	double calculateSalary() const override
	{
		return monthlySalary;
	}
	void displayInfo() const override
	{
		std::cout << "\nName: " << name
			<< ", ID: " << id
			<< ", Monthly Salary: " << monthlySalary 
			<< ", Total Salary: " << calculateSalary() << std::endl;
	}
	~SalariedEmployee() override {}
};

class HourlyEmployee : public Employee
{
protected:
	double hourlyRate{};
	int hoursWorked{};
public:
	HourlyEmployee(std::string name, int id, double rate, int hours)
		: Employee{ name, id }, hourlyRate{ rate }, hoursWorked{ hours } {};
	double calculateSalary() const override
	{
		return hourlyRate * hoursWorked;
	}
	void displayInfo() const override
	{
		std::cout << "\nName: " << name
			<< ", ID: " << id
			<< ", Hourly Rate: " << hourlyRate
			<< ", Hours Worked: " << hoursWorked
			<< ", Total Salary: " << calculateSalary() << std::endl;
	}
	~HourlyEmployee() override {}
};

class CommissionEmployee : public Employee
{
protected:
	double baseSalary{};
	double salesAmount{};
	double commissionRate{};
public:
	CommissionEmployee(std::string name, int id , double salary, double amount, double rate)
		: Employee{name, id}, baseSalary {salary}, salesAmount{ amount }, commissionRate{ rate } {};
	double calculateSalary() const override
	{
		return baseSalary + (salesAmount * commissionRate);
	}
	void displayInfo() const override
	{
		std::cout << "\nName: " << name
			<< ", ID: " << id
			<< ", Sales Amount: " << salesAmount
			<< ", Commission Rate: " << commissionRate
			<< ", Base Salary: " << baseSalary 
			<< ", Total Salary: " << calculateSalary() << std::endl;
	}
	~CommissionEmployee() override {}
};

void readEmployeeFile(std::vector<Employee*>& employeeVector)
{
	std::ifstream instream{ "employees.txt" };
	if (!instream)
	{
		std::cout << "file opening err" << std::endl; 
		return;
	}
	std::string employeeType{};
	while (instream >> employeeType)
	{
		if (employeeType == "Salaried")
		{
			int id{};
			std::string name{};
			double monthlySalary{};

			instream >> id >> name >> monthlySalary;
			SalariedEmployee* employee{ new SalariedEmployee(name, id, monthlySalary) };
			Employee* employeeptr{ employee };
			employeeVector.push_back(employeeptr);
		}
		else if (employeeType == "Hourly")
		{
			int id{};
			std::string name{};
			double hourlyRate{};
			int hoursWorked{};

			instream >> id >> name >> hourlyRate >> hoursWorked;
			HourlyEmployee* employee{ new HourlyEmployee(name, id, hourlyRate, hoursWorked) };
			Employee* employeeptr{ employee };
			employeeVector.push_back(employeeptr);
		}
		else if (employeeType == "Commission")
		{
			int id{};
			std::string name{};
			double baseSalary{};
			double salesAmount{};
			double commissionRate{};

			instream >> id >> name >> baseSalary >> salesAmount >> commissionRate;
			CommissionEmployee* employee{ new CommissionEmployee(name, id, baseSalary, salesAmount, commissionRate) };
			Employee* employeeptr{ employee };
			employeeVector.push_back(employeeptr);
		}
		else
		{
			std::cout << "there was an issue" << std::endl;
		}
	}
}

void printEmployees(const std::vector<Employee*>& employeeVector)
{
	for (int i{ 0 }; i < employeeVector.size(); i++)
	{
		employeeVector.at(i)->displayInfo();
	}
}

void destructEmployees(std::vector<Employee*>& employeeVector)
{
	for (int i{ 0 }; i < employeeVector.size(); i++)
	{
		delete employeeVector.at(i);
	}
}

int main()
{
	std::vector<Employee*> employeeVector{};
	readEmployeeFile(employeeVector);
	printEmployees(employeeVector);
	destructEmployees(employeeVector);
	return 0;
}