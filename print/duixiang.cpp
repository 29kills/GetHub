#include<iostream>
#include<stdlib.h>
#include<Windows.h>
class Car//������
{
public://��������//���к����ɵ���
	std::string color;
	std::string engine;
	unsigned int gas;//���в��ɳ�ʼ��
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
	std::cout<<"���������:";
    std::cin>>liter;
	sgas=gas;
	if((sgas+=liter)<=100)//ע���ж�����ı������ֵ�����м���������ֹԭ�������ı�
	{
		gas+=liter;
	}
	else
	{
		std::cout<<"�����������ֵ��������ֵӦ�����ڣ�"<<100-gas<<'\n';
		std::cout <<"����";
		Car::fillTank();//�ݹ�
	}
}
int Car::running (void)
{
	std::cout <<"ʣ��"<<100*gas/100<<"%"<<"����\n";
	std::cout <<"��120���ٶ��ƶ�"<<'\n';
	gas--;
	return gas;
}
void Car::warning (void)
{
	std::cout<<"��ʣ��"<<100*gas/100<<"%"<<"����\n";

}
int main()
{
	char i;
	Car mycar;//�����ഴ��һ������
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
		std::cout <<"���ͣ�(Y/N)\n";
		std::cin>>i;
		if('Y'==i||'y'==i)
		{
			mycar.fillTank();
		}
	}
	if(mycar.gas<=0)
	{
		std::cout <<"�����ˣ�"<<'\n';
		break;
	}
}
	system("pause");
    return 0;
}