#include "dictionary.h"
#include "head.h"

Dictionary::Dictionary()							//向字典添加预定义变量
{
	table.push_back(Variable("ans", 0));
	define_name("x_for_function", 0);
	define_name("pi", acos(-1));
	define_name("e", exp(1));
	define_name("h", 6.62607015e-34);
	define_name("hb", 1.05457266e-34);
	define_name("kb", 1.380649e-23);
	define_name("G", 6.67259e-11);
	define_name("g", 9.80);
	define_name("c", 299792458);
	define_name("NA", 6.02214076e23);
	define_name("me", 9.109534e-31);
	define_name("e0", 1.602176634e-19);
	define_name("mp", 1.6726485e-27);
	define_name("mn", 1.6749543e-27);
	define_name("mu", 1.6605655e-27);		//unit of atom mass
	define_name("eps0", 8.85418781762037e-12);
	define_name("mu0", 4e-7 * acos(-1));
}

double Dictionary::get_value(string s)						//用名字得到值
{
	for (int i = 0; i < table.size(); i++)
		if (table[i].name == s)
			return table[i].value;
	error("undefined variable " + s);
}

void Dictionary::set_value(string s, double d)				//改变值
{
	for(int i=0;i< table.size();i++)
		if (table[i].name == s)
		{
			table[i].value = d;
			return;
		}
	error("undefined variable " + s);
}

bool Dictionary::is_declared(string n)						//查询变量是否声明
{
	if (n == "deg"||n=="rad")
		error("can not define system keywords as variables");
	for (int i = 0; i < table.size(); i++)
		if (table[i].name == n)
			return true;
	return false;
}

double Dictionary::define_name(string n, double v)			//初始化变量
{
	while (is_declared(n))
	{
		cout<<(n + " decleared twice,")<<"rename "<<n<<" as "<<(n+"_new")<<endl;		//如果变量存在更改名字
		n += "_new";
	}
	table.push_back(Variable(n, v));
	return v;
}

double Dictionary::delete_name(string n)					//删除变量
{
	if (n == "ans")
		error("can not delete \"ans\"");
	for ( int i = 0; i < (table.size()); i++)
		if (table[i].name == n)
		{
			double d = table[i].value;
			swap(table[i], table[table.size() - 1]);
			cout << n << " deleted, =" ;
			table.pop_back();
			while (is_declared(n + "_new"))
			{
				for (int i = 0; i < table.size(); i++)
					if (table[i].name == n + "_new")
					{
						table[i].name = n;
						cout << (n + "_new") << " rename as " << n <<"="<< table[i].value<<endl;
						break;
					}
				n += "new";
			}
			return d;
		}
	error(n+" not in variable table");
}