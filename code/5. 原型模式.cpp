#include <iostream>
#include <string>
#include <vector>

/* 
* 原型模式：
* 抽象原型接口prototype: 声明一个克隆自身的方法clone
* 具体原型类ConcretePrototype: 实现clone方法，复制当前对象并返回一个新对象。
*/ 

// 抽象原型类
// 这是一个抽象基类，包含两个纯虚函数 clone 和 getDetails
class Prototype {
public:
	virtual Prototype* clone() const = 0;
	virtual std::string getDetails() const = 0;
	virtual ~Prototype() {} // 定义了一个虚析构函数，以确保在删除派生类对象时能正确调用析构函数。
};

// 具体原型类
// RectanglePrototype 继承自 Prototype，实现了 clone 和 getDetails 函数。
class RectanglePrototype : public Prototype {
private:
	std::string color;
	int width;
	int height;
public :

	RectanglePrototype(std::string color, int width, int height) : 
		color(color), width(width), height(height) {}

	/* 
	* clone 方法返回一个新的 RectanglePrototype 对象的拷贝。
	* 该方法的返回类型是 Prototype*，表示返回一个指向 Prototype 对象的指针。
	* 这个指针实际上会指向一个新的 RectanglePrototype 对象，因为 RectanglePrototype 是 Prototype 的子类。
	* *this 是当前对象的引用，这意味着新对象是通过复制当前对象的所有数据成员来初始化的。
	*/ 
	Prototype* clone() const override {
		return new RectanglePrototype(*this);
	}

	// getDetails 方法返回矩形的详细信息。
	std::string getDetails() const override {
		return "Color: " + color + ", Width: " + std::to_string(width) + ", Height: " + std::to_string(height);
	}
};

// 客户端程序
int main() {
	std::string color;
	int width, height;
	std::cin >> color >> width >> height;

	// 创建 原型 对象
	/*
	* 使用 Prototype* orginRectangle = new RectanglePrototype(color, width, height); 这种方式创建对象之所以可行，
	* 是因为 C++ 允许在创建对象时使用基类指针指向派生类对象。
	* 这种机制称为多态性（Polymorphism），是面向对象编程的重要特性之一。
	*/
	Prototype* orginRectangle = new RectanglePrototype(color, width, height);

	int N;
	std::cin >> N;

	std::vector<Prototype*> rectangles;
	for (int i = 0; i < N; ++i) {
		// 克隆原型对象
		Prototype* clonedRectangle = orginRectangle->clone();
		rectangles.push_back(clonedRectangle);
	}

	// 输出详细信息
	for (const auto& rectangle : rectangles) {
		std::cout << rectangle->getDetails() << std::endl;
	}

	// 释放克隆对象的内存
	for (const auto& rectangle : rectangles) {
		delete rectangle;
	}

	// 释放原型对象的内存
	delete orginRectangle;

	return 0;
}