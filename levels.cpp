class room//������� 
{
public:
	int type = 0;//����(0:) 
	bool enterable = 0;//�Ƿ�ɽ��� 
	virtual string check(){}//�麯�������������е���ʵ��;
};
class room_fight: public room//ս������ 
{
public:
	entity enemy;
	string check()
	{
		return "111";
	}
};
class level//ÿһ���ͼ 
{
	string name = "";
	int width = 0;
	int height = 0;
	room** pixs = NULL;//�ؿ���ͼ����ֵ����ͬ�ķ���
	level(int l_width, int l_height)
	{
		width = l_width;
		height = l_height;
		pixs = new room*[height];
		for(int line = 0; line < height; line += 1)
			pixs[line] = new room[width];
	}
};
