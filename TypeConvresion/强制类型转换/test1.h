#include<iostream>
#include<string>
using namespace std;

void Insert(size_t pos,int x)//C�е���ʽת��
{
	for(int i=x;i>=pos;i--)//��ѭ��������ʽ��intת����size_t,������ѭ��
	{
		cout << i << endl;
	}
}

void test1()//C++�еľ�̬ת��
{
	int i=48;
	//C++�еľ�̬ת�����������ת����������C�е���ʽת����
	char ch=static_cast<char>(i);//static_char ��һ���� �൱��һ���ؼ���
	cout << i  << endl ;
	cout << ch << endl;

	//���������ת��������C�е�ǿ������ת��,(�����ɲ�д������ֱ��ʹ�ú�������ʹ�ú�����ַ�������ܴ��ڿ�ƽ̨����)
	int* p=&i;
	int j=reinterpret_cast<int>(p);//int* --->int ;
	cout << p << endl;
	cout << j << endl;

	//const���ε�����ת����const���εı�����ʵ���Ըı䣬�����׳��ִ��󣨼Ĵ���ֵ���ڴ�ֵ����ͬ���⣩��
	const int a = 2;//const ���εı�����������������Ż����ڼĴ����У��ڴ���Ҳ��ŵ��У����Ĵ�����ַ����ȡ����
	//volatile const int a = 2;//const ���εı�����volatile �ڴ�ɼ���ֱ�ӽ�aֵ�����ڴ��У������ڼĴ�����
	int* p2 = const_cast<int*>(&a);
	*p2 = 3; //a���ڴ��е�ֵ���޸ģ��Ĵ����е�ֵδ�޸ģ����׵��´���
	cout << a << endl;//aȡ���ǼĴ�����ֵ����Ȼ��2
	cout << *p2 << endl; //*p2���ڴ��е�ֵ��3
}

class A
{
public :
	virtual void fun()//���б������麯���������
	{}
public :
	int _a;
};

class B : public A
{
public :
	int _b;
};

void dynamic_test(A *pa)
{
    B* pb;
	pb = dynamic_cast<B*>(pa);//��ȫת��,������ת������0������ת��
	if(pb)
		cout << "paָ������,��ȫ,��ת��" << endl;
	else
		cout << "paָ���࣬����ȫ������ת��" <<endl; 
}

void AB_test()
{
	A aa;//�������
	B bb;//�������
	A* pa;//����ָ��
	B* pb;//����ָ��

	//pb = &aa;//����ָ�벻��ָ������󣬼����ܽ�����Ķ��������ָ��
	pb = &bb;//���ָ��ֻ��ָ���Լ��Ķ��󣬻�ָ������Ķ��󣬲���ָ����Ķ���

	pa = &aa; //����ָ��ָ�������
	pb = (B*)pa;//������ָ��paǿת������ָ�루����ȫת����
	//pb->_b=10;//���ڣ�paָ�������(&aa),������_b������ǿת�����_bԽ��
	dynamic_test(pa);

	pa = &bb;//����ָ��ָ���������
	pb = (B*)pa;//������ָ��paǿת������ָ�� ������ȫת����
	pb->_b = 10;//paָ���������(&bb),����_b������ǿת�����_b����Խ��
	dynamic_test(pa);
	cout << pb->_b << endl;
}

class C
{
public :
	//explicit C(int x)//���������죬�ӹؼ���explicit��׼�������ʽ����ת��
	C(int x)//���������죬�������ʽ����ת��
		:_c(x)//��ʼ�������б�
	{
		cout << "C(int x)" << endl;
	}
	C(const C& x)//��������
	{
		cout << "C(const C& x)" << endl;
	}

	C& operator = (const C& c)//��ֵ����
	{
		_c=c._c;
		return *this;
	}
public:
	int _c;
};

void string_test()
{
	string s1("1111");//ֱ�ӹ���һ��s1����
	string s2="1111";//��ʽ����ת�� + (���� + �������� + �Ż�)==����

	char* ch1="1111";//���ݱ��������ֳ�������ջ�б�����ָ��ĳ�������ַ��ch1��
	char ch2[]="1111";//��ջ�п���һ���ڴ�ռ䣬�������

	cout << sizeof(s1) <<endl ;//һ��string����Ϊ28/32���ֽ�
	cout << sizeof(s2) << endl ;
	
	cout << sizeof(ch1) << endl;//��ַռ4���ֽ�
	cout << sizeof(ch2) << endl;//�����С�����ַ����ĳ��ȣ���������'\0'5��

	//���������캯�����Ż�
	C c1(4);//�������ֱ�ӵ��ù��캯��
	C c2=5;//�������󣬽����Ż�����ù��캯������ʽ����ת����
	cout << c1._c << endl;
	cout << c2._c << endl;

	c2=c1;//��ֵ����
	cout << c2._c << endl;
}