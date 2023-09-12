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
class matr
{
public:
	T** pin = NULL;
	int msize_line;
	int msize_list;
	matr(){}
	matr(Tuple<int, int> size)
	{
		msize_line = size.first_elemt();
		msize_list = size.second_elemt();
		pin = new T*[size.first_elemt()];
		for(int line = 0; line < size.first_elemt(); line += 1)
			pin[line] = new T[size.second_elemt()];
	}
	matr(T** values, Tuple<int, int> size)
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
	matr(cyclist<column<T>> arrays)
	{
		msize_line = arrays.size();
		msize_list = arrays[0].size();
		pin = new T*[msize_line];
		for(int line = 0; line < msize_line; line += 1)
		{
			pin[line] = new T[msize_list];
			for(int list = 0; list < msize_list; list += 1)
				pin[line][list] = arrays[line][list];
		}
	}
	~matr()
	{
		for(int line = 0; line < msize_line; line += 1)
			delete[] pin[line];
		delete[] pin;
	}
	matr<T> transpose()
	{
		matr<T> amatrix(Tuple<int, int>(msize_list, msize_line));
		for(int list = 0; list < msize_line; list += 1)
			amatrix.set_list((*this)[list], list);
		return amatrix;
	}
	void set_line(column<T> aline, int line)//长度不匹配将不会设置 
	{
		if(aline.size() == msize_list)
			for(int list = 0; list < aline.size(); list += 1)
				pin[line][list] = aline[list];
	}
	void set_list(column<T> alist, int list)//长度不匹配将不会设置 
	{
		if(alist.size() == msize_line)
			for(int line = 0; line < alist.size(); line += 1)
				pin[line][list] = alist[line];
	}
	column<T> operator[](int line)//越界访问将报错（返回行） 
	{
		column<T> acol(msize_list);
		if(0 <= line && line < msize_line)
			for(int list = 0; list < msize_list; list += 1)
				acol.set(pin[line][list], list);
		return acol;
	}
	friend ostream &operator<<(ostream &output, const matr<T> &amatrix)
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
};


