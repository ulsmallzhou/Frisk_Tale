string full(int length, char chara)//产生一个字符的定长字符串 
{
	string out = "";
	string out_0;
	out_0 = chara;
	for(int num = 0; num < length; num += 1)
		out = out + out_0;
	return out;
}


typedef Tuple<Tuple<int, int>, cyclist<string>> outputbox;


template <typename T>
outputbox output(T input)//输出框模板函数，正常情况下用的是下面的特化 
{Tuple<int, int> a(0, 0); cyclist<string> b({""}); return Tuple<Tuple<int, int>, cyclist<string>>(a, b);}


template<>
outputbox output(int input)//针对int的特化 
{
	string out = to_string(input);
	Tuple<int, int> size(1, out.size());
	cyclist<string> text({out});
	return Tuple<Tuple<int, int>, cyclist<string>>(size, text);
}
template<>
outputbox output(long long int input)//针对long long int的特化 
{
	string out = to_string(input);
	Tuple<int, int> size(1, out.size());
	cyclist<string> text({out});
	return Tuple<Tuple<int, int>, cyclist<string>>(size, text);
}
template<>
outputbox output(char input)//针对char的特化 
{
	string out;
	out = input;
	out = "\'" + out + "\'";
	Tuple<int, int> size(1, out.size());
	cyclist<string> text({out});
	return Tuple<Tuple<int, int>, cyclist<string>>(size, text);
}
template<>
outputbox output(double input)//针对double的特化 
{
	string out = to_string(input);
	Tuple<int, int> size(1, out.size());
	cyclist<string> text({out});
	return Tuple<Tuple<int, int>, cyclist<string>>(size, text);
}
template<>
outputbox output(string input)//针对string的特化 
{
	Tuple<int, int> size(1, input.size());
	cyclist<string> text({input});
	return Tuple<Tuple<int, int>, cyclist<string>>(size, text);
}


template <typename T1, typename T2>
outputbox output(Tuple<T1, T2> input)//针对Tuple的特化 
{
	Tuple<Tuple<int, int>, cyclist<string>> outputbox1 = output(input.elemt_0);
	Tuple<Tuple<int, int>, cyclist<string>> outputbox2 = output(input.elemt_1);
	Tuple<int, int> size_1 = outputbox1.elemt_0;
	Tuple<int, int> size_2 = outputbox2.elemt_0;
	cyclist<string> text_1 = outputbox1.elemt_1;
	cyclist<string> text_2 = outputbox2.elemt_1;
	int height = max(size_1.elemt_0, size_2.elemt_0);
	int width = max(size_1.elemt_1, size_2.elemt_1);//(, )
	//下面对所有元素进行空格补全
	for(int line = 0; line < size_1.elemt_0; line += 1)
		text_1[line] = text_1[line] + full(width - text_1[line].size(), ' ');
	for(int line = 0; line < size_2.elemt_0; line += 1)
		text_2[line] = text_2[line] + full(width - text_2[line].size(), ' ');
	cyclist<string> texts;
	string text;
	string spaces = full(width, ' ');
	for(int line = 0; line < height; line += 1)
	{
		text = (line == height - 1 ? "[" : " ");
		text = text + (line + size_1.elemt_0 < height ? spaces : text_1[line + size_1.elemt_0 - height]);
		text = text + (line == height - 1 ? ", " : "  ");
		text = text + (line + size_2.elemt_0 < height ? spaces : text_2[line + size_2.elemt_0 - height]);
		text = text + (line == height - 1 ? "]" : " ");
		texts.append({text});
	}
	Tuple<int, int> size(height, 2 * width + 4);
	return Tuple<Tuple<int, int>, cyclist<string>>(size, texts);
}


template <typename T>
outputbox output(cyclist<T> input)//针对cyclist的特化，后续可以对换行进行改进，也可以改进两侧括号 
{
	int element_num = input.size();
	Tuple<Tuple<int, int>, cyclist<string>> outputbox;
	Tuple<int, int> sizes[element_num];
	cyclist<string> texts[element_num];
	for(int num = 0; num < element_num; num += 1)
	{
		outputbox = output(input[num]);
		sizes[num] = outputbox.elemt_0;
		texts[num] = outputbox.elemt_1;
	}
	int height = 0;
	int width = 0;
	for(int id = 0; id < element_num; id += 1)
	{
		height = max(height, sizes[id].elemt_0);
		width = max(width, sizes[id].elemt_1);
	}
	//下面对所有字符串作空格补全
	for(int id = 0; id < element_num; id += 1)
		for(int line = 0; line < sizes[id].elemt_0; line += 1)
			texts[id][line] = texts[id][line] + full(width - texts[id][line].size(), ' ');
	cyclist<string> out_texts;
	string text;
	string spaces = full(width, ' ');
	for(int line = 0; line < height; line += 1)
	{
		text = (line == height - 1 ? "[" : " ");
		for(int id = 0; id < element_num; id += 1)
		{
			if(id > 0)
				text = text + (line == height - 1 ? ", " : "  ");
			text = text + (line + sizes[id].elemt_0 < height ? spaces : texts[id][line + sizes[id].elemt_0 - height]);
		}
		text = text + (line == height - 1 ? "]" : " ");
		out_texts.append({text});
	}
	Tuple<int, int> size(height, element_num * (width + 2));
	return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
}

/*
template <typename T1, typename T2>
Tuple<Tuple<int, int>, cyclist<string>> output(dict<T1, T2> input)//针对dict的特化 
{
	
}*/


template <typename T>
outputbox output(matrix<T> input)//针对matrix的特化，可考虑改进为不同的行宽列宽 
{
	Tuple<int, int> matrix_size = input.size();
	Tuple<Tuple<int, int>, cyclist<string>> outputbox;
	Tuple<int, int> sizes[matrix_size.elemt_0][matrix_size.elemt_1];
	cyclist<string> texts[matrix_size.elemt_0][matrix_size.elemt_1];
	int height = 0;
	int width = 0;
	for(int line = 0; line < matrix_size.elemt_0; line += 1)
		for(int list = 0; list < matrix_size.elemt_1; list += 1)
		{
			outputbox = output(input[line][list]);
			sizes[line][list] = outputbox.elemt_0;
			texts[line][list] = outputbox.elemt_1;
			height = max(height, sizes[line][list].elemt_0);
			width = max(width, sizes[line][list].elemt_1);
		}
	//下面对所有字符串作空格补全
	for(int line = 0; line < matrix_size.elemt_0; line += 1)
		for(int list = 0; list < matrix_size.elemt_1; list += 1)
			for(int text_id = 0; text_id < sizes[line][list].elemt_0; text_id += 1)
				texts[line][list][text_id] = texts[line][list][text_id] + full(width - texts[line][list][text_id].size(), ' ');
	cyclist<string> out_texts;
	string text;
	string spaces = full(width, ' ');
	string edge[5] = {"(", "/", "|", "\\", ")"};
	for(int line = 0; line < matrix_size.elemt_0; line += 1)
		for(int subline = 0; subline < height; subline += 1)
		{
			if(matrix_size.elemt_0 == 1 && height == 1) text = edge[0];
			else if(line == 0 && subline == 0) text = edge[1];
			else if(line == matrix_size.elemt_0 - 1 && subline == height - 1) text = edge[3];
			else text = edge[2];
			for(int list = 0; list < matrix_size.elemt_1; list += 1)
			{
				if(list > 0)
					text = text + " ";
				text = text + (line + sizes[line][list].elemt_0 < height ? spaces : texts[line][list][line + sizes[line][list].elemt_0 - height]);
			}
			if(matrix_size.elemt_0 == 1 && height == 1) text = text + edge[4];
			else if(line == 0 && subline == 0) text = text + edge[3];
			else if(line == matrix_size.elemt_0 - 1 && subline == height - 1) text = text + edge[1];
			else text = text + edge[2];
			out_texts.append({text});
		}
	Tuple<int, int> size(height * matrix_size.elemt_0, (width + 1) * matrix_size.elemt_1 + 1);
	return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
}

/*class basetype//所有基础类的合集，有需要再启用 
{
public:
	int type_name = 0;//1:int, 2:long long int, 3:char, 4:double, 5:string
	int bint = 0;
	long long int bllint = 0;
	char bchar = '\0';
	double bdouble = 0.0;
	string bstring = "";
	basetype(){type_name = 1;}
	basetype(int input){type_name = 1; bint = input;}
	basetype(long long int input){type_name = 2; bllint = input;}
	basetype(char input){type_name = 3; bchar = input;}
	basetype(double input){type_name = 4; bdouble = input;}
	basetype(string input){type_name = 5; bstring = input;}
	basetype(const basetype &input)
	{
		type_name = input.type_name;
		bint = input.bint; bllint = input.bllint; bchar = input.bchar; bdouble = input.bdouble; bstring = input.bstring;
	}
	operator int(){return bint;}
	operator long long int(){return bllint;}
	operator char(){return bchar;}
	operator double(){return bdouble;}
	operator string(){return bstring;}
	string type()
	{
		string name;
		switch(type_name)
		{
			case 1:
				name = "int";
				break;
			case 2:
				name = "long long int";
				break;
			case 3:
				name = "char";
				break;
			case 4:
				name = "double";
				break;
			case 5:
				name = "string";
				break;
		}
	}
	void operator=(int input){bint = input; bllint = 0; bchar = '\0'; bdouble = 0.0; bstring = ""; type_name = 1;}
	void operator=(long long int input){bint = 0; bllint = input; bchar = '\0'; bdouble = 0.0; bstring = ""; type_name = 2;}
	void operator=(char input){bint = 0; bllint = 0; bchar = input; bdouble = 0.0; bstring = ""; type_name = 3;}
	void operator=(double input){bint = 0; bllint = 0; bchar = '\0'; bdouble = input; bstring = ""; type_name = 4;}
	void operator=(string input){bint = 0; bllint = 0; bchar = '\0'; bdouble = 0.0; bstring = ""; type_name = 5;}
	void operator=(const basetype &input)
	{
		type_name = input.type_name;
		bint = input.bint; bllint = input.bllint; bchar = input.bchar; bdouble = input.bdouble; bstring = input.bstring;
	}
	Tuple<Tuple<int, int>, cyclist<string>> output()
	{
		string out;
		switch(type_name)
		{
			case 1:
				out = to_string(bint);
				break;
			case 2:
				out = to_string(bllint);
				break;
			case 3:
				out = bchar;
				out = "\'" + out + "\'";
				break;
			case 4:
				out = to_string(bdouble);
				break;
			case 5:
				out = bstring;
				break;
		}
		Tuple<int, int> size(1, out.size());
		cyclist<string> text({out});
		return Tuple<Tuple<int, int>, cyclist<string>>(size, text);
	}
	friend ostream &operator<<(ostream &output, basetype abase)
	{
		Tuple<Tuple<int, int>, cyclist<string>> outputbox = abase.output();
		int line_num = outputbox.elemt_0.elemt_0;
		for(int line = 0; line < line_num; line += 1)
		{
			if(line > 0)
				output<<"\n";
			output<<outputbox.elemt_1[line];
		}
		return output;
	}
};*/
