//该页面为界面选项设置页 
//B_WIDTH = 184, B_HEIGHT = 52, 位于position.cpp
const int levels_num = 5;
page Home(topos(0, 0), B_HEIGHT, B_WIDTH, home, pr_home);//起始页面
page Empty(topos(0, 0), 0, 0, empty, pr_empty);//空页面，直接返回 

page Home_Start(topos(0, 0), B_HEIGHT, B_WIDTH, home_start, pr_home_start),\
	 Home_Glory(topos(0, 0), B_HEIGHT, B_WIDTH, home_glory, pr_home_glory),\
	 Home_Option(topos(5, 57), 42, 70, home_option, pr_home_option);//进入游戏，成就页（当前未做），选项

page Home_Start_Play(topos(5, 55), 41, 74, home_start_play, pr_home_start_play),\
	 Home_Start_SaveLoad(topos(0, 59), B_HEIGHT, 66, home_start_saveload, pr_home_start_saveload);//正式进入游戏（NewGame, Continue），存读档界面

page Home_Start_Play_Adventure(topos(10, 59), 30, 66, home_start_play_adventure, pr_home_start_play_adventure),\
	 Home_Start_Play_Training(topos(5, 59), 41, 66, home_start_play_training, pr_home_start_play_training),\
	 Home_Start_SaveLoad_Archieve1(topos(5, 55), 41, 74, home_start_saveload_archieve, ),\
	 Home_Start_SaveLoad_Archieve2,\
	 Home_Start_SaveLoad_Archieve3;

page Home_Start_Play_Adventure_Levels,\
	 Home_Start_Play_Adventure_Back,\
	 Home_Start_Play_Training_Attack,\
	 Home_Start_Play_Training_Defense,\
	 Home_Start_Play_Training_Magic,\
	 Home_Start_SaveLoad_Archieve_Success;
	 



option Home__Start(11, 60, 2, "START", topos(1, 62), topos(2, 8), &Home_Start),\
	   Home__Glory(11, 60, 2, "GLORY", topos(14, 62), topos(2, 8), &Home_Glory),\
	   Home__Option(11, 60, 2, "OPTION", topos(27, 62), topos(2, 3), &Home_Option),\
	   Home__Exit(11, 60, 2, "EXIT", topos(40, 62), topos(2, 13), &Empty);

option Home_Start__NewGame(11, 78, 2, "NEW GAME ", topos(1, 53), topos(2, 3), &Home_Start_Play),\
	   Home_Start__SaveLoad(11, 78, 2, "SAVELOAD", topos(14, 53), topos(2, 3), &Home_Start_SaveLoad),\
	   Home_Start__Continue(11, 78, 2, "CONTINUE", topos(27, 53), topos(2, 3), &Home_Start_Play),\
	   Home_Start__Back(11, 78, 2, "  BACK  ", topos(40, 53), topos(2, 3), &Empty);
option Home_Glory__Ok(11, 24, 2, "OK", topos(40, 80), topos(2, 3), &Empty);
option Home_Option__Ok(11, 24, 2, "OK", topos(30, 23), topos(2, 3), &Empty);

option Home_Start_Play__Adventure(11, 68, 2, "EXPLORE", topos(2, 3), topos(2, 3), &Home_Start_Play_Adventure),\
	   Home_Start_Play__Training(11, 68, 2, " TRAIN ", topos(15, 3), topos(2, 3), &Home_Start_Play_Training),\
	   Home_Start_Play__Back(11, 68, 2, " BACK ", topos(28, 3), topos(2, 7), &Empty);
option Home_Start_SaveLoad__Archieve1(11, 60, 2, "SLOT 1", topos(1, 3), topos(2, 3), &Home_Start_SaveLoad_Archieve1),\
	   Home_Start_SaveLoad__Archieve2(11, 60, 2, "SLOT 2", topos(14, 3), topos(2, 3), &Home_Start_SaveLoad_Archieve2),\
	   Home_Start_SaveLoad__Archieve3(11, 60, 2, "SLOT 3", topos(27, 3), topos(2, 3), &Home_Start_SaveLoad_Archieve3),\
	   Home_Start_SaveLoad__Back(11, 60, 2, " BACK ", topos(40, 3), topos(2, 3), &Empty);

option Home_Start_Play_Adventure__Levels[levels_num] = {\
	{.height = 11, .width = 60, .chartype = 2, .text = "LEVEL1", .option_position = topos(1, 3), .text_position = topos(2, 3), .nextpage = &Empty},\
	{.height = 11, .width = 60, .chartype = 2, .text = "LEVEL2", .option_position = topos(14, 3), .text_position = topos(2, 3), .nextpage = &Empty},\
	{.height = 11, .width = 60, .chartype = 2, .text = "LEVEL3", .option_position = topos(27, 3), .text_position = topos(2, 3), .nextpage = &Empty},\
	{.height = 11, .width = 60, .chartype = 2, .text = "LEVEL4", .option_position = topos(40, 3), .text_position = topos(2, 3), .nextpage = &Empty},\
	{.height = 11, .width = 60, .chartype = 2, .text = "LEVEL5", .option_position = topos(53, 3), .text_position = topos(2, 3), .nextpage = &Empty}},\
	   Home_Start_Play_Adventure__Back(11, 60, 2, " BACK ", topos(66, 3), topos(2, 3), &Empty);
option Home_Start_Play_Training__Attack,\
	   Home_Start_Play_Training__Defense,\
	   Home_Start_Play_Training__Magic,\
	   Home_Start_Play_Training__Back;
option Home_Start_SaveLoad_Archieve__Save,\
	   Home_Start_SaveLoad_Archieve__Load,\
	   Home_Start_SaveLoad_Archieve__Back;

option Home_Start_SaveLoad_Archieve_Success__Ok;

