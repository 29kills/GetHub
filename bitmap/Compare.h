
#ifndef __COMPARE_H__

#define __COMPARE_H__

#include<stdio.h>
size_t SDBMHash(const char *str);
size_t RSHash(const char *str);
size_t APHash(const char *str);
size_t JSHash(const char *str);
size_t DEKHash(const char* str);



size_t SDBMHash(const char *str)
{
	size_t hash = 0;
	size_t ch = 0;
	while(ch = (size_t)*str++)
	{
		hash = 65599 * hash + ch;
	}
	return hash;
}

size_t RSHash(const char *str)
{ 
	size_t hash = 0;
	size_t magic = 63689;
	size_t ch = 0;
	while (ch = (size_t)*str++)
	{
		hash = hash * magic + ch;
		magic *= 378551;
	}
	return hash;
}

size_t APHash(const char *str)
{
	size_t hash = 0;
	size_t ch;
	long i = 0;
	for (; ch = (size_t)*str++; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
		}
	}
	return hash;
}

size_t JSHash(const char *str)
{
	size_t hash = 1315423911;
	size_t ch = 0;

	if(!*str)
		return 0;
	
	while (ch = (size_t)*str++)
	{
		hash ^= ((hash << 5) + ch + (hash >> 2));
	}
	return hash;
}

size_t DEKHash(const char* str)
{
    size_t hash = 1315423911;
	size_t ch = 0;

	if(!*str)
		return 0;

	while (ch = (size_t)*str++)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ ch;
	}
	return hash;
}




#endif