#include <iostream>
#include <vector>

using namespace std;

// 抽象主题
class House {
public:
    virtual void show() = 0;
    virtual ~House() {}
};

// 真实主题
class RealHouse : public House {
private:
    int m_area;
public:
    RealHouse(int area) : m_area(area) {}

    void show() override {
        cout << "YES" << endl;
    }

    int getArea() {
        return this->m_area;
    }
};

// 代理类
class Proxy : public House {
private:
    RealHouse* m_house;

public:
    Proxy(int area) {
        m_house = new RealHouse(area);
    }

    void show() override {
        if (this->m_house->getArea() > 100) m_house->show();
        else cout << "NO" << endl;
    }

    ~Proxy() {
        if (m_house) {
            delete m_house;
            m_house = nullptr;
        }
    }
};

int main() {

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int area;
        cin >> area;
        House* proxy = new Proxy(area);
        proxy->show();
        delete proxy;
    }

    return 0;
}