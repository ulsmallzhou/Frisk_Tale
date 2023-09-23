int getopration(initializer_list<string> cases)//操作读取并匹配到选项，返回匹配到的选项序号（0起始） 
{
	char ipt;
	string input;
	int length = cases.size(), iptsize = 0;
	auto* option = cases.begin();
	bool match = 0;
	for(; ; )
	{
		input = "";
		gotopos(LAST_POS);
		cout<<"请输入需要进行的操作（wsad上下左右或直接输入选项名,yes选择当前选项）:";
		for(; ; )
		{
			cin>>noskipws>>ipt;
			if(ipt == '\n')
			{
				if(input == "")
					input = "\n";
				break;
			}
			else
				input += ipt;
		}
		iptsize = input.size();
		gotopos(LAST_POS);
		for(int num = 0; num < iptsize + 70; num += 1)
			cout<<" ";
		option = cases.begin();
		for(int num = 0; num < length; num += 1)
		{
			if(*option == input)
				return num;
			option++;
		}
		
	}
}
int getakey(initializer_list<char> cases)//获取接下来的一个按键输入并匹配 
{
	gotopos(LAST_POS);
	char input;
	int length = cases.size();
	auto* pin = cases.begin();
	for(; ; )
	{
		input = getch();
		pin = cases.begin();
		for(int num = 0; num < length; num += 1)
		{
			if(*pin == input)
				return num;
			pin++;
		}
	}
}
void anyinput()//任意键继续
{
	gotopos(LAST_POS);
	char ipt;
	for(; ; )
		if(_kbhit())
		{
			ipt = _getch();
			break;
		}
}
int timer_getakey(initializer_list<char> cases, long long int maxdelay)//maxdelay:ms
{
	gotopos(LAST_POS);
	clock_t start, stop;
	start = clock();
	int key = getakey(cases);
	stop = clock();
	double duration = ((double)(stop - start))/CLK_TCK;//s
	long long int delay = (int)(1000 * duration);
	return (maxdelay > delay ? 0 : 1) * cases.size() + key;
}
//获取接下来的一个合法输入并返回其序号，若超出给定时间（ms）则返回值增加匹配键位数
int update_get(int delay, int counter)//实时获取键盘被按下的情况，返回该按键的char值，否则返回-1；delay单位ms
{
	int out = -1;
	dict<int, int> keybd_input;
	for(int num = 0; num < counter; num += 1)
	{
		Sleep(delay / counter);
		gotopos(LAST_POS);
		if(_kbhit())
			out = (int)_getch();
		else
			out = -1;
		if(keybd_input.find(out) != -1)
			keybd_input.set(out, keybd_input[out] + 1);
		else
			keybd_input.set(out, 1);
	}
	
	return out;
}
//该方法在低delay下不稳定，需要较高counter取样 

