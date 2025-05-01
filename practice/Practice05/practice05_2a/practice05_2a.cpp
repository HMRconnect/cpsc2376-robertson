#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int vecSum(std::vector<int>& vec)
{
	return std::accumulate(vec.begin(), vec.end(),0);
}

int multiply(int a, int b)
{
	return a * b;
}

int vecProduct(std::vector<int>& vec)
{
	return std::accumulate(vec.begin(), vec.end(), 1, multiply);
}

int main()
{
	std::vector <int> vec{ 2,2,4,8 }; 
	std::cout << "Sum of elements: " << vecSum(vec) << std::endl;
	std::cout << "Product of elements: " << vecProduct(vec) << std::endl;


	return 0;
}