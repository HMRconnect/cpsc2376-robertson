#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

class Shape
{
public:
	virtual double getArea() const = 0;
	virtual ~Shape() {}
};

class Rectangle : public Shape
{
protected:
	int length{};
	int width{};
public:
	Rectangle(int length, int width)
		: length(length), width(width) {}
	double getArea() const override
	{
		return length * width;
	}
	~Rectangle() override {}
};

class Circle : public Shape
{
protected:
	int radius{};
public:
	Circle(int radius)
		: radius(radius) {}
	double getArea() const override
	{
		return (radius * radius) * 3.14;
	}
	~Circle() override {}
};

void readShapes(std::vector<std::unique_ptr<Shape>>& shapes)
{
	std::ifstream instream{ "shapes.txt" };
	if (!instream)
	{
		std::cout << "file opening err" << std::endl;
		return;
	}
	std::string shapeType{};
	while (instream >> shapeType)
	{
		if (shapeType == "rectangle")
		{
			int length{};
			int width{};
			instream >> length >> width;
			shapes.push_back(std::unique_ptr<Shape> { std::make_unique<Rectangle>(length, width) });
		}
		else if (shapeType == "circle")
		{
			int radius{};
			instream >> radius;
			shapes.push_back(std::unique_ptr<Shape> { std::make_unique<Circle>(radius) });
		}
		else
		{
			std::cout << "error reading data" << std::endl;
		}
	}
}

void printAllAreas(const std::vector<std::unique_ptr<Shape>>& shapes)
{
	for (int i{0}; i < shapes.size(); i++)
	{
		std::cout << "Area: " << shapes.at(i)->getArea() << std::endl;
	}
}

int main()
{
	std::vector<std::unique_ptr<Shape>> shapes{};
	readShapes(shapes);
	printAllAreas(shapes);

	return 0;
}