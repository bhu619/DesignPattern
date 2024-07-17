#include <iostream>
#include <vector>
#include <memory> // 包含智能指和内存管理相关功能

using namespace std;

// 抽象积木接口
class Block {
public:
    virtual void produce() = 0; // 纯虚函数, 定义接口
    virtual ~Block() = default; // 基类析构函数
};

// 圆形积木实现
class CircleBlock : public Block {
public:
    void produce() override {
        cout << "Circle Block" << endl;
    }
};

// 方形积木实现
class SquareBlock : public Block {
public:
    void produce() override {
        cout << "Square Block" << endl;
    }
};

// 抽象积木工厂接口
class BlockFactory {
public:
    virtual unique_ptr<Block> createBlock() = 0;
    virtual ~BlockFactory() = default;
};

// 圆形积木工厂实现
class CircleBlockFactory : public BlockFactory {
public:
    unique_ptr<Block> createBlock() override {
        /* make_unique 函数模板：
        * std::make_unique 是一个函数模板，用于创建一个类型为 T 的对象，并返回一个指向该对象的 std::unique_ptr。
        * 它可以接受构造函数的参数，并将这些参数转发给对象的构造函数。

        * <CircleBlock>：
        * 这里的 CircleBlock 是模板参数，表示我们要创建的对象类型是 CircleBlock。

        * ()：
        * 这个括号表示没有传递给 CircleBlock 构造函数的参数，即使用默认构造函数来创建 CircleBlock 对象。
        */
        return make_unique<CircleBlock>();
    }
};

// 方形积木工厂实现
class SquareBlockFactory : public BlockFactory {
public:
    unique_ptr<Block> createBlock() override{
        return make_unique<SquareBlock>();
    }
};

// 积木工厂系统
class BlockFactorySystem {
private:
    vector<unique_ptr<Block>> blocks;

public:
    void produceBlocks(BlockFactory& factory, int nums) {
        for (int i = 0; i < nums; ++i) {
            unique_ptr<Block> block = factory.createBlock(); // 调用了 BlockFactory 的 createBlock 方法，通过工厂模式创建了一个新的 Block 对象，并将其包装在 std::unique_ptr 中。
            block->produce(); // 调用了 Block 对象的 produce 方法。
            blocks.push_back(move(block));
        }
    }

    const vector<unique_ptr<Block>>& getBlocks() const {
        return blocks;
    }
};

int main() {
    int n; // 代表生产的次数
    string blockName;
    int blockNum;
    cin >> n;

    // 创建积木工厂系统
    BlockFactorySystem factorySystem;

    // 创建具体工厂对象
    CircleBlockFactory circleFactory;
    SquareBlockFactory squareFactory;

    while (n--) {
        cin >> blockName >> blockNum;

        if (blockName == "Circle") {
            factorySystem.produceBlocks(circleFactory, blockNum);
        }
        else if (blockName == "Square") {
            factorySystem.produceBlocks(squareFactory, blockNum);
        }
    }

    return 0;
}