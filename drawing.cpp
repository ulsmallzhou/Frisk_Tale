#include <bits/stdc++.h>
#include <windows.h>
#include <math.h>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
#include "keybd.cpp"
#include "python3.cpp"
#include "mathtype.cpp"
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


//������ԣ�1001(dict:KeyError), 1002(sqrt:Negtive), 1003(DividedByZero)
//1004(Matrix:OutOfRange), 1005(Matrix:SizeNotMatch), 1006(Matrix:AllZero), 1007(Matrix:NotFullrank)
//


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
	endwords(start, stop);*/
	matrix<double> a({column<double>({1, 0, 0}), column<double>({1, 1, 0}),\
					  column<double>({1, 1, 1}), column<double>({1, 1, 1})});
	matrix<double> b({column<double>({4, 1, 6}), column<double>({7, 1, 9}), column<double>({2, 1, 3})});
	//cout<<a<<endl;
	Tuple<matrix<double>, matrix<double>> t = a.QR_decomposition();
	cout<<a<<endl<<t.elemt_0<<endl<<t.elemt_1;
	return 0;
}
