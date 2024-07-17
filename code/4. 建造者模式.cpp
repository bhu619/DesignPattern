#include <iostream>
#include <string>
#include <memory>

using namespace std;

/*
* 小明家新开了一家自行车工厂，用于使用自行车配件（车架 frame 和车轮 tires ）进行组装定制不同的自行车，包括山地车和公路车。
* 山地车使用的是Aluminum Frame（铝制车架）和 Knobby Tires（可抓地轮胎），
* 公路车使用的是 Carbon Frame （碳车架）和 Slim Tries。
* 现在它收到了一笔订单，要求定制一批自行车，
* 请你使用【建造者模式】告诉小明这笔订单需要使用那些自行车配置吧。
*/

// 产品 抽象建造者 具体建造者 指导者
// 自行车产品
class Bike {
public:
    string frame;
    string tires;

    void setFrame(const std::string& frame) {
        // this 是一个指向当前对象的指针。
        // this->frame 是当前对象的 frame 成员变量。
        this->frame = frame;
    }

    void setTires(const std::string& tires) {
        this->tires = tires;
    }

    // 友元函数 
    // 类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。
 //   friend ostream& operator<<(ostream& os, const Bike& bike) {
 //       os << bike.frame << " " << bike.tires;
 //       return os;
//    }
};

// 自行车建造者接口
class BikeBuilder {
public:
    virtual void buildFrame() = 0;
    virtual void buildTires() = 0;
    virtual Bike getResult() = 0;
    virtual ~BikeBuilder() = default; // 虚析构函数以确保派生类的析构函数被调用
};

// 山地自行车建造者
class MountainBikeBuilder : public BikeBuilder {
private:
    Bike bike;

public:
    void buildFrame() override {
        bike.setFrame("Aluminum Frame");
    }

    void buildTires() override {
        bike.setTires("Knobby Tires");
    }

    Bike getResult() override {
        return bike;
    }
};

// 公路自行车建造者
class RoadBikeBuilder : public BikeBuilder {
private:
    Bike bike;

public:
    void buildFrame() override {
        bike.setFrame("Carbon Frame");
    }

    void buildTires() override {
        bike.setTires("Slim Tires");
    }

    Bike getResult() override {
        return bike;
    }
};

// 自行车Director，负责构建自行车
class BikeDirector {
public:
    Bike construct(BikeBuilder& builder) {
        builder.buildFrame();
        builder.buildTires();
        return builder.getResult();
    }
};


int main() {
    int n; // 订单数量
    cin >> n;

    // 在C++中，BikeDirector director; 是在栈上分配一个 BikeDirector 对象。
    // 当在栈上分配对象时，不需要手动调用 delete 来释放内存，因为当该对象超出作用域时，C++ 会自动调用对象的析构函数，并释放与该对象相关的内存。

    // 相比之下，在堆上分配对象时，例如通过 new 关键字，需要手动调用 delete 来释放内存，以避免内存泄漏。
    // 这也是使用智能指针（如 std::unique_ptr 和 std::shared_ptr）的一个重要原因，因为它们会自动管理内存释放，
    // 防止内存泄漏。
    BikeDirector director;

    while (n--) {
        string Type;
        cin >> Type;

        unique_ptr<BikeBuilder> builder;

        if (Type == "mountain") {
            builder = make_unique<MountainBikeBuilder>();
        }
        else if (Type == "road") {
            builder = make_unique<RoadBikeBuilder>();
        }
        else {
            cout << "Wrong Type!" << endl;
            return 0;
        }

        Bike bike = director.construct(*builder);
        cout << bike.frame << " " << bike.tires << endl;
    }

    return 0;
}