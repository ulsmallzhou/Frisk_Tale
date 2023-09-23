typedef int (*todo)();
typedef void (*printff)(position pos, int refresh);


class page;
cyclist<page*> pagelist;//已经打开的页面列表，回退时用 


class option
{
public:
	int height = 0;
	int width = 0;
	int chartype = 0;//0:normal, 1:65char, 2:87char 
	string text = "";
	position option_position = topos(0, 0);//按键相对于页面基点的相对坐标 
	position text_position = topos(2, 3);//文本相对于按键坐标的相对坐标 
	color selected = defaultcolour[7];//被选中的颜色，默认黄色 
	color not_selected = defaultcolour[6];//未被选中的颜色，默认棕色
	page* nextpage;//按钮对应的下一个页面 
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
	void setcolor(color select, color noselect)//设置选项颜色 
	{
		selected = select;
		not_selected = noselect;
	}
	void settext(int type, string str, position relative)//设置文本内容位置格式 
	{
		text = str;
		chartype = type;
		text_position = relative;
	}
	void set(int aheight, int awidth, int type, string str, position relative, position textpos, color sele, color nosele, page* apage)//整体设置 
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
	int func();//按键对应的函数（即前往执行下一个页面的函数）
};


class page//TODO
{
public:
	int height = 0;
	int width = 0;
	position pagebase = topos(0, 0);//界面基准坐标 
	cyclist<option*> options;//选项
	int chosedoption = 0;//被选定的选项 
	todo func;//界面对应的函数
	printff pageprint;//显示函数 
	page(){}
	page(position pos, int aheight, int awidth, todo afunc, printff aprint)
	{
		height = aheight;
		width = awidth;
		pagebase = pos;
		func = afunc;
		pageprint = aprint;
	}
	void addoption(option* anoption){options.append({anoption});}//增加一个选项
	void setfunc(todo funct){func = funct;}
	void setprint(printff aprint){pageprint = aprint;}
};


int option::func()
{
	pagelist.append({nextpage});
	return nextpage->func();
}

