#include"speechmanager.h"

speechmanager::speechmanager()
{
	init();
	create();
	load();
}

void speechmanager::menu()
{
	cout << "--------------------------------------------------" << endl;
	cout << "***********  欢迎使用演讲比赛管理系统  ***********" << endl;
	cout << "**********        1.开始演讲比赛        **********" << endl;
	cout << "**********        2.查看往届记录        **********" << endl;
	cout << "**********        3.清空比赛记录        **********" << endl;
	cout << "**********        0.退出比赛系统        **********" << endl;
	cout << "--------------------------------------------------" << endl;
}

void speechmanager::exitsystem()
{
	cout << "确认退出吗？（y/n）" << endl;
	char c;
	cin >> c;
	if (c == 'y' || c == 'Y')
	{
		cout << "欢迎下次使用" << endl;
		exit(0);
	}
	else
	{
		system("pause");
		system("cls");
	}
}

void speechmanager::init()
{
	v1.clear();
	v2.clear();
	v3.clear();
	m.clear();
	m_index = 0;  // 0表示第一轮，1表示第二轮
	m_record.clear();
	isempty = true;
}

void speechmanager::create()
{
	speaker sp;
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name = "选手";
		name += nameseed[i];
		sp.m_name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_score[j] = 0;
		}
		v1.push_back(i + 10001);
		m.insert(make_pair(i + 10001, sp));
	}
}

void speechmanager::begin()
{
	// 第一轮比赛
	choose();
	contest();
	showresult();
	m_index++;  // 进入第二轮

	// 第二轮比赛
	choose();
	contest();
	showresult();
	save();

	// 重置系统
	init();
	create();
	load();
	system("pause");
	system("cls");
}

void speechmanager::choose()
{
	cout << "第" << m_index + 1 << "轮比赛选手正在抽签" << endl;
	cout << "----------------------------------------" << endl;
	cout << "抽签后演讲顺序如下:" << endl;

	if (m_index == 0)  // 第一轮选手
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
	}
	else  // 第二轮选手
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
	}
	cout << endl;
	system("pause");
}

void speechmanager::contest()
{
	multimap<double, int, greater<double>> mm;
	int num = 0;

	cout << "第" << m_index + 1 << "轮比赛正式开始" << endl;
	cout << "------------------------------------" << endl;

	vector<int> v4;
	if (m_index == 0)
	{
		v4 = v1;  // 第一轮参赛选手
	}
	else
	{
		v4 = v2;  // 第二轮参赛选手
	}

	for (vector<int>::iterator it = v4.begin(); it != v4.end(); it++)
	{
		num++;
		deque<double> d;

		// 10个评委打分
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.0f;
			d.push_back(score);
		}

		// 排序后去掉最高最低分
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();

		// 计算平均分
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / double(d.size());

		// 保存分数（0或1，不越界）
		m[*it].m_score[m_index] = avg;
		mm.insert(make_pair(avg, *it));

		// 每6人一组，取前3晋级
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "组比赛成绩" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = mm.begin(); mit != mm.end(); mit++)
			{
				cout << "编号：" << mit->second << " 姓名：" << m[mit->second].m_name << " 平均分：" << m[mit->second].m_score[m_index] << endl;
			}

			int count = 0;
			for (multimap<double, int, greater<double>>::iterator mit = mm.begin(); mit != mm.end() && count < 3; mit++, count++)
			{
				if (m_index == 0)
				{
					v2.push_back(mit->second);  // 第一轮晋级到v2
				}
				else
				{
					v3.push_back(mit->second);  // 第二轮晋级到v3
				}
			}
			mm.clear();
		}
	}

	cout << "第" << m_index + 1 << "轮比赛结束" << endl;
	cout << "------------------------------------" << endl;
	system("pause");
}

void speechmanager::showresult()
{
	vector<int> v;
	if (m_index == 0)
	{
		v = v2;
		cout << "第一轮比赛晋级选手：" << endl;
		for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		{
			cout << "编号：" << *it << " 姓名：" << m[*it].m_name << " 平均分：" << m[*it].m_score[m_index] << endl;
		}
	}
	else
	{
		v = v3;
		cout << "第二轮比赛最终结果（冠亚季军）：" << endl;
		// 只显示前三名及第二轮分数
		for (int i = 0; i < 3 && i < v.size(); i++)
		{
			string rank;
			if (i == 0) rank = "冠军";
			else if (i == 1) rank = "亚军";
			else rank = "季军";

			cout << rank << "：编号" << v[i]
				<< " 姓名：" << m[v[i]].m_name
				<< " 第二轮分数：" << m[v[i]].m_score[m_index] << endl;
		}
	}
	cout << endl;
	system("pause");
	system("cls");
	menu();
}

void speechmanager::save()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	// 只保存前三名及第二轮分数
	for (size_t i = 0; i < v3.size() && i < 3; i++)
	{
		ofs << v3[i] << ","  // 编号
			<< m[v3[i]].m_score[1];  // 只保存第二轮分数
		if (i != 2) ofs << ",";
	}
	ofs << endl;
	ofs.close();

	cout << "保存成功！" << endl;
	isempty = false;
	cout << "本届比赛完毕！" << endl;
}

void speechmanager::load()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		isempty = true;
		ifs.close();
		return;
	}

	m_record.clear();
	string data;
	int index = 0;

	// 读取整行数据
	while (getline(ifs, data))
	{
		vector<string> v;
		size_t start = 0;
		size_t pos;

		while (true)
		{
			pos = data.find(',', start);
			if (pos == string::npos)
			{
				v.push_back(data.substr(start));
				break;
			}
			v.push_back(data.substr(start, pos - start));
			start = pos + 1;
		}
		m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	isempty = m_record.empty();
}

void speechmanager::find()
{
	if (isempty)
	{
		cout << "文件不存在或为空！" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++)
		{
			cout << "第" << it->first + 1 << "届比赛结果：" << endl;
			if (it->second.size() >= 6)  // 确保数据完整
			{
				cout << "冠军：编号" << it->second[0] << " 分数：" << it->second[1] << endl;
				cout << "亚军：编号" << it->second[2] << " 分数：" << it->second[3] << endl;
				cout << "季军：编号" << it->second[4] << " 分数：" << it->second[5] << endl;
			}
			cout << "------------------------------------" << endl;
		}
	}
	system("pause");
	system("cls");
}

void speechmanager::clear()
{
	cout << "确认清空吗？（y/n)" << endl;
	char ch;
	cin >> ch;
	if (ch == 'y' || ch == 'Y')
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		init();
		create();
		load();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

speechmanager::~speechmanager()
{

}
