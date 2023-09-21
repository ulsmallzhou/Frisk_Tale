template <typename T>
class column
{
public:
	T* pin = NULL;
	int csize = 0;
	column(){}
	column(int length){csize = length; pin = new T[length];}
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
	template <typename T_other>
	column<T> operator*(const T_other &coef)
	{
		column<T> outcolumn = *this;
		for(int id = 0; id < csize; id += 1)
			outcolumn.pin[id] = (T)(outcolumn.pin[id] * coef);
		return outcolumn;
	}
	template <typename T_other>
	column<T> operator/(const T_other &coef)
	{
		column<T> outcolumn = *this;
		for(int id = 0; id < csize; id += 1)
			outcolumn.pin[id] = (T)(outcolumn.pin[id] / coef);
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
		sum = sum + (T)(col_1[id] * col_2[id]);
	return sum;
}
template <typename T>
double modulu(column<T> col){return sqrt(column_inner_product(col, col));}//T只能是数字类 


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
		if(msize_line == 0 || msize_list == 0)
			exit(1008);
		pin = new T*[size.first_elemt()];
		for(int line = 0; line < size.first_elemt(); line += 1)
			pin[line] = new T[size.second_elemt()];
	}
	matrix(T** values, Tuple<int, int> size)
	{
		msize_line = size.first_elemt();
		msize_list = size.second_elemt();
		if(msize_line == 0 || msize_list == 0)
			exit(1008);
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
		if(msize_line == 0 || msize_list == 0)
			exit(1008);
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
		if(msize_line == 0 || msize_list == 0)
			exit(1008);
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
	Tuple<int, int> size(){return Tuple<int, int>(msize_line, msize_list);}
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
		if(msize_line == 0 || msize_list == 0)
			exit(1008);
		pin = new T*[msize_line];
		for(int line = 0; line < msize_line; line += 1)
			pin[line] = new T[msize_list];
	}
	void reshape(Tuple<int, int> newsize)//重构长宽，需要面积不变 
	{
		long long int old_size = msize_line * msize_list;
		long long int new_size = newsize.elemt_0 * newsize.elemt_1;
		if(new_size != old_size)
			exit(1005);
		T** newpin = new T*[newsize.elemt_0];
		for(int line = 0; line < newsize.elemt_0; line += 1)
			newpin[line] = new T[newsize.elemt_1];
		for(long long int elemt = 0; elemt < new_size; elemt += 1)
			newpin[elemt / newsize.elemt_1][elemt % newsize.elemt_1] = pin[elemt / msize_list][elemt % msize_list];
		for(int line = 0; line < msize_line; line += 1)
			delete[] pin[line];
		delete[] pin;
		pin = newpin;
		msize_line = newsize.elemt_0;
		msize_list = newsize.elemt_1;
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
	void insert_line(int line, column<T> aline)//line：插入的行是第几行 
	{
		if(aline.size() != msize_list)
			exit(1005);
		if(!(0 <= line && line <= msize_line))
			exit(1004);
		T** newpin = new T*[msize_line + 1];
		for(int newline = 0; newline < msize_line + 1; newline += 1)
		{
			newpin[newline] = new T[msize_list];
			for(int list = 0; list < msize_list; list += 1)
				if(newline < line)
					newpin[newline][list] = pin[newline][list];
				else if(newline > line)
					newpin[newline][list] = pin[newline - 1][list];
				else if(newline == line)
					newpin[newline][list] = aline.pin[list];
		}
		for(int line = 0; line < msize_line; line += 1)
			delete[] pin[line];
		delete[] pin;
		pin = newpin;
		msize_line = msize_line + 1;
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
	void delete_line(int line)//删除行 
	{
		if(line < 0 || line >= msize_line)
			exit(1004);
		if(msize_line == 1 || msize_list == 0)
			exit(1008);
		T** newpin = new T*[msize_line - 1];
		for(int newline = 0; newline < msize_line - 1; newline += 1)
		{
			newpin[newline] = new T[msize_list];
			for(int list = 0; list < msize_list; list += 1)
				if(newline < line)
					newpin[newline][list] = pin[newline][list];
				else
					newpin[newline][list] = pin[newline + 1][list];
		}
		for(int line = 0; line < msize_line; line += 1)
			delete[] pin[line];
		delete[] pin;
		pin = newpin;
		msize_line = msize_line - 1;
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
	void insert_list(int list, column<T> alist)//list：插入的行是第几列 
	{
		if(alist.size() != msize_line)
			exit(1005);
		if(!(0 <= list && list <= msize_list))
			exit(1004);
		T** newpin = new T*[msize_line];
		for(int line = 0; line < msize_line; line += 1)
		{
			newpin[line] = new T[msize_list + 1];
			for(int newlist = 0; newlist < msize_list + 1; newlist += 1)
				if(newlist < list)
					newpin[line][newlist] = pin[line][newlist];
				else if(newlist > list)
					newpin[line][newlist] = pin[line][newlist - 1];
				else if(newlist == list)
					newpin[line][newlist] = alist.pin[line];
		}
		for(int line = 0; line < msize_line; line += 1)
			delete[] pin[line];
		delete[] pin;
		pin = newpin;
		msize_list = msize_list + 1;
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
	void delete_list(int list)//删除列 
	{
		if(list < 0 || list >= msize_list)
			exit(1004);
		if(msize_list == 1 || msize_line == 0)
			exit(1008);
		T** newpin = new T*[msize_line];
		for(int line = 0; line < msize_line; line += 1)
		{
			newpin[line] = new T[msize_list - 1];
			for(int newlist = 0; newlist < msize_list - 1; newlist += 1)
				if(newlist < list)
					newpin[line][newlist] = pin[line][newlist];
				else
					newpin[line][newlist] = pin[line][newlist + 1];
		}
		for(int line = 0; line < msize_line; line += 1)
			delete[] pin[line];
		delete[] pin;
		pin = newpin;
		msize_list = msize_list - 1;
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
			acol = this->get_line(line);
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
	static matrix<T> diag(cyclist<T> values)//产生对角矩阵 
	{
		int size = values.size();
		matrix<T> outmatrix(Tuple<int, int>(size, size));
		for(int line = 0; line < size; line += 1)
			for(int list = 0; list < size; list += 1)
				outmatrix.set_point(line, list, (line == list ? values[line] : (T)(0)));
		return outmatrix;
	}
	static matrix<T> full(Tuple<int, int> size, T value)//产生一个全填充的给定大小的矩阵 
	{
		matrix<T> outmatrix(size);
		for(int line = 0; line < size.elemt_0; line += 1)
			for(int list = 0; list < size.elemt_1; list += 1)
				outmatrix.set_point(line, list, value);
		return outmatrix;
	}
	static matrix<T> block(matrix<matrix<T>> input)//矩阵的矩阵视为分块矩阵
	{
		if(input.msize_line == 0 || input.msize_list == 0)
			exit(1008);
		Tuple<int, int> input_size(input.msize_line, input.msize_list);
		int height[input_size.elemt_0];
		int width[input_size.elemt_1];
		int height_sum = 0;
		int width_sum = 0;
		for(int line = 0; line < input_size.elemt_0; line += 1)
		{
			height[line] = input[line][0].msize_line;
			if(height[line] == 0)
				exit(1008);
			height_sum += height[line];
		}
		for(int list = 0; list < input_size.elemt_1; list += 1)
		{
			width[list] = input[0][list].msize_list;
			if(width[list] == 0)
				exit(1008);
			width_sum += width[list];
		}
		for(int line = 0; line < input_size.elemt_0; line += 1)
			for(int list = 0; list < input_size.elemt_1; list += 1)
				if(input[line][list].msize_line != height[line] || input[line][list].msize_list != width[list])
					exit(1005);
		matrix<T> matrixs[input_size.elemt_0];
		for(int line = 0; line < input_size.elemt_0; line += 1)
		{
			matrixs[line] = input[line][0];
			for(int list = 1; list < input_size.elemt_1; list += 1)
				matrixs[line].splice_right(input[line][list]);
		}
		matrix<T> outmatrix = matrixs[0];
		for(int line = 1; line < input_size.elemt_0; line += 1)
			outmatrix.splice_low(matrixs[line]);
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
	/* TODO (#1#): 快速幂 */
	matrix<T> power(int index)//矩阵求幂 
	{
		if(msize_line != msize_list)
			exit(1005);
		matrix<T> base = *this;
		if(index == 0)
			return matrix<T>::quantity(msize_line, (T)(1));
		else if(index < 0)
			return base.inverse().power(-index);
		else
		{
			for(int pow = 1; pow < index; pow += 1)
				base = base * (*this);
			base.ensure();
			return base;
		}
	}
	matrix<T> to_uppertri()//行简化为上三角矩阵 
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
			for(int line = ruler + 1; line < base.msize_line; line += 1)//下面的行进行去首 
			{
				temp = base.pin[line][main_list[ruler]] / base.pin[ruler][main_list[ruler]];
				for(int list = 0; list < base.msize_list; list += 1)
				{
					base.pin[line][list] = base.pin[line][list] - temp * base.pin[ruler][list];
					if(abs(base.pin[line][list]) <= 0.0000000000001)
						base.pin[line][list] = (T)(0);
				}
			}
		}
		base.ensure();
		return base;
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
		base.ensure();
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
	matrix<T> inverse()//求逆或广义逆（注：本矩阵计算工具不考虑复数 
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
			outmatrix.ensure();
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
		B.ensure();
		C.ensure();
		return Tuple<matrix<T>, matrix<T>>(B, C);
	}
	Tuple<matrix<T>, matrix<T>> QR_decomposition()//QR分解
	{
		int this_rank = this->rank();
		if(this_rank == 0)
			exit(1006);
		if(this_rank < msize_list)
			exit(1007);
		matrix<T> Q = *this;
		matrix<T> R(Tuple<int, int>(msize_list, msize_list));
		T coef(0);
		column<T> coef_0, coef_1;
		for(int list = 0; list < msize_list; list += 1)
		{
			coef_0 = Q.get_list(list);
			for(int sublist = 0; sublist < list; sublist += 1)
			{
				coef_1 = Q.get_list(sublist);
				coef = -column_inner_product(coef_1, coef_0) / column_inner_product(coef_1, coef_1);
				Q.plus_list(list, coef_1 * coef);
			}
			Q.mult_list<double>(list, 1 / modulu(Q.get_list(list)));
		}
		R = Q.transpose() * (*this);
		Q.ensure();
		R.ensure();
		return Tuple<matrix<T>, matrix<T>>(Q, R);
	}
	/* TODO (#1#): 记得更换自己写的sqrt函数 */
	T det()//求行列式或广义行列式 
	{
		if(msize_line > msize_list)
			return sqrt((*this * this->transpose()).det());
		else if(msize_line < msize_list)
			return this->transpose().det();
		matrix<T> submatrix = this->to_uppertri();
		T prod(1);
		for(int linest = 0; linest < msize_line; linest += 1)
			prod = (T)(prod * submatrix.pin[linest][linest]);
		return prod;
	}
	/* TODO (#1#): 补全求解方程组 */
	matrix<T> kramer()//求以该矩阵为增广矩阵的方程组的解集
	{
		if(msize_line == 0 || msize_list <= 1)
			exit(1008);
		matrix<T> base = this->to_stepped();
		int rank = base.rank();
		int unknown = msize_list - 1;
		//下一步：找出非主元列，作为自由变量
		bool* notmain = new bool[msize_list];
		int notmain_num = msize_list;
		for(int list = 0; list < msize_list; list += 1)
			notmain[list] = 1;
		for(int line = 0; line < rank; line += 1)
			for(int list = 0; list < msize_list; list += 1)
				if(base.pin[line][list] != (T)(0))
				{
					notmain[list] = 0;
					notmain_num -= 1;
					break;
				}
	}
	matrix<T> kramer(matrix<T> coefs)//求以该矩阵为系数矩阵的方程组的解集 
	{
		if(coefs.msize_line != msize_line || coefs.msize_list != 1)
			exit(1005);
		if(msize_line == 0 || msize_list == 0)
			exit(1008);
		return this->splice_right(coefs).kramer();
	}
	void ensure()//打补丁：double计算会产生误差导致0不严格 
	{
		if(typeid(pin[0][0]).name()[0] < '0' || typeid(pin[0][0]).name()[0] > '9')//不是自定义的准确类型 
			for(int list = 0; list < msize_list; list += 1)
				for(int line = 0; line < msize_line; line += 1)
					if(abs(pin[line][list]) <= 0.0000000000001)
						pin[line][list] = (T)(0);
	}
};

/*
template <typename T>
class nparray
{
	void* values = NULL;
	int dimension = 0;
	cyclist<int> asize;
	nparray(){}
	nparray(int dimen)
	{
		
	}
};*/


