#include <bits/stdc++.h>
#include <windows.h>
#include <math.h>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
#include "keybd.cpp"
#include "python3.cpp"
#include "matrix.cpp"/*
#include "geometry.cpp"
#include "color.cpp"
#include "position.cpp"
#include "print.cpp"
#include "scanf.cpp"
#include "entity.cpp"
#include "levels.cpp"
#include "page.cpp"
#include "loadsave.cpp"
#include "declare.cpp"
#include "pageandoption.cpp"
#include "pageoptionfunction.cpp"
#include "initialization.cpp"*/
//时间测试函数 
//clock_t start, stop;
//start = clock();
//需要测试运行时间的代码 
//stop = clock();
//double duration = ((double)(stop - start))/CLK_TCK;


//错误调试：1001(dict:KeyError), 1003(DividedByZero)
//1004(Matrix:OutOfRange), 1005(Matrix:SizeNotMatch), 1006(Matrix:AllZero), 1007(Matrix:NotFullrank)
//


//战斗-战斗//punch, knife, magic, cancel
//战斗-行动//check, talk, flirt, cancel
//战斗-物品//cancel
//战斗-饶恕//spare, run, save, cancel
//战斗事件(分事件成功执行返回1，使得事件结束) 
int main()
{
	/*for(int num = 0; ; num += 1)
	{
		cout<<update_get(50)<<" ";//应当检测连续的三个数以排除意外波动
	}*//*
	initialization();//初始化
	clock_t start = clock();
	Home.func();
	clock_t stop = clock();
	endwords(start, stop);*//*
	matrix<int> m({column<int>({2, 3, 4, 5, 60000}),\
				   column<int>({10, 20, 30, 40, 1}),\
				   column<int>({200, 300, 400, 500, 20}),\
				   column<int>({1000, 2000, 3000, 4000, 10})});
	m.mult_line<int>(0, 3);
	cout<<m;*/
	matrix<double> a({column<double>({1, 2, 3}), column<double>({4, 5, 6}), column<double>({7, 8, 9})});
	matrix<double> b({column<double>({4, 1, 6}), column<double>({7, 1, 9}), column<double>({2, 1, 3})});
	//cout<<a<<endl;
	cout<<a.inverse();
	return 0;
}
