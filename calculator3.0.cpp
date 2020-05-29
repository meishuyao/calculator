/*
Simple calculator

Revision history:
	Originally written by Mei Shuyao April 2020
	Second editon by Mei Shuyao April 2020
	Third edition by Mei Shuyao May 2020

This program implements a basic expression calculator.
Designed for pyhsics and engineering cases.
Support user_defined variable and function.
Support solving equation and tabling.
Support io to and from file.

The grammar for input is:

Input:
	File
	Claculate

Calculate:
	Statement
	Print
	Quit
	Help
	Calculation Statement

Statement:
	Declaration variable/function
	Expression
	Table
	Solving equation
	Sum

Declaration:
	"let" Name "=" Expression
	"set" Name "=" Expression
	"delete" Name
	"let" Function name "=" Expression
	"delete" Function name

Expression:
	Term
	Expression"+"Term
	Expression"-"Term

Term:
	U_primary
	Term"*"U_primary
	Term"/"U_primary
	Term"%"U_primary

U_primary:
	Primary
	U_primary"^"Primary
	U_Primary"!"
	U_Primary"deg"

Primary:
	Number
	Variable
	"Function("Expression")"
	"("Expression")"
	"-"Primary
	"+"Primary

Input comes from a string through the Token_stream called ts.
Variables stored in Dictionary called var_table;
Functions stored in a structure called func_table;

*/

#include "calculate.h"

using namespace std;

string getstr(istream* ip)		//读入一行，以'\n'或';'结尾
{
	if (ip == nullptr)
		ip = &cin;
	string s;
	char c;
	while ((c = ip->get()) != '\n'&&c!=';')
	{
		if (c == EOF)			//or EOF，返回一个flag
			return "%file end";
		s += c;
	}
	s += ';';
	if (s == ";")
		s = getstr(ip);			//空字符串递归调用
	return s;
}

int main()
try
{
	cout << "Welcome to simple calculator.\n";
	cout << "Enter to calculate.\nEnter \"help\" for help.\n\n";
	ifstream* ip = nullptr;

	ip = new ifstream("./settings.txt");
	if(*ip)
		while (true)
		{
			string s = getstr(ip);
			if (s== "%file end")
				break;
			calculate(s, ip);
		}
	delete ip;
	ip = nullptr;

	ofstream* op = nullptr;
	vector<string>error_list;								//在文件中遇到错误方便退出
	init_error_list(error_list);
	while (true)
	{
		if (ip != nullptr)									//判断是否在文件内
		{													//在文件内
			string s = getstr(ip);
			if (s == "file;")								//文件内出现"file"报错
			{
				cout << "can't open a file in a file!!!\n";
				ip->close();
				delete ip;
				ip = nullptr;
				continue;
			}
			if (s == "%file end")							//文件结尾，关闭文件
			{
				ip->close();
				delete ip;
				ip = nullptr;
				continue;
			}
			string ans = calculate(s, ip);						//计算
			for (int i = 0; i < error_list.size(); i++)			//判断计算返回结果是否为报错
			{
				if (error_list[i] == ans)
				{
					ip->close();
					delete ip;
					ip = nullptr;
					continue;
				}
			}
			if (op == nullptr)										//输出
				cout <<">>"<< s<<endl<< ans<< endl;					//输出到控制台
			else
			{														//输出到文件
				(*op) << ">>" << s << endl << ans << endl;
				cout << ">>" << s << endl << ans << endl;
			}
		}
		else											//文件外
		{
			cout << ">>";
			string s = getstr(ip);
			if (s == "file;")							//判断关键字"file"
			{
				cout << "input or output:";
				string mode;
				cin >> mode;
				if (mode == "i" || mode == "input" || mode == "in")					//打开输入文件
				{
					cout << "input path:";
					string ipath;
					cin >> ipath;
					ip = new ifstream(ipath.c_str());
					if (!(*ip))
						cout << "can't open file" << endl;
				}
				else if (mode == "o" || mode == "output" || mode == "out")			//打开或创建输出文件
				{
					cout << "output path:";
					string opath;
					cin >> opath;
					if (opath == "cout")			//若为cout则改回输出到控制台
					{
						op->close();
						delete op;
						op = nullptr;
					}
					else									//创建输出文件
					{
						op = new ofstream(opath.c_str());
						if (!(*op))
							cout << "can't open file" << endl;
					}
					
				}
				else
				{
					cout << "unknown mode" << endl;
					continue;
				}
			}
			else
				if(op==nullptr)								//输出到控制台
					cout << calculate(s,nullptr) << endl;
				else
				{											//输出到文件
					string ans = calculate(s, nullptr);
					(*op) << ">>" << s << endl << ans << endl;
					cout << ans << endl;
				}
		}
		
	}
	return 0;
}
catch (const std::exception& e)
{
	cerr << e.what() << endl;
	cin.ignore('\n');
}
catch (...)
{
	cerr << "unexpected error" << endl;
	cin.ignore('\n');
}