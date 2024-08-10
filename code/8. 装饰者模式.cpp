#include <iostream>
#include <memory>

// 咖啡接口，抽象基类
class Coffee {
public:
    virtual ~Coffee() {}  // 虚析构函数
    virtual void brew() = 0; // 纯虚函数
};

// 具体的黑咖啡类，继承自 Coffee 类，重写 brew 方法以输出制作黑咖啡和拿铁的过程。
class BlackCoffee : public Coffee {
public:
    void brew() override {
        std::cout << "Brewing Black Coffee" << std::endl;
    }
};

// 具体的拿铁类
class Latte : public Coffee {
public:
    void brew() override {
        std::cout << "Brewing Latte" << std::endl;
    }
};

/* 
* 这里的 Decorator 类扩展了 Coffee 类，并在内部维护了一个 Coffee 类型的 unique_ptr，用于指向装饰的对象。
* 通过这种方式，Decorator 类可以在执行自己的功能之前或之后调用原有对象的功能，从而实现功能的扩展。
*
* Decorator 类继承自 Coffee 类，这使得装饰器本身也是一个 Coffee 对象。
* 通过 protected 访问限定符，类中定义了一个指向 Coffee 对象的 unique_ptr 名为 coffee，这个智能指针负责管理其指向的 Coffee 对象的生命周期。
* 构造函数 Decorator(std::unique_ptr<Coffee> coffee) 接收一个指向 Coffee 类型对象的 unique_ptr，并通过 std::move 将其转移给成员变量 coffee，这样可以避免不必要的拷贝，同时确保了资源的有效管理。
* brew 方法覆盖了基类的 brew 方法。在此方法中，首先检查内部 coffee 指针是否非空，然后调用其 brew 方法，这样就实现了在调用装饰器自身功能之前或之后添加原始 Coffee 对象的功能。
*/

// 装饰者抽象类
class Decorator : public Coffee {
protected:
    std::unique_ptr<Coffee> coffee;

public:
    // 将 Coffee 对象的所有权从传入的参数转移到 Decorator 类的 coffee 成员变量
    Decorator(std::unique_ptr<Coffee> Coffee) : coffee(std::move(Coffee)) {}

    void brew() override {
        if (coffee) {
            coffee->brew();
        }
    }
};

// 具体的牛奶装饰者类
class MilkDecorator : public Decorator {
public:
    /*
    * :Decorator(std::move(coffee))：这是成员初始化列表的一部分，它调用基类 Decorator 的构造函数。
    * 这里使用 std::move(coffee) 表示将 coffee 对象的所有权从 MilkDecorator 的构造函数传递到 Decorator 类。
    * 这是必要的，因为 unique_ptr 不能被复制，只能被移动，这保证了内存资源的独占性。
    */
    MilkDecorator(std::unique_ptr<Coffee> coffee) : Decorator(std::move(coffee)) {}

    void brew() override {
        Decorator::brew();
        std::cout << "Adding Milk" << std::endl;
    }
};

// 具体的糖装饰者类
class SugarDecorator : public Decorator {
public:
    SugarDecorator(std::unique_ptr<Coffee> coffee) : Decorator(std::move(coffee)) {}

    void brew() override {
        Decorator::brew();
        std::cout << "Adding Sugar" << std::endl;
    }
};

// 客户端代码
int main() {
    int coffeeType, condimentType;
    while (std::cin >> coffeeType >> condimentType) {
        // 根据输入制作咖啡
        std::unique_ptr<Coffee> coffee;

        if (coffeeType == 1) {
            coffee = std::make_unique<BlackCoffee>(); // 创建一个 BlackCoffee 类型的智能指针
        }
        else if (coffeeType == 2) {
            coffee = std::make_unique<Latte>();
        }
        else {
            std::cout << "Invalid coffee type" << std::endl;
            continue;
        }

        // 根据输入添加调料
        if (condimentType == 1) {
            /*
            * std::make_unique<MilkDecorator>(std::move(coffee)) 创建一个 MilkDecorator 类型的智能指针。
            * std::move(coffee) 操作将原有的 coffee 指针的所有权转移到新创建的 MilkDecorator 对象中。
            * 在 MilkDecorator 的构造函数中，通过调用父类 Decorator 的构造函数，std::move(coffee) 传递的 unique_ptr<Coffee> 参数将初始化 Decorator 类中的 coffee 成员变量
            * 将通过 std::make_unique<MilkDecorator> 返回的 unique_ptr 重新赋值给 coffee 变量。这意味着现在 coffee 指向的是一个装饰过的咖啡对象，具有添加牛奶的功能。
            */
            coffee = std::make_unique<MilkDecorator>(std::move(coffee));
        }
        else if (condimentType == 2) {
            coffee = std::make_unique<SugarDecorator>(std::move(coffee));
        }
        else {
            std::cout << "Invalid condiment type" << std::endl;
            continue;
        }

        // 输出制作过程
        coffee->brew();
    }

    return 0;
}
