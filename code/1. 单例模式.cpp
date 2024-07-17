#include <iostream>
#include <map>
#include <vector>

using namespace std;

class ShoppingCartManager {
public:

    /* 引用返回 : getInstance() 方法返回对 instance 的引用。
    *  返回引用而不是对象的副本是至关重要的，因为这保证了所有通过 getInstance() 获取的 ShoppingCartManager 引用都指向同一个实例，这正是单例模式所要确保的。
    */
    static ShoppingCartManager& getInstance() {
        /* 局部静态变量: 方法中的 instance 被声明为静态局部变量。
        * 在C++中，局部静态变量在第一次执行到该变量声明的位置时被初始化，
        * 之后即便函数调用结束，它的值也不会被销毁，而是保持其状态直到下次调用。
        */
        static ShoppingCartManager instance;
        return instance;
    }

    void addCart(const string& itemName, int num) {
        if (myCart.find(itemName) == myCart.end()) {
            order.push_back(itemName);
        }
        myCart[itemName] += num;
    }

    void showCart() const {
        for (const auto& item : order) { // &使用引用，避免不必要的拷贝，提高效率
            cout << item << ' ' << myCart.at(item) << endl;
        }
        return;
    }
private:
    ShoppingCartManager() {} // 私有构造函数，确保一个类仅有一个实例，并提供一个全局访问点到该实例。
    map<string, int> myCart; // map 底层实现为红黑树
    vector<string> order; // 用于保持插入顺序
};

int main() {
    string name;
    int num;
    while (cin >> name >> num) {
        ShoppingCartManager& cart = ShoppingCartManager::getInstance();
        cart.addCart(name, num);
    }
    const ShoppingCartManager& cart = ShoppingCartManager::getInstance();
    cart.showCart();

    return 0;
}