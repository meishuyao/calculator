/*The grammar for input is :

Input:
File
Claculate

Calculate :
Statement
Print
Quit
Help
Calculation Statement

Statement :
Declaration variable / function
Expression
Table
Solving equation
Sum

Declaration :
"let" Name "=" Expression
"set" Name "=" Expression
"delete" Name
"let" Function name "=" Expression
"delete" Function name

Expression :
Term
Expression"+"Term
Expression"-"Term

Term :
U_primary
Term"*"U_primary
Term"/"U_primary
Term"%"U_primary

U_primary :
Primary
U_primary"^"Primary
U_Primary"!"
U_Primary"deg"

Primary :
	Number
	Variable
	"Function("Expression")"
	"("Expression")"
	"-"Primary
	"+"Primary*/

#pragma once

#ifndef CALC_H
#define CALC_H

#include "head.h"

//�﷨����

string calculate(string s, istream* out_ip);	//��Ҫ���㺯��
double statement(istream* out_ip);				
double declaration(char k);
double expression();
double term();
double u_primary();
double primary();
double equation(istream* out_ip);
double table(istream* out_ip);
double sum(istream* out_ip);

//��������
//void statistics();
void clean_up_mess();
void init_error_list(vector<string>&);
void read_number(double& d, string name,istream* out_ip);		//���ڶ��ⲿ����

#endif // CALC_H
