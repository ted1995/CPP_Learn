#include<iostream>
using namespace std;


enum oper
{
	Add = 1,
	Sub,
	Multi,
	Div
};

//�����ӿ���
class InterOperation
{
public:
	//�麯�������̳У���������ʵ��
	virtual double get_result(double a, double b) = 0;
};

//����
class OperationAdd :public InterOperation
{
public:
	virtual double get_result(double a, double b)
	{
		return a + b;
	}
};

//����
class OperationSub :public InterOperation
{
public:
	virtual double get_result(double a, double b)
	{
		return a - b;
	}
};

//����
class OperationMulti :public InterOperation
{
public:
	virtual double get_result(double a, double b)
	{
		return a * b;
	}
};

//����
class OperationDiv :public InterOperation
{
public:
	virtual double get_result(double a, double b)
	{
		if (b == 0)
		{
			cout << "DIV ERROR" << endl;
		}
		return a / b;
	}
};

//������
class SimpleFactory
{
public:
	virtual InterOperation* CreateOper(int type)
	{
		InterOperation* inoper = NULL;
		switch (type)
		{
		case 1:
		{
			//ʵ��������Ķ����ø���ָ��˶���
			inoper = new OperationAdd();
			break;
		}
		case 2:
		{
			inoper = new OperationSub();
			break;
		}
		case 3:
		{
			inoper = new OperationMulti();
			break;
		}
		case 4:
		{
			inoper = new OperationDiv();
			break;
		}
		default:
		{
			cout << "caculate error" << endl;
			break;
		}
		}
		return inoper;
	}
};


//��������
class caculator
{
public:
	//���캯����ʼ�������빤�������
	caculator(SimpleFactory* simfact)
	{
		_simfact = simfact;
	}
	//���ù������Ա�����õ��������ʵ��,��������
	double operation(double a, double b, int type)
	{	
		InterOperation* op = _simfact->CreateOper(type);
		return op->get_result(a, b);
	}
private:
	SimpleFactory* _simfact;
};


//�������ӿ�
void mycaculator(double a, double b, oper myoper)
{
	//ʵ��������
	SimpleFactory* sf = new SimpleFactory;
	//���빤������
	caculator cacu(sf);
	double result=cacu.operation(a, b, myoper);
	cout << result << endl;
}


int main()
{
	mycaculator(1, 2, Div);
}


//�����Ǹ������ֻ࣬��һ�����麯����������̳л��ಢ�������㺯������ʵ���û���ָ��ָ�����е�������ʵ�������󣬲������������ڵķ���
//�����ฺ����ݴ���Ĳ���ʵ������������������
//������������û������������Ӧ�ļ�����
//�û������������󣬼�����ʵ���������࣬�����������ȡ��Ӧ��������ʵ�����ɻ���ָ��ָ�������ʵ��������ʵ��������Ӧ�����㷽���ó���������