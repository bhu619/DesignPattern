#include<iostream>

using namespace std;

// 目标接口: 根据用户输入选择
// 适配器类
// 被适配者

class USB {
public:
	virtual void chargeWithUSB() = 0;
	virtual ~USB() {}
};

class TypeC {
public:
	virtual void chargeWithTypeC() = 0;
	virtual ~TypeC() {}
};

// 适配器类: TypeC接口适配USB充电器
class USBAdapter : public USB {
public:
	void chargeWithUSB() override {
		std::cout << "USB Adapter" << std::endl;
	}
};

// 新电脑类，使用 TypeC 接口
class NewComputer : public TypeC {
private:
	USBAdapter* adapter;

public:
	// 构造函数中初始化 adapter
	NewComputer(USBAdapter* adapter) : adapter(adapter) {}
	// C口充电
	void chargeWithTypeC() override
	{
		std::cout << "TypeC" << std::endl;
	}

	void chargeWithUSB() {
		adapter->chargeWithUSB();
	}

	~NewComputer() { delete adapter; }
};



// 适配器充电器类，使用 USB 接口
class AdapterCharger : public USB {
public:
	void chargeWithUSB() override {
		std::cout << "USB Adapter" << std::endl;
	}
};

int main() {
	int n; // 表示后面有N组测试数据。
	cin >> n;

	int type; // 充电类型
	USBAdapter* newadapter = new USBAdapter();
	NewComputer* computer = new NewComputer(newadapter);
	while (n--) {
		cin >> type;
		if (type == 1) {
			// 1表示使用电脑本身的TypeC接口
			computer->chargeWithTypeC();
		}
		else if (type == 2) {
			// 2表示使用扩展坞的USB接口充电。
			computer->chargeWithUSB();
		}
		else {
			cout << "Wrong Charge Type!" << endl;
		}
	}
	delete computer;
	return 0;
}