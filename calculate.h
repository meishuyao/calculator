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


    \begin{framed}
    Input:\par
    \qquad File\par
    \qquad        Calculate\par\par
        Calculate:\par
        \qquad        Statement\par
        \qquad        Print\par
        \qquad         Quit\par
        \qquad          Help\par
        \qquad        Calculation Statement\par\par
        Statement:\par
        \qquad        Declarate variable/function\par
        \qquad        Expression\par
        \qquad        Table\par
        \qquad        Solve equation\par
        \qquad        Sum\par\par
        Declaration:\par
        \qquad        ``let" Name ``=" Expression\par
        \qquad         ``set" Name ``=" Expression\par
        \qquad         ``delete" Name\par
        \qquad         ``let" Function name ``=" Expression\par
        \qquad        ``delete" Function name\par\par
        Expression:\par
        \qquad       Term\par
        \qquad        Expression``+"Term\par
        \qquad        Expression``-"Term\par\par
        Term:\par
        \qquad        U\_primary\par
        \qquad         Term``*"U\_primary\par
        \qquad         Term``/"U\_primary\par
        \qquad         Term``\%"U\_primary\par\par
        U\_primary:\par
        \qquad        Primary\par
        \qquad        U\_primary``\^"Primary\par
        \qquad         U\_Primary``!"\par
        \qquad          U\_Primary``deg"\par\par
        Primary:\par
        \qquad          Number\par
        \qquad         Variable\par
        \qquad        ``Function("Expression``)"\par
        \qquad        ``("Expression``)"\par
        \qquad        ``-"Primary\par
        \qquad          ``+"Primary\par
    \end{framed}
