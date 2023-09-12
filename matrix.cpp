template <typename T>
class column
{
public:
	T* pin = NULL;
	int asize = 0;
	column(){}
	column(int length)
	{
		asize = length;
		pin = new T[length];
	}
	column(T* values, int length)
	{
		asize = length;
		pin = new T[length];
		for(int num = 0; num < length; num += 1)
			pin[num] = values[num];
	}
	column(cyclist<T> inputs)//初始化列表初始化 
	{
		asize = inputs.size();
		pin = new T[asize];
		for(int num = 0; num < asize; num += 1)
			pin[num] = inputs[num];
	}
	column(initializer_list<T> inputs)//初始化列表初始化 
	{
		asize = inputs.size();
		auto* input = inputs.begin();
		pin = new T[asize];
		for(int num = 0; num < asize; num += 1)
		{
			pin[num] = *input;
			input++;
		}
	}
	column(const column<T> &anarray)
	{
		asize = anarray.asize;
		pin = new T[asize];
		for(int num = 0; num < asize; num += 1)
			pin[num] = anarray.pin[num];
	}
	~column(){delete[] pin;}
	int size(){return asize;}
	void set(cyclist<T> inputs)//长度不匹配将不会设置 
	{
		if(inputs.size() == asize)
			for(int id = 0; id < asize; id += 1)
				pin[id] = inputs[id];
	}
	void set(T input, int id)//下标不合适将不会设置 
	{
		if(id >= 0 && id < asize)
			pin[id] = input;
	}
	T &operator[](int subscript)//越界访问将报错
	{
		if(subscript < 0 || subscript >= asize)
			exit(1002);
		return pin[subscript];
	}
	void operator=(const column<T> &acol)
	{
		asize = acol.asize;
		pin = new T[asize];
		for(int num = 0; num < asize; num += 1)
			pin[num] = acol.pin[num];
	}
	friend ostream &operator<<(ostream &output, const column<T> &acol)
	{
		output<<"[";
		for(int id = 0; id < acol.asize; id += 1)
		{
			if(id > 0)
				output<<", ";
			output<<acol.pin[id];
		}
		output<<"]";
	}
};


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
	matrix<T> transpose()
	{
		matrix<T> amatrix(Tuple<int, int>(msize_list, msize_line));
		for(int list = 0; list < msize_line; list += 1)
			amatrix.set_list((*this)[list], list);
		return amatrix;
	}
	void set_line(int line, column<T> aline)//长度不匹配将不会设置 
	{
		if(aline.size() == msize_list && 0 <= line && line < msize_line)
			for(int list = 0; list < aline.size(); list += 1)
				pin[line][list] = aline[list];
	}
	void set_list(int list, column<T> alist)//长度不匹配将不会设置 
	{
		if(alist.size() == msize_line && 0 <= list && list < msize_list)
			for(int line = 0; line < alist.size(); line += 1)
				pin[line][list] = alist[line];
	}
	void set_point(int line, int list, T value)//越界将不会设置 
	{
		if(0 <= line && line < msize_line && 0 <= list && list < msize_list)
			pin[line][list] = value;
	}
	column<T>& operator[](int line)//越界访问将报错（返回行） 
	{
		static column<T> acol(msize_list);
		if(0 <= line && line < msize_line)
			for(int list = 0; list < msize_list; list += 1)
				acol.set(pin[line][list], list);
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
	static matrix<T> quantity(int size, T value)//产生数量阵，即单位阵的数乘 
	{
		matrix<T> outmatrix(Tuple<int, int>(size, size));
		for(int line = 0; line < size; line += 1)
			for(int list = 0; list < size; list += 1)
				outmatrix.set_point(line, list, (line == list ? value : (T)(0)));
		return outmatrix;
	}
	static matrix<T> zero(int size, T value)//产生零矩阵 
	{
		matrix<T> outmatrix(Tuple<int, int>(size, size));
		for(int line = 0; line < size; line += 1)
			for(int list = 0; list < size; list += 1)
				outmatrix.set_point(line, list, (T)(0));
		return outmatrix;
	}
	void swap_lines(int line_1, int line_2)//交换两行元素 
	{
		if(line_1 >= 0 && line_1 < msize_line && line_2 >= 0 && line_2 < msize_line && line_1 != line_2)
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
		if(list_1 >= 0 && list_1 < msize_list && list_2 >= 0 && list_2 < msize_list && list_1 != list_2)
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
	void plus_line(int line, column<T> acol)//行加行 
	{
		if(acol.size() == msize_list && 0 <= line && line < msize_line)
			for(int list = 0; list < msize_list; list += 1)
				pin[line][list] = pin[line][list] + acol[list];
	}
	void plus_list(int list, column<T> acol)//列加列 
	{
		if(acol.size() == msize_line && 0 <= list && list < msize_list)
			for(int line = 0; line < msize_line; line += 1)
				pin[line][list] = pin[line][list] + acol[line];
	}
	void right_extension(matrix<T> amatrix)//把输入的矩阵（若大小匹配）拼接到该矩阵右侧 
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
	}
	void left_extension(matrix<T> amatrix)//把输入的矩阵（若大小匹配）拼接到该矩阵左侧 
	{
		
	}
	void high_extension(matrix<T> amatrix)//把输入的矩阵（若大小匹配）拼接到该矩阵上侧 
	{
		
	}
	void low_extension(matrix<T> amatrix)//把输入的矩阵（若大小匹配）拼接到该矩阵下侧 
	{
		
	}
	Tuple<matrix<T>, matrix<T>> cut_left_right(int list)//左右切成两个矩阵 
	{
		
	}
	Tuple<matrix<T>, matrix<T>> cut_high_low(int line)//上下切成两个矩阵 
	{
		
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


