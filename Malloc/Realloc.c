#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char* ch = (char*)malloc(sizeof(char)*10);
	strcpy(ch,"123456789");
	printf("%d\n",strlen(ch));
	printf("%p\n",ch);

	ch =(char*) realloc(ch,5);//�ڴ�ռ䱻��С��������Ϊ��ʱ������NULL
	printf("%p\n",ch);
	strcpy(ch,"789");
	printf("%d\n",strlen(ch));//�ռ䱻���գ��ɷ��ʣ�������ʹ�ã���������
	printf("%p",ch);
	printf("%s",ch);
	
	ch =(char*) realloc(ch,5);
	strcpy(ch,"1234");
	printf("%d\n",strlen(ch));
	
	return 0;
}
