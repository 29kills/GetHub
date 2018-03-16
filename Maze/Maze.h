#pragma once
#include<iostream>
#include<stack>
#include<string.h>
#include<assert.h>

using namespace std;

#define ROW 6
#define LOW 6

struct Pos
{
	size_t _x;
	size_t _y;
};
typedef Pos pos;

class maze
{
public:
	maze()//拷贝构造函数的参数需使用引用，否则会造成循环递归
	{}

	void maze_Init(const int mp[][LOW])
	{
		//memmove(map,mp,sizeof(mp));
		int i = 0;
		int j = 0;
		for(i = 0;i < ROW;i++)
		{
			for(j = 0;j < LOW;j++)
			{
				map[i][j] = mp[i][j];
			}
		}
	}

	void maze_print()
	{
		int i = 0;
		int j = 0;
		for(i = 0;i < ROW;i++)
		{
			for(j = 0;j < LOW;j++)
			{
				printf("%2d ",map[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	void Maze_run(const pos& enter)//非递归
	{
		pos next;
		stack<pos> s;//使用栈，栈存结构体变量
		s.push(enter);//入口入栈
		while(!s.empty())
		{
			pos cur = s.top();
			s.pop();
			map[cur._x][cur._y] = 2;
			if(Exit(&cur,&enter))//到达出口,cur,且不为入口
			{
				return;
			}//退出
			//up
			next = cur;
			next._x -= 1;
			if(can(next))//可走？
			{
				s.push(next);
			}//入栈
			//right
			next = cur;
			next._y += 1; 
			if(can(next))//可走？
			{
				s.push(next);
			}//入栈
			//down
			next = cur;
			next._x += 1;
			if(can(next))//可走？
			{
				s.push(next);
			}//入栈
			//left
			next = cur;
			next._y -= 1;
			if(can(next))//可走？
			{
				s.push(next);
			}//入栈
			//maze_print();
		}
	}

	void Min(pos* enter)
	{
		size_t i = 0;
		stack<pos> s_cur;
		stack<pos> s_min;
		Min_run(enter,s_cur,s_min,enter);
		cout << "路径长" << s_min.size()<< endl;
		while(!s_min.empty())
		{
			cout << s_min.top()._x << ' ';
			cout << s_min.top()._y << ' ';
			s_min.pop();
			cout << endl;
		}
  	}
	void Min_run(pos* next,stack<pos>& s_cur,stack<pos>& s_min,pos* enter)//最短路径
	{
		pos cur;
		//pos next;
		if(!s_cur.empty())//栈不为空
		{
			cur = s_cur.top();//栈顶
			map[next->_x][next->_y] = map[cur._x][cur._y] + 1 ;
		}
		s_cur.push(*next);

		if(Exit(next,enter))//到达出口,cur,且不为入口
		{
			if(s_cur.size() < s_min.size() || s_min.empty())
				s_min = s_cur;//调用栈的拷贝构造实现栈的赋值
		}
		//up
		cur = *next;
		cur._x -= 1;
		if(can2(&cur,next))//可走？
		{
             Min_run(&cur,s_cur,s_min,enter);
		}
		//right
		cur = *next;
		cur._y += 1;
		if(can2(&cur,next))//可走？
		{
             Min_run(&cur,s_cur,s_min,enter);
		}
		//down
		cur = *next;
		cur._x += 1;
		if(can2(&cur,next))//可走？
		{
             Min_run(&cur,s_cur,s_min,enter);
		}
		//left
		cur = *next;
		cur._y -= 1;
		if(can2(&cur,next))//可走？
		{
             Min_run(&cur,s_cur,s_min,enter);
		}
	
		s_cur.pop();//不满足的出栈
	}
	bool can2(pos* cur,pos* next)
	{
		//在范围内 且 下一位置（cur）未走过或比当前位置数据大 
		if((cur->_x >=0 && cur->_x < ROW && cur->_y >= 0 && cur->_y < LOW)&&
			(map[cur->_x][cur->_y] == 1 || map[cur->_x][cur->_y] > map[next->_x][next->_y]))
			return true;
		return false;
	}

	bool Exit(const pos* cur,const pos* enter)
	{
		if(!(cur->_x == enter->_x && cur->_y == enter->_y))//不为入口
		{
			if((cur->_x == 0 || cur->_x == ROW-1 || cur->_y == 0 || cur->_y == LOW-1))//到达出口
			return true;
			else
			return false;
		}
		return false;
	}
	bool can(const pos& next)
	{
		if(map[next._x][next._y] == 1)
			return true;
		return false;
	}

private:
	int map[ROW][LOW];
};

void test()
{
	pos enter = {5,1};//入口
	int mp[][LOW]={
		{0,0,0,0,0,0},
		{0,1,1,1,1,0},
		{0,1,0,0,1,1},
		{0,1,0,0,1,0},
		{0,1,1,1,1,1},
		{0,2,0,1,0,0}};

		maze m1;
		m1.maze_Init(mp);
		m1.maze_print();

		//m1.Maze_run(enter);//非递归
		//m1.maze_print();
		m1.Min(&enter);//递归
		m1.maze_print();
}
