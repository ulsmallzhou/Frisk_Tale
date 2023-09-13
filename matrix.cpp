template <typename T>
class column
{
public:
	T* pin = NULL;
	int csize = 0;
	column(){}
	column(int length)
	{
		csize = length;
		pin = new T[length];
	}
	column(T* values, int length)
	{
		csize = length;
		pin = new T[length];
		for(int num = 0; num < length; num += 1)
			pin[num] = values[num];
	}
	column(cyclist<T> inputs)//初始化列表初始化 
	{
		csize = inputs.size();
		pin = new T[csize];
		for(int num = 0; num < csize; num += 1)
			pin[num] = inputs[num];
	}
	column(initializer_list<T> inputs)//初始化列表初始化 
	{
		csize = inputs.size();
		auto* input = inputs.begin();
		pin = new T[csize];
		for(int num = 0; num < csize; num += 1)
		{
			pin[num] = *input;
			input++;
		}
	}
	column(const column<T> &anarray)
	{
		csize = anarray.csize;
		pin = new T[csize];
		for(int num = 0; num < csize; num += 1)
			pin[num] = anarray.pin[num];
	}
	~column(){delete[] pin;}
	int size(){return csize;}
	void set(cyclist<T> inputs)//长度不匹配将不会设置 
	{
		if(inputs.size() == csize)
			for(int id = 0; id < csize; id += 1)
				pin[id] = inputs[id];
		else
			exit(1005);
	}
	void set(T input, int id)//下标不合适将不会设置 
	{
		if(id >= 0 && id < csize)
			pin[id] = input;
		else
			exit(1004);
	}
	T &operator[](int subscript)//越界访问将报错
	{
		if(subscript < 0 || subscript >= csize)
			exit(1004);
		return pin[subscript];
	}
	void operator=(const column<T> &acol)
	{
		csize = acol.csize;
		pin = new T[csize];
		for(int num = 0; num < csize; num += 1)
			pin[num] = acol.pin[num];
	}
	column<T> operator-()
	{
		column<T> outcolumn = *this;
		for(int id = 0; id < csize; id += 1)
			outcolumn.pin[id] = -outcolumn.pin[id];
		return outcolumn;
	}
	column<T> operator-(const column<T> &acol)
	{
		column<T> outcolumn = *this;
		for(int id = 0; id < csize; id += 1)
			outcolumn.pin[id] = outcolumn.pin[id] - acol.pin[id];
		return outcolumn;
	}
	column<T> operator+(const column<T> &acol)
	{
		column<T> outcolumn = *this;
		for(int id = 0; id < csize; id += 1)
			outcolumn.pin[id] = outcolumn.pin[id] + acol.pin[id];
		return outcolumn;
	}
	column<T> operator*(const column<T> &acol)
	{
		column<T> outcolumn = *this;
		for(int id = 0; id < csize; id += 1)
			outcolumn.pin[id] = (T)(outcolumn.pin[id] * acol.pin[id]);
		return outcolumn;
	}
	column<T> operator/(const column<T> &acol)
	{
		column<T> outcolumn = *this;
		for(int id = 0; id < csize; id += 1)
			outcolumn.pin[id] = (T)(outcolumn.pin[id] / acol.pin[id]);
		return outcolumn;
	}
	friend ostream &operator<<(ostream &output, const column<T> &acol)
	{
		output<<"[";
		for(int id = 0; id < acol.csize; id += 1)
		{
			if(id > 0)
				output<<", ";
			output<<acol.pin[id];
		}
		output<<"]";
	}
};
template <typename T>
T column_inner_product(column<T> col_1, column<T> col_2)//T只能是数字类 
{
	T sum(0);
	if(col_1.csize != col_2.csize)
		exit(1005);
	for(int id = 0; id < col_1.csize; id += 1)
		sum = sum + col_1[id] * col_2[id];
	return sum;
}


template <typename T>
class matrix
{
public:
	T** pin = NULL;
	int msize_line = 0;
	int msize_list = 0;
	matrix(){}
	matrix(Tuple<int, int> size)
	{
		msize_line = size.first_elemt();
		msize_list = size.second_elemt();
		pin = new T*[size.first_elemt()];
		for(int line = 0; line < size.first_elemt(); line += 1)
			pin[line] = new T[size.second_elemt()];
	}
	matrix(T** values, Tuple<int, int> size)
	{
		msize_line = size.first_elemt();
		msize_list = size.second_elemt();
		pin = new T*[size.first_elemt()];
		for(int line = 0; line < size.first_elemt(); line += 1)
		{
			pin[line] = new T[size.second_elemt()];
			for(int list = 0; list < size.second_elemt(); list += 1)
				pin[line][list] = values[line][list];
		}
	}
	matrix(cyclist<column<T>> arrays)
	{
		msize_line = arrays.size();
		msize_list = arrays[0].size();
		for(int id = 1; id < msize_line; id += 1)
			if(msize_list > arrays[id].size())
				msize_list = arrays[id].size();
		pin = new T*[msize_line];
		for(int line = 0; line < msize_line; line += 1)
		{
			pin[line] = new T[msize_list];
			for(int list = 0; list < msize_list; list += 1)
				pin[line][list] = arrays[line][list];
		}
	}
	matrix(const matrix<T> &amatrix)
	{
		msize_line = amatrix.msize_line;
		msize_list = amatrix.msize_list;
		pin = new T*[msize_line];
		for(int line = 0; line < msize_line; line += 1)
		{
			pin[line] = new T[msize_list];
			for(int list = 0; list < msize_list; list += 1)
				pin[line][list] = amatrix.pin[line][list];
		}
	}
	~matrix()
	{
		for(int line = 0; line < msize_line; line += 1)
			delete[] pin[line];
		delete[] pin;
	}
	void set_size(Tuple<int, int> size)//重置大小将删除所有数据，因此务必仅对未直接初始化的矩阵使用该函数 
	{
		if(pin != NULL)
		{
			for(int line = 0; line < msize_line; line += 1)
				if(pin[line] != NULL)
					delete[] pin[line];
			delete[] pin;
		}
		msize_line = size.elemt_0;
		msize_list = size.elemt_1;
		pin = new T*[msize_line];
		for(int line = 0; line < msize_line; line += 1)
			pin[line] = new T[msize_list];
	}
	void set_line(int line, column<T> aline)//长度不匹配或越界将报错 
	{
		if(aline.size() != msize_list)
			exit(1005);
		if(!(0 <= line && line < msize_line))
			exit(1004);
		for(int list = 0; list < aline.size(); list += 1)
			pin[line][list] = aline[list];
	}
	column<T> get_line(int line)//获得行，越界报错 
	{
		column<T> aline(msize_list);
		if(line >= 0 && line < msize_line)
			for(int list = 0; list < msize_list; list += 1)
				aline.pin[list] = pin[line][list];
		else
			exit(1004);
		return aline;
	}
	void set_list(int list, column<T> alist)//长度不匹配或越界将报错 
	{
		if(alist.size() != msize_line)
			exit(1005);
		if(!(0 <= list && list < msize_list))
			exit(1004);
		for(int line = 0; line < alist.size(); line += 1)
			pin[line][list] = alist[line];
	}
	column<T> get_list(int list)//获得列，越界报错 
	{
		column<T> alist(msize_line);
		if(list >= 0 && list < msize_list)
			for(int line = 0; line < msize_line; line += 1)
				alist.pin[line] = pin[line][list];
		else
			exit(1004);
		return alist;
	}
	void set_point(int line, int list, T value)//越界将报错 
	{
		if(0 <= line && line < msize_line && 0 <= list && list < msize_list)
			pin[line][list] = value;
		else
			exit(1004);
	}
	column<T>& operator[](int line)//越界访问将报错（返回行） 
	{
		static column<T> acol(msize_list);
		if(0 <= line && line < msize_line)
			for(int list = 0; list < msize_list; list += 1)
				acol.set(pin[line][list], list);
		else
			exit(1004);
		return acol;
	}
	friend ostream &operator<<(ostream &output, const matrix<T> &amatrix)
	{
		output<<"[";
		for(int line = 0; line < amatrix.msize_line; line += 1)
		{
			output<<(line ? "\n [" : "[");
			for(int list = 0; list < amatrix.msize_list; list += 1)
			{
				if(list > 0)
					output<<", ";
				output<<amatrix.pin[line][list];
			}
			output<<"]";
		}
		output<<"]";
	}
	void operator=(const matrix<T> &amatrix)
	{
		msize_line = amatrix.msize_line;
		msize_list = amatrix.msize_list;
		pin = new T*[msize_line];
		for(int line = 0; line < msize_line; line += 1)
		{
			pin[line] = new T[msize_list];
			for(int list = 0; list < msize_list; list += 1)
				pin[line][list] = amatrix.pin[line][list];
		}
	}
	matrix<T> operator+(const matrix<T> &amatrix)
	{
		if(msize_line != amatrix.msize_line || msize_list != amatrix.msize_list)
			exit(1005);
		matrix<T> outmatrix = amatrix;
		for(int line = 0; line < msize_line; line += 1)
			for(int list = 0; list < msize_list; list += 1)
				outmatrix.pin[line][list] = outmatrix.pin[line][list] + pin[line][list];
		return outmatrix;
	}
	matrix<T> operator-(const matrix<T> &amatrix)
	{
		if(msize_line != amatrix.msize_line || msize_list != amatrix.msize_list)
			exit(1005);
		matrix<T> outmatrix = amatrix;
		for(int line = 0; line < msize_line; line += 1)
			for(int list = 0; list < msize_list; list += 1)
				outmatrix.pin[line][list] = -outmatrix.pin[line][list] + pin[line][list];
		return outmatrix;
	}
	matrix<T> operator*(const matrix<T> &amatrix)//矩阵乘法 
	{
		if(msize_list != amatrix.msize_line)
			exit(1005);
		matrix<T> outmatrix = matrix<T>::zero(Tuple<int, int>(msize_line, amatrix.msize_list));
		for(int line = 0; line < msize_line; line += 1)
			for(int list = 0; list < amatrix.msize_list; list += 1)
				for(int involution = 0; involution < msize_list; involution += 1)
					outmatrix.pin[line][list] = outmatrix.pin[line][list] + (T)(pin[line][involution] * amatrix.pin[involution][list]);
		return outmatrix;
	}
	matrix<T> operator-()
	{
		matrix<T> outmatrix = *this;
		for(int line = 0; line < msize_line; line += 1)
			for(int list = 0; list < msize_list; list += 1)
				outmatrix.pin[line][list] = -outmatrix.pin[line][list];
		return outmatrix;
	}
	bool operator==(const matrix<T> &amatrix)
	{
		if(msize_line != amatrix.msize_line || msize_list != amatrix.msize_list)
			return 0;
		for(int line = 0; line < msize_line; line += 1)
			for(int list = 0; list < msize_list; list += 1)
				if(pin[line][list] != amatrix.pin[line][list])
					return 0;
		return 1;
	}
	bool operator!=(const matrix<T> &amatrix)
	{
		return !(*this == amatrix);
	}
	static matrix<T> quantity(int size, T value)//产生数量阵，即单位阵的数乘 
	{
		matrix<T> outmatrix(Tuple<int, int>(size, size));
		for(int line = 0; line < size; line += 1)
			for(int list = 0; list < size; list += 1)
				outmatrix.set_point(line, list, (line == list ? value : (T)(0)));
		return outmatrix;
	}
	static matrix<T> zero(Tuple<int, int> size)//产生零矩阵 
	{
		matrix<T> outmatrix(size);
		for(int line = 0; line < size.elemt_0; line += 1)
			for(int list = 0; list < size.elemt_1; list += 1)
				outmatrix.set_point(line, list, (T)(0));
		return outmatrix;
	}
	void swap_lines(int line_1, int line_2)//交换两行元素 
	{
		if(!(line_1 >= 0 && line_1 < msize_line && line_2 >= 0 && line_2 < msize_line))
			exit(1004);
		if(line_1 != line_2)
		{
			T temp;
			for(int list = 0; list < msize_list; list += 1)
			{
				temp = pin[line_1][list];
				pin[line_1][list] = pin[line_2][list];
				pin[line_2][list] = temp;
			}
		}
	}
	void swap_lists(int list_1, int list_2)//交换两列元素 
	{
		if(!(list_1 >= 0 && list_1 < msize_list && list_2 >= 0 && list_2 < msize_list))
			exit(1004);
		if(list_1 != list_2)
		{
			T temp;
			for(int line = 0; line < msize_line; line += 1)
			{
				temp = pin[line][list_1];
				pin[line][list_1] = pin[line][list_2];
				pin[line][list_2] = temp;
			}
		}
	}
	template <typename T_coef>
	void mult_line(int line, T_coef coef)//行数乘 
	{
		if(line >= 0 && line < msize_line)
			for(int list = 0; list < msize_list; list += 1)
				pin[line][list] = (T)(pin[line][list] * coef);
	}
	template <typename T_coef>
	void mult_list(int list, T_coef coef)//列数乘 
	{
		if(list >= 0 && list < msize_list)
			for(int line = 0; line < msize_line; line += 1)
				pin[line][list] = (T)(pin[line][list] * coef);
	}
	template <typename T_coef>
	void mult(T_coef coef)//整体数乘
	{
		for(int line = 0; line < msize_line; line += 1)
			for(int list = 0; list < msize_list; list += 1)
				pin[line][list] = pin[line][list] * coef;
	}
	void plus_line(int line, column<T> acol)//行加行 
	{
		if(acol.size() != msize_list)
			exit(1005);
		if(!(0 <= line && line < msize_line))
			exit(1004);
		for(int list = 0; list < msize_list; list += 1)
			pin[line][list] = pin[line][list] + acol[list];
	}
	void plus_list(int list, column<T> acol)//列加列 
	{
		if(acol.size() != msize_line)
			exit(1005);
		if(!(0 <= list && list < msize_list))
			exit(1004);
		for(int line = 0; line < msize_line; line += 1)
			pin[line][list] = pin[line][list] + acol[line];
	}
	void plus(T coef)//整体加 
	{
		for(int line = 0; line < msize_line; line += 1)
			for(int list = 0; list < msize_list; list += 1)
				pin[line][list] = pin[line][list] + coef;
	}
	void splice_right(matrix<T> amatrix)//把输入的矩阵（若大小匹配）拼接到该矩阵右侧 
	{
		if(msize_line == amatrix.msize_line)
		{
			T** newpin = new T*[msize_line];
			for(int line = 0; line < msize_line; line += 1)
			{
				newpin[line] = new T[msize_list + amatrix.msize_list];
				for(int list = 0; list < msize_list; list += 1)
					newpin[line][list] = pin[line][list];
				for(int list = msize_list; list < msize_list + amatrix.msize_list; list += 1)
					newpin[line][list] = amatrix.pin[line][list - msize_list];
			}
			msize_list = msize_list + amatrix.msize_list;
			for(int line = 0; line < msize_line; line += 1)
				delete[] pin[line];
			delete[] pin;
			pin = newpin;
		}
		else
			exit(1005);
	}
	void splice_left(matrix<T> amatrix)//把输入的矩阵（若大小匹配）拼接到该矩阵左侧 
	{
		if(msize_line == amatrix.msize_line)
		{
			T** newpin = new T*[msize_line];
			for(int line = 0; line < msize_line; line += 1)
			{
				newpin[line] = new T[msize_list + amatrix.msize_list];
				for(int list = 0; list < amatrix.msize_list; list += 1)
					newpin[line][list] = amatrix.pin[line][list];
				for(int list = amatrix.msize_list; list < msize_list + amatrix.msize_list; list += 1)
					newpin[line][list] = pin[line][list - amatrix.msize_list];
			}
			msize_list = msize_list + amatrix.msize_list;
			for(int line = 0; line < msize_line; line += 1)
				delete[] pin[line];
			delete[] pin;
			pin = newpin;
		}
		else
			exit(1005);
	}
	void splice_high(matrix<T> amatrix)//把输入的矩阵（若大小匹配）拼接到该矩阵上侧 
	{
		if(msize_list == amatrix.msize_list)
		{
			T** newpin = new T*[msize_line + amatrix.msize_line];
			for(int line = 0; line < amatrix.msize_line; line += 1)
			{
				newpin[line] = new T[msize_list];
				for(int list = 0; list < msize_list; list += 1)
					newpin[line][list] = amatrix.pin[line][list];
			}
			for(int line = amatrix.msize_line; line < msize_line + amatrix.msize_line; line += 1)
			{
				newpin[line] = new T[msize_list];
				for(int list = 0; list < msize_list; list += 1)
					newpin[line][list] = pin[line - amatrix.msize_line][list];
			}
			for(int line = 0; line < msize_line; line += 1)
				delete[] pin[line];
			delete[] pin;
			msize_line = msize_line + amatrix.msize_line;
			pin = newpin;
		}
		else
			exit(1005);
	}
	void splice_low(matrix<T> amatrix)//把输入的矩阵（若大小匹配）拼接到该矩阵下侧 
	{
		if(msize_list == amatrix.msize_list)
		{
			T** newpin = new T*[msize_line + amatrix.msize_line];
			for(int line = 0; line < msize_line; line += 1)
			{
				newpin[line] = new T[msize_list];
				for(int list = 0; list < msize_list; list += 1)
					newpin[line][list] = pin[line][list];
			}
			for(int line = msize_line; line < msize_line + amatrix.msize_line; line += 1)
			{
				newpin[line] = new T[msize_list];
				for(int list = 0; list < msize_list; list += 1)
					newpin[line][list] = amatrix.pin[line - msize_line][list];
			}
			for(int line = 0; line < msize_line; line += 1)
				delete[] pin[line];
			delete[] pin;
			msize_line = msize_line + amatrix.msize_line;
			pin = newpin;
		}
		else
			exit(1005);
	}
	Tuple<matrix<T>, matrix<T>> cut_left_right(int del_list)//左右切成两个矩阵，list为左侧矩阵的列数
	{
		matrix<T> left = *this;
		matrix<T> right;
		if(0 < del_list && del_list < msize_list)
		{
			left.set_size(Tuple<int, int>(msize_line, del_list));
			right.set_size(Tuple<int, int>(msize_line, msize_list - del_list));
			for(int list = 0; list < del_list; list += 1)
				for(int line = 0; line < msize_line; line += 1)
					left.pin[line][list] = pin[line][list];
			for(int list = del_list; list < msize_list; list += 1)
				for(int line = 0; line < msize_line; line += 1)
					right.pin[line][list - del_list] = pin[line][list];
		}
		else
			exit(1004);
		return Tuple<matrix<T>, matrix<T>>(left, right);
	}
	Tuple<matrix<T>, matrix<T>> cut_high_low(int del_line)//上下切成两个矩阵，line为上侧矩阵的行数 
	{
		matrix<T> high = *this;
		matrix<T> low;
		if(0 < del_line && del_line < msize_line)
		{
			high.set_size(Tuple<int, int>(del_line, msize_list));
			low.set_size(Tuple<int, int>(msize_line - del_line, msize_list));
			for(int line = 0; line < del_line; line += 1)
				for(int list = 0; list < msize_list; list += 1)
					high.pin[line][list] = pin[line][list];
			for(int line = del_line; line < msize_line; line += 1)
				for(int list = 0; list < msize_list; list += 1)
					low.pin[line - del_line][list] = pin[line][list];
		}
		else
			exit(1004);
		return Tuple<matrix<T>, matrix<T>>(high, low);
	}
	matrix<T> distribution(matrix<T> amatrix)//矩阵的点对点乘法
	{
		if(msize_line != amatrix.msize_line || msize_list != amatrix.msize_list)
			exit(1005);
		matrix<T> outmatrix = amatrix;
		for(int line = 0; line < msize_line; line += 1)
			for(int list = 0; list < msize_list; list += 1)
				outmatrix.pin[line][list] = (T)(outmatrix.pin[line][list] * pin[line][list]);
		return outmatrix;
	}
	matrix<T> to_stepped()//求行简化阶梯型矩阵（需要T为定义了良好除法的数量类，至少是frac类或double类或complex<double>） 
	{
		matrix<T> base = *this;
		bool all_zero = 1;
		bool mainpoint_find = 0;
		cyclist<int> main_list;//存放主要列
		T temp;//临时变量 
		//第一阶段：从上到下
		for(int ruler = 0; ruler < base.msize_line; ruler += 1)
		{
			all_zero = 1;
			for(int line = ruler; line < base.msize_line && all_zero; line += 1)
				for(int list = 0; list < base.msize_list && all_zero; list += 1)
					if(base.pin[line][list] != (T)(0))
						all_zero = 0;
			if(all_zero)
				break;
			mainpoint_find = 0;
			for(int list = 0; list < base.msize_list && !mainpoint_find; list += 1)
				for(int line = ruler; line < base.msize_line && !mainpoint_find; line += 1)
					if(base.pin[line][list] != (T)(0))
					{
						mainpoint_find = 1;
						base.swap_lines(ruler, line);//行交换
						temp = base.pin[ruler][list];
						main_list.append({list});//记录矩阵主要列
					}
			for(int list = 0; list < base.msize_list; list += 1)//行系数归一
				base.pin[ruler][list] = base.pin[ruler][list] / temp;
			for(int line = ruler + 1; line < base.msize_line; line += 1)//下面的行进行去首 
			{
				temp = base.pin[line][main_list[ruler]];
				for(int list = 0; list < base.msize_list; list += 1)
				{
					base.pin[line][list] = base.pin[line][list] - temp * base.pin[ruler][list];
					if(abs(base.pin[line][list]) <= 0.0000000000001)
						base.pin[line][list] = (T)(0);
				}
			}
		}
		//第二阶段：从下到上
		for(int line = main_list.size() - 2; line >= 0; line -= 1)
			for(int subline = line + 1; subline < main_list.size(); subline += 1)
			{
				temp = base.pin[line][main_list[subline]];
				for(int list = 0; list < base.msize_list; list += 1)
					base.pin[line][list] = base.pin[line][list] - temp * base.pin[subline][list];
			}
		//打补丁：double计算会产生误差导致0不严格 
		for(int list = 0; list < base.msize_list; list += 1)
			for(int line = 0; line < base.msize_line; line += 1)
				if(abs(base.pin[line][list]) <= 0.0000000000001)
					base.pin[line][list] = (T)(0);
		return base;
	}
	int rank()//返回矩阵的秩 
	{
		matrix<T> base = this->to_stepped();
		for(int line = msize_line - 1; line >= 0; line -= 1)
			for(int list = 0; list < msize_list; list += 1)
				if(base.pin[line][list] != (T)(0))
					return line + 1;
		return 0;
	}
	matrix<T> transpose()//转置 
	{
		matrix<T> amatrix(Tuple<int, int>(msize_list, msize_line));
		for(int list = 0; list < msize_line; list += 1)
			amatrix.set_list(list, this->get_line(list));
		return amatrix;
	}
	matrix<T> inverse()//求逆（或广义逆）注：本矩阵计算工具不考虑复数 
	{
		int this_rank = this->rank();
		if(this_rank == 0)
			exit(1006);
		if(msize_line == msize_list && msize_line == this_rank)//一般的可逆矩阵
		{
			matrix<T> base = *this;
			base.splice_right(matrix<T>::quantity(base.msize_line, (T)(1)));
			base = base.to_stepped();
			base = base.cut_left_right(base.msize_line).elemt_1;
			return base;
		}
		else
		{
			Tuple<matrix<T>, matrix<T>> fullrank = this->fullrank_decomposition();
			matrix<T> B = fullrank.elemt_0;
			matrix<T> C = fullrank.elemt_1;
			matrix<T> BH = B.transpose();
			matrix<T> CH = C.transpose();
			matrix<T> outmatrix = CH * (C * CH).inverse() * (BH * B).inverse() * BH;
			//打补丁：double计算会产生误差导致0不严格 
			for(int list = 0; list < outmatrix.msize_list; list += 1)
				for(int line = 0; line < outmatrix.msize_line; line += 1)
					if(abs(outmatrix.pin[line][list]) <= 0.0000000000001)
						outmatrix.pin[line][list] = (T)(0);
			return outmatrix;
		}
	}
	Tuple<matrix<T>, matrix<T>> fullrank_decomposition()//满秩分解,A=BC,return Tuple(B, C) 
	{
		int this_rank = this->rank();
		if(this_rank == 0)
			exit(1006);
		matrix<T> C = this->to_stepped();
		C = C.cut_high_low(this_rank).elemt_0;
		matrix<T> B(Tuple<int, int>(msize_line, this_rank));
		for(int line = 0; line < this_rank; line += 1)
			for(int list = 0; list < msize_list; list += 1)
				if(C.pin[line][list] != (T)(0))
				{
					B.set_list(line, this->get_list(list));
					break;
				}
		return Tuple<matrix<T>, matrix<T>>(B, C);
	}
	Tuple<matrix<T>, matrix<T>> QR_decomposition()//QR分解
	{
		if(msize_line != msize_list)
			exit(1005);
		int this_rank = this->rank();
		if(this_rank == 0)
			exit(1007);
	}
};


template <typename T>
class nparray
{
	void* values;
	int dimension = 0;
	cyclist<int> asize;
	nparray(){}
	/*nparray(int dimen)
	{
		
	}*/
};


