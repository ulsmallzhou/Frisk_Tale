void fullscreen()//ȫ����ȥ����С�����Ͳ��滬�� 
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
	/*HMENU hmenu = GetSystemMenu(hwnd, 0);
	RemoveMenu(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);
	DestroyMenu(hmenu);
	ReleaseDC(hwnd, NULL);//*/
	SetWindowLongPtrA(hwnd, GWL_STYLE, GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
}
int max_list(initializer_list<int> values)//�õ���ʼ���б����ֵ 
{
	int size = values.size();
	auto* value = values.begin();
	int maxs = 0;
	for(int num = 0; num < size; num += 1)
	{
		if(*value > maxs)
			maxs = *value;
		value++;
	}
	return maxs;
}
template <typename T>
T* arraysame(T value, int length)//�γ�һ���ɿس��ȵ�ÿ��Ԫ����ͬ������ 
{
	T* pin = new T[length];
	for(int num = 0; num < length; num += 1)
		pin[num] = value;
	return pin;
}
void readin_mono_1(cyclist<picture*> pics, string address, cyclist<int> heights, cyclist<int> widths)//һ���ļ��������ŵ�ɫͼƬ 
{
	ifstream fin(address);
	char aline[1000];
	int counter = 0;
	int picture_num = pics.size();//ͼƬ�� 
	int lines = 0, lists = 0;
	int maxlines = 0, maxlists = 0;
	for(int vid = 0; vid < picture_num; vid += 1)//�õ����Χ 
	{
		if(widths[vid] > maxlists)
			maxlists = widths[vid];
		if(heights[vid] > maxlines)
			maxlines = heights[vid];
	}
	bool** values = new bool*[maxlines];
	for(int line = 0; line < maxlines; line += 1)
		values[line] = new bool[maxlists];
	for(int pid = 0; pid < picture_num; pid += 1)
	{
		fin.getline(aline, 1000);//��ȡһ�����У���ΪͼƬ֮��ļ�� 
		counter = 0;
		lines = heights[pid];
		lists = widths[pid];
		for(int line = 0; line < lines; line += 1)
		{
			fin.getline(aline, 1000);
			for(int chara = 0; chara < 1000; chara += 1)
				if(aline[chara] == '0' || aline[chara] == '1')
				{
					values[counter / lists][counter % lists] = (bool)(aline[chara] - '0');
					counter += 1;
				}
				else if(aline[chara] == '\0' || aline[chara] == '/' && aline[chara + 1] == '/')
					break;
		}
		pics[pid]->set(values, lines, lists);
	}
	fin.close();
	for(int line = 0; line < maxlines; line += 1)
		delete[] values[line];
	delete[] values;
}
//ע����������ѭ���б�ĳ�ʼ���б��ʼ������
void readin_mono_2(picture* pics, int picture_num, string address, cyclist<int> heights, cyclist<int> widths)//һ���ļ��������ŵ�ɫͼƬ 
{
	ifstream fin(address);
	char aline[1000];
	int counter = 0;
	int lines = 0, lists = 0;
	int maxlines = 0, maxlists = 0;
	for(int vid = 0; vid < picture_num; vid += 1)//�õ����Χ 
	{
		if(widths[vid] > maxlists)
			maxlists = widths[vid];
		if(heights[vid] > maxlines)
			maxlines = heights[vid];
	}
	bool** values = new bool*[maxlines];
	for(int line = 0; line < maxlines; line += 1)
		values[line] = new bool[maxlists];
	for(int pid = 0; pid < picture_num; pid += 1)
	{
		fin.getline(aline, 1000);//��ȡһ�����У���ΪͼƬ֮��ļ�� 
		counter = 0;
		lines = heights[pid];
		lists = widths[pid];
		for(int line = 0; line < lines; line += 1)
		{
			fin.getline(aline, 1000);
			for(int chara = 0; chara < 1000; chara += 1)
				if(aline[chara] == '0' || aline[chara] == '1')
				{
					values[counter / lists][counter % lists] = (bool)(aline[chara] - '0');
					counter += 1;
				}
				else if(aline[chara] == '\0' || aline[chara] == '/' && aline[chara + 1] == '/')
					break;
		}
		pics[pid].set(values, lines, lists);
	}
	fin.close();
	for(int line = 0; line < maxlines; line += 1)
		delete[] values[line];
	delete[] values;
}
void readin_mono_3(picture* pics, int picture_num, string address, int* heights, int* widths)//һ���ļ��������ŵ�ɫͼƬ 
{
	ifstream fin(address);
	char aline[1000];
	int counter = 0;
	int lines = 0, lists = 0;
	int maxlines = 0, maxlists = 0;
	for(int vid = 0; vid < picture_num; vid += 1)//�õ����Χ 
	{
		if(widths[vid] > maxlists)
			maxlists = widths[vid];
		if(heights[vid] > maxlines)
			maxlines = heights[vid];
	}
	bool** values = new bool*[maxlines];
	for(int line = 0; line < maxlines; line += 1)
		values[line] = new bool[maxlists];
	for(int pid = 0; pid < picture_num; pid += 1)
	{
		fin.getline(aline, 1000);//��ȡһ�����У���ΪͼƬ֮��ļ�� 
		counter = 0;
		lines = heights[pid];
		lists = widths[pid];
		for(int line = 0; line < lines; line += 1)
		{
			fin.getline(aline, 1000);
			for(int chara = 0; chara < 1000; chara += 1)
				if(aline[chara] == '0' || aline[chara] == '1')
				{
					values[counter / lists][counter % lists] = (bool)(aline[chara] - '0');
					counter += 1;
				}
				else if(aline[chara] == '\0' || aline[chara] == '/' && aline[chara + 1] == '/')
					break;
		}
		pics[pid].set(values, lines, lists);
	}
	fin.close();
	for(int line = 0; line < maxlines; line += 1)
		delete[] values[line];
	delete[] values;
}
//1:picture*��ѭ������Ҳ�ɴ����ʼ���б�, 23:picture��������
void readin_colo(cyclist<colorpicture*> cpics, string address, cyclist<int> heights, cyclist<int> widths)//һ���ļ��������Ų�ɫͼƬ 
{
	ifstream fin(address);
	char aline[1000];
	int counter = 0;
	int colorpicture_num = cpics.size();//ͼƬ�� 
	int lines = 0, lists = 0;
	int maxlines = 0, maxlists = 0;
	int value = 0;//������ʱ�����ֵ 
	bool ready = 0;//�ж���ĩ�Ƿ���Ҫ����һ�� 
	for(int vid = 0; vid < colorpicture_num; vid += 1)//�õ����Χ 
	{
		if(widths[vid] > maxlists)
			maxlists = widths[vid];
		if(heights[vid] > maxlines)
			maxlines = heights[vid];
	}
	int** values = new int*[maxlines];
	for(int line = 0; line < maxlines; line += 1)
		values[line] = new int[maxlists];
	for(int pid = 0; pid < colorpicture_num; pid += 1)
	{
		fin.getline(aline, 1000);//��ȡһ�����У���ΪͼƬ֮��ļ�� 
		counter = 0;
		lines = heights[pid];
		lists = widths[pid];
		for(int line = 0; line < lines; line += 1)
		{
			fin.getline(aline, 1000);
			for(int chara = 0; chara < 1000; chara += 1)
				if(aline[chara] == '\0' || aline[chara] == '/' && aline[chara + 1] == '/')
				{
					if(ready)
					{
						values[counter / lists][counter % lists] = value;
						counter += 1;
						value = 0;
					}
					break;
				}
				else if(aline[chara] >= '0' && aline[chara] <= '9')
				{
					value = value * 10 + aline[chara] - '0';
					ready = 1;
				}
				else if(aline[chara] == ',')
				{
					values[counter / lists][counter % lists] = value;
					counter += 1;
					value = 0;
					ready = 0;
				}
		}
		cpics[pid]->set(values, lines, lists);
	}
	fin.close();
	for(int line = 0; line < maxlines; line += 1)
		delete[] values[line];
	delete[] values;
}
//void
void page_get_options(page* apage, cyclist<option*> options)//һ��ҳ���Լ����������İ�ť 
{
	int option_num = options.size();
	for(int oid = 0; oid < option_num; oid += 1)
		apage->addoption(options[oid]);
}
void page_get_optionarray(page* apage, option* options, int option_num)//��������ʽ���밴ť 
{
	for(int oid = 0; oid < option_num; oid += 1)
		apage->addoption(&options[oid]);
}


void readin_pictures()//����ͼƬ����
{
	readin_mono_3(char65, char65_number, "./pictures/char65.txt", arraysame(5, char65_number), arraysame(6, char65_number));//����char65�ַ� 
	readin_mono_3(char87, char87_number, "./pictures/char87.txt", arraysame(7, char87_number), arraysame(8, char87_number));//����char87�ַ� 
	readin_mono_2(hearts, 7, "./pictures/hearts.txt", {3, 4, 5, 6, 7, 8, 9}, {3, 5, 7, 10, 11, 14, 15});//������������
	readin_mono_1({&p_fight, &p_act, &p_items, &p_mercy}, "./pictures/icon_fight.txt", {7, 7, 7, 7}, {11, 11, 11, 11});//����ս�����ĸ�ͼ��
}
void pages_get_options()//��������������ӵ�ѡ�� 
{
	page_get_options(&Home, {&Home__Start, &Home__Glory, &Home__Option, &Home__Exit});
	page_get_options(&Home_Start, {&Home_Start__NewGame, &Home_Start__SaveLoad, &Home_Start__Continue, &Home_Start__Back});
	page_get_options(&Home_Glory, {&Home_Glory__Ok});
	page_get_options(&Home_Option, {&Home_Option__Ok});
	page_get_options(&Home_Start_Play, {&Home_Start_Play__Adventure, &Home_Start_Play__Training, &Home_Start_Play__Back});
	page_get_options(&Home_Start_SaveLoad, {&Home_Start_SaveLoad__Archieve1, &Home_Start_SaveLoad__Archieve2, &Home_Start_SaveLoad__Archieve3, &Home_Start_SaveLoad__Back});
	page_get_optionarray(&Home_Start_Play_Adventure, Home_Start_Play_Adventure__Levels, levels_num);
	page_get_options(&Home_Start_Play_Adventure, {&Home_Start_Play_Adventure__Back});
	page_get_options(&Home_Start_Play_Training, {&Home_Start_Play_Training__Attack, &Home_Start_Play_Training__Defense, &Home_Start_Play_Training__Magic, &Home_Start_Play_Training__Back});
	page_get_options(&Home_Start_SaveLoad_Archieve1, {&Home_Start_SaveLoad_Archieve__Save, &Home_Start_SaveLoad_Archieve__Load, &Home_Start_SaveLoad_Archieve__Back});
	page_get_options(&Home_Start_SaveLoad_Archieve2, {&Home_Start_SaveLoad_Archieve__Save, &Home_Start_SaveLoad_Archieve__Load, &Home_Start_SaveLoad_Archieve__Back});
	page_get_options(&Home_Start_SaveLoad_Archieve3, {&Home_Start_SaveLoad_Archieve__Save, &Home_Start_SaveLoad_Archieve__Load, &Home_Start_SaveLoad_Archieve__Back});
	
}
void readin_level(int level_id)//����ؿ���ͼ
{
	
}


void initialization()//��ʼ�� 
{
	fullscreen();//���ڴ�С��ʼ�� 
	srand(time(NULL));//��������� 
	print_string(ZERO_POS, "��ȡ�ز���...", default_colour);
	readin_pictures();//��ȡ����ͼƬ�ز�
	pages_get_options();//��ѡ�����ӵ�ҳ��
	pagelist.append({&Home});//������ʼ���� 
	system("title Frisk������ð��");
	print_string(ZERO_POS, "���л�Ϊȫ�����������������\nע�⣺�벻Ҫ��������", default_colour);
	anyinput();
	system("cls");
}
void endwords(clock_t start, clock_t stop)
{
	double duration = ((double)(stop - start))/CLK_TCK;//s
	int delay = (int)(duration);
	system("cls");
	print_string(ZERO_POS, "��������ʱ��Ϊ" + to_string(delay) + "��\n���������������Ϸ", default_colour);
	anyinput();
}


