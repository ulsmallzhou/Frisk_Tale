#include <bits/stdc++.h>
#include <windows.h>
#include <math.h>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
#include "keybd.cpp"
#include "python3.cpp"/*
#include "matrix.cpp"
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


//������ԣ�1001(dict:KeyError), 1002(vatiable_array:OutOfRange)


//ս��-ս��//punch, knife, magic, cancel
//ս��-�ж�//check, talk, flirt, cancel
//ս��-��Ʒ//cancel
//ս��-��ˡ//spare, run, save, cancel
//ս���¼�(���¼��ɹ�ִ�з���1��ʹ���¼�����) 

/* TODO (#1#): �������Զ�����������output���� */

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
	endwords(start, stop);*/
	cyclist<int> a({1, 2});
	cyclist<cyclist<int>> b({a, cyclist<int>({2, 3, 4, 5, 6}), cyclist<int>({3, 4, 5, 6, 7, 8})});
	cyclist<cyclist<cyclist<int>>> c({b, b});
	cout<<c;
	return 0;
}
