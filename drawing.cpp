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
//ʱ����Ժ��� 
//clock_t start, stop;
//start = clock();
//��Ҫ��������ʱ��Ĵ��� 
//stop = clock();
//double duration = ((double)(stop - start))/CLK_TCK;


//������ԣ�1001(dict:KeyError), 1002(vatiable_array:OutOfRange), 1003(DividedByZero)


//ս��-ս��//punch, knife, magic, cancel
//ս��-�ж�//check, talk, flirt, cancel
//ս��-��Ʒ//cancel
//ս��-��ˡ//spare, run, save, cancel
//ս���¼�(���¼��ɹ�ִ�з���1��ʹ���¼�����) 
int main()
{
	/*for(int num = 0; ; num += 1)
	{
		cout<<update_get(50)<<" ";//Ӧ��������������������ų����Ⲩ��
	}*//*
	initialization();//��ʼ��
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
	matrix<int> a({column<int>({1, 2, 3}), column<int>({4, 5, 6}), column<int>({7, 8, 9})});
	cout<<a;
	a.mult_list(0, 3.3);
	cout<<endl<<a;
	a.swap_lines(0, 1);
	cout<<endl<<a;
	cout<<endl<<matrix<int>::quantity(5, 20);
	a.right_extension(a);
	a.right_extension(a);
	cout<<endl<<a;
	return 0;
}
