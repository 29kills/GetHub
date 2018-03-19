#include<iostream>
//using namespace std;
//华氏温度=摄氏温度*9.0/5.0+32
int main()
{
	const unsigned short ADD_SUBTRACT=32 ;//宏定义
	const double RATIO =9.0/5.0;
	double tempIn,tempOut;//温度输入于输出变量
	char typeIn,typeOut;//温度类型输入与输出

	while(1)
	{
		std::cout <<"输入温度值和类型（xx.x c/f):";
		std::cin >>tempIn>>typeIn;
		std::cin.ignore(100,'\n');//忽略输入时的回车与结尾相互作用起到暂停的作用
		std::cout <<'\n';
		switch(typeIn)//转化类型选择
	  {
		case 'c':
		case 'C':
			tempOut=tempIn*RATIO+ADD_SUBTRACT;
			typeOut='F';
			typeIn='C';
			break;
		case 'F':
		case 'f':
			tempOut=(tempIn-ADD_SUBTRACT)/RATIO;
			typeOut='C';
			typeIn='F';
			break;
		default :
			typeIn='E';	
	  }
		if(typeIn!='E')
		{
		std::cout<<tempIn<<typeIn<<"="<<tempOut<<typeOut<<'\n';
		break;
		}
		else
		{
		 std::cout<<"typeIn ERROR!"<<'\n';
		 std::cout<<"重新输入"<<'\n';
		}
	}
   std::cout <<"输入任意键结束程序!"<<"\n";
   std::cin.get();//暂停
	   return 0;

}