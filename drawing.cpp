#include "include.cpp"
//时间测试函数 
//clock_t start, stop;
//start = clock();
//需要测试运行时间的代码 
//stop = clock();
//double duration = ((double)(stop - start))/CLK_TCK;


//错误调试：1001(dict:KeyError), 1002(sqrt:Negtive), 1003(DividedByZero)
//1004(Matrix:OutOfRange), 1005(Matrix:SizeNotMatch), 1006(Matrix:AllZero)
//1007(Matrix:NotFullrank), 1008(Matrix:ZeroSize)
//1009(Geometry:Uncertain), 1010(P_int:Illegal)


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
	initialization();//初始化
	clock_t start = clock();
	Home.func();
	clock_t stop = clock();
	endwords(start, stop);
}*/
