int getopration(initializer_list<string> cases)//������ȡ��ƥ�䵽ѡ�����ƥ�䵽��ѡ����ţ�0��ʼ�� 
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
		cout<<"��������Ҫ���еĲ�����wsad�������һ�ֱ������ѡ����,yesѡ��ǰѡ�:";
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
int getakey(initializer_list<char> cases)//��ȡ��������һ���������벢ƥ�� 
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
void anyinput()//���������
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
//��ȡ��������һ���Ϸ����벢��������ţ�����������ʱ�䣨ms���򷵻�ֵ����ƥ���λ��
