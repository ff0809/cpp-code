//#include<iostream>
//using namespace std;
//
//class teacher;
//class student
//{
//private:
//	string name;
//	int id;
//	int score;
//public:
//	student(string n, int i, int s) :name(n), id(i), score(s) {}
//	friend class teacher;
//};
//class teacher
//{
//private:
//	string tname;
//public:
//	teacher(string tn):tname(tn){}
//	void update(student&stu,int newscore)
//	{
//		stu.score = newscore;
//		cout << tname << "修改" << stu.name << "的成绩为" << stu.score << endl;
//	}
//	void printinfo(student&stu)
//	{
//		cout << "姓名" << stu.name << "学号" << stu.id << "当前成绩" << stu.score << endl;
//	}
//};
//void test()
//{
//	student stu("费凡", 2454259, 80);
//	teacher tea("李艳");
//	tea.printinfo(stu);
//	tea.update(stu, 85);
//	tea.printinfo(stu);
//}
//int main()
//{
//	test();
//}