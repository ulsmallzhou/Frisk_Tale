void print_string(position pos, string str, color colour)//��ת����� 
{
	set_color(colour);
	gotopos(pos);
	cout<<str;
	reset_color();
}
void print_num_small(position pos, long long int number, short max_lists, color colour)//��ӡС����
{
	string output = to_string(number);
	int len = output.length();
	print_string(pos, output.substr(0, min(len, max_lists - pos.lists)), colour);
}
void print_square(position pos, short height, short width, char oper_edge, char oper_inside, bool full, color colour_edge, color colour_inside)//��ӡ����
{
	string edge = "", inside = "", oper_o, oper_i;
	oper_o = oper_edge;
	oper_i = oper_inside;
	for(int times = 0; times < width; times += 1)
		edge.append(oper_o);
	for(int times = 1; times < width - 1; times += 1)
		inside.append(oper_i);
	print_string(pos, edge, colour_edge);//�ϱ� 
	print_string(topos(pos.lines + height - 1, pos.lists), edge, colour_edge);//�±� 
	for(int line = 1; line < height - 1; line += 1)//���ұ� 
	{
		print_string(topos(pos.lines + line, pos.lists), oper_o, colour_edge);
		print_string(topos(pos.lines + line, pos.lists + width - 1), oper_o, colour_edge);
	}
	if(full && width > 2 && height > 2)//�ڲ� 
		for(int line = 1; line < height - 1; line += 1)
			print_string(topos(pos.lines + line, pos.lists + 1), inside, colour_inside);
}
void print_widesquare(position pos, short height, short width, char oper_edge, char oper_inside, bool full, color colour_edge, color colour_inside)//��ӡ��߿�2�ľ��� 
{
	print_square(pos, height, width, oper_edge, oper_inside, full, colour_edge, colour_inside);
	print_square(pos + topos(0, 1), height, width - 2, oper_edge, oper_inside, full, colour_edge, colour_inside);
}


class picture//��ɫͼƬ��
{
public:
	int width = 0, height = 0;
	bool** pin = NULL;
	picture(){}//�չ��캯�� 
	picture(int p_height, int p_width)
	{
		width = p_width;
		height = p_height;
		pin = new bool*[height];
		for(int line = 0; line < height; line += 1)
			pin[line] = new bool[width];
	}
	picture(int p_height, int p_width, initializer_list<initializer_list<bool>> values)
	{
		width = p_width;
		height = p_height;
		pin = new bool*[height];
		for(int line = 0; line < height; line += 1)
			pin[line] = new bool[width];
		auto* pixpins = values.begin();
		for(int line = 0; line < height; line += 1)
		{
			auto* pixpin = (*pixpins).begin();
			for(int list = 0; list < width; list += 1)
			{
				pin[line][list] = *pixpin;
				pixpin++;
			}
			pixpins++;
		}
	}
	picture(const picture &pic)
	{
		width = pic.width;
		height = pic.height;
		pin = new bool*[height];
		for(int line = 0; line < height; line += 1)
		{
			pin[line] = new bool[width];
			for(int list = 0; list < width; list += 1)
				pin[line][list] = pic.pin[line][list];
		}
	}
	~picture()
	{
		if(pin != NULL)
		{
			for(int num = 0; num < height; num += 1)
				delete[] pin[num];
			delete[] pin;
		}
	}
	bool operator==(const picture& pic)//==���� 
	{
		bool same = 1;
		same = same && (width == pic.width) && (height == pic.height);
		if(same) for(int line = 0; line < height; line += 1)
			for(int list = 0; list < width; list += 1)
				if(pin[line][list] != pic.pin[line][list])
				{
					same = 0;
					break;
				}
		return same;
	}
	void set_line(short line, initializer_list<bool> values)//������ 
	{
		auto* pixpin = values.begin();
		for(int list = 0; list < width; list += 1)
		{
			pin[line][list] = *pixpin;
			pixpin++;
		}
	}
	void set_list(short list, initializer_list<bool> values)//������
	{
		auto* pixpin = values.begin();
		for(int line = 0; line < height; line += 1)
		{
			pin[line][list] = *pixpin;
			pixpin++;
		}
	}
	void set(initializer_list<initializer_list<bool>> values)//ֱ�����ã�ȫ�����ã� 
	{
		auto* pixpins = values.begin();
		for(int line = 0; line < height; line += 1)
		{
			auto* pixpin = (*pixpins).begin();
			for(int list = 0; list < width; list += 1)
			{
				pin[line][list] = *pixpin;
				pixpin++;
			}
			pixpins++;
		}
	}
	void set(bool** values, int p_height, int p_width)//ֱ�����ã�ȫ�����ã���������գ�
	{
		width = p_width;
		height = p_height;
		pin = new bool*[height];
		for(int line = 0; line < height; line += 1)
			pin[line] = new bool[width];
		for(int line = 0; line < height; line += 1)
			for(int list = 0; list < width; list += 1)
				pin[line][list] = values[line][list];
	}
	//void set(picture pic, int start_line, int start_list, )
	void print(position pos, color colour)//�򵥵Ĵ�ӡͼƬ
	{
		for(int line = 0; line < height; line += 1)
			for(int list = 0; list < width; list += 1)
				if(pin[line][list])
					print_string(pos + topos(line, list), " ", colour);
		gotopos(LAST_POS);
	}
	void print(position pos, int start_line, int start_list, int linenum, int listnum, color colour)//��ӡͼƬ��һ���� 
	{
		for(int line = 0; line < min(height - start_line, linenum); line += 1)
			for(int list = 0; list < min(width - start_list, listnum); list += 1)
				if(pin[line + start_line][list + start_list])
					print_string(pos + topos(line, list), " ", colour);
		gotopos(LAST_POS);
	}
};
picture p_fight, p_act, p_items, p_mercy;//ս��ͼ�꣬���ڳ�ʼ���ж��� 
const int char65_number = 92;//65����ַ��� 
picture char65[char65_number];//���ڳ�ʼ����д�� 
const int char87_number = 37;//87����ַ���
picture char87[char87_number];//���ڳ�ʼ����д�� 
picture hearts[7];//����ͼƬ�����ڳ�ʼ����д�� 


class colorpicture//��ɫͼƬ��
{
public:
	int width = 0, height = 0;
	int** pin = NULL;//0~15ΪĬ����ɫ���룬16Ϊ�� 
	colorpicture(){}//�չ��캯�� 
	colorpicture(int p_height, int p_width)//��ͼƬ��С���죬Ĭ��ȫͼΪ͸��ɫ 
	{
		width = p_width;
		height = p_height;
		pin = new int*[height];
		for(int line = 0; line < height; line += 1)
		{
			pin[line] = new int[width];
			for(int list = 0; list < width; list += 1)
				pin[line][list] = 16;//Ĭ����Ϊ͸��ͼƬ 
		}
	}
	colorpicture(int p_height, int p_width, int colour_id)//��ͼƬ��С����һ�Ŵ�ɫͼ 
	{
		width = p_width;
		height = p_height;
		pin = new int*[height];
		for(int line = 0; line < height; line += 1)
		{
			pin[line] = new int[width];
			for(int list = 0; list < width; list += 1)
				pin[line][list] = colour_id;
		}
	}
	colorpicture(int p_height, int p_width, initializer_list<initializer_list<int>> values)
	{
		width = p_width;
		height = p_height;
		pin = new int*[height];
		for(int line = 0; line < height; line += 1)
			pin[line] = new int[width];
		auto* pixpins = values.begin();
		for(int line = 0; line < height; line += 1)
		{
			auto* pixpin = (*pixpins).begin();
			for(int list = 0; list < width; list += 1)
			{
				pin[line][list] = *pixpin;
				pixpin++;
			}
			pixpins++;
		}
	}
	~colorpicture()
	{
		if(pin != NULL)
		{
			for(int num = 0; num < height; num += 1)
				delete[] pin[num];
			delete[] pin;
		}
	}
	bool operator==(const colorpicture& cpic)//==���� 
	{
		bool same = 1;
		same = same && (width == cpic.width) && (height == cpic.height);
		if(same) for(int line = 0; line < height; line += 1)
			for(int list = 0; list < width; list += 1)
				if(pin[line][list] != cpic.pin[line][list])
				{
					same = 0;
					break;
				}
		return same;
	}
	void set_size(int p_height, int p_width)//���ù�� 
	{
		if(pin != NULL)
		{
			for(int num = 0; num < height; num += 1)
				delete[] pin[num];
		}
		width = p_width;
		height = p_height;
	}
	void set_line(short line, initializer_list<int> values)//������ 
	{
		auto* pixpin = values.begin();
		for(int list = 0; list < width; list += 1)
		{
			pin[line][list] = *pixpin;
			pixpin++;
		}
	}
	void set_list(short list, initializer_list<int> values)//������
	{
		auto* pixpin = values.begin();
		for(int line = 0; line < height; line += 1)
		{
			pin[line][list] = *pixpin;
			pixpin++;
		}
	}
	void set(initializer_list<initializer_list<int>> values)//ֱ�����ã�ȫ�����ã� 
	{
		auto* pixpins = values.begin();
		for(int line = 0; line < height; line += 1)
		{
			auto* pixpin = (*pixpins).begin();
			for(int list = 0; list < width; list += 1)
			{
				pin[line][list] = *pixpin;
				pixpin++;
			}
			pixpins++;
		}
	}
	void set(int** values, int p_height, int p_width)//ֱ�����ã�ȫ�����ã���������գ�
	{
		width = p_width;
		height = p_height;
		pin = new int*[height];
		for(int line = 0; line < height; line += 1)
			pin[line] = new int[width];
		for(int line = 0; line < height; line += 1)
			for(int list = 0; list < width; list += 1)
				pin[line][list] = values[line][list];
	}
	void set(picture pic, int start_line, int start_list, int colour_id)//���õ�ɫͼ�������� 
	{
		int lines = min(pic.height, height - start_line);
		int lists = min(pic.width, width - start_list);
		for(int line = 0; line < lines; line += 1)
			for(int list = 0; list < lists; list += 1)
				if(pic.pin[line][list])
					pin[line + start_line][list + start_list] = colour_id;
	}
	void print(position pos)//�򵥵Ĵ�ӡͼƬ
	{
		for(int line = 0; line < height; line += 1)
			for(int list = 0; list < width; list += 1)
				if(pin[line][list] < 16)
					print_string(pos + topos(line, list), " ", defaultcolour[pin[line][list]]);
		gotopos(LAST_POS);
	}
	void print(position pos, int start_line, int start_list, int linenum, int listnum)//��ӡͼƬ��һ���� 
	{
		int lines = min(height - start_line, linenum);
		int lists = min(width - start_list, listnum);
		for(int line = 0; line < lines; line += 1)
			for(int list = 0; list < lists; list += 1)
				if(pin[line + start_line][list + start_list] < 16)
					print_string(pos + topos(line, list), " ", defaultcolour[pin[line + start_line][list + start_list]]);
		gotopos(LAST_POS);
	}
};
colorpicture blackbackground(B_HEIGHT, B_WIDTH, 0);


int char65_id(string str)//�ַ�����ͼƬ��Ŷ�Ӧ
{
	int length = str.size();
	if(length == 1)
	{
		if(str[0] >= '0' && str[0] <= '9')
			return str[0] - '0';
		else if(str[0] >= 'A' && str[0] <= 'Z')
			return str[0] - 'A' + 10;
		else if(str[0] >= 'a' && str[0] <= 'z')
			return str[0] - 'a' + 10;
		else switch(str[0])
		{
			//'!'~')':36~45
			case '!':
				return 36;
			case '@':
				return 37;
			case '#':
				return 38;
			case '$':
				return 39;
			case '%':
				return 40;
			case '^':
				return 41;
			case '&':
				return 42;
			case '*':
				return 43;
			case '(':
				return 44;
			case ')':
				return 45;
			//'`' '��' '~' '-' '_' '+' '[' ']' '{' '}' '\' '|' '/' ':' ';' ',' '.' ''' '"' '?'
			//46  47   48  49  50  51  52  53  54  55  56  57  58  59  60  61  62  63  64  65
			case '`':
				return 46;
			/*case '��':
				return 47;*/
			case '~':
				return 48;
			case '-':
				return 49;
			case '_':
				return 50;
			case '+':
				return 51;
			case '[':
				return 52;
			case ']':
				return 53;
			/*case '{':
				return 54;*/
			case '}':
				return 55;
			case '\\':
				return 56;
			case '|':
				return 57;
			case '/':
				return 58;
			case ':':
				return 59;
			case ';':
				return 60;
			case ',':
				return 61;
			case '.':
				return 62;
			case '\'':
				return 63;
			case '\"':
				return 64;
			case '\?':
				return 65;
			//'=' '!=' '<' '>' '<=' '>='
			//66  67   68  69  70   71
			case '=':
				return 66;
			case '<':
				return 68;
			case '>':
				return 69;
		}
	}
	else switch(1000 * (int)str.substr(1, length - 2)[0] + (int)str.substr(1, length - 2)[length - 3] + length * 100)
	{
		case 1000 * (int)'`' + (int)'.' + 400:
			return 47;
		case 1001 * (int)'{' + 300:
			return 54;
		//'=' '!=' '<' '>' '<=' '>='
		//66  67   68  69  70   71
		case 1000 * (int)'!' + (int)'=' + 400:
			return 67;
		case 1000 * (int)'<' + (int)'=' + 400:
			return 70;
		case 1000 * (int)'>' + (int)'=' + 400:
			return 71;
		//'�հ�' '��1��' '��2��' '��3��' '��4��' '��5��' '�׿�' '��5��' '��4��' '��3��' '��2��' '��1��'
		//72     73      74      75      76      77      78     79      80      81      82      83
		case 1000 * (int)'s' + (int)'e' + 700:
			return 72;
		case 1000 * (int)'l' + (int)'1' + 700:
			return 73;
		case 1000 * (int)'l' + (int)'2' + 700:
			return 74;
		case 1000 * (int)'l' + (int)'3' + 700:
			return 75;
		case 1000 * (int)'l' + (int)'4' + 700:
			return 76;
		case 1000 * (int)'l' + (int)'5' + 700:
			return 77;
		case 1000 * (int)'f' + (int)'l' + 600:
			return 78;
		case 1000 * (int)'r' + (int)'5' + 800:
			return 79;
		case 1000 * (int)'r' + (int)'4' + 800:
			return 80;
		case 1000 * (int)'r' + (int)'3' + 800:
			return 81;
		case 1000 * (int)'r' + (int)'2' + 800:
			return 82;
		case 1000 * (int)'r' + (int)'1' + 800:
			return 83;
		//'��1��' '��2��' '��3��' '��4��' '��4��' '��3��' '��2��' '��1��'
		//84      85      86      87      88      89      90      91
		case 1000 * (int)'l' + (int)'1' + 600:
			return 84;
		case 1000 * (int)'l' + (int)'2' + 600:
			return 85;
		case 1000 * (int)'l' + (int)'3' + 600:
			return 86;
		case 1000 * (int)'l' + (int)'4' + 600:
			return 87;
		case 1000 * (int)'h' + (int)'4' + 700:
			return 88;
		case 1000 * (int)'h' + (int)'3' + 700:
			return 89;
		case 1000 * (int)'h' + (int)'2' + 700:
			return 90;
		case 1000 * (int)'h' + (int)'1' + 700:
			return 91;
	}
	return 72;
}
//"{>=}", "{<=}", "{!=}", "{`.}", "{{}", "{space}", "{full}", "{left1}"~"{left5}", "{right5}"~"{right1}", "{low1}"~"{low4}", "{high4}"~"{high1}"
int char87_id(char input)
{
	if(input == ' ')
		return 36;
	else if(input >= '0' && input <= '9')
		return input - '0';
	else if(input >= 'a' && input <= 'z')
		return input - 'a' + 10;
	else if(input >= 'A' && input <= 'Z')
		return input - 'A' + 10;
	return 36;
}
//'0'~'9', 'A'~'Z', ' '
void print_heart(position pos, int size, bool clear, color colour)//��ӡ����(size:1(3*3), 2(4*5), 3(5*7), 4(6*10), 5(7*11), 6(8*14), 7(9*15))
{
	if(size > 0 && size < 8)
	{
		if(clear)
			print_square(pos, hearts[size - 1].height, hearts[size - 1].width, ' ', ' ', 1, default_colour, default_colour);
		hearts[size - 1].print(pos, colour);
	}
}
void print_dialogbox()//���ã���滭���Ի��� 
{
	print_square(dialogbox_pos, DIALOG_HEIGHT, DIALOG_WIDTH, ' ', ' ', 0, anti_default_colour, anti_default_colour);
	print_square(topos(0, -1) + dialogbox_pos, DIALOG_HEIGHT, DIALOG_WIDTH + 2, ' ', ' ', 0, anti_default_colour, anti_default_colour);
	reset_color();
	print_square(topos(1, 1) + dialogbox_pos, DIALOG_HEIGHT - 2, DIALOG_WIDTH - 2, ' ', ' ', 1, default_colour, default_colour);
}
void print_65string(position pos, string str, color colour, int sleeptime)//��ӡ����65����ַ���
{
	int length = str.size();
	int printed_num = 0;
	for(int pin = 0; pin < length; pin += 1)
		if(str[pin] != '{')
		{
			char65[char65_id(str.substr(pin, 1))].print(pos + topos(0, 7 * printed_num), colour);
			printed_num += 1;
			Sleep(sleeptime);
		}
		else for(int subpin = pin + 2; subpin < length; subpin += 1)
			if(str[subpin] == '}')
			{
				char65[char65_id(str.substr(pin, subpin - pin + 1))].print(pos + topos(0, 7 * printed_num), colour);
				pin = subpin;
				printed_num += 1;
				Sleep(sleeptime);
				break;
			}
}
void print_87string(position pos, string str, color colour, int sleeptime)//��ӡ����87����ַ���
{
	int length = str.size();
	for(int pin = 0; pin < length; pin += 1)
	{
		char87[char87_id(str[pin])].print(pos + topos(0, 9 * pin), colour);
		Sleep(sleeptime);
	}
}
void print_option(position pos, int option, bool selected, bool ifpicture)//��ӡѡ��(1:fight, 2:act, 3:items, 4:mercy)
{
	color print_colour = selected ? selected_option : not_selected_option;
	print_square(pos + topos(0, -1), OP_HEIGHT, OP_WIDTH + 2, ' ', ' ', 0, print_colour, print_colour);
	print_square(pos, OP_HEIGHT, OP_WIDTH, ' ', ' ', 0, print_colour, print_colour);//��ӡ��� 
	switch(option)
	{
		case 1:
			print_87string(pos + topos(2, 14), "FIGHT", print_colour, 0);
			break;
		case 2:
			print_87string(pos + topos(2, 14), " ACT ", print_colour, 0);
			break;
		case 3:
			print_87string(pos + topos(2, 14), "ITEMS", print_colour, 0);
			break;
		case 4:
			print_87string(pos + topos(2, 14), "MERCY", print_colour, 0);
			break;
	}
	if(ifpicture)
		switch(option)
		{
			case 1:
				p_fight.print(pos + topos(2, 2), print_colour);
				break;
			case 2:
				p_act.print(pos + topos(2, 2), print_colour);
				break;
			case 3:
				p_items.print(pos + topos(2, 2), print_colour);
				break;
			case 4:
				p_mercy.print(pos + topos(2, 2), print_colour);
				break;
		}
	reset_color();
}

