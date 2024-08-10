#include<iostream>

using namespace std;

// Ŀ��ӿ�: �����û�����ѡ��
// ��������
// ��������

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

// ��������: TypeC�ӿ�����USB�����
class USBAdapter : public USB {
public:
	void chargeWithUSB() override {
		std::cout << "USB Adapter" << std::endl;
	}
};

// �µ����࣬ʹ�� TypeC �ӿ�
class NewComputer : public TypeC {
private:
	USBAdapter* adapter;

public:
	// ���캯���г�ʼ�� adapter
	NewComputer(USBAdapter* adapter) : adapter(adapter) {}
	// C�ڳ��
	void chargeWithTypeC() override
	{
		std::cout << "TypeC" << std::endl;
	}

	void chargeWithUSB() {
		adapter->chargeWithUSB();
	}

	~NewComputer() { delete adapter; }
};



// ������������࣬ʹ�� USB �ӿ�
class AdapterCharger : public USB {
public:
	void chargeWithUSB() override {
		std::cout << "USB Adapter" << std::endl;
	}
};

int main() {
	int n; // ��ʾ������N��������ݡ�
	cin >> n;

	int type; // �������
	USBAdapter* newadapter = new USBAdapter();
	NewComputer* computer = new NewComputer(newadapter);
	while (n--) {
		cin >> type;
		if (type == 1) {
			// 1��ʾʹ�õ��Ա����TypeC�ӿ�
			computer->chargeWithTypeC();
		}
		else if (type == 2) {
			// 2��ʾʹ����չ���USB�ӿڳ�硣
			computer->chargeWithUSB();
		}
		else {
			cout << "Wrong Charge Type!" << endl;
		}
	}
	delete computer;
	return 0;
}