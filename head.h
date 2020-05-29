#pragma once

using namespace std;

#include <iostream>
#include<iomanip>
#include<fstream>

#include<vector>
//#include<map>
#include<math.h>

#include "token.h"
#include "dictionary.h"
#include "function.h"


void error(string s);				//throw runtime_error
void keep_window_open(char c);		//退出后保持窗口打开
long long int fact(int n);			//阶乘
void print_help();					//打印帮助

/*void cal_single_var(vector<double>& data);							//统计模式函数
void cal_double_var(vector<double>& datax, vector<double>& datay);
void cal_double_var_kx(vector<double>& datax, vector<double>& datay);*/

int rounding(double x);				//取整
