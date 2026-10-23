//#include<iostream>
//#include<vector>
//#include<string>
//#include<deque>
//#include<algorithm>
//#include<ctime>
//using namespace std;
//
//class person
//{
//public:
//	string m_name;
//	int m_score;
//	person(string name, int score)
//	{
//		m_name = name;
//		m_score = score;
//	}
//};
//
//void add(vector<person>& v)
//{
//	string nameseed = "ABCDE";
//	for (int i = 0; i < 5; i++)
//	{
//		string name = "Ñ¡ÊÖ";
//		int score = 0;
//		name += nameseed[i];
//		person p(name, score);
//		v.push_back(p);
//	}
//}
//void givescore(vector<person>& v)
//{
//	for (vector<person>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		deque<int>d;
//		int sum = 0, avg = 0;
//		for (int i = 0; i < 10; i++)
//		{
//			d.push_back(rand() % 61 + 40);
//		}
//		sort(d.begin(), d.end());
//		d.pop_back();
//		d.pop_front();
//		for (int i = 0; i < d.size(); i++)
//		{
//			sum += d[i];
//		}
//		avg = sum /d.size();
//		(*it).m_score = avg;
//	}
//}
//
//void show(const vector<person>& v)
//{
//	for (int i = 0; i < 5; i++)
//	{
//		cout << v[i].m_name << " " << v[i].m_score << endl;
//	}
//}
//
//int main()
//{
//	srand((unsigned int)time(NULL));
//	vector<person>v;
//	add(v);
//	givescore(v);
//	show(v);
//}
