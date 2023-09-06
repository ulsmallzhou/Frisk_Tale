void fullscreen()//全屏并去除缩小按键和侧面滑块 
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
	/*HMENU hmenu = GetSystemMenu(hwnd, 0);
	RemoveMenu(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);
	DestroyMenu(hmenu);
	ReleaseDC(hwnd, NULL);//*/
	SetWindowLongPtrA(hwnd, GWL_STYLE, GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
}
int max_list(initializer_list<int> values)//得到初始化列表最大值 
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
T* arraysame(T value, int length)//形成一个可控长度的每个元素相同的数组 
{
	T* pin = new T[length];
	for(int num = 0; num < length; num += 1)
		pin[num] = value;
	return pin;
}
void readin_mono_1(cyclist<picture*> pics, string address, cyclist<int> heights, cyclist<int> widths)//一个文件里读入多张单色图片 
{
	ifstream fin(address);
	char aline[1000];
	int counter = 0;
	int picture_num = pics.size();//图片数 
	int lines = 0, lists = 0;
	int maxlines = 0, maxlists = 0;
	for(int vid = 0; vid < picture_num; vid += 1)//得到最大范围 
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
		fin.getline(aline, 1000);//读取一个空行，作为图片之间的间隔 
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
//注：可以利用循环列表的初始化列表初始化方法
void readin_mono_2(picture* pics, int picture_num, string address, cyclist<int> heights, cyclist<int> widths)//一个文件里读入多张单色图片 
{
	ifstream fin(address);
	char aline[1000];
	int counter = 0;
	int lines = 0, lists = 0;
	int maxlines = 0, maxlists = 0;
	for(int vid = 0; vid < picture_num; vid += 1)//得到最大范围 
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
		fin.getline(aline, 1000);//读取一个空行，作为图片之间的间隔 
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
void readin_mono_3(picture* pics, int picture_num, string address, int* heights, int* widths)//一个文件里读入多张单色图片 
{
	ifstream fin(address);
	char aline[1000];
	int counter = 0;
	int lines = 0, lists = 0;
	int maxlines = 0, maxlists = 0;
	for(int vid = 0; vid < picture_num; vid += 1)//得到最大范围 
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
		fin.getline(aline, 1000);//读取一个空行，作为图片之间的间隔 
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
//1:picture*的循环链表（也可传入初始化列表）, 23:picture的数组名
void readin_colo(cyclist<colorpicture*> cpics, string address, cyclist<int> heights, cyclist<int> widths)//一个文件里读入多张彩色图片 
{
	ifstream fin(address);
	char aline[1000];
	int counter = 0;
	int colorpicture_num = cpics.size();//图片数 
	int lines = 0, lists = 0;
	int maxlines = 0, maxlists = 0;
	int value = 0;//用来临时存放数值 
	bool ready = 0;//判断行末是否需要存入一次 
	for(int vid = 0; vid < colorpicture_num; vid += 1)//得到最大范围 
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
		fin.getline(aline, 1000);//读取一个空行，作为图片之间的间隔 
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
void page_get_options(page* apage, cyclist<option*> options)//一个页面以及其所包含的按钮 
{
	int option_num = options.size();
	for(int oid = 0; oid < option_num; oid += 1)
		apage->addoption(options[oid]);
}
void page_get_optionarray(page* apage, option* options, int option_num)//以数组形式读入按钮 
{
	for(int oid = 0; oid < option_num; oid += 1)
		apage->addoption(&options[oid]);
}


void readin_pictures()//读入图片数据
{
	readin_mono_3(char65, char65_number, "./pictures/char65.txt", arraysame(5, char65_number), arraysame(6, char65_number));//读入char65字符 
	readin_mono_3(char87, char87_number, "./pictures/char87.txt", arraysame(7, char87_number), arraysame(8, char87_number));//读入char87字符 
	readin_mono_2(hearts, 7, "./pictures/hearts.txt", {3, 4, 5, 6, 7, 8, 9}, {3, 5, 7, 10, 11, 14, 15});//读入心形数据
	readin_mono_1({&p_fight, &p_act, &p_items, &p_mercy}, "./pictures/icon_fight.txt", {7, 7, 7, 7}, {11, 11, 11, 11});//读入战斗的四个图标
}
void pages_get_options()//读入各界面相链接的选项 
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
void readin_level(int level_id)//读入关卡地图
{
	
}


void initialization()//初始化 
{
	fullscreen();//窗口大小初始化 
	srand(time(NULL));//随机数种子 
	print_string(ZERO_POS, "读取素材中...", default_colour);
	readin_pictures();//读取所有图片素材
	pages_get_options();//把选项链接到页面
	pagelist.append({&Home});//进入起始界面 
	system("title Frisk的奇妙冒险");
	print_string(ZERO_POS, "请切换为全屏（按任意键继续）\n注意：请不要按键过快", default_colour);
	anyinput();
	system("cls");
}
void endwords(clock_t start, clock_t stop)
{
	double duration = ((double)(stop - start))/CLK_TCK;//s
	int delay = (int)(duration);
	system("cls");
	print_string(ZERO_POS, "本次游玩时间为" + to_string(delay) + "秒\n输入任意键结束游戏", default_colour);
	anyinput();
}


