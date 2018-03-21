#include<iostream>
#include<stdlib.h>
#include<Windows.h>
class Car//创建类
{
public://公共属性//所有函数可调用
	std::string color;
	std::string engine;
	unsigned int gas;//类中不可初始化
	unsigned int wheel;
	unsigned int liter;

	void setColor (std::string col);
	void setEngine(std::string eng);
	void setWheel(unsigned int whe);
	void fillTank(void);
	int running(void);
	void warning (void);
};

void Car::setColor(std::string col)
{
	color=col;
}
void Car::setEngine(std::string eng)
{
	engine=eng;
}
void Car::setWheel(unsigned int whe)
{
	wheel=whe;
}
void Car::fillTank()
{
	int sgas;
	getchar();
	std::cout<<"输入加油量:";
    std::cin>>liter;
	sgas=gas;
	if((sgas+=liter)<=100)//注意判断语句会改变变量的值，用中间变量替代防止原变量被改变
	{
		gas+=liter;
	}
	else
	{
		std::cout<<"油量超过最大值，输入数值应不大于："<<100-gas<<'\n';
		std::cout <<"重新";
		Car::fillTank();//递归
	}
}
int Car::running (void)
{
	std::cout <<"剩余"<<100*gas/100<<"%"<<"油量\n";
	std::cout <<"以120的速度移动"<<'\n';
	gas--;
	return gas;
}
void Car::warning (void)
{
	std::cout<<"还剩余"<<100*gas/100<<"%"<<"油量\n";

}
int main()
{
	char i;
	Car mycar;//根据类创建一个对象
	mycar.setColor("WHITE");
	mycar.setEngine("US");
	mycar.setWheel(4);
	mycar.liter=100;
	mycar.gas=mycar.liter;
	while(mycar.running())
{
	if(mycar.running()<10)
	{
		mycar.warning();
		std::cout <<"加油？(Y/N)\n";
		std::cin>>i;
		if('Y'==i||'y'==i)
		{
			mycar.fillTank();
		}
	}
	if(mycar.gas<=0)
	{
		std::cout <<"无油了！"<<'\n';
		break;
	}
}
	system("pause");
    return 0;
}