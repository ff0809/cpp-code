#include<iostream>
using namespace std;

class CPU
{
public:
	virtual void cal() = 0;
};
class Card
{
public:
	virtual void show() = 0;
};
class Memory
{
public:
	virtual void save() = 0;
};
class computer
{
private:
	CPU* m_cpu;
	Card* m_card;
	Memory* m_mem;
public:
	computer(CPU* cpu, Card* card, Memory* mem) :m_cpu(cpu), m_card(card), m_mem(mem) {};
	void work()
	{
		m_cpu->cal();
		m_card->show();
		m_mem->save();
	}
	~computer()
	{
		if (m_cpu != NULL)
		{
			delete m_cpu;
			m_cpu = NULL;
		}
		if (m_card != NULL)
		{
			delete m_card;
			m_card = NULL;
		}
		if (m_mem != NULL)
		{
			delete m_mem;
			m_mem = NULL;
		}
	}
};
class CPUI :public CPU
{
	virtual void cal()
	{
		cout << "¼ÆËã" << endl;
	}
};
class CardI :public Card
{
	virtual void show()
	{
		cout << "ÏÔÊ¾" << endl;
	}
};
class MemoryI :public Memory
{
	virtual void save()
	{
		cout << "´æ´¢" << endl;
	}
};
void test()
{
	CPU* cpui = new CPUI;
	Card* cardi = new CardI;
	Memory* memoryi = new MemoryI;
	
	computer* computeri = new computer(cpui, cardi, memoryi);
	computeri->work();
	delete computeri;
}
int main() 
{
	test();
}