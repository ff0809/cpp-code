#include<iostream>
using namespace std;

template<class T>
class myarray
{
private:
	int m_capacity;
	int m_size;
	T* paddress;
public:
	//有参构造
	myarray(int capacity)
	{
		cout << "有参构造" << endl;
		m_capacity = capacity;
		m_size = 0;
		paddress = new T[m_capacity];
	}
	//拷贝构造
	myarray(const myarray& arr)
	{
		cout << "拷贝构造" << endl;
		m_capacity = arr.m_capacity;
		m_size = arr.m_size;
		//深拷贝
		paddress = new T[arr.m_capacity];
		for (int i = 0; i < m_size; i++)
		{
			paddress[i] = arr.paddress[i];
		}
	}
	//operator=防止浅拷贝问题
	myarray& operator=(const myarray& arr)
	{
		cout << "operator=构造" << endl;
		//原有堆区若有数据则先释放
		if (paddress != NULL)
		{
			delete[]paddress;
			paddress = NULL;
			m_capacity = 0;
			m_size = 0;
		}
		//深拷贝
		m_capacity = arr.m_capacity;
		m_size = arr.m_size;
		paddress = new T[arr.m_capacity];
		for (int i = 0; i < m_size; i++)
		{
			paddress[i] = arr.paddress[i];
		}
		return *this;
	}

	//operator[]重载运算符
	T& operator[](int index)
	{
		return paddress[index];
	}

	//尾插法
	void insert(const T& val)
	{
		if (m_size == m_capacity)
		{
			return;
		}
		paddress[m_size] = val;
		m_size++;
	}
	//尾删法
	void del()
	{
		if (m_size > 0)
		{
			m_size--;
		}
	}
	//获取数组容量
	int getcapacity()
	{
		return m_capacity;
	}
	//获取数组元素个数
	int getsize()
	{
		return m_size;
	}

	//析构函数
	~myarray()
	{
		cout << "析构" << endl;
		if (paddress != NULL)
		{
			delete[]paddress;
			paddress = NULL;
		}
	}
};