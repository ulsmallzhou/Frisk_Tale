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
//1009(Geometry:Uncertain), 1010(P_int:Illegal)


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
	}/*
	matrix<double> a({column<double>({4, 0, 0, 2, 4}), column<double>({1, 1, 0, 3, 12}),\
					  column<double>({1, 1, 1, 2, 3}), column<double>({1, 1, 1, 1, 2}),\
					  column<double>({1, 0, 0, 4, 10})});*/
	/*cout<<a;
	a.insert_line(1, column<double>({4, 0, 201, 2, 4}));
	cout<<endl<<a;
	a.insert_list(1, column<double>({4, 0, 201, 1023, 2, 4}));
	cout<<endl<<a;
	a.reshape(Tuple<int, int>(3, 12));
	cout<<endl<<a;*/
	/*Vectors<double> a(12, 2, -2), b(1, -1, 0), d(0, -2, 2);
	Surface<double> c(a, b, d);
	outputbox outputbox_c = output(c);
	print_block(outputbox_c);
	cout<<endl<<get_height(outputbox_c)<<" "<<get_width(outputbox_c)<<endl<<get_text(outputbox_c);*/
	p_int a, b;
	a = "-123456123456543212345654323456765432345676543234567789";
	b = "1234567884567645";
	//cout<<a<<" % "<<b<<" = "<<(a % b)<<endl;
	cout<<a.tostring()<<endl<<b.tostring();
	cout<<endl<<a.size()<<" "<<b.size();
	return 0;
}
/*
int main()
{
	initialization();//��ʼ��
	clock_t start = clock();
	Home.func();
	clock_t stop = clock();
	endwords(start, stop);
}*/
