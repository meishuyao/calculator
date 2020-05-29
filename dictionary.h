#pragma once
#ifndef DICTIONARY_H
	#define DICTIONARY_H

using namespace std;

#include<vector>
#include<iostream>

class Variable				//变量类
{
public:
	//bool isconst;
	double value;
	string name;
	Variable(string n,double v) :value(v),name(n) {}
};

class Dictionary			//字典类，储存变量
{
private:
	vector<Variable> table;
public:
	Dictionary();
	double get_value(string s);
	void set_value(string s, double d);
	bool is_declared(string n);
	double define_name(string n, double v);
	double delete_name(string n);
};


#endif // !DICTIONARY_H


