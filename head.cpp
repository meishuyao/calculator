#include "head.h"

void error(string s)
{
	throw runtime_error(s);
}


void keep_window_open(char c)
{
	cout << "please enter " << c << " to exit"<<endl;
	while (c != getchar());
}

long long int fact(int n)	//阶乘
{
	if (n < 0)
		error("factiorial on negetive number");
	if (n == 0)
		return 1;
	long long int ans = 1;
	while (n > 1)
	{
		ans *= n;
		if (ans < 0)
			error("n is too big");
		n--;
	}
	return ans;
}

void print_help()
{
	/*
	cout << "\n\nA Simple Calculator\nCopyright meishuyao\nSecond edition. Apr 2020\nIf there's any bug,please text me.\n\n";
	cout << "number support:\n20=20.0=2e2\n\n";
	cout << "operator supported:\n+\tplus\n-\tminus\n*\tmultiply\t(use 2*x, but not 2x)\n/\tdivide\n%\tmode\n!\tfactorial\n^\tpower\n()\tbraket\n\n";
	cout << "radian to degree:\n180deg = pi\nx deg is permitted, xdeg not permitted, which means a new variable \"xdeg\"\n\n";
	cout << "variable support:\nlet name = expression;\t\tinitialize a variable\nset name = expression;\t\tchange a vriable's value\ndelete name;\t\t\tdelete a variable\nans \t\t\t\tthe last result\n\n";
	cout << "const number:\npi\t3.1415926535898\ne\t2.7182818284\nh\t6.62607015e-34\nhb\t1.05457266e-34\nkb\t1.380649e-23\nG\t6.67259e-11\ng\t9.80\nc0\t299792458\nNA\t6.02214076e-23\nme\t9.109534e-31\n"
		<<"e0\t1.602176634e-19\nmp\t1.6726485e-27\nmn\t1.6749543e-27\nmu\t1.6605655e-27\neps0\t8.854187818e-12\nmu0\t4*pi*e-7\n\n";
	cout << "math functions:\n" << "sin()\tcos()\ttan()\tcot()\narcsin()\tarccos()\narctan()\tarccot()\nsinh()\tcosh()\ttanh()\tcoth()\narcsinh()\tarccosh()\n"
		<<"arctanh()\tsinc()=sin(x)/x\nln()\tlog10()\texp()\tabs()\nsqrt()\npow(,)\nC(,)\tcombination number\nA(,)\tarrangement number\n\n";
	cout << "Self-defined function:\n" << "let name(x)=expression ,x is unchangable\ndelete name()\n\n";
	cout << "Equation:\nsolve g(x)=0\nuse self-defined functions\nuse table before solve equation is suggested\n\n";
	cout << "table:\ntable g()\nto enter table mode\n\n";
	cout<< "sum:\ntable g()\nto enter summing mode\n\n";
	*/
	cout << "\n\n欢迎使用简易计算器\nCopyright meishuyao\nSecond edition. Apr 2020\n若计算器存在任何异常请联系开发者\n\n";
	cout << "数字：\n直接输入 20 = 小数 20.0 = 科学计数法 2e2\n\n";
	cout << "运算符：\n+\t-\t/\t*（勿使用2x，应添加乘号，如2*x）\n%取余\t^幂\t!阶乘\n()括号\n\n";
	cout << "角度：默认为弧度制\n180deg = pi\npi rad = 180\n注：使用未知数时应写为x deg，而不是xdeg，否则将被识别为变量\n\t注意pi/2rad将被识别为pi/(2rad)，使用时请添加括号\n\n";
	cout << "自定义变量：\nlet name = expression\t\t初始化变量\nset name = expression\t\t改变变量值\ndelete name\t\t\t删除变量\nans \t\t\t\t最后一次计算结果\n\n";
	cout << "自定义函数：\nname(expression)\t\t调用函数\nlet name(x) = expression\t定义函数\ndelete name()\t\t\t删除函数\n注意：set不能用于函数，若想改变函数请先删除再定义。\n\n";
	cout << "预定义常数：\npi\t3.1415926535898\ne\t2.7182818284\nh\t6.62607015e-34\nhb\t1.05457266e-34\nkb\t1.380649e-23\nG\t6.67259e-11\ng\t9.80\nc0\t299792458\nNA\t6.02214076e-23\nme\t9.109534e-31\n"
		<< "e0\t1.602176634e-19\nmp\t1.6726485e-27\nmn\t1.6749543e-27\nmu\t1.6605655e-27\neps0\t8.854187818e-12\nmu0\t4*pi*e-7\n\n";
	cout << "预定义函数：\n" << "sin()\tcos()\ttan()\tcot()\narcsin()\tarccos()\narctan()\tarccot()\nsinh()\tcosh()\ttanh()\tcoth()\narcsinh()\tarccosh()\n"
		<< "arctanh()\tsinc()=sin(x)/x\nln()\tlog10()\texp()\tabs()\nsqrt()\npow(,)\nC(,)\t组合数\nA(,)\t排列数\n\n";
	cout << "解方程：\nsolve g(x)=0\t\t需要预先定义函数\n注：推荐先使用列表功能找到解所在区间，本功能使用二分法\n\n";
	cout << "列表：\ntable g()\t\t进入列表模式\n\n";
	cout << "求和：\nsum g()\t\t\t进入求和模式\n\n";
	cout << "读写文件：\tfile\n\n";
	cout << "return,";
}

int rounding(double x)			//取整
{
	if (x >= 0)
		return int(x + 0.5);
	return int(x - 0.5);
}

/*
void cal_single_var(vector<double>& data) 
{
	int n = data.size();
	if (n <= 1)
		error("less than 2 couples of data");
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += data[i];
	double avg = sum / n;
	cout << "avgerage:\t" << avg << endl;
	double variance = 0;
	for (int i = 0; i < n; i++)
		variance += pow((data[i]-avg),2);
	cout << "variance:\t" << variance << endl;
	double sigma = sqrt(variance);
	cout << "sigma:\t\t" << sigma << endl;
	double s = sqrt(variance/(n-1));
	cout << "s:\t\t" << s << endl;
	if (n > 2)
	{
		double u = s/sqrt(n)*(1.959+2.406/(n-1-1.064));
		cout << "u(0.95):\t" << u << endl;
		double ur = u / avg;
		cout << "ur(0.95):\t" << ur << endl;
	}
	cout << endl;
}

void cal_double_var(vector<double>& datax, vector<double>& datay) 
{
	int n = datax.size();
	if (n <=2)
		error("less than 3 couples of data");
	double sumx = 0;
	for (int i = 0; i < n; i++)
		sumx += datax[i];
	double avgx = sumx / n;
	double sumy = 0;
	for (int i = 0; i < n; i++)
		sumy+= datay[i];
	double avgy = sumy / n;
	int k_up = 0;
	for (int i = 0; i < n; i++)
		k_up += (datax[i]-avgx)*datay[i];
	int k_down = 0;
	for (int i = 0; i < n; i++)
		k_down += pow((datax[i] - avgx),2);
	double k=k_up/k_down;
	double b=avgy-k*avgx;
	cout << "k:\t" << k << endl;
	cout << "b:\t" << b << endl;
	if (n > 3)
	{
		double rss = 0;
		for (int i = 0; i < n; i++)
			rss += pow(datay[i] - k * datax[i] - b, 2);
		double sy = sqrt(rss / (n - 2));
		double sk = sy / sqrt(k_down);
		double sb = sy * sqrt(avgx * avgx / k_down + 1 / n);
		double t_095 = 1.959 + 2.406 / (n - 2 - 1.064);
		double uk = t_095 * sk;
		double ub = t_095 * sb;
		cout << "uk:\t" << uk << endl;
		cout << "ub:\t" << ub << endl;
	}
	cout<<endl;
}

void cal_double_var_kx(vector<double>& datax, vector<double>& datay)
{
	int n = datax.size();
	if (n <= 1)
		error("less than 2 couples of data");
	int k_up = 0;
	for (int i = 0; i < n; i++)
		k_up += datax[i] * datay[i];
	int k_down = 0;
	for (int i = 0; i < n; i++)
		k_down += pow(datax[i], 2);
	double k = k_up / k_down;
	cout << "k:\t" << k << endl;
	if (n > 2)
	{
		double rss = 0;
		for (int i = 0; i < n; i++)
			rss += pow(datay[i] - k * datax[i], 2);
		double sy = sqrt(rss / (n - 1));
		double sk = sy / sqrt(k_down);
		double t_095 = 1.959 + 2.406 / (n - 1 - 1.064);
		double uk = t_095 * sk;
		cout << "uk:\t" << uk << endl;
	}
	cout << endl;
}
*/