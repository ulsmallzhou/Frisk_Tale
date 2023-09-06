int public_1(page* apage)//公共运行函数 
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
int home_start_play_adventure()
{
	return 0;
}
int home_start_play_training()
{
	return 0;
}
int home_start_saveload_archieve1()
{
	return 0;
}
int home_start_saveload_archieve2()
{
	return 0;
}
int home_start_saveload_archieve3()
{
	return 0;
}





void pr_public_1(page* apage, position pos, int refresh)//公共打印函数 
{
	if(refresh)
		print_widesquare(pos, apage->height, apage->width, ' ', ' ', 1, anti_default_colour, default_colour);
	int option_num = apage->options.size();
	for(int oid = 0; oid < option_num; oid += 1)
		apage->options[oid]->print(apage->pagebase, apage->chosedoption == oid);
}
void pr_empty(position pos, int refresh){}
void pr_home(position pos, int refresh){pr_public_1(&Home, pos, refresh);}
void pr_home_start(position pos, int refresh){pr_public_1(&Home_Start, pos, refresh);}
void pr_home_glory(position pos, int refresh){pr_public_1(&Home_Glory, pos, refresh);}
void pr_home_option(position pos, int refresh){pr_public_1(&Home_Option, pos, refresh);}
void pr_home_start_play(position pos, int refresh){pr_public_1(&Home_Start_Play, pos, refresh);}
void pr_home_start_saveload(position pos, int refresh){pr_public_1(&Home_Start_SaveLoad, pos, refresh);}
void pr_home_start_play_adventure(position pos, int refresh)
{
	
}
void pr_home_start_play_training(position pos, int refresh)
{
	
}
void pr_home_start_saveload_archieve1(position pos, int refresh)
{
	
}
void pr_home_start_saveload_archieve2(position pos, int refresh)
{
	
}
void pr_home_start_saveload_archieve3(position pos, int refresh)
{
	
}


