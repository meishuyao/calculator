/*
Simple calculator

Revision history:
	Originally written by Mei Shuyao April 2020
	Second editon by Mei Shuyao April 2020



Third edition, this file change to a head file. Main function in a new file.
*/


#include "calculate.h"

Function func_table;
Token_stream ts;
Dictionary var_table;
ostringstream* op=0;
void clean_up_mess() { ts.ignore(';'); }

string calculate(string s, istream* out_ip)
{
	try
	{
		ts.set_input(s);			//初始化输入s
		if(op!=nullptr)				//初始化输出
			delete op;
		op = new ostringstream;
		(*op)<<setprecision(12)<<statement(out_ip);	//计算
		ts.set_input_back();
		return op->str();
	}
	catch (const std::exception& e)
	{
		ts.set_input_back();
		return e.what();			//将error作为string返回
	}
}

double expression()
{
	double left = term();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case'+':
			left += term();
			t = ts.get();
			break;
		case'-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			var_table.set_value("ans", left);
			return left;
		}
	}
}

double term()
{
	double left = u_primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case'*':
			left *= u_primary();
			t = ts.get();
			break;
		case'/':
		{
			double d = u_primary();
			if (d == 0)
				error("divided by 0");
			left /= d;
			t = ts.get();
			break;
		}
		case'%':
		{
			double d = u_primary();
			int i1 = rounding(left);		//四舍五入取整
			if (i1 != left)
				error("left-hand operand of % not int");
			int i2 = rounding(d);
			if (i2 != d)
				error("right-hand operand of % not int");
			if (i2 == 0)
				error("%:moded by 0");
			left = i1 % i2;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double u_primary()
{
	double left = primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case'^':
		{
			double d = primary();
			left = func_table.use2("pow(", left, d);		//调用函数表pow
			t = ts.get();
			break;
		}
		case '!':
		{
			int i = rounding(left);
			if (i != left)
				error(" base of factorial not int");
			left = fact(i);									//调用阶乘函数
			t = ts.get();
			break;
		}
		default:
			if (t.name == "deg")									//处理deg及rad
				return left * var_table.get_value("pi") / 180;
			else if (t.name == "rad")
				return left * 180 / var_table.get_value("pi");
			ts.putback(t);
			return left;
		}
	}

}

double primary()
{
	Token t = ts.get();
	if (t.kind == NAME)							//如果为变量提前读取数值，并直接更改t的类型
	{
		t.value = var_table.get_value(t.name);
		t.kind = NUMBER;
	}
	switch (t.kind)
	{
	case FUNCTION:									//函数
	{
		string func_name = t.name;
		double ans;

		double d = expression();					//第一个参数
		t = ts.get();
		if (t.kind == ',')
		{
			ans = func_table.use2(func_name, d, expression());		//调用双参数函数表
			t = ts.get();
			if (t.kind != ')')
				ts.putback(t);
		}
		else
		{
			if (t.kind != ')')
				ts.putback(t);
			if (func_table.is_decleared(func_name, ts))			//调用单参数函数表
			{
				var_table.set_value("x_for_function", d);
				ans = expression();
				ts.set_input_back();
			}
			else
				ans = func_table.use(func_name, d);				//否则调用预定义函数
		}
		return ans;
	}
	case'(':													//小括号
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
			error("')'expected");
		return d;
	}
	case NUMBER:
	{
		double var = t.value;
		t = ts.get();
		if ((t.kind == NAME || t.kind == FUNCTION)&&t.name!="deg" && t.name != "rad")  //"2x"不正确，报错
			error("2x is not correct,* needed");
		ts.putback(t);
		return var;
	}
	case'-':
		return -primary();									//单目减
	case'+':
		return primary();									//单目加
	default:
		error("primary expected");
	}
}

double statement(istream* out_ip)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case HELP:
		print_help();									//打印帮助
		return 0;
	/*case STATISTICS:
		statistics();
		return 0;*/
	case EQUATION:
		return equation(out_ip);						//解方程
	case TABLE:
		return table(out_ip);							//列表
	case SUM:
		return sum(out_ip);								//求和
	case LET: case SET: case DELETE:
		return declaration(t.kind);						//声明
	default:
		ts.putback(t);
		return expression();
	}
}

double declaration(char k)									//声明或删除
{
	Token t = ts.get();
	if (t.kind == FUNCTION)									//声明函数
	{
		string func_name = t.name;
		if (k == DELETE)
		{
			func_table.delete_function(func_name);
			clean_up_mess();
			return 0;
		}
		if (k == SET)
			error("name expected, can't change a function, please delete and re-define it");
		if ((t = ts.get()).name != "x" || (t = ts.get()).kind != ')' || (t = ts.get()).kind != '=')
			error("gramma: let g(x)=...");
		string v;
		char c;
		while ((c = ts.getchar()) != '\n' && c != ';')
		{
			if (c == 'x')
				v += "x_for_function";
			else
				v += c;
		}
		ts.putback(c);
		v += ';';
		func_table.define_function(func_name, v);
		if (func_table.is_decleared(func_name, ts))
		{
			var_table.set_value("x_for_function", 1);
			double d = expression();
			ts.set_input_back();
			(*op) <<"test: "<< func_name<<"1)=";
			return d;
		}
		error("unknown error when defining function");
	}
	else if (t.kind != NAME)							//申明变量
		error("name expected");
	string var_name = t.name;

	if (k == DELETE)
		return var_table.delete_name(var_name);
	Token t2 = ts.get();
	if (t2.kind != '=')
		error("= missing after " + var_name);
	double d = expression();
	if (k == LET)
		var_table.define_name(var_name, d);
	else
		var_table.set_value(var_name, d);
	return d;
}

double equation(istream* out_ip)				//解方程
{
	(*op) << "x=";
	Token t = ts.get();
	if (t.kind != FUNCTION)
		error("a function expected");
	string func_name = t.name;
	clean_up_mess();
	if(out_ip==nullptr)
		cout << "use Bisection method, please enter interval\n";	//input
	double left, right;
	double fl, fm, fr;
	while (true)			//check initial number
		try
	{
		read_number(left, "left value", out_ip);
		read_number(right, "right value", out_ip);
		if (left >= right)
		{
			cout << "left should be larger than right, try again\n";
			continue;
		}
		if (func_table.is_decleared(func_name, ts))
		{
			var_table.set_value("x_for_function", left);
			fl = expression();
			ts.set_input_back();
		}
		else
			error("unknown function");
		if (func_table.is_decleared(func_name, ts))
		{
			var_table.set_value("x_for_function", right);
			fr = expression();
			ts.set_input_back();
		}
		else
			error("unknown function");
		if (fl == 0)
			return left;
		if (fr == 0)
			return right;
		if (((fl > 0) && (fr < 0)) || ((fl < 0) && (fr > 0)))
			break;
		cout << ("bad interval, " + func_name + "left)*" + func_name + "right) > 0 , try again\nif you want to quit equation mode enter anything except number\n");
	}
	catch (const std::exception& e)
	{
		error("quit equation mode");
	}
	
	double middle = (left + right) / 2;		//bisection，计算
	while (true) 
	{
		if (func_table.is_decleared(func_name, ts))
		{
			var_table.set_value("x_for_function", middle);
			fm = expression();
			ts.set_input_back();
		}
		else
			error("unknown function");
		if (func_table.is_decleared(func_name, ts))
		{
			var_table.set_value("x_for_function", right);
			fr = expression();
			ts.set_input_back();
		}
		else
			error("unknown function");
		if (fm == 0)
			return middle;
		if (((fm > 0) && (fr < 0)) || ((fm < 0) && (fr > 0)))
		{
			left = middle;
			middle= (left + right) / 2;
		}
		else
		{
			right = middle;
			middle = (left + right) / 2;
		}
		if ((right-left) < 1e-10)
			break;
	}
	return middle;
}

double table(istream* out_ip)					//列表
{
	Token t = ts.get();
	if (t.kind != FUNCTION)
		error("a function expected");
	string func_name = t.name;
	clean_up_mess();
	double begin, end, step;
	bool fail = true;
	while (fail)								//列表区间
	{
		read_number(begin, "begin", out_ip);
		read_number(end, "end", out_ip);
		read_number(step, "step", out_ip);
		if (begin > end)
			cout << "table: begin should be smaller than end\n";
		else if (step <= 0)
			cout << "table: step should be larger than 0";
		else
			fail=false;
	}
	for (double i = begin; i - end<1e-6; i += step)			//计算
	{
		double ans;
		if (func_table.is_decleared(func_name, ts))
		{
			var_table.set_value("x_for_function", i);
			ans = expression();
			ts.set_input_back();
		}
		else
			ans = func_table.use(func_name, i);
		(*op)<<func_name<<i<<")="<<setprecision(12)<< ans <<endl;
	}
	(*op) << "suceeded ,";
	return 0;
}

double sum(istream* out_ip)				//求和
{
	Token t = ts.get();
	if (t.kind != FUNCTION)
		error("a function expected");
	string func_name = t.name;
	clean_up_mess();
	double begin, end;
	bool fail = true;
	while (fail)							//区间
	{
		read_number(begin, "begin",out_ip);
		read_number(end, "end", out_ip);
		if (begin > end)
			cout << "sum: begin should be smaller than end\n";
		else
			fail = false;
	}
	int left = (int)begin;
	int right;
	if ((int)end == end)
		right = end;
	else
		right=(int)end + 1;
	(*op) << "sum(" << func_name << ")," << left << "," << right << ")=";
	double ans=0;
	for (int i = begin; i <= end; i ++)							//计算
	{
		if (func_table.is_decleared(func_name, ts))
		{
			var_table.set_value("x_for_function", i);
			ans+= expression();
			ts.set_input_back();
		}
		else
			ans += func_table.use(func_name, i);
	}
	return ans;
}


/*
void statistics()
{
	while (true)
	try
	{
		cout << "please enter mode\ns:single variable calculation\nd:least squares linear fitting y=kx+b\tk:y=kx\nq:quit statistics mode\n";
		Token t = ts.get();
		char mode;
		if (t.kind == NAME)
			mode = t.name[0];
		else
			mode = 'r';
		switch (mode)
		{
		case'r':
			continue;
		case'q':
			return;
		case's':
		{
			vector<double> data;
			cout << "please type in data, end with character 'c' for calculate\nenter \"quit\" to quit,'r' to restart\n";
			t = ts.get();
			while (t.kind == NUMBER || t.kind == FUNCTION)
			{
				if (t.kind == FUNCTION)
				{
					t.value = func_table.use(t.name, expression());
					Token t2 = ts.get();
					if (t2.kind != ')')
						error("')'expected");
					cout << "=" << t.value << endl;
				}
				data.push_back(t.value);
				t = ts.get();
			}
			if (t.kind == NAME && t.name == "r")
			{
				continue;
			}
			if (t.kind == NAME && t.name == "c")
			{
				cal_single_var(data);
				continue;
			}
			else if (t.kind == QUIT)
				return;
			else
				error("unknown character");
		}
		case'd':case'k':
		{
			vector<double> datay, datax;
			if (mode == 'd')
				cout << "in model y=kx+b\nplease type in x, end with character 'c' to continue\nenter \"quit\" to quit,'r' to restart\n";
			else
				cout << "in model y=kx\nplease type in x, end with character 'c' to continue\nenter \"quit\" to quit,'r' to restart\n";
			t = ts.get();
			while (t.kind == NUMBER || t.kind == FUNCTION)
			{
				if (t.kind == FUNCTION)
				{
					t.value = func_table.use(t.name, expression());
					Token t2 = ts.get();
					if (t2.kind != ')')
						error("')'expected");
					cout << "=" << t.value << endl;
				}
				datax.push_back(t.value);
				t = ts.get();
			}
			if (t.kind == NAME && t.name == "c")
			{
				if (mode == 'd')
					cout << "in model y=kx+b\nplease type in y, end with character 'c' to calculate\n";
				else
					cout << "in model y=kx\nplease type in y, end with character 'c' to calculate\n";
				t = ts.get();
				while (t.kind == NUMBER || t.kind == FUNCTION)
				{
					if (t.kind == FUNCTION)
					{
						t.value = func_table.use(t.name, expression());
						Token t2 = ts.get();
						if (t2.kind != ')')
							error("')'expected");
						cout << "=" << t.value << endl;
					}
					datay.push_back(t.value);
					t = ts.get();
				}
			}
			if (t.kind == NAME && t.name == "r")
			{
				continue;
			}
			if (t.kind == NAME && t.name == "c")
			{
				if (datax.size() != datay.size())
					error("number of x and number of y doesn't match");
				if (mode == 'd')
					cal_double_var(datax, datay);
				else
					cal_double_var_kx(datax, datay);
				continue;
			}
			else if (t.kind == QUIT)
				return;
			else
				error("unknown character");
		}
		default:
			error("unknown mode");
		}
	}
	catch (const std::exception & e)
	{
		cerr << e.what() << endl;
		clean_up_mess();
	}
}*/

void read_number(double& d, string name,  istream* out_ip)		//从外界读数据
{
	if (out_ip == nullptr)
	{
		cout << name << ": ";
		out_ip = &cin;
	}
	else
	{
		char c;
		while (isspace(c = out_ip->get())||c=='\n'||c==';')		//删去空白符
			;
		out_ip->putback(c);
		string s;
		while ((c = out_ip->get()) != ':')				//比较语法
			s += c;
		if (s != name)
			error("wrong gramma");
	}
	(*out_ip) >> d;							//读数据
	if (out_ip->fail())
	{
		cin.clear();
		error("please enter a number");
	}
}

void init_error_list(vector<string>& s)				//初始化error_list
{
	s.push_back("wrong gramma");
	s.push_back("please enter a number");
	s.push_back("a function expected");
	s.push_back("quit equation mode");
	s.push_back("unknown function");

}
