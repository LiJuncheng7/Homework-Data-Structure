/*
 *	ע:����ʱ��ԭ��,�˳���ʵ�ֽ�Ϊ�򵥣�ʵ���˻������ܣ������ݼ��û�зǳ�ȫ��ĸ��ǣ���Ŀ��ѧԺ�����������򻯣�
 *	   ��ع���Ҳ�ɸĽ��������ļ����ݼ������г����д�������ͺ;�ȷλ�ã�����ʦԭ��;
 *	   ���ܽṹ����ɿ��ƺ���sports_meeting�е�������ʾչʾ;
 *	
 * �洢�ṹ:���ճɼ����ñ������ļ��У�����Ҫ��ѯ�ɼ�ʱ���ȡ�ļ�����;
 *			�����ṹ��:һ��������Ŀ�����ݳ�Ա������Ŀ����ѧԺ��,ÿһ��ѧԺ�Ļ���(����ѧԺ������Ӧ���֣�����ѧԺ����Ϊ0)������ѧԺ����������;
 *					   ��һ������ѧԺ�����ݳ�Ա����ѧԺ���ơ�Ů�������ܷ֡����������ܷ֡������ܷ֡�ÿһ����Ŀ��������ÿ����Ŀ�Ļ���;
 *		    ��������:�ֱ�洢ȫ����Ŀ��ȫ��ѧԺ�������±꼴��Ŀ��ѧԺ�ı��;
 *		    �ĸ�map����:�ֱ��ʾ��Ŀ��ѧԺ���������ŵ�ӳ��;
 *		    
 * ʹ�÷���:һ���������������һ����ѯ������һ�����ݼ�⺯����һ�����ݶ�ȡ������һ��������̿��ƺ���;
 * 
 * ���ݲ���:��һ�����Ե����ݰ����ļ����ݡ��ն������������棬��Ҫ�漰��Ŀ���ơ���Ŀ����ѧԺ����ѧԺ���ơ�ѧԺ���ֵļ��;
 *          �ڶ���Ϊ�򵥿��ǣ������ѧԺ���Ʋ���200+N����ʽ��������10��ѧԺ�ģ���������201��210����Ŀ�������ƣ���101��100+N�������ַ�����ʽ�洢��
 *				  ��ȻҲ���Խ�ѧԺ����Ŀ�����ƴ������ļ��У�ÿ�ε��ļ��в����ж�;
 *          �����������ļ����ݲ����޸Ĳ����ļ����ݽ��в��ԣ�����ȡ����ʱ��⵽�д��һ����ֹͣ��ȡ������λ�ã������ȫ���Ǵ������ݣ��򱨵�һ��Ϊ����;
 *                �����ն�����������ʱ����Ҫ��⣬д����Ŀ���гɼ�����ѯ��Ŀǰ�����Լ���ѯĳ��ѧԺ��ĳ����Ŀ�еĳɼ�;
 *                д����Ŀ�ɼ�ʱ���ȼ����Ŀ���ơ���Ŀ����ѧԺ������ȷ�ԣ���ȷ�����ִ�У�������������;
 *                ��������ÿһ��ѧԺ�����ƺͻ��֣�����⵽�д���ʱ����������������˳�����;
 *          ע:�ļ�������ȫ��ȷ��4_item_right.txt,���ݲ�����ȷ��4_item_part.txt,������ȫ����(���ڼ�⵽����ͱ���������Ϊ��������ƺ�û������)
 *             �ն�������ʵʱ����Υ�����ݼ���;
 *             ���Խ��:��������������гɹ�����Ҳ��֪����ô��ʾ���ѵ���ͼ����
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
	ifstream in("D:/My Filename/Learning_Files/���ݽṹ���㷨/hws/4_items.txt");
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
		cout << "�밴�չ�����ʾ����ָ��:\n1.д��ɼ�\n2.��ѯ�ɼ�\n0.��������" << endl; cin >> order;
		if (order == 1)
		{
			ofstream out("D:/My Filename/Learning_Files/���ݽṹ���㷨/hws/4_items.txt", ofstream::out | ofstream::app);
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
				cout << "��������Ŀ����:"; cin >> item;
				cout << "��Ŀȡǰ����Ϊ����:"; cin >> flag;
				if (item == "0")break;

				//Check if the information is correct;
				int item_num = stoi(item);
				int outstanding = stoi(flag);
				if (!(item_num > 100 && item_num < 100 + M + W + 1 && (outstanding == 5 || outstanding == 3)))pass = false;
				if (!pass)
					cout << "������������,����������! �������롮0 0��������һ��:" << endl;
			} while (!pass);

			//Input name and grade of schools;
			if (item != "0")
			{
				string school, grade, line = item + " " + flag + "\t";
				cout << "������ѧԺ���ơ�ѧԺ�ɼ���int�����Կո�����,���롮0 0������:";
				while (cin >> school >> grade)
				{
					if (school == "0")break;
					bool _pass = true;
					do
					{
						_pass = check_name_grade(school, grade, flag);
						if (!_pass)
						{
							cout << "������������,����������!\n" << "������ѧԺ���ơ�ѧԺ�ɼ���int�����Կո����֣�";
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

			cout << "1.����ѧԺ�����������\n2.����ѧԺ�ֽܷ������\n3.����Ů�������ֽܷ������\n"
				"4.�������������ֽܷ������\n5.��ѯ������Ŀ�ɼ�\n6.��ѯĳ��ѧԺ��ĳ����Ŀ�ĳɼ�\n7.������һ��" << endl;
			while (cin >> order)
			{
				if (order == 7)break;
				inquiry(order);
				cout << "1.����ѧԺ�����������\n2.����ѧԺ�ֽܷ������\n3.����Ů�������ֽܷ������\n"
					"4.�������������ֽܷ������\n5.��ѯ������Ŀ�ɼ�\n6.��ѯĳ��ѧԺ��ĳ����Ŀ�ĳɼ�\n7.������һ��" << endl;
			}
		}
	} while (order);
}

int main()
{
	sports_meeting();
	return 0;
}