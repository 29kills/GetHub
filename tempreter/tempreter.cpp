#include<iostream>
//using namespace std;
//�����¶�=�����¶�*9.0/5.0+32
int main()
{
	const unsigned short ADD_SUBTRACT=32 ;//�궨��
	const double RATIO =9.0/5.0;
	double tempIn,tempOut;//�¶��������������
	char typeIn,typeOut;//�¶��������������

	while(1)
	{
		std::cout <<"�����¶�ֵ�����ͣ�xx.x c/f):";
		std::cin >>tempIn>>typeIn;
		std::cin.ignore(100,'\n');//��������ʱ�Ļس����β�໥��������ͣ������
		std::cout <<'\n';
		switch(typeIn)//ת������ѡ��
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
		 std::cout<<"��������"<<'\n';
		}
	}
   std::cout <<"�����������������!"<<"\n";
   std::cin.get();//��ͣ
	   return 0;

}