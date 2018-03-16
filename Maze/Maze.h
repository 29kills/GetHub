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
	maze()//�������캯���Ĳ�����ʹ�����ã���������ѭ���ݹ�
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
	void Maze_run(const pos& enter)//�ǵݹ�
	{
		pos next;
		stack<pos> s;//ʹ��ջ��ջ��ṹ�����
		s.push(enter);//�����ջ
		while(!s.empty())
		{
			pos cur = s.top();
			s.pop();
			map[cur._x][cur._y] = 2;
			if(Exit(&cur,&enter))//�������,cur,�Ҳ�Ϊ���
			{
				return;
			}//�˳�
			//up
			next = cur;
			next._x -= 1;
			if(can(next))//���ߣ�
			{
				s.push(next);
			}//��ջ
			//right
			next = cur;
			next._y += 1; 
			if(can(next))//���ߣ�
			{
				s.push(next);
			}//��ջ
			//down
			next = cur;
			next._x += 1;
			if(can(next))//���ߣ�
			{
				s.push(next);
			}//��ջ
			//left
			next = cur;
			next._y -= 1;
			if(can(next))//���ߣ�
			{
				s.push(next);
			}//��ջ
			//maze_print();
		}
	}

	void Min(pos* enter)
	{
		size_t i = 0;
		stack<pos> s_cur;
		stack<pos> s_min;
		Min_run(enter,s_cur,s_min,enter);
		cout << "·����" << s_min.size()<< endl;
		while(!s_min.empty())
		{
			cout << s_min.top()._x << ' ';
			cout << s_min.top()._y << ' ';
			s_min.pop();
			cout << endl;
		}
  	}
	void Min_run(pos* next,stack<pos>& s_cur,stack<pos>& s_min,pos* enter)//���·��
	{
		pos cur;
		//pos next;
		if(!s_cur.empty())//ջ��Ϊ��
		{
			cur = s_cur.top();//ջ��
			map[next->_x][next->_y] = map[cur._x][cur._y] + 1 ;
		}
		s_cur.push(*next);

		if(Exit(next,enter))//�������,cur,�Ҳ�Ϊ���
		{
			if(s_cur.size() < s_min.size() || s_min.empty())
				s_min = s_cur;//����ջ�Ŀ�������ʵ��ջ�ĸ�ֵ
		}
		//up
		cur = *next;
		cur._x -= 1;
		if(can2(&cur,next))//���ߣ�
		{
             Min_run(&cur,s_cur,s_min,enter);
		}
		//right
		cur = *next;
		cur._y += 1;
		if(can2(&cur,next))//���ߣ�
		{
             Min_run(&cur,s_cur,s_min,enter);
		}
		//down
		cur = *next;
		cur._x += 1;
		if(can2(&cur,next))//���ߣ�
		{
             Min_run(&cur,s_cur,s_min,enter);
		}
		//left
		cur = *next;
		cur._y -= 1;
		if(can2(&cur,next))//���ߣ�
		{
             Min_run(&cur,s_cur,s_min,enter);
		}
	
		s_cur.pop();//������ĳ�ջ
	}
	bool can2(pos* cur,pos* next)
	{
		//�ڷ�Χ�� �� ��һλ�ã�cur��δ�߹���ȵ�ǰλ�����ݴ� 
		if((cur->_x >=0 && cur->_x < ROW && cur->_y >= 0 && cur->_y < LOW)&&
			(map[cur->_x][cur->_y] == 1 || map[cur->_x][cur->_y] > map[next->_x][next->_y]))
			return true;
		return false;
	}

	bool Exit(const pos* cur,const pos* enter)
	{
		if(!(cur->_x == enter->_x && cur->_y == enter->_y))//��Ϊ���
		{
			if((cur->_x == 0 || cur->_x == ROW-1 || cur->_y == 0 || cur->_y == LOW-1))//�������
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
	pos enter = {5,1};//���
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

		//m1.Maze_run(enter);//�ǵݹ�
		//m1.maze_print();
		m1.Min(&enter);//�ݹ�
		m1.maze_print();
}
