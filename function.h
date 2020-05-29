#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include "head.h"

typedef double (*FP)(double);
typedef double (*FP2)(double,double);

class Function			//储存函数的类
{
private:
	vector<pair<string,FP> >table;
	vector<pair<string, FP2> >table2;
	vector<pair<string, string> >s_table;

public:
	Function();
	double use(string func_name, double x);
	double use2(string func_name, double x, double y);
	bool is_decleared(string n,Token_stream& ts);
	void define_function(string func_name, string v);
	void delete_function(string n);
};

//数学函数

double cot(double);
double arcsin(double);
double arccos(double);
double arccot(double);
double coth(double);
double arccosh(double);
double sinc(double);
double m_pow(double, double);
double a(double, double);
double c(double, double);


#endif