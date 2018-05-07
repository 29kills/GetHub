#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char* ch = (char*)malloc(sizeof(char)*10);
	strcpy(ch,"123456789");
	printf("%d\n",strlen(ch));
	printf("%p\n",ch);

	ch =(char*) realloc(ch,5);//内存空间被缩小，当个数为空时，返回NULL
	printf("%p\n",ch);
	strcpy(ch,"789");
	printf("%d\n",strlen(ch));//空间被回收，可访问，但不可使用，否则会崩溃
	printf("%p",ch);
	printf("%s",ch);
	
	ch =(char*) realloc(ch,5);
	strcpy(ch,"1234");
	printf("%d\n",strlen(ch));
	
	return 0;
}
