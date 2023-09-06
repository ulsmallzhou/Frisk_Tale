class room//房间基类 
{
public:
	int type = 0;//类型(0:) 
	bool enterable = 0;//是否可进入 
	virtual string check(){}//虚函数，房间子类中单独实现;
};
class room_fight: public room//战斗房间 
{
public:
	entity enemy;
	string check()
	{
		return "111";
	}
};
class level//每一层地图 
{
	string name = "";
	int width = 0;
	int height = 0;
	room** pixs = NULL;//关卡地图，数值代表不同的房间
	level(int l_width, int l_height)
	{
		width = l_width;
		height = l_height;
		pixs = new room*[height];
		for(int line = 0; line < height; line += 1)
			pixs[line] = new room[width];
	}
};
