void gotoxy(short lines,short lists){SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{lists,lines});}
//某些时候输出需要反复横跳，故将光标移动函数封装在此
const short int B_WIDTH = 184, B_HEIGHT = 52;//背景规格


class position//坐标类 
{
public:
	int lines = 0;
	int lists = 0;
	position(){}
	position(int line, int list)
	{
		lines = line;
		lists = list;
	}
	position operator+(const position& pos)
	{
		position pos_new(this->lines + pos.lines, this->lists + pos.lists);
		return pos_new;
	}
	bool operator==(const position& pos)
	{
		return this->lines == pos.lines && this->lists == pos.lists;
	}
	bool operator!=(const position& pos)
	{
		return this->lines != pos.lines || this->lists != pos.lists;
	}
};
position topos(int line, int list)//参数转位置 
{
	position pos(line, list);
	return pos;
}
double euclid_distance(position pos_1, position pos_2)//计算直线距离 
{
	return sqrt((pos_1.lines - pos_2.lines) * (pos_1.lines - pos_2.lines) + (pos_1.lists - pos_2.lists) * (pos_1.lists - pos_2.lists));
}
int manhattan_distance(position pos_1, position pos_2)//计算曼哈顿距离（横平竖直）
{
	return abs(pos_1.lines - pos_2.lines) + abs(pos_1.lists - pos_2.lists);
}
int chebyshev_distance(position pos_1, position pos_2)//计算切比雪夫距离（允许斜45°但视为1） 
{
	return max(abs(pos_1.lines - pos_2.lines), abs(pos_1.lists - pos_2.lists));
}
double minkowski_distance(double p, position pos_1, position pos_2)//计算p-范数下的距离（闵可夫斯基距离） 
{
	return pow(pow(pos_1.lines - pos_2.lines, p) + pow(pos_1.lists - pos_2.lists, p), 1 / p);
}


void gotopos(position pos){gotoxy(pos.lines, pos.lists);}//跳转函数 
const position ZERO_POS(0, 0), LAST_POS(B_HEIGHT + 1, 0);//起始点和最终跳转点 
const position A(0, -1), S(-1, 0), D(0, 1), W(1, 0);//坐标变化
const position op_l_h(4, 20), op_l_l(20, 20), op_r_h(4, 99), op_r_l(20, 99);
const short int OP_WIDTH = 61, OP_HEIGHT = 11;//四个选项的位置及规格
const position dialogbox_pos(34, 14);
const short int DIALOG_WIDTH = 152, DIALOG_HEIGHT = 15;//对话框位置及规格 
const position dialog_pos_left_high(36, 16), dialog_pos_left_low(42, 16), dialog_pos_right_high(36, 51), dialog_pos_right_low(42, 51);//对话显示的位置 

