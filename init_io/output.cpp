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
int get_height(outputbox input){return input.elemt_0.elemt_0;}//获取高度
int get_width(outputbox input){return input.elemt_0.elemt_1;}//获取宽度
cyclist<string> get_text(outputbox input){return input.elemt_1;}//获取文本




template <typename T>
outputbox output(T input)//输出框模板函数，正常情况下用的是下面的特化 
{Tuple<int, int> size(0, 0); cyclist<string> texts({""}); return Tuple<Tuple<int, int>, cyclist<string>>(size, texts);}


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
const int MAX_AFTER_POINT = 2;
template<>
outputbox output(double input)//针对double的特化 
{
	string out = to_string(input);
	out = out.substr(0, out.size() - 6 + MAX_AFTER_POINT);
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
template<>
outputbox output(p_int input)//针对p_int的特化 
{
	Tuple<int, int> size(1, input.size());
	cyclist<string> text({input.tostring()});
	return Tuple<Tuple<int, int>, cyclist<string>>(size, text);
}




template <typename T1, typename T2>
outputbox output(Tuple<T1, T2> input)//针对Tuple的特化 
{
	Tuple<Tuple<int, int>, cyclist<string>> outputbox1 = output(input.elemt_0);
	Tuple<Tuple<int, int>, cyclist<string>> outputbox2 = output(input.elemt_1);
	cyclist<string> text_1 = get_text(outputbox1);
	cyclist<string> text_2 = get_text(outputbox2);
	int height_1 = get_height(outputbox1); int height_2 = get_height(outputbox2);
	int height = max(height_1, height_2);
	int width_1 = get_width(outputbox1); int width_2 = get_width(outputbox2);
	//下面对所有元素进行空格补全
	for(int line = 0; line < height_1; line += 1)
		text_1[line] = text_1[line] + full(width_1 - text_1[line].size(), ' ');
	for(int line = 0; line < height_2; line += 1)
		text_2[line] = text_2[line] + full(width_2 - text_2[line].size(), ' ');
	cyclist<string> texts;
	string text;
	string spaces_1 = full(width_1, ' ');
	string spaces_2 = full(width_2, ' ');
	if(height == 1)
	{
		text = "(";
		text = text + (height_1 == 0 ? spaces_1 : text_1[0]);
		text = text + ", ";
		text = text + (height_2 == 0 ? spaces_2 : text_2[0]);
		text = text + ")";
		texts.append({text});
		Tuple<int, int> size(1, width_1 + width_2 + 4);
		return Tuple<Tuple<int, int>, cyclist<string>>(size, texts);
	}
	else
	{
		string edge[3] = {"/", "|", "\\"};
		for(int line = -1; line <= height; line += 1)
		{
			if(line == -1) text = edge[0] + " ";
			else if(line == height) text = edge[2] + " ";
			else text = edge[1] + " ";
			text = text + (line + height_1 < height || line == height ? spaces_1 : text_1[line + height_1 - height]);
			text = text + (line == height - 1 ? ", " : "  ");
			text = text + (line + height_2 < height || line == height ? spaces_2 : text_2[line + height_2 - height]);
			if(line == -1) text = text + " " + edge[2];
			else if(line == height) text = text + " " + edge[0];
			else text = text + " " + edge[1];
			texts.append({text});
		}
		Tuple<int, int> size(height + 2, width_1 + width_2 + 6);
		return Tuple<Tuple<int, int>, cyclist<string>>(size, texts);
	}
}


template <typename T>
outputbox output(cyclist<T> input)//针对cyclist的特化，后续可以对换行进行改进
{
	int element_num = input.size();
	Tuple<Tuple<int, int>, cyclist<string>> outputbox;
	int heights[element_num];
	int height = 0;
	int widths[element_num];
	int width_sum = 0;
	cyclist<string> texts[element_num];
	for(int num = 0; num < element_num; num += 1)
	{
		outputbox = output(input[num]);
		heights[num] = get_height(outputbox);
		widths[num] = get_width(outputbox);
		texts[num] = get_text(outputbox);
		height = max(height, heights[num]);
		width_sum += widths[num];
	}
	//下面对所有字符串作空格补全
	for(int id = 0; id < element_num; id += 1)
		for(int line = 0; line < heights[id]; line += 1)
			texts[id][line] = texts[id][line] + full(widths[id] - texts[id][line].size(), ' ');
	cyclist<string> out_texts;
	string text;
	string spaces[element_num];
	for(int id = 0; id < element_num; id += 1)
		spaces[id] = full(widths[id], ' ');
	if(height == 1)
	{
		text = "[";
		for(int id = 0; id < element_num; id += 1)
		{
			if(id > 0)
				text = text + ", ";
			text = text + (heights[id] == 0 ? spaces[id] : texts[id][0]);
		}
		text = text + "]";
		out_texts.append({text});
		Tuple<int, int> size(height, width_sum + 2 * element_num);
		return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
	}
	else
	{
		string edge[4] = {"+-", "| ", " |", "-+"};
		for(int line = -1; line <= height; line += 1)
		{
			if(line == -1 || line == height) text = edge[0];
			else text = edge[1];
			for(int id = 0; id < element_num; id += 1)
			{
				if(id > 0)
					text = text + (line == height - 1 ? ", " : "  ");
				text = text + (line + heights[id] < height || line == height ? spaces[id] : texts[id][line + heights[id] - height]);
			}
			if(line == -1 || line == height) text = text + edge[3];
			else text = text + edge[2];
			out_texts.append({text});
		}
		Tuple<int, int> size(height + 2, width_sum + 2 * element_num + 2);
		return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
	}
}


template <typename T1, typename T2>
Tuple<Tuple<int, int>, cyclist<string>> output(dict<T1, T2> input)//针对dict的特化 TODO
{
	int element_num = input.size();
	Tuple<Tuple<int, int>, cyclist<string>> outputbox;
	int key_height[element_num];
	int key_width[element_num];
	cyclist<string> key_texts[element_num];
	int value_height[element_num];
	int value_width[element_num];
	cyclist<string> value_texts[element_num];
	int height = 0;
	int width_sum = 0;
	for(int num = 0; num < element_num; num += 1)
	{
		outputbox = output(input.key[num]);
		key_height[num] = get_height(outputbox);
		key_width[num] = get_width(outputbox);
		key_texts[num] = get_text(outputbox);
		outputbox = output(input.value[num]);
		value_height[num] = get_height(outputbox);
		value_width[num] = get_width(outputbox);
		value_texts[num] = get_text(outputbox);
		height = max(height, key_height[num]);
		height = max(height, value_height[num]);
		width_sum = width_sum + key_width[num] + value_width[num];
	}
	//下面对所有字符串作空格补全
	for(int id = 0; id < element_num; id += 1)
	{
		for(int line = 0; line < key_height[id]; line += 1)
			key_texts[id][line] = key_texts[id][line] + full(key_width[id] - key_texts[id][line].size(), ' ');
		for(int line = 0; line < value_height[id]; line += 1)
			value_texts[id][line] = value_texts[id][line] + full(value_width[id] - value_texts[id][line].size(), ' ');
	}
	cyclist<string> out_texts;
	string text;
	string key_spaces[element_num], value_spaces[element_num];
	for(int id = 0; id < element_num; id += 1)
	{
		key_spaces[id] = full(key_width[id], ' ');
		value_spaces[id] = full(value_width[id], ' ');
	}
	string edge[8] = {" /", "/ ", "| ", " |", " \\", "\\ ", "< ", " >"};
	if(height == 1)
	{
		text = "{";
		for(int id = 0; id < element_num; id += 1)
		{
			if(id > 0)
				text = text + ", ";
			text = text + (key_height[id] == 0 ? key_spaces[id] : key_texts[id][0]);
			text = text + ": ";
			text = text + (value_height[id] == 0 ? value_spaces[id] : value_texts[id][0]);
		}
		text = text + "}";
		out_texts.append({text});
		Tuple<int, int> size(height, width_sum + 4 * element_num);
		return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
	}
	else if(height % 2)
	{
		for(int line = -1; line <= height; line += 1)
		{
			if(line == -1) text = edge[0];
			else if(line == height / 2) text = edge[6];
			else if(line == height) text = edge[4];
			else text = edge[3];
			for(int id = 0; id < element_num; id += 1)
			{
				if(id > 0)
					text = text + (line == height - 1 ? ", " : "  ");
				text = text + (line + key_height[id] < height || line == height ?\
							   key_spaces[id] : key_texts[id][line + key_height[id] - height]);
				text = text + (line == height - 1 ? ": " : "  ");
				text = text + (line + value_height[id] < height || line == height ?\
							   value_spaces[id] : value_texts[id][line + value_height[id] - height]);
			}
			if(line == -1) text = text + edge[5];
			else if(line == height / 2) text = text + edge[7];
			else if(line == height) text = text + edge[1];
			else text = text + edge[2];
			out_texts.append({text});
		}
		Tuple<int, int> size(height + 2, width_sum + 4 * element_num + 2);
		return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
	}
	else
	{
		for(int line = -1; line <= height; line += 1)
		{
			if(line == -1) text = edge[0];
			else if(line == height / 2 - 1) text = edge[1];
			else if(line == height / 2) text = edge[5];
			else if(line == height) text = edge[4];
			else text = edge[3];
			for(int id = 0; id < element_num; id += 1)
			{
				if(id > 0)
					text = text + (line == height - 1 ? ", " : "  ");
				text = text + (line + key_height[id] < height || line == height ?\
							   key_spaces[id] : key_texts[id][line + key_height[id] - height]);
				text = text + (line == height - 1 ? ": " : "  ");
				text = text + (line + value_height[id] < height || line == height ?\
							   value_spaces[id] : value_texts[id][line + value_height[id] - height]);
			}
			if(line == -1) text = text + edge[5];
			else if(line == height / 2 - 1) text = text + edge[4];
			else if(line == height / 2) text = text + edge[0];
			else if(line == height) text = text + edge[1];
			else text = text + edge[2];
			out_texts.append({text});
		}
		Tuple<int, int> size(height + 2, width_sum + 4 * element_num + 2);
		return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
	}
}


const bool MATRIX_SEPARATOR = 0;//矩阵是否打印横向分隔符
template <typename T>
outputbox output(matrix<T> input)//针对matrix的特化
{
	Tuple<int, int> matrix_size = input.size();
	Tuple<Tuple<int, int>, cyclist<string>> outputbox;
	int heights[matrix_size.elemt_0][matrix_size.elemt_1];
	int widths[matrix_size.elemt_0][matrix_size.elemt_1];
	cyclist<string> texts[matrix_size.elemt_0][matrix_size.elemt_1];
	int height[matrix_size.elemt_0];
	int height_sum = 0;
	int width[matrix_size.elemt_1];
	int width_sum = 0;
	for(int line = 0; line < matrix_size.elemt_0; line += 1)
		height[line] = 0;
	for(int list = 0; list < matrix_size.elemt_1; list += 1)
		width[list] = 0;
	for(int line = 0; line < matrix_size.elemt_0; line += 1)
		for(int list = 0; list < matrix_size.elemt_1; list += 1)
		{
			outputbox = output(input[line][list]);
			heights[line][list] = get_height(outputbox);
			widths[line][list] = get_width(outputbox);
			texts[line][list] = get_text(outputbox);
			height[line] = max(height[line], heights[line][list]);
			width[list] = max(width[list], widths[line][list]);
		}
	for(int line = 0; line < matrix_size.elemt_0; line += 1)
		height_sum += height[line];
	for(int list = 0; list < matrix_size.elemt_1; list += 1)
		width_sum += width[list];
	//下面对所有字符串作空格补全
	for(int line = 0; line < matrix_size.elemt_0; line += 1)
		for(int list = 0; list < matrix_size.elemt_1; list += 1)
			for(int text_id = 0; text_id < heights[line][list]; text_id += 1)
				texts[line][list][text_id] = full(width[list] - texts[line][list][text_id].size(), ' ') + texts[line][list][text_id];
	cyclist<string> out_texts;
	string text;
	string spaces[matrix_size.elemt_1];
	for(int list = 0; list < matrix_size.elemt_1; list += 1)
		spaces[list] = full(width[list], ' ');
	string edge[6] = {"(", "/", "|", "\\", ")", "+"};
	for(int line = 0; line < matrix_size.elemt_0; line += 1)
	{
		if(line > 0 && MATRIX_SEPARATOR)//添加横向分隔符 
		{
			text = edge[2];
			for(int list = 0; list < matrix_size.elemt_1; list += 1)
			{
				if(list > 0)
					text = text + edge[5];
				text = text + full(width[list], '-');
			}
			text = text + edge[2];
			out_texts.append({text});
		}
		for(int subline = 0; subline < height[line]; subline += 1)
		{
			if(height_sum == 1) text = edge[0];
			else if(line == 0 && subline == 0) text = edge[1];
			else if(line == matrix_size.elemt_0 - 1 && subline == height[line] - 1) text = edge[3];
			else text = edge[2];
			for(int list = 0; list < matrix_size.elemt_1; list += 1)
			{
				if(list > 0)
					text = text + edge[2];
				text = text + (subline + heights[line][list] < height[line] ?\
							   spaces[list] : texts[line][list][subline + heights[line][list] - height[line]]);
			}
			if(height_sum == 1) text = text + edge[4];
			else if(line == 0 && subline == 0) text = text + edge[3];
			else if(line == matrix_size.elemt_0 - 1 && subline == height[line] - 1) text = text + edge[1];
			else text = text + edge[2];
			out_texts.append({text});
		}
	}
	Tuple<int, int> size(height_sum + (MATRIX_SEPARATOR ? matrix_size.elemt_0 - 1 : 0), width_sum + matrix_size.elemt_1 + 1);
	return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
}


template<typename T>
outputbox output(point_2<T> input)//针对point的特化
{
	return output(cyclist<T>({input.x, input.y}));
}
template<typename T>
outputbox output(point_3<T> input)//针对Vectors的特化
{
	return output(cyclist<T>({input.x, input.y, input.z}));
}
template<typename T>
outputbox output(Line_3<T> input)//针对Line_3的特化
{
	outputbox number[6];
	number[0] = output(input.start.x); number[1] = output(input.start.y); number[2] = output(input.start.z);
	number[3] = output(input.veloc.x); number[4] = output(input.veloc.y); number[5] = output(input.veloc.z);
	int height[6];
	int width[6];
	cyclist<string> text[6];
	for(int id = 0; id < 6; id += 1)
	{
		height[id] = get_height(number[id]);
		width[id] = get_width(number[id]);
		text[id] = get_text(number[id]);
	}
	int width_upper = 0, width_lower = 0;
	width_upper = max(max(width_upper, width[0]), max(width[1], width[2]));
	width_lower = max(max(width_lower, width[3]), max(width[4], width[5]));
	int height_upper = 0, height_lower = 0;
	height_upper = max(max(height_upper, height[0]), max(height[1], height[2]));
	height_lower = max(max(height_lower, height[3]), max(height[4], height[5]));
	int frac_width = max(width_upper + 4, width_lower);//一个分式的宽度
	//下面对所有字符串作空格补全 
	int space_num;
	for(int id = 0; id < 3; id += 1)
		for(int line = 0; line < height[id]; line += 1)//分子补全时不补前面四列 
		{
			space_num = frac_width - width[id] - 4;
			text[id][line] = full(space_num / 2, ' ') + text[id][line] + full(space_num - space_num / 2, ' ');
		}
	for(int id = 3; id < 6; id += 1)
		for(int line = 0; line < height[id]; line += 1)//分母补全时全补充 
		{
			space_num = frac_width - width[id];
			text[id][line] = full(space_num / 2, ' ') + text[id][line] + full(space_num - space_num / 2, ' ');
		}
	cyclist<string> out_texts;
	string textline;
	string space_upper = full(frac_width - 4, ' ');
	string space_lower = full(frac_width, ' ');
	for(int line = 0; line < height_upper; line += 1)
	{
		textline = (line == height_upper / 2 ? "x - " : "    ");
		textline = textline + (line + height[0] < height_upper ? space_upper : text[0][line + height[0] - height_upper]);
		textline = textline + "   ";
		textline = textline + (line == height_upper / 2 ? "y - " : "    ");
		textline = textline + (line + height[1] < height_upper ? space_upper : text[1][line + height[1] - height_upper]);
		textline = textline + "   ";
		textline = textline + (line == height_upper / 2 ? "z - " : "    ");
		textline = textline + (line + height[2] < height_upper ? space_upper : text[2][line + height[2] - height_upper]);
		out_texts.append({textline});
	}
	out_texts.append({full(frac_width, '-') + " = " + full(frac_width, '-') + " = " + full(frac_width, '-')});
	for(int line = 0; line < height_lower; line += 1)
	{
		textline = (line + height[3] < height_lower ? space_lower : text[3][line + height[3] - height_lower]);
		textline = textline + "   ";
		textline = textline + (line + height[4] < height_lower ? space_lower : text[4][line + height[4] - height_lower]);
		textline = textline + "   ";
		textline = textline + (line + height[5] < height_lower ? space_lower : text[5][line + height[5] - height_lower]);
		out_texts.append({textline});
	}
	Tuple<int, int> size(height_upper + 1 + height_lower, 3 * (frac_width + 2));
	return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
}
/* TODO (#1#): 补全surface的输出 */
template<typename T>
outputbox output(Surface<T> input)//针对Surface的特化
{
	point_3<T> coef = cross_product(input.veloc_1, input.veloc_2);
	outputbox number[6];
	number[0] = output(input.start.x); number[1] = output(input.start.y); number[2] = output(input.start.z);
	number[3] = output(coef.x); number[4] = output(coef.y); number[5] = output(coef.z);
	int height[6];
	int max_height = 0;
	int width[6];
	int width_coef = 0, width_start = 0;
	cyclist<string> text[6];
	for(int id = 0; id < 6; id += 1)
	{
		height[id] = get_height(number[id]);
		width[id] = get_width(number[id]);
		text[id] = get_text(number[id]);
		max_height = max(max_height, height[id]);
		if(id < 3)
			width_start = max(width_start, width[id]);
		else
			width_coef = max(width_coef, width[id]);
	}
	//下面对所有字符串作空格补全
	int space_num;
	for(int id = 0; id < 3; id += 1)
		for(int line = 0; line < height[id]; line += 1)
		{
			space_num = width_start - width[id];
			text[id][line] = full(space_num / 2, ' ') + text[id][line] + full(space_num - space_num / 2, ' ');
		}
	for(int id = 3; id < 6; id += 1)
		for(int line = 0; line < height[id]; line += 1)
		{
			space_num = width_coef - width[id];
			text[id][line] = full(space_num / 2, ' ') + text[id][line] + full(space_num - space_num / 2, ' ');
		}
	cyclist<string> out_texts;
	string textline = "";
	string space_coef = full(width_coef, ' ');
	string space_start = full(width_start, ' ');
	if(max_height == 1)
	{
		string const_text[] = {"(x - ", "(y - ", "(z - ", ") + ", ") + ", ") = 0"};
		textline = "";
		for(int rank = 0; rank < 3; rank += 1)
		{
			textline = textline + (height[3 + rank] == 0 ? space_coef : text[3 + rank][0]);
			textline = textline + const_text[rank];
			textline = textline + (height[rank] == 0 ? space_start : text[rank][0]);
			textline = textline + const_text[3 + rank];
		}
		out_texts.append({textline});
		Tuple<int, int> size(1, 3 * (width_coef + width_start) + 28);
		return Tuple<Tuple<int, int>, cyclist<string>>(size, out_texts);
	}/*
	else
	{
		string edge[3] = {"/", "|", "\\"};
		for(int line = 0; line < height; line += 1)
		{
			if(line == -1) text = edge[0] + " ";
			else if(line == height) text = edge[2] + " ";
			else text = edge[1] + " ";
			text = text + (line + height_1 < height ? spaces_1 : text_1[line + height_1 - height]);
			text = text + (line == height - 1 ? ", " : "  ");
			text = text + (line + height_2 < height ? spaces_2 : text_2[line + height_2 - height]);
			if(line == -1) text = text + " " + edge[2];
			else if(line == height) text = text + " " + edge[0];
			else text = text + " " + edge[1];
			texts.append({text});
		}
		Tuple<int, int> size(height + 2, width_1 + width_2 + 6);
		return Tuple<Tuple<int, int>, cyclist<string>>(size, texts);
	}*/
}






void print_block(outputbox input, position pos)//把outputbox类的东西打印出来（带地址） 
{
	for(int line = 0; line < input.elemt_0.elemt_0; line += 1)
	{
		gotopos(pos + topos(line, 0));
		cout<<input.elemt_1[line];
	}
}
void print_block(outputbox input)//把outputbox类的东西打印出来 
{
	for(int line = 0; line < input.elemt_0.elemt_0; line += 1)
		cout<<input.elemt_1[line]<<endl;
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
