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
void keep_window_open(char c);		//�˳��󱣳ִ��ڴ�
long long int fact(int n);			//�׳�
void print_help();					//��ӡ����

/*void cal_single_var(vector<double>& data);							//ͳ��ģʽ����
void cal_double_var(vector<double>& datax, vector<double>& datay);
void cal_double_var_kx(vector<double>& datax, vector<double>& datay);*/

int rounding(double x);				//ȡ��
