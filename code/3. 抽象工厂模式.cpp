#include <iostream>
#include <string>

using namespace std;

/* 小明家新开了两个工厂用来生产家具，一个生产现代风格的沙发和椅子，
 * 一个生产古典风格的沙发和椅子，
 * 现在工厂收到了一笔订单，请你帮他设计一个系统，描述订单需要生产家具的信息。
*/

// 抽象产品类: 沙发 和 椅子
class Chair {
public:
    virtual void showInfo() = 0;
};

class Sofa {
public:
    virtual void displayInfo() = 0;
};

// 具体产品类: 具体沙发和椅子
class ModernChair : public Chair {
public:
    void showInfo() override {
        std::cout << "modern chair" << std::endl;
    }
};

class ClassicalChair : public Chair {
public:
    void showInfo() override {
        std::cout << "classical chair" << std::endl;
    }
};

class ModernSofa : public Sofa {
public:
    void displayInfo() override {
        std::cout << "modern sofa" << std::endl;
    }
};

class ClassicalSofa : public Sofa {
public:
    void displayInfo() override {
        std::cout << "classical sofa" << std::endl;
    }
};

// 抽象家居工厂接口
class FurnitureFactory {
public:
    virtual Chair* createChair() = 0;
    virtual Sofa* createSofa() = 0;
};

// 具体现代风格家居工厂
class ModernFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() override {
        return new ModernChair();
    }

    Sofa* createSofa() override {
        return new ModernSofa();
    }
};

// 具体古典风格家居工厂
class ClassicalFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() override {
        return new ClassicalChair();
    }

    Sofa* createSofa() override {
        return new ClassicalSofa();
    }
};

int main() {
    int n; //订单数量
    cin >> n;

    while (n--) {
        string Type;
        cin >> Type;

        FurnitureFactory* factory = nullptr;

        if (Type == "modern") {
            factory = new ModernFurnitureFactory();
        }
        else if (Type == "classical") {
            factory = new ClassicalFurnitureFactory();
        }
        else {
            cout << "Wrong Type!" << endl;
            return 0;
        }

        Chair* chair = factory->createChair();
        Sofa* sofa = factory->createSofa();

        chair->showInfo();
        sofa->displayInfo();
    }
    return 0;
}