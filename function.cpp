#include "function.h"

Function::Function()							//构造函数，加预定义函数
{
	table.push_back(pair<string, FP>("ln(", log));
	table.push_back(pair<string, FP>("sin(", sin));
	table.push_back(pair<string, FP>("cos(", cos));
	table.push_back(pair<string, FP>("tan(", tan));
	table.push_back(pair<string, FP>("sqrt(", sqrt));
	table.push_back(pair<string, FP>("exp(", exp));
	table.push_back(pair<string, FP>("cot(", cot));
	table.push_back(pair<string, FP>("arcsin(", arcsin));
	table.push_back(pair<string, FP>("arccos(", arccos));
	table.push_back(pair<string, FP>("arctan(", atan));
	table.push_back(pair<string, FP>("arccot(", arccot));
	table.push_back(pair<string, FP>("sinc(", sinc));
	table.push_back(pair<string, FP>("log10(", log10));
	table.push_back(pair<string, FP>("abs(", abs));
	table.push_back(pair<string, FP>("sinh(", sinh));
	table.push_back(pair<string, FP>("cosh(", cosh));
	table.push_back(pair<string, FP>("tanh(", tanh));
	table.push_back(pair<string, FP>("coth(", coth));
	table.push_back(pair<string, FP>("arcsinh(", asinh));
	table.push_back(pair<string, FP>("arccosh(", arccos));
	table.push_back(pair<string, FP>("arctanh(", atanh));
	
	table2.push_back(pair<string, FP2>("pow(", m_pow));
	table2.push_back(pair<string, FP2>("A(", a));
	table2.push_back(pair<string, FP2>("C(", c));

}

bool Function::is_decleared(string func_name,Token_stream& ts)		//判断是否已经声明
{
	for (int i = 0; i < s_table.size(); i++)
	{
		if (func_name == s_table[i].first)
		{
			ts.set_input(s_table[i].second);
			return true;
		}		
	}
	return false;
}

void Function::define_function(string func_name, string v)			//定义
{
	for(int i=0;i<table.size();i++)
		if (func_name == table[i].first)
		{
			error(func_name + ") is a math function, can not overload");
		}
	for (int i = 0; i < s_table.size(); i++)
	{
		if (func_name == s_table[i].first)
		{
			error(func_name + ") defined twice");
		}
	}
	s_table.push_back(pair<string,string>(func_name,v));
}

void Function::delete_function(string func_name)					//删除
{
	for (int i = 0; i < (s_table.size()); i++)
		if (s_table[i].first == func_name)
		{
			swap(s_table[i], s_table[s_table.size() - 1]);
			cout << func_name << ") deleted,";
			s_table.pop_back();
			return;
		}
	error(func_name + " not in function table");
}

double Function::use(string func_name, double x)					//使用单变量函数
{
	for (int i = 0; i < table.size(); i++)
	{
		if (func_name == table[i].first)
			return table[i].second(x);
	}
	
	error("unknown function");
}

double Function::use2(string func_name, double x, double y)			//使用双变量函数
{
	for (int i = 0; i < table2.size(); i++)
	{
		if (func_name == table2[i].first)
			return table2[i].second(x,y);
	}

	error("unknown function");
}

//数学函数

double cot(double x)
{
	if (x == 0 || x == acos(-1) || x == -acos(-1))
		error("cot() undefined at pi/2+k*pi");
	return 1 / tan(x);
}

double arcsin(double x)
{
	if (x > acos(-1) / 2 || x < -acos(-1) / 2)
		error("arcsin() undefined outside [-pi/2,pi/2]");
	return asin(x);
}

double arccos(double x)
{
	if (x > acos(-1) / 2 || x < -acos(-1) / 2)
		error("arccos() undefined outside [-pi/2,pi/2]");
	return acos(x);
}

double arccot(double x)
{
	if (x == 0)
		error("coth() undefined at 0");
	return 1 / tanh(x);
}

double coth(double x)
{
	if (x == 0)
		error("coth() undefined at 0");
	return 1 / tanh(x);
}

double arccosh(double x)
{
	if (x < 1)
		error("arccosh() undefined (-inf,1)");
	return acosh(x);
}

double sinc(double x)
{
	if (x == 0)
		return 1;
	return sin(x) / x;
}

double m_pow(double x, double y)
{
	if (x < 0)
		if (rounding(y) != y)
			error("negetive number doesn't have fracional power");
	return pow(x, y);
}

double a(double x, double y)
{
	int bignum = rounding(x), smallnum = rounding(y);
	if (bignum != x)
		error("parameter of C not int");
	if (smallnum != y)
		error("parameter of C not int");
	if (x == y)
		return fact(x);
	else if (x < y)
	{
		int temp = x;
		x = y;
		y = temp;
	}
	long long int ans = 1;
	for (int i = 0; i < smallnum; i++)
		ans *= (bignum - i);
	return (double)ans;
}

double c(double x, double y)
{
	int bignum = rounding(x), smallnum = rounding(y);
	if (bignum != x)
		error("parameter of C not int");
	if (smallnum != y)
		error("parameter of C not int");
	if (x == y)
		return 1;
	else if (x < y)
	{
		int temp = x;
		x = y;
		y = temp;
	}
	long long int ans = 1;
	for (int i = 0; i < smallnum; i++)
		ans *= (bignum - i) / (i + 1);
	return (double)ans;
}