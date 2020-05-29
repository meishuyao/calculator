#include"head.h"
using namespace std;

void Token_stream::putback(Token t)		//�Ż�buffer
{
	if (full)
		error("putback() into a full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get()			//��ip���token
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch= this->getchar();
	while(isspace(ch)&&ch!='\n')
		ch = this->getchar();
	switch (ch)
	{
	case'\n':																				//�����
		return Token(PRINT);
	case PRINT: case '=':case',':
	case'(':case')':
	case'+':case'-':case'*':case'/':
	case'!':case'%':case'^':
		return Token(ch);
	case'.':
	case'0':case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':		//����
	{
		ip->putback(ch);
		double val;
		*ip >> val;
		return Token(NUMBER, val);
	}
	default:
		if (isalpha(ch))																	//��������
		{
			string s;
			s += ch;
			while (ip->get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '('))
			{
				s += ch;
				if (ch == '(')
					return Token(FUNCTION, s);
			}
			ip->putback(ch);
			for (int i = 0; i < keyword_table.size(); i++)
			{
				if (s == keyword_table[i].first)
					return Token(keyword_table[i].second);
			}
			return Token(NAME, s);
		}
		error("unknown character");
	}
}

char Token_stream::getchar()
{
	return ip->get();
}

void Token_stream::putback(char c)
{
	ip->putback(c);
}

void Token_stream::ignore(char c)					//����������
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (ch=this->getchar())
		if (ch == c)
			return;
}

void Token_stream::set_input_back()				//�ָ�ip
{
	delete ip;
	ip = ip_buff;
	if (full == true)
		full = false;
}

void Token_stream::set_input(string s)			//��ʼ��ip
{
	if (full == true)
	{
		full = false;
		//cin.putback(buffer.kind);
	}
	if (ip != nullptr)
		ip_buff = ip;
	ip = new stringstream(s);
	if (!(*ip))
		error("bad input");
}