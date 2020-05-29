//输入输出头文件

#pragma once
#ifndef TOKEN_H
	#define TOKEN_H
#include<sstream>

//预定义常量（token的类型）
const char NUMBER = '8';
const char QUIT = 'q';
const char PRINT = ';';
const char NAME = 'n';
const char LET = 'l';
const char SET = 's';
const char DELETE = 'd';
const char HELP = 'h';
const char FUNCTION = 'f';
const char EQUATION = 'e';
//const char STATISTICS = 't';
const char TABLE = 't';
const char SUM = 'j';

const vector<pair<string, char> >keyword_table = { pair<string,char>("quit", QUIT),pair<string,char>("let", LET) ,pair<string,char>("set", SET) ,pair<string,char>("delete", DELETE) ,
		pair<string,char>("help", HELP) ,pair<string,char>("solve", EQUATION),pair<string,char>("table", TABLE),pair<string,char>("sum", SUM) };

class Token					//输入基本单位
{
public:
	char kind;		//operator or number
	double value;
	string name;

	Token(char ch) :kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
	Token(char ch,string n):kind(ch),name(n),value(0){}
};

class Token_stream			//输入流
{
public:
	Token_stream() : full(false), buffer(0),ip(nullptr),ip_buff(nullptr){}

	Token get();
	char getchar();
	void putback(char c);
	void putback(Token t);
	void ignore(char c);
	void set_input(string s);
	void set_input_back();

private:
	istream* ip;			//输入来源
	istream* ip_buff;		//ip缓存
	bool full;
	Token buffer;			//token缓存
};


#endif
