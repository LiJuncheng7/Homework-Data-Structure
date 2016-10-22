/*
 *	注:由于时间原因,此程序实现较为简单，实现了基本功能，但数据检测没有非常全面的覆盖，项目和学院的名称有所简化，
 *	   相关功能也可改进，比如文件数据检测可以列出所有错误的类型和精确位置，望老师原谅;
 *	   功能结构框架由控制函数sports_meeting中的文字提示展示;
 *	
 * 存储结构:最终成绩长久保存在文件中，当需要查询成绩时便读取文件数据;
 *			两个结构体:一个代表项目，数据成员包括项目优秀学院数,每一个学院的积分(优秀学院给予相应积分，其余学院积分为0)、优秀学院排名及名称;
 *					   另一个代表学院，数据成员包括学院名称、女生团体总分、男生团体总分、团体总分、每一个项目的排名、每个项目的积分;
 *		    两个数组:分别存储全部项目和全部学院，数组下标即项目或学院的编号;
 *		    四个map对象:分别表示项目和学院的名称与编号的映射;
 *		    
 * 使用方法:一个排序输出函数、一个查询函数、一个数据检测函数、一个数据读取函数、一个整体进程控制函数;
 * 
 * 数据测试:第一：测试的数据包括文件数据、终端数据两个方面，主要涉及项目名称、项目优秀学院数、学院名称、学院积分的检测;
 *          第二：为简单考虑，这里的学院名称采用200+N的形式，例如有10个学院的，则名称是201到210，项目名称类似，是101到100+N，均以字符串形式存储；
 *				  当然也可以将学院和项目的名称储存在文件中，每次到文件中查找判断;
 *          第三：对于文件数据采用修改部分文件数据进行测试，当读取数据时检测到有错的一行则停止读取并报错（位置），如果全部是错误数据，则报第一行为错误;
 *                对于终端数据有三种时候需要检测，写入项目所有成绩、查询项目前几名以及查询某个学院在某个项目中的成绩;
 *                写入项目成绩时首先检测项目名称、项目优秀学院数的正确性，正确则继续执行，否则重新输入;
 *                对于输入每一个学院的名称和积分，当检测到有错误时立即重新输入或者退出程序;
 *          注:文件数据完全正确如4_item_right.txt,数据部分正确如4_item_part.txt,数据完全错误(由于检测到错误就报错，个人认为这个测试似乎没有意义)
 *             终端数据则实时输入违法数据即可;
 *             测试结果:程序基本功能运行成功（我也不知道怎么表示，难道截图？）
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define M 4    //Number of men's item;
#define W 3    //Number of women's item;
#define S 10   //Number of schools;

map<string, int> schools_name;       //Conversion between school name and school number;
map<int, string> arc_schools_name;
map<string, int> items_name;         //Conversion between item name and item number;
map<int, string> arc_items_name;

//Struct item stands for an item;
struct item
{
	item() :grade(S, 0) {}

	int flag = 0;            //Number of outstanding schools;
	vector<int> grade;       //Grades of all schools in this item;
	vector<int> outstanding; //Outstanding schools in this item sorting by their rank;

	//Get and sort outstanding schools in this item;
	void sort()
	{
		//Get outstanding schools' name;
		for (int i = 0; i != S; ++i)
			if (grade[i])
				outstanding.push_back(i);

		//Insertion sort;
		for (int i = 1, j; i != flag; ++i)
		{
			int temp = outstanding[i];
			for (j = i; j > 0 && grade[temp] > grade[outstanding[j - 1]]; --j)
				outstanding[j] = outstanding[j - 1];
			outstanding[j] = temp;
		}
	}
};

vector<item> items(M + W);   //All the items;

//Struct school stands for a school;
struct school
{
	school() :grade(M + W, 0), rank(M + W, 0){}

	int school_name = 0;   //Name of school;
	int girls_sum = 0;     //Total score of girls;
	int boys_sum = 0;      //Total score of boys;
	int sum = 0;           //Total score of school;
	vector<int> grade;     //Grades in all the items;
	vector<int> rank;      //Rank in all the items;

	//Get grades and rank in all the items;
	void get_information()
	{
		for (int i = 0; i != M + W; ++i)
		{
			grade[i] = items[i].grade[school_name];
			if (items[i].flag == 3)
				switch (grade[i])
				{
					case 5:rank[i] = 1; break;
					case 3:rank[i] = 2; break;
					case 2:rank[i] = 3; break;
					default:rank[i] = 0; break;
				}
			else
				switch (grade[i])
				{
					case 7:rank[i] = 1; break;
					case 5:rank[i] = 2; break;
					case 3:rank[i] = 3; break;
					case 2:rank[i] = 4; break;
					case 1:rank[i] = 5; break;
					default:rank[i] = 0; break;
				}
		}
	}

	//Get total score of girls,boys ans school in all the items;
	void get_sum()
	{
		for (int i = 0; i != M; ++i)
			boys_sum += grade[i];
		for (int j = M; j != M + W; ++j)
			girls_sum += grade[j];
		sum = boys_sum + girls_sum;
	}
};

vector<school> schools(S);           //All the schools;

//Comparison functions used to sort grades among schools;
bool comparison_school_num(const school &lhs, const school &rhs) { return lhs.school_name < rhs.school_name; }
bool comparison_school_sum(const school &lhs, const school &rhs) { return lhs.sum > rhs.sum; }
bool comparison_girls_sum(const school &lhs, const school &rhs) { return lhs.girls_sum > rhs.girls_sum; }
bool comparison_boys_sum(const school &lhs, const school &rhs) { return lhs.boys_sum > rhs.boys_sum; }

//Sort grades by given method and output the result;
void sort_information(int flag)
{
	switch(flag)
	{
		case 1:sort(schools.begin(), schools.end(), comparison_school_num); break;  //Sort by school name;
		case 2:sort(schools.begin(), schools.end(), comparison_school_sum); break;  //Sort by total score  of school;
		case 3:sort(schools.begin(), schools.end(), comparison_girls_sum); break;   //Sort by total score of girls;
		case 4:sort(schools.begin(), schools.end(), comparison_boys_sum); break;    //Sort by total score of boys;
		default:break;
	}

	for (auto &elem : schools)
	{
		cout << arc_schools_name[elem.school_name] << " school:"
			<< "sum = " << elem.sum << "\t"
			<< "sum of girls = " << elem.girls_sum << "\t"
			<< "sum of boys = " << elem.boys_sum << endl << endl;
	}
}

//Inquiry different information by given method;
void inquiry(int flag)
{
	switch(flag)
	{
		case 1://school name;
			sort_information(1);break;
		case 2://school score
			sort_information(2);break;
		case 3://girls' score
			sort_information(3);break;
		case 4://boys' score
			sort_information(4);break;
		case 5://inquiry item
			{
				cout << "Please enter name of item:";
				string item; cin >> item; int i = 0;

				cout << "The first " << items[items_name[item]].flag << " schools are: ";
				for (const auto &n : items[items_name[item]].outstanding)
					cout << arc_schools_name[n] << "(" << ++i << ") ";
				cout << endl;
				break;
			}
		case 6://inquiry school and item
			{
				cout << "Please enter name of school and number of item:";
				string school_name, item_name;cin >> school_name >> item_name;

				cout << "score = " << schools[schools_name[school_name]].grade[items_name[item_name]] << "\t";
				cout << "rank = " << schools[schools_name[school_name]].rank[items_name[item_name]] << endl;
				break;
			}
		default:break;
	}
}

//Check if the data read or input is correct,including school name and grade;
bool check_name_grade(const string &school, const string &grade, const string &flag)
{
	int school_name = stoi(school);
	int school_grade = stoi(grade);
	
	//Check the name of school;
	if (!(school_name > 200 && school_name < 200 + S + 1))
		return false;

	//Check the grade of school;
	if (flag == "5")
		if (!(school_grade == 7 || school_grade == 5 || school_grade == 3 || school_grade == 2 || school_grade == 1 || school_grade == 0))
			return false;
	if (flag == "3")
		if (!(school_grade == 5 || school_grade == 3 || school_grade == 2 || school_grade == 0))
			return false;

	return true;
}

//Init conversion rule between name and relative number;
//Read data from the file and check whether if it is safe;
bool read_data()
{
	//Init conversion rule;
	for (int i = 0, j = 201; i != S; ++i, ++j)
	{
		string s = to_string(j);
		schools_name[s] = i;
		arc_schools_name[i] = s;
	}
	for (int i = 0, j = 101; i != M + W; ++i, ++j)
	{
		string s = to_string(j);
		items_name[s] = i;
		arc_items_name[i] = s;
	}

	//Read data from file;
	ifstream in("D:/My Filename/Learning_Files/数据结构与算法/hws/4_items.txt");
	if (!in)
		return false;

	string line;      //Save current line read just now;
	int counter = 0;  //Record number of current line; 
	while(getline(in,line))
	{
		++counter;
		istringstream is(line);
		string item, flag;
		is >> item >> flag;

		//Check if name of the item and number of outstanding schools which kept in the file is correct;
		int item_num = stoi(item);
		int outstanding = stoi(flag);
		if (!(item_num > 100 && item_num < 100 + M + W + 1 && (outstanding == 5 || outstanding == 3)))
		{
			cout << "There is something wrong in the " << counter << "th line!" << endl;
			exit(1);
		}

		items[items_name[item]].flag = stoi(flag);
		string school, grade;   //Save name and grade;
		while (is >> school >> grade)
		{
			//Check if the information is correct;
			if (!check_name_grade(school, grade, flag))
			{
				cout << "There is something wrong at the " << counter << "th line in the file!" << endl;
				exit(1);
			}

			int score = stoi(grade);
			items[items_name[item]].grade[schools_name[school]] = score;
		}
	}

	//Init basic information of schools;
	for (int i=0;i!=S;++i)
	{
		schools[i].school_name = i;
		schools[i].get_information();
		schools[i].get_sum();
	}
	for (int i = 0; i != M + W; ++i)
		items[i].sort();

	return true;
}

//Control the whole process;
void sports_meeting()
{
	int order;//Save the operation order;
	do
	{
		cout << "请按照功能提示输入指令:\n1.写入成绩\n2.查询成绩\n0.结束程序" << endl; cin >> order;
		if (order == 1)
		{
			ofstream out("D:/My Filename/Learning_Files/数据结构与算法/hws/4_items.txt", ofstream::out | ofstream::app);
			if (!out)
			{
				cerr << "Fail to open the file!" << endl;
				exit(0);
			}

			//Input name of the item and its number of outstanding schools;
			string item, flag;
			bool pass;//Record validity of the information;
			do
			{
				pass = true;
				cout << "请输入项目名称:"; cin >> item;
				cout << "项目取前几名为优秀:"; cin >> flag;
				if (item == "0")break;

				//Check if the information is correct;
				int item_num = stoi(item);
				int outstanding = stoi(flag);
				if (!(item_num > 100 && item_num < 100 + M + W + 1 && (outstanding == 5 || outstanding == 3)))pass = false;
				if (!pass)
					cout << "输入数据有误,请重新输入! 或者输入‘0 0’返回上一级:" << endl;
			} while (!pass);

			//Input name and grade of schools;
			if (item != "0")
			{
				string school, grade, line = item + " " + flag + "\t";
				cout << "请输入学院名称、学院成绩（int），以空格区分,输入‘0 0’结束:";
				while (cin >> school >> grade)
				{
					if (school == "0")break;
					bool _pass = true;
					do
					{
						_pass = check_name_grade(school, grade, flag);
						if (!_pass)
						{
							cout << "输入数据有误,请重新输入!\n" << "请输入学院名称、学院成绩（int），以空格区分：";
							cin >> school >> grade;
						}
					} while (!_pass);
					line += ("\t" + school + " " + grade);
				}
				out << "\n" + line;
			}
		}

		if (order == 2)
		{
			read_data();

			cout << "1.按照学院名称排序输出\n2.按照学院总分降序输出\n3.按照女子团体总分降序输出\n"
				"4.按照男子团体总分降序输出\n5.查询单个项目成绩\n6.查询某个学院在某个项目的成绩\n7.返回上一级" << endl;
			while (cin >> order)
			{
				if (order == 7)break;
				inquiry(order);
				cout << "1.按照学院名称排序输出\n2.按照学院总分降序输出\n3.按照女子团体总分降序输出\n"
					"4.按照男子团体总分降序输出\n5.查询单个项目成绩\n6.查询某个学院在某个项目的成绩\n7.返回上一级" << endl;
			}
		}
	} while (order);
}

int main()
{
	sports_meeting();
	return 0;
}