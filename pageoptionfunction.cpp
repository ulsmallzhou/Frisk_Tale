int public_1(page* apage)//公共运行函数（全显示并选择）  
{
	bool ifend = 0;
	int inputrank = 0;
	bool changed = 1, refresh = 1;
	int option_num = apage->options.size();
	for(; ifend == 0; )
	{
		if(changed)
			apage->pageprint(apage->pagebase, refresh);
		inputrank = getakey({'w', 's', '\r', 72, 80, 27, 8});
		switch(inputrank)
		{
			case 0:
			case 3:
				changed = !(apage->chosedoption == 0);
				refresh = 0;
				apage->chosedoption = apage->chosedoption == 0 ? apage->chosedoption : apage->chosedoption - 1;
				break;
			case 1:
			case 4:
				refresh = 0;
				changed = !(apage->chosedoption == option_num - 1);
				apage->chosedoption = apage->chosedoption == option_num - 1 ? apage->chosedoption : apage->chosedoption + 1;
				break;
			case 2:
				refresh = 1;
				changed = 1;
				ifend = apage->options[apage->chosedoption]->func();
				apage->chosedoption = 0;
				break;
			case 5://esc
			case 6://backspace
				refresh = 1;
				changed = 1;
				apage->chosedoption = option_num - 1;
				ifend = apage->options[apage->chosedoption]->func();
				apage->chosedoption = 0;
				break;
		}
	}
	return 0;
}
int public_2(page* apage)//公共运行函数（不全显示并选择，共显示3个选项） 
{
	bool ifend = 0;
	int inputrank = 0;
	bool changed = 1, refresh = 1, up_down = 1;
	int option_num = apage->options.size();
	for(; ifend == 0; )
	{
		if(changed)
			apage->pageprint(apage->pagebase, refresh + 2 * up_down);//refresh = ifrefresh + 2 * up_down
		inputrank = getakey({'w', 's', '\r', 72, 80, 27, 8});
		switch(inputrank)
		{
			case 0:
			case 3:
				changed = !(apage->chosedoption == 0);
				up_down = 1;
				refresh = apage->chosedoption > 2;
				apage->chosedoption = apage->chosedoption == 0 ? apage->chosedoption : apage->chosedoption - 1;
				break;
			case 1:
			case 4:
				changed = !(apage->chosedoption == option_num - 1);
				up_down = 0;
				refresh = apage->chosedoption < option_num - 4;
				apage->chosedoption = apage->chosedoption == option_num - 1 ? apage->chosedoption : apage->chosedoption + 1;
				break;
			case 2:
				refresh = 1;
				changed = 1;
				ifend = apage->options[apage->chosedoption]->func();
				apage->chosedoption = 0;
				break;
			case 5://esc
			case 6://backspace
				refresh = 1;
				changed = 1;
				apage->chosedoption = option_num - 1;
				ifend = apage->options[apage->chosedoption]->func();
				apage->chosedoption = 0;
				break;
		}
	}
	return 0;
}
int empty()//page:empty(back)
{
	pagelist.del(pagelist.size() - 1);
	if(pagelist.size() > 0)
		pagelist.del(pagelist.size() - 1);
	return 1;
}
int home(){return public_1(&Home);}
int home_start(){return public_1(&Home_Start);}
int home_glory(){return public_1(&Home_Glory);}
int home_option(){return public_1(&Home_Option);}
int home_start_play(){return public_1(&Home_Start_Play);}
int home_start_saveload(){return public_1(&Home_Start_SaveLoad);}
int home_start_play_adventure(){return public_1(&Home_Start_Play_Adventure);}
int home_start_play_training(){return public_1(&Home_Start_Play_Training);}
int home_start_saveload_archieve1(){return public_1(&Home_Start_SaveLoad_Archieve1);}
int home_start_saveload_archieve2(){return public_1(&Home_Start_SaveLoad_Archieve2);}
int home_start_saveload_archieve3(){return public_1(&Home_Start_SaveLoad_Archieve3);}





void pr_public_1(page* apage, position pos, int refresh)//公共打印函数（全显示） 
{
	if(refresh)
		print_widesquare(pos, apage->height, apage->width, ' ', ' ', 1, anti_default_colour, default_colour);
	int option_num = apage->options.size();
	for(int oid = 0; oid < option_num; oid += 1)
		apage->options[oid]->print(apage->pagebase, apage->chosedoption == oid);
}
void pr_public_2(page* apage, position pos, int refresh)//公共打印函数（不全显示） 
{
	if(refresh % 2)//refresh = ifrefresh + 2 * up_down
		print_widesquare(pos, apage->height, apage->width, ' ', ' ', 1, anti_default_colour, default_colour);
	int option_num = apage->options.size();
	bool up_down = refresh / 2;
	int chosed = apage->chosedoption;
	/* TODO (#1#): 上的情况异常 */
	if(up_down)//1:up, 0:down
		for(int oid = max(chosed - 2, 0); oid < max(chosed + 1, 3); oid += 1)
			apage->options[oid]->print(apage->pagebase - topos(13, 0) * max(chosed - 2, 0), apage->chosedoption == oid);
	else
		for(int oid = min(chosed, option_num - 2); oid < min(chosed + 3, option_num); oid += 1)
			apage->options[oid]->print(apage->pagebase - topos(13, 0) * min(chosed, option_num - 3), apage->chosedoption == oid);
}
void pr_empty(position pos, int refresh){}
void pr_home(position pos, int refresh){pr_public_1(&Home, pos, refresh);}
void pr_home_start(position pos, int refresh){pr_public_1(&Home_Start, pos, refresh);}
void pr_home_glory(position pos, int refresh){pr_public_1(&Home_Glory, pos, refresh);}
void pr_home_option(position pos, int refresh){pr_public_1(&Home_Option, pos, refresh);}
void pr_home_start_play(position pos, int refresh){pr_public_1(&Home_Start_Play, pos, refresh);}
void pr_home_start_saveload(position pos, int refresh){pr_public_2(&Home_Start_SaveLoad, pos, refresh);}
void pr_home_start_play_adventure(position pos, int refresh){pr_public_2(&Home_Start_Play_Adventure, pos, refresh);}
void pr_home_start_play_training(position pos, int refresh){pr_public_1(&Home_Start_Play_Training, pos, refresh);}
void pr_home_start_saveload_archieve1(position pos, int refresh){pr_public_1(&Home_Start_SaveLoad_Archieve1, pos, refresh);}
void pr_home_start_saveload_archieve2(position pos, int refresh){pr_public_1(&Home_Start_SaveLoad_Archieve2, pos, refresh);}
void pr_home_start_saveload_archieve3(position pos, int refresh){pr_public_1(&Home_Start_SaveLoad_Archieve3, pos, refresh);}


