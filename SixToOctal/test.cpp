//十六进制转8进制
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string *s1,*s2;
	int n;
	int i,j,k;
	cin>>n;
	s1 = new string[n];
	s2 = new string[n];
	for(i = 0; i < n; i++)
		cin >> s1[i];
	for(i=0;i<n;i++)
	{
		for(j=0;j<s1[i].length();j++)
		{
			switch(s1[i][j])
			{
			case '0':s2[i]+="0000";break;
			case '1':s2[i]+="0001";break;
			case '2':s2[i]+="0010";break;
			case '3':s2[i]+="0011";break;
			case '4':s2[i]+="0100";break;
			case '5':s2[i]+="0101";break;
			case '6':s2[i]+="0110";break;
			case '7':s2[i]+="0111";break;
			case '8':s2[i]+="1000";break;
			case '9':s2[i]+="1001";break;
			case 'A':s2[i]+="1010";break;
			case 'B':s2[i]+="1011";break;
			case 'C':s2[i]+="1100";break;
			case 'D':s2[i]+="1101";break;
			case 'E':s2[i]+="1110";break;
			case 'F':s2[i]+="1111";break;
			default:break;
			}
		}
		if(s2[i].length()%3==1)
		s2[i]="00"+s2[i];
		if(s2[i].length()%3==2)
		s2[i]="0"+s2[i];
		int flag=0;
		for(k=0;k<s2[i].length()-2;k+=3)
		{
			int p=4*(s2[i][k]-'0')+2*(s2[i][k+1]-'0')+s2[i][k+2]-'0';
			if(p)
			flag=1;
			if(flag)
			cout<<p;
			} 
			cout<<endl;
		} 
		return 0;
}
