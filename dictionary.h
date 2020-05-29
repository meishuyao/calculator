#pragma once
#ifndef DICTIONARY_H
	#define DICTIONARY_H

using namespace std;

#include<vector>
#include<iostream>

class Variable				//������
{
public:
	//bool isconst;
	double value;
	string name;
	Variable(string n,double v) :value(v),name(n) {}
};

class Dictionary			//�ֵ��࣬�������
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


