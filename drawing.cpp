#include <bits/stdc++.h>
#include <windows.h>
#include <math.h>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
#include "include.cpp"
//ʱ����Ժ��� 
//clock_t start, stop;
//start = clock();
//��Ҫ��������ʱ��Ĵ��� 
//stop = clock();
//double duration = ((double)(stop - start))/CLK_TCK;


//������ԣ�1001(dict:KeyError), 1002(sqrt:Negtive), 1003(DividedByZero)
//1004(Matrix:OutOfRange), 1005(Matrix:SizeNotMatch), 1006(Matrix:AllZero)
//1007(Matrix:NotFullrank), 1008(Matrix:ZeroSize)
//1009(Geometry:Uncertain)


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
	matrix<double> a({column<double>({4, 0, 0, 2, 4}), column<double>({1, 1, 0, 3, 12}),\
					  column<double>({1, 1, 1, 2, 3}), column<double>({1, 1, 1, 1, 2}),\
					  column<double>({1, 0, 0, 4, 10})});*/
	matrix<double> a({column<double>({4, 1, 6}), column<double>({7, 1, 9}), column<double>({2, 1, 3}), column<double>({2, 1, 3})});
	/*cout<<a;
	a.insert_line(1, column<double>({4, 0, 201, 2, 4}));
	cout<<endl<<a;
	a.insert_list(1, column<double>({4, 0, 201, 1023, 2, 4}));
	cout<<endl<<a;
	a.reshape(Tuple<int, int>(3, 12));
	cout<<endl<<a;*/
	cyclist<matrix<double>> b({a, a});
	Tuple<Tuple<int, int>, cyclist<string>> outputbox_b = output(b);
	for(int line = 0; line < outputbox_b.elemt_0.elemt_0; line += 1)
		cout<<outputbox_b.elemt_1[line]<<endl;
	return 0;
}/*
int main()
{
	initialization();//��ʼ��
	clock_t start = clock();
	Home.func();
	clock_t stop = clock();
	endwords(start, stop);
}*/
