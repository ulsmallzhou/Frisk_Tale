void gotoxy(short lines,short lists){SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{lists,lines});}
//ĳЩʱ�������Ҫ�����������ʽ�����ƶ�������װ�ڴ�
const short int B_WIDTH = 184, B_HEIGHT = 52;//�������


class position//������ 
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
position topos(int line, int list)//����תλ�� 
{
	position pos(line, list);
	return pos;
}
double euclid_distance(position pos_1, position pos_2)//����ֱ�߾��� 
{
	return sqrt((pos_1.lines - pos_2.lines) * (pos_1.lines - pos_2.lines) + (pos_1.lists - pos_2.lists) * (pos_1.lists - pos_2.lists));
}
int manhattan_distance(position pos_1, position pos_2)//���������پ��루��ƽ��ֱ��
{
	return abs(pos_1.lines - pos_2.lines) + abs(pos_1.lists - pos_2.lists);
}
int chebyshev_distance(position pos_1, position pos_2)//�����б�ѩ����루����б45�㵫��Ϊ1�� 
{
	return max(abs(pos_1.lines - pos_2.lines), abs(pos_1.lists - pos_2.lists));
}
double minkowski_distance(double p, position pos_1, position pos_2)//����p-�����µľ��루�ɿɷ�˹�����룩 
{
	return pow(pow(pos_1.lines - pos_2.lines, p) + pow(pos_1.lists - pos_2.lists, p), 1 / p);
}


void gotopos(position pos){gotoxy(pos.lines, pos.lists);}//��ת���� 
const position ZERO_POS(0, 0), LAST_POS(B_HEIGHT + 1, 0);//��ʼ���������ת�� 
const position A(0, -1), S(-1, 0), D(0, 1), W(1, 0);//����仯
const position op_l_h(4, 20), op_l_l(20, 20), op_r_h(4, 99), op_r_l(20, 99);
const short int OP_WIDTH = 61, OP_HEIGHT = 11;//�ĸ�ѡ���λ�ü����
const position dialogbox_pos(34, 14);
const short int DIALOG_WIDTH = 152, DIALOG_HEIGHT = 15;//�Ի���λ�ü���� 
const position dialog_pos_left_high(36, 16), dialog_pos_left_low(42, 16), dialog_pos_right_high(36, 51), dialog_pos_right_low(42, 51);//�Ի���ʾ��λ�� 

