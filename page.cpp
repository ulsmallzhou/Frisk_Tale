typedef int (*todo)();
typedef void (*printff)(position pos, int refresh);


class page;
cyclist<page*> pagelist;//�Ѿ��򿪵�ҳ���б�����ʱ�� 


class option
{
public:
	int height = 0;
	int width = 0;
	int chartype = 0;//0:normal, 1:65char, 2:87char 
	string text = "";
	position option_position = topos(0, 0);//���������ҳ������������� 
	position text_position = topos(2, 3);//�ı�����ڰ��������������� 
	color selected = defaultcolour[7];//��ѡ�е���ɫ��Ĭ�ϻ�ɫ 
	color not_selected = defaultcolour[6];//δ��ѡ�е���ɫ��Ĭ����ɫ
	page* nextpage;//��ť��Ӧ����һ��ҳ�� 
	option(){}
	option(int aheight, int awidth, int type, string str, position relative, position textpos, page* apage)
	{
		height = aheight;
		width = awidth;
		text = str;
		chartype = type;
		text_position = textpos;
		option_position = relative;
		nextpage = apage;
	}
	option(int aheight, int awidth, int type, string str, position relative, position textpos, color sele, color nosele, page* apage)
	{
		height = aheight;
		width = awidth;
		chartype = type;
		text = str;
		text_position = textpos;
		option_position = relative;
		selected = sele;
		not_selected = nosele;
		nextpage = apage;
	}
	bool operator==(const option& opt)
	{
		return chartype == opt.chartype && text == opt.text;
	}
	void setcolor(color select, color noselect)//����ѡ����ɫ 
	{
		selected = select;
		not_selected = noselect;
	}
	void settext(int type, string str, position relative)//�����ı�����λ�ø�ʽ 
	{
		text = str;
		chartype = type;
		text_position = relative;
	}
	void set(int aheight, int awidth, int type, string str, position relative, position textpos, color sele, color nosele, page* apage)//�������� 
	{
		height = aheight;
		width = awidth;
		chartype = type;
		text = str;
		text_position = textpos;
		option_position = relative;
		selected = sele;
		not_selected = nosele;
		nextpage = apage;
	}
	void print(position pos, bool ifselected)
	{
		color colour = ifselected ? selected : not_selected;
		print_widesquare(pos + option_position, height, width, ' ', ' ', 0, colour, colour);
		switch(chartype)
		{
			case 0:
				print_string(pos + option_position + text_position, text, colour);
				break;
			case 1:
				print_65string(pos + option_position + text_position, text, colour, 0);
				break;
			case 2:
				print_87string(pos + option_position + text_position, text, colour, 0);
				break;
		}
	}
	int func();//������Ӧ�ĺ�������ǰ��ִ����һ��ҳ��ĺ�����
};


class page//TODO
{
public:
	int height = 0;
	int width = 0;
	position pagebase = topos(0, 0);//�����׼���� 
	cyclist<option*> options;//ѡ��
	int chosedoption = 0;//��ѡ����ѡ�� 
	todo func;//�����Ӧ�ĺ���
	printff pageprint;//��ʾ���� 
	page(){}
	page(position pos, int aheight, int awidth, todo afunc, printff aprint)
	{
		height = aheight;
		width = awidth;
		pagebase = pos;
		func = afunc;
		pageprint = aprint;
	}
	void addoption(option* anoption){options.append({anoption});}//����һ��ѡ��
	void setfunc(todo funct){func = funct;}
	void setprint(printff aprint){pageprint = aprint;}
};


int option::func()
{
	pagelist.append({nextpage});
	return nextpage->func();
}

