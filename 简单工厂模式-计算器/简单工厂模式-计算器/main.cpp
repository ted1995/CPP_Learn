#include<iostream>
using namespace std;


enum oper
{
	Add = 1,
	Sub,
	Multi,
	Div
};

//操作接口类
class InterOperation
{
public:
	//虚函数用来继承，子类重新实现
	virtual double get_result(double a, double b) = 0;
};

//加类
class OperationAdd :public InterOperation
{
public:
	virtual double get_result(double a, double b)
	{
		return a + b;
	}
};

//减类
class OperationSub :public InterOperation
{
public:
	virtual double get_result(double a, double b)
	{
		return a - b;
	}
};

//乘类
class OperationMulti :public InterOperation
{
public:
	virtual double get_result(double a, double b)
	{
		return a * b;
	}
};

//除类
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

//工厂类
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
			//实例化子类的对象，让父类指向此对象
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


//计算器类
class caculator
{
public:
	//构造函数初始化，传入工厂类对象
	caculator(SimpleFactory* simfact)
	{
		_simfact = simfact;
	}
	//调用工厂类成员方法得到具体操作实例,并计算结果
	double operation(double a, double b, int type)
	{	
		InterOperation* op = _simfact->CreateOper(type);
		return op->get_result(a, b);
	}
private:
	SimpleFactory* _simfact;
};


//计算器接口
void mycaculator(double a, double b, oper myoper)
{
	//实例化工厂
	SimpleFactory* sf = new SimpleFactory;
	//传入工厂对象
	caculator cacu(sf);
	double result=cacu.operation(a, b, myoper);
	cout << result << endl;
}


int main()
{
	mycaculator(1, 2, Div);
}


//基类是个抽象类，只有一个纯虚函数，运算类继承基类并重载运算函数，以实现用基类指针指向所有的运算类实例化对象，并调用运算类内的方法
//工厂类负责根据传入的参数实例化具体的运算类对象
//计算器类根据用户的需求产生相应的计算结果
//用户输入运算需求，计算类实例化工厂类，并根据需求获取相应的运算类实例，由基类指针指向此运算实例，运算实例调用相应的运算方法得出计算结果。