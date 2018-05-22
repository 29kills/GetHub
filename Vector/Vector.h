#pragma once

typedef int DataType;

class Vector
{
public:
	Vector()
		:_first(NULL)
		,_finish(NULL)
		,_endofstorage(NULL)
	{}

	Vector(const Vector& v)
	{
		if (v.Size() > 0)
		{
			_first = new DataType[v.Size()];
			memcpy(_first, v._first, sizeof(DataType)*v.Size());

			_finish = _first + v.Size();
			_endofstorage = _first + v.Size();
		}
		else
		{
			_first = _finish = _endofstorage = NULL;
		}
	}

	// v1 = v2
	//Vector& operator=(const Vector& v)
	//{
	//	if (this != &v)
	//	{
	//		if (v.Size() > 0)
	//		{
	//			DataType* tmp = new DataType[v.Size()];
	//			memcpy(tmp, v._first, sizeof(DataType)*v.Size());

	//			delete[] _first;

	//			_first = tmp;
	//			_finish = _first + v.Size();
	//			_endofstorage = _first + v.Size();
	//		}
	//		else
	//		{
	//			_finish = _first;
	//		}	
	//	}

	//	return *this;
	//}

	// v1 = v2
	Vector& operator=(Vector v)
	{
		swap(_first, v._first);
		swap(_finish, v._finish);
		swap(_endofstorage, v._endofstorage);

		return *this;
	}


	~Vector()
	{
		delete[] _first;
		_first = _finish = _endofstorage = NULL;
	}

	size_t Size() const
	{
		return _finish-_first;
	}

	size_t Capacity() const
	{
		return _endofstorage-_first;
	}

	void Expand(size_t n)
	{
		if (n > Capacity())
		{
			size_t size = Size();
			DataType* tmp = new DataType[n];

			if (_first)
			{
				memcpy(tmp, _first, sizeof(DataType)*Size());
				delete[] _first;
			}

			_first = tmp;
			_finish = _first + size;
			_endofstorage = _first + n;
		}
	}

	void PushBack(DataType x)
	{
	/*	if (_finish == _endofstorage)
		{
			if (Capacity() == 0)
			{
				Expand(3);
			}
			else
			{
				Expand(Capacity()*2);
			}
		}

		*_finish = x;
		++_finish;*/

		Insert(Size(), x);
	}

	void Reserve(size_t n)
	{
		if (n > Capacity())
		{
			Expand(n);
		}
	}

	void PopBack()
	{
		assert(_finish > _first);
		--_finish;
	}

	void Insert(size_t pos, DataType x)
	{
		assert(pos <= Size());
		if (_finish == _endofstorage)
		{
			if (Capacity() == 0)
				Expand(3);
			else
				Expand(Capacity()*2);
		}
		
		int end = Size()-1;
		while (end >= (int)pos)
		{
			_first[end+1] = _first[end];
			--end;
		}

		_first[pos] = x;
		++_finish;
	}

	void Erase(size_t pos)
	{
		assert(pos < Size());

		size_t cur = pos;
		while (cur < Size()-1)
		{
			_first[cur] = _first[cur+1];
			++cur;
		}

		--_finish;
	}

	size_t Find(DataType x);

	void Print()
	{
		DataType* cur = _first;
		while (cur != _finish)
		{
			cout<<*cur<<" ";
			++cur;
		}
		cout<<endl;
	}

private:
	DataType* _first;
	DataType* _finish;
	DataType* _endofstorage;
};

void TestVector()
{
	Vector v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.Print();

	Vector v2(v1);
	v2.Print();

	Vector v3;
	v3 = v1;
	v3.Print();


	v1.Insert(0, 0);
	v1.Print();
	v1.Erase(0);
	v1.Print();
}