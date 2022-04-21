#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

//mark111
char tmp; //逐字读入
int cnt = 0; //当前是第几个字
bool has_reached_equal_mark; //在等号哪一侧
string parameter; //系数
bool is_negative; //负号处理
bool is_unknown; //当前项是否是未知数
char unknown; //未知数是哪个字母
double unknown_parameter = 0, normal_parameter = 0; //模拟移项操作完成后的系数之和

inline void calculate()
{
	if (cnt == 1) //如果是第一个字符触发了求和，则不处理
	{
		return;
	}
	
	if (parameter.empty()) //-x特殊处理
	{
		parameter = "1";
	}
	
	if (is_unknown) //是未知数
	{
		if (is_negative != has_reached_equal_mark) //要变号
		{
			unknown_parameter -= stod(parameter);
		}
		else //不变号
		{
			unknown_parameter += stod(parameter);
		}
	}
	else //不是未知数
	{
		if (is_negative == has_reached_equal_mark) //要变号
		{
			normal_parameter -= stod(parameter);
		}
		else //不变号
		{
			normal_parameter += stod(parameter);
		}
	}
	
	//reset
	parameter = "";
	is_negative = false;
	is_unknown = false;
}

int main()
{
	has_reached_equal_mark = false;
	while ((tmp = (char)getchar()))
	{
		cnt++;
		if (tmp == '\n')//句末：求和，然后结束
		{
			calculate();
			break;
		}
		if (tmp == '=') //等号：求和，然后改变参数
		{
			calculate();
			has_reached_equal_mark = true;
			cnt = 0;
			continue;
		}
		if (tmp == '+') //正号：不需要处理，求和
		{
			calculate();
			continue;
		}
		if (tmp == '-') //负号：求和，然后改变参数
		{
			calculate();
			is_negative = true;
			continue;
		}
		if (tmp >= 'a' && tmp <= 'z') //字母：存未知数，然后改变参数
		{
			unknown = tmp;
			is_unknown = true;
			continue;
		}
		if (tmp >= '0' && tmp <= '9') //数字：存入parameter里等待stoi
		{
			parameter += tmp;
		}
	}
	
	double ans = normal_parameter / unknown_parameter;
	printf("%c=%.3lf", unknown, ans == 0 ? 0 : ans);
	
	return 0;
}