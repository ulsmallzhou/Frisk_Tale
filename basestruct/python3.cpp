template <typename T0, typename T1>
class Tuple;


class outputbox_base;


template <typename T>
class node//节点模板 
{
public:
	T value;
	node<T>* next = NULL;
	node<T>* before = NULL;
	node(){}//空构造函数 
	node(T input){value = input;}
	node(const node &anode){value = anode.value;}//拷贝构造时仅复制T而不复制指针 
	~node(){}//被删除的节点指向的内存可能还有用 
};


template <typename T0, typename T1>
class Tuple;
template <typename T>
class cyclist//列表模板（其实是循环双向链表）
{
public:
	int lsize = 0;//长度 
	node<T>* start = NULL;//指向起始点
	cyclist(){}
	cyclist(T input)
	{
		start = new node<T>;
		start->value = input;
		start->next = start;
		start->before = start;//唯一元素的前驱与后继均为自身 
		lsize = 1;
	}
	cyclist(initializer_list<T> inputs)//初始化列表初始化 
	{
		lsize = inputs.size();
		auto* input = inputs.begin();
		start = new node<T>;
		node<T>* pin = start;
		pin->value = *input;
		for(int num = 1; num < lsize; num += 1)
		{
			input++;
			pin->next = new node<T>;
			pin->next->before = pin;
			pin = pin->next;
			pin->value = *input;
		}//除首尾不相连外，指针链建立完毕
		start->before = pin;
		pin->next = start;//首尾相连 
	}
	cyclist(T* inputs, int valuenum)//数组初始化 
	{
		lsize = valuenum;
		start = new node<T>;
		node<T>* pin = start;
		pin->value = inputs[0];
		for(int num = 1; num < lsize; num += 1)
		{
			pin->next = new node<T>;
			pin->next->before = pin;
			pin = pin->next;
			pin->value = inputs[num];
		}//除首尾不相连外，指针链建立完毕
		start->before = pin;
		pin->next = start;//首尾相连 
	}
	cyclist(const cyclist<T> &alist)//拷贝构造函数，要求alist非空 
	{
		lsize = alist.lsize;
		start = new node<T>;
		node<T>* alist_pin = alist.start;
		start->value = alist_pin->value;
		alist_pin = alist_pin->next;
		start->before = start;
		start->next = start;
		node<T>* pin = start;
		for(int num = 1; num < lsize; num += 1)
		{
			pin->next = new node<T>;
			pin->next->before = pin;
			pin = pin->next;
			pin->value = alist_pin->value;
			alist_pin = alist_pin->next;
		}
		start->before = pin;
		pin->next = start;
	}
	~cyclist()//内存释放 
	{
		for(int num = 1; num < lsize; num += 1)
		{
			start = start->next;
			delete start->before;
		}
		if(lsize > 0)
			delete start;
	}
	int size(){return lsize;}
	void append(initializer_list<T> inputs)//以初始化列表增加元素
	{
		auto* input = inputs.begin();
		int maxnum = inputs.size();
		node<T>* pin = NULL;
		if(lsize == 0)
		{
			start = new node<T>;
			start->value = *input;
			start->before = start;
			start->next = start;
			input++;
			pin = start;
			for(int num = 1; num < maxnum; num += 1)
			{
				pin->next = new node<T>;
				pin->next->before = pin;
				pin = pin->next;
				pin->value = *input;
				input++;
			}
		}
		else
		{
			pin = start->before;//指向最后一个元素 
			for(int num = 0; num < maxnum; num += 1)
			{
				pin->next = new node<T>;
				pin->next->before = pin;
				pin = pin->next;
				pin->value = *input;
				input++;
			}
		}
		pin->next = start;
		start->before = pin;//首尾重新相连 
		lsize += maxnum;
	}
	void append(T* inputs, int inputnum)//以数组增加元素
	{
		node<T>* pin = NULL;
		if(lsize == 0)
		{
			start = new node<T>;
			start->value = inputs[0];
			start->before = start;
			start->next = start;
			pin = start;
			for(int num = 1; num < inputnum; num += 1)
			{
				pin->next = new node<T>;
				pin->next->before = pin;
				pin = pin->next;
				pin->value = inputs[num];
			}
		}
		else
		{
			pin = start->before;//指向最后一个元素 
			for(int num = 0; num < inputnum; num += 1)
			{
				pin->next = new node<T>;
				pin->next->before = pin;
				pin = pin->next;
				pin->value = inputs[num];
			}
		}
		pin->next = start;
		start->before = pin;//首尾重新相连 
		lsize += inputnum;
	}
	T &operator[](int rank)//越界访问将循环，下标从0开始
	{
		for(; rank < 0 && lsize > 0; rank += lsize);
		for(; rank >= lsize && lsize > 0; rank -= lsize);
		node<T>* pin = start;
		if(lsize == 0)
			pin = new node<T>;
		else for(int num = 0; num < rank; num += 1)
			pin = pin->next;
		return pin->value;
	}
	template <typename T_other>
	cyclist<T> operator+(const cyclist<T_other> &alist)//分别相加，+后面的list被广播（循环） 
	{
		int length = alist.lsize == 0 ? 0 : (lsize / alist.lsize) * alist.lsize;
		cyclist<T> outlist;
		node<T>* pin_1 = start;
		node<T_other>* pin_2 = alist.start;
		for(int id = 0; id < length; id += 1)
		{
			outlist.append({(T)(pin_1->value + pin_2->value)});
			pin_1 = pin_1->next;
			pin_2 = pin_2->next;
		}
		return outlist;
	}
	template <typename T_other>
	cyclist<T> operator-(const cyclist<T_other> &alist)//和加法类似的减法 
	{
		int length = alist.lsize == 0 ? 0 : (lsize / alist.lsize) * alist.lsize;
		cyclist<T> outlist;
		node<T>* pin_1 = start;
		node<T_other>* pin_2 = alist.start;
		for(int id = 0; id < length; id += 1)
		{
			outlist.append({(T)(pin_1->value - pin_2->value)});
			pin_1 = pin_1->next;
			pin_2 = pin_2->next;
		}
		return outlist;
	}
	cyclist<T> operator-()//单纯负号重载 
	{
		cyclist<T> outlist;
		node<T>* pin = start;
		for(int id = 0; id < lsize; id += 1)
		{
			outlist.append({-(pin->value)});
			pin = pin->next;
		}
		return outlist;
	}
	template <typename T_other>
	cyclist<T> operator*(const T_other &coef)//乘法（禁止非数字类） 
	{
		cyclist<T> outlist;
		node<T>* pin = start;
		for(int id = 0; id < lsize; id += 1)
		{
			outlist.append({(T)((pin->value) * coef)});
			pin = pin->next;
		}
		return outlist;
	}
	template <typename T_other>
	cyclist<T> operator/(const T_other &coef)//除法（禁止非数字类） 
	{
		if(coef == 0)
			exit(1003);
		cyclist<T> outlist;
		node<T>* pin = start;
		for(int id = 0; id < lsize; id += 1)
		{
			outlist.append({(T)((pin->value) / coef)});
			pin = pin->next;
		}
		return outlist;
	}
	bool operator==(const cyclist<T> &alist)
	{
		if(lsize != alist.lsize)
			return 0;
		node<T>* pin_1 = start;
		node<T>* pin_2 = alist.start;
		for(int id = 0; id < lsize; id += 1)
		{
			if(pin_1->value != pin_2->value)
				return 0;
			pin_1 = pin_1->next;
			pin_2 = pin_2->next;
		}
		return 1;
	}
	bool operator!=(const cyclist<T> &alist){return !(*this == alist);}
	void extend(cyclist<T> inputs)//列表拼接
	{
		int length = inputs.size();
		if(length > 0)
		{
			node<T>* pin = NULL;
			if(lsize == 0)
			{
				start = new node<T>;
				start->before = start;
				start->next = start;
				start->value = inputs[0];
				pin = start;
				for(int num = 1; num < length; num += 1)
				{
					pin->next = new node<T>;
					pin->next->value = inputs[num];
					pin->next->before = pin;
					pin = pin->next;
				}
			}
			else
			{
				pin = start->before;//指向最后一个元素 
				for(int num = 0; num < length; num += 1)
				{
					pin->next = new node<T>;
					pin->next->value = inputs[num];
					pin->next->before = pin;
					pin = pin->next;
				}
			}
			pin->next = start;
			start->before = pin;
			lsize += length;
		}
	}
	int find(T input)//元素查找，返回其下标，若无则返回-1，需要类型T重载==
	{
		int rank = -1;
		node<T>* pin = start;
		for(int num = 0; num < lsize; num += 1)
		{
			if(input == pin->value)
			{
				rank = num;
				break;
			}
			pin = pin->next;
		}
		return rank;
	}
	bool del(int rank)//指定下标元素删除，删除成功返回1
	{
		if(rank < 0 || rank >= lsize)
			return 0;
		else if(lsize == 1)
		{
			delete start;
			start = NULL;
		}
		else if(rank == 0)
		{
			start = start->next;
			start->before = start->before->before;
			delete start->before->next;
			start->before->next == start;
		}
		else
		{
			node<T>* pin = start;
			for(int num = 0; num < rank; num += 1)//循环完后pin指向该删除的节点 
				pin = pin->next;
			pin->next->before = pin->before;
			pin = pin->next;
			delete pin->before->next;
			pin->before->next = pin;
		}
		lsize -= 1;
		return 1;
	}
	bool* del(initializer_list<T> values)//指定内容元素删除，返回一个数组表示是否成功删除，需要类型T重载==
	{
		auto* value = values.begin();
		int length = values.size();
		bool* success = new bool[length];
		bool ifcontinue = 1;
		for(int num = 0; num < length; )
		{
			if(lsize == 0)
			{
				for(int id = num; id < length; id += 1)
					success[id] = 0;
				break;
			}
			else if(lsize == 1)
			{
				if(start->value == *value)
				{
					delete start;
					start = NULL;
					lsize = 0;
					success[num] = 1;
				}
				else
					success[num] = 0;
				num += 1;
				value++;
				continue;
			}
			else
			{
				ifcontinue = 1;
				for(int id = 0; id < lsize; id += 1)
					if((*this)[id] == *value)
					{
						this->del(id);
						ifcontinue = 0;
						success[num] = 1;
						break;
					}
				if(ifcontinue)
				{
					num += 1;
					value++;
				}
			}
		}
		return success;
	}
	void empty()
	{
		if(lsize > 0)
		{
			for(int id = lsize - 1; id >= 0; id -= 1)
				this->del(id);
		}
	}
	friend ostream &operator<<(ostream &output, const cyclist<T> &alist)
	{
		char Ttype = typeid(T).name()[0];
		int sid = (Ttype == 'c' ? 1 : (Ttype == 'S' ? 2 : 0));
		string str[3] = {"", "\'", "\""};
		output<<"[";
		node<T>* pin = alist.start;
		for(int id = 0; id < alist.lsize; id += 1)
		{
			if(id > 0)
				output<<", ";
			output<<str[sid];
			output<<(pin->value);
			output<<str[sid];
			pin = pin->next;
		}
		output<<"]";
	}
	void operator=(const cyclist<T> &alist)
	{
		lsize = alist.lsize;
		start = new node<T>;
		node<T>* alist_pin = alist.start;
		start->value = alist_pin->value;
		alist_pin = alist_pin->next;
		start->before = start;
		start->next = start;
		node<T>* pin = start;
		for(int num = 1; num < lsize; num += 1)
		{
			pin->next = new node<T>;
			pin->next->before = pin;
			pin = pin->next;
			pin->value = alist_pin->value;
			alist_pin = alist_pin->next;
		}
		start->before = pin;
		pin->next = start;
	}/*
	Tuple<Tuple<int, int>, cyclist<string>> output()
	{
		Tuple<Tuple<int, int>, cyclist<string>> elements[lsize];
		node<T>* pin = start;
		for(int id = 0; id < lsize; id += 1)
		{
			elements[id] = pin->value.output();
			pin = pin->next;
		}
		return elements[0];
	}*/
};


template <typename T0, typename T1>
class Tuple//二元元组 
{
public:
	T0 elemt_0;
	T1 elemt_1;
	Tuple(){}
	Tuple(T0 aelemt_0, T1 aelemt_1)
	{
		elemt_0 = aelemt_0;
		elemt_1 = aelemt_1;
	}
	Tuple(const Tuple<T0, T1> &atuple)
	{
		elemt_0 = atuple.elemt_0;
		elemt_1 = atuple.elemt_1;
	}
	~Tuple(){}
	void set(T0 aelemt_0, T1 aelemt_1)
	{
		elemt_0 = aelemt_0;
		elemt_1 = aelemt_1;
	}
	Tuple<T1, T0> swap(){return Tuple(elemt_1, elemt_0);}
	T0 first_elemt(){return elemt_0;}
	T1 second_elemt(){return elemt_1;}
	friend ostream &operator<<(ostream &output, const Tuple<T0, T1> &aTuple)
	{
		char Ttype1 = typeid(T0).name()[0], Ttype2 = typeid(T1).name()[0];
		int sid1 = (Ttype1 == 'c' ? 1 : (Ttype1 == 'S' ? 2 : 0)), sid2 = (Ttype2 == 'c' ? 1 : (Ttype2 == 'S' ? 2 : 0));
		string str[3] = {"", "\'", "\""};
		output<<"(";
		output<<str[sid1];
		output<<aTuple.elemt_0;
		output<<str[sid1];
		output<<", ";
		output<<str[sid2];
		output<<aTuple.elemt_1;
		output<<str[sid2];
		output<<")";
		return output; 
	}
	void operator=(const Tuple<T0, T1> &aTuple)
	{
		elemt_0 = aTuple.elemt_0;
		elemt_1 = aTuple.elemt_1;
	}
	template <typename T_other_1, typename T_other_2>
	Tuple<T0, T1> operator+(const Tuple<T_other_1, T_other_2> &aTuple)
	{
		Tuple<T0, T1> outTuple((T0)(elemt_0 + aTuple.elemt_0), (T1)(elemt_1 + aTuple.elemt_1));
		return outTuple;
	}
	template <typename T_other_1, typename T_other_2>
	Tuple<T0, T1> operator-(const Tuple<T_other_1, T_other_2> &aTuple)
	{
		Tuple<T0, T1> outTuple((T0)(elemt_0 - aTuple.elemt_0), (T1)(elemt_1 - aTuple.elemt_1));
		return outTuple;
	}
	Tuple<T0, T1> operator-()//单纯负号重载 
	{
		Tuple<T0, T1> outTuple(-elemt_0, -elemt_1);
		return outTuple;
	}
	template <typename T_other>
	Tuple<T0, T1> operator*(const T_other &coef)//乘法（禁止非数字类） 
	{
		Tuple<T0, T1> outTuple((T0)(elemt_0 * coef), (T1)(elemt_1 * coef));
		return outTuple;
	}
	template <typename T_other>
	Tuple<T0, T1> operator/(const T_other &coef)//除法（禁止非数字类） 
	{
		if(coef == 0)
			exit(1003);
		Tuple<T0, T1> outTuple((T0)(elemt_0 / coef), (T1)(elemt_1 / coef));
		return outTuple;
	}
	bool operator==(const Tuple<T0, T1> &aTuple)
	{
		return elemt_0 == aTuple.elemt_0 && elemt_1 == aTuple.elemt_1;
	}
	bool operator!=(const Tuple<T0, T1> &aTuple){return !(*this == aTuple);}
};


template <class T_0, class T_1>
cyclist<Tuple<T_0, T_1>> merge(cyclist<T_0> list_0, cyclist<T_1> list_1)//两个列表拼合为元组列表 
{
	cyclist<Tuple<T_0, T_1>> list_merge;
	int size = min(list_0.lsize, list_1.lsize);
	for(int id = 0; id < size; id += 1)
		list_merge.append({Tuple<T_0, T_1>(list_0[id], list_1[id])});
	return list_merge;
}


template <typename T_key, typename T_value>
class dict//字典类，可用来做counter 
{
public:
	cyclist<T_key> key;
	cyclist<T_value> value;
	int dsize = 0;
	dict(){}
	dict(initializer_list<T_key> keys, initializer_list<T_value> values)//两个初始化列表进行初始化 
	{
		int length = min(keys.size(), values.size());
		auto* akey = keys.begin();
		auto* avalue = values.begin();
		bool same = 0;
		int same_id = 0;
		for(int num = 0; num < length; num += 1)
		{
			same = 0;
			for(int id = 0; id < dsize; id += 1)
				if(key[id] == *akey)
				{
					same = 1;
					same_id = id;
					break;
				}
			if(!same)
			{
				key.append({*akey});
				value.append({*avalue});
				dsize += 1;
			}
			else
				value[same_id] = *avalue;
			akey++;
			avalue++;
		}
	}
	dict(cyclist<T_key> keys, cyclist<T_value> values)//两个初始化列表进行初始化 
	{
		int length = min(keys.size(), values.size());
		bool same = 0;
		int same_id = 0;
		for(int num = 0; num < length; num += 1)
		{
			same = 0;
			for(int id = 0; id < dsize; id += 1)
				if(key[id] == keys[num])
				{
					same = 1;
					same_id = id;
					break;
				}
			if(!same)
			{
				key.append({keys[num]});
				value.append({values[num]});
				dsize += 1;
			}
			else
				value[same_id] = values[num];
		}
	}
	dict(const dict<T_key, T_value> &adict)
	{
		key = adict.key;
		value = adict.value;
		dsize = adict.dsize;
	}
	int size(){return dsize;}
	T_value &operator[](T_key akey)//若访问不存在的key则报错退出 
	{
		for(int id = 0; id < dsize; id += 1)
			if(key[id] == akey)
				return value[id];
		exit(1001);
	}
	bool set(T_key akey, T_value avalue)//设置键对应的值（返回0），或增加新的键值对（返回1） 
	{
		for(int id = 0; id < dsize; id += 1)
			if(key[id] == akey)
			{
				value[id] = avalue;
				return 0;
			}
		key.append({akey});
		value.append({avalue});
		dsize += 1;
		return 1;
	}
	bool del(T_key akey)//返回是否成功删除
	{
		for(int id = 0; id < dsize; id += 1)
			if(akey == key[id])
			{
				key.del(id);
				value.del(id);
				dsize -= 1;
				return 1;
			}
		return 0;
	}
	bool find(T_key akey){return key.find(akey) != -1;}//查找键值是否已存在 
	cyclist<T_key> get_keys(){return key;}//返回键的列表 
	cyclist<T_value> get_values(){return value;}//返回值的列表 
	cyclist<Tuple<T_key, T_value>> items()
	{
		cyclist<Tuple<T_key, T_value>> item;
		for(int id = 0; id < dsize; id += 1)
			item.append({Tuple<T_key, T_value>(key[id], value[id])});
		return item;
	}
	friend ostream &operator<<(ostream &output, const dict<T_key, T_value> &adict)
	{
		char Ttype1 = typeid(T_key).name()[0], Ttype2 = typeid(T_value).name()[0];
		int sid1 = (Ttype1 == 'c' ? 1 : (Ttype1 == 'S' ? 2 : 0)), sid2 = (Ttype2 == 'c' ? 1 : (Ttype2 == 'S' ? 2 : 0));
		string str[3] = {"", "\'", "\""};
		output<<"{";
		node<T_key>* akey = adict.key.start;
		node<T_value>* avalue = adict.value.start;
		for(int id = 0; id < adict.dsize; id += 1)
		{
			if(id > 0)
				output<<", ";
			output<<str[sid1];
			output<<akey->value;
			output<<str[sid1];
			output<<": ";
			output<<str[sid2];
			output<<avalue->value;
			output<<str[sid2];
			akey = akey->next;
			avalue = avalue->next;
		}
		output<<"}";
		return output; 
	}
	void operator=(const dict<T_key, T_value> &adict)
	{
		key = adict.key;
		value = adict.value;
		dsize = adict.dsize;
	}
	bool operator==(const dict<T_key, T_value> &adict)
	{
		return dsize == adict.dsize && key == adict.key && value != adict.value;
	}
	bool operator!=(const dict<T_key, T_value> &adict){return !(*this == adict);}
};
template <typename T>
class counter//统计计数器 
{
public:
	dict<T, int> pool;
	counter(){}
	counter(cyclist<T> names)//设置计数列表，默认全重置0 
	{
		int length = names.size();
		for(int num = 0; num < length; num += 1)
			pool.set(names[num], 0);
	}
	int size(){return pool.size();}
	void add(T akey)//添加统计项 
	{
		if(pool.key.find(akey) == -1)
			pool.set(akey, 0);
	}
	void reset()//全部重置 
	{
		int length = pool.size();
		cyclist<T> keys = pool.get_keys();
		for(int id = 0; id < length; id += 1)
			pool.set(keys[id], 0);
	}
	void plus(T aname, int delta)//计数，若名字列表中不存在该值，则新建该值的统计 
	{
		this->add(aname);//存在则无效，不存在则创建 
		pool.set(aname, pool[aname] + delta);
	}
	void plus(cyclist<T> names, cyclist<int> values)//一次性计数多个 
	{
		for(int id = 0; id < pool.size(); id += 1)
		{
			this->add(names[id]);
			pool.set(names[id], pool[names[id]] + values[id]);
		}
	}
	Tuple<cyclist<T>, int> maxlist()//取最大值
	{
		Tuple<cyclist<T>, int> max_list;
		int maxs = -2147483648;
		cyclist<T> keys = pool.get_keys();
		for(int id = 0; id < keys.size(); id += 1)
			if(pool[keys[id]] > maxs)
			{
				maxs = pool[keys[id]];
				max_list.elemt_0.empty();
				max_list.elemt_1 = maxs;
				max_list.elemt_0.append({keys[id]});
			}
			else if(pool[keys[id]] == maxs)
				max_list.elemt_0.append({keys[id]});
		return max_list;
	}
	Tuple<cyclist<T>, int> minlist()//取最小值 
	{
		Tuple<cyclist<T>, int> min_list;
		int mins = 2147483647;
		cyclist<T> keys = pool.get_keys();
		for(int id = 0; id < keys.size(); id += 1)
			if(pool[keys[id]] < mins)
			{
				mins = pool[keys[id]];
				min_list.elemt_0.empty();
				min_list.elemt_1 = mins;
				min_list.elemt_0.append({keys[id]});
			}
			else if(pool[keys[id]] == mins)
				min_list.elemt_0.append({keys[id]});
		return min_list;
	}
	friend ostream &operator<<(ostream &output, const counter<T> &acounter)
	{
		output<<acounter.pool;
		return output;
	}
};


//template <typename T>
//class array_py//numpy数组 
//{
//public:
//	int dimension = 0;//维数 
//	cyclist<int> coordinates;//每个维数的长度
//	cyclist<long long int> prods;//辅助数组，计算系数用 
//	int value_num = 1;//总共的元素个数 
//	T* values = NULL;//元素的一元数组
//	array_py(){}
//	array_py(int dimen, cyclist<int> coordinatelist)//大小确定 
//	{
//		dimension = dimen;
//		for(int axis = 0; axis < dimen; axis += 1)
//		{
//			coordinates.append({coordinatelist[axis]});
//			value_num = max(1, value_num * coordinatelist[axis]);
//			prods.append({(long long int)coordinates[axis]});//先随便填数，让辅助数组达到需求长度 
//		}
//		values = new T[value_num];
//		prods[dimen - 1] = 1;
//		for(int axis = dimen - 2; axis >= 0; axis -= 1)
//			prods[axis] = coordinates[axis + 1] * prods[axis + 1];
//	}
//	array_py(int dimen, cyclist<int> coordinatelist, cyclist<T> valuelist)//大小确定，内容填充，顺便完成广播机制 
//	{
//		dimension = dimen;
//		for(int axis = 0; axis < dimen; axis += 1)
//		{
//			coordinates.append({coordinatelist[axis]});
//			value_num = max(1, value_num * coordinatelist[axis]);
//			prods.append({(long long int)coordinates[axis]});//先随便填数，让辅助数组达到需求长度 
//		}
//		values = new T[value_num];
//		for(int id = 0; id < value_num; id += 1)
//			values[id] = valuelist[id];
//		prods[dimen - 1] = 1;
//		for(int axis = dimen - 2; axis >= 0; axis -= 1)
//			prods[axis] = coordinates[axis + 1] * prods[axis + 1];
//	}
//	~array_py(){delete[] values;}
//	T &operator[](cyclist<int> subscripts)//越界访问将循环，下标从0开始；默认最后缺省的坐标分量为0，多的分量无效 
//	{
//		int length = subscripts.size();
//		cyclist<int> fixed_subscripts;
//		if(length >= dimension)
//			for(int axis = 0; axis < dimension; axis += 1)
//				fixed_subscripts.append({subscripts[axis] % coordinates[axis]});
//		else
//		{
//			for(int axis = 0; axis < length; axis += 1)
//				fixed_subscripts.append({subscripts[axis] % coordinates[axis]});
//			for(int axis = length; axis < dimension; axis += 1)
//				fixed_subscripts.append({0});
//		}
//		long long int ranks = 0;
//		for(int axis = 0; axis < dimension; axis += 1)
//			ranks += prods[axis] * fixed_subscripts[axis];
//		return values[ranks];
//	}
//	/*array<T> subarray(cyclist<int> subscripts)
//	{
//		
//	}*/
//};


int** product(initializer_list<int> axis)//笛卡尔积，生成二维数组，每一行都是一个笛卡尔积元素 
{
	auto* pin = axis.begin();
	int dimension = axis.size();
	int* pro = new int[dimension];
	for(int num = 0; num < dimension; num += 1)
		pro[num] = 1;
	for(int num = 0; num < dimension; num += 1)
	{
		for(int subnum = 0; subnum <= num; subnum += 1)
			pro[subnum] *= *pin;
		pin++;
	}
	int maxnum = pro[0];
	int** out = new int*[maxnum];
	for(int id = 0; id < maxnum; id += 1)
	{
		out[id] = new int[dimension];
		out[id][dimension - 1] = id % pro[dimension - 1];
		for(int num = dimension - 2; num >= 0; num -= 1)
			out[id][num] = (id % pro[num]) / pro[num + 1];
	}
	return out;
}
/*typeid().name()
int : i
double : d
char : c
string : A[length + 1]_c//"123"->A4_c
string : Ss//所有string通用 
dict<int, int> : 4dictIiiE : 4dict<I(i, i)E>
Tuple<int, char> : 5TupleIicE : 5Tuple<I(i, c)E>
Tuple<char, char> : 5TupleIccE : 5Tuple<I(c, c)E>
Tuple<char, Tuple<string, double>> : 5TupleIcS_ISsdEE : 5Tuple<I(c, S_<I(Ss-d)E>)E>
Tuple<Tuple<char, int>, Tuple<string, double>> : 5TupleIS_IciES_ISsdEE : 5Tuple<I(S_<I(c-i)E>S_<I(Ss-d)E>)E>
cyclist<int> : 7cyclistIiE : 7cyclist<I(i)E>
cyclist<char> : 7cyclistIcE : 7cyclist<I(c)E>
cyclist<Tuple<char, string>> : 7cyclistI5TupleIcSsEE : 7cyclist<I(5Tuple<I(c, Ss)E>)E>
Tuple<cyclist<int>, cyclist<double>> : 5TupleI7cyclistIiES0_IdEE : 5Tuple<I(7cyclist<I(i)E>, S0_<I(d)E>)E>
Tuple<cyclist<int>, Tuple<double, int>> : 5TupleI7cyclistIiES_IdiEE : 5Tuple<I(7cyclist<I(i)E>, S_<I(d, i)E>)E>
Tuple<int, int*> : 5TupleIiPiE : 5Tuple<I(i, P-i)E>
Tuple<int, int**> : 5TupleIiPPiE : 5Tuple<I(i, PP-i)E>
Tuple<int, Tuple<int, double>*> : 5TupleIiPS_IidEE : 5Tuple<I(i, P-S_<I(i, d)E>)E>
Tuple<Tuple<int, double>, Tuple<int, double>> : 5TupleIS_IidES0_E : 5Tuple<I(S_<I(i, d)E>, S0_)E>
Tuple<Tuple<int, double>, Tuple<int, double>*> : 5TupleIS_IidEPS0_E : 5Tuple<I(S_<I(i, d)E>, P-S0_)E>
Tuple<Tuple<int, double>*, Tuple<int, double>> : 5TupleIPS_IidES0_E : 5Tuple<I(P-S_<I(i, d)E>, S0_)E>
Tuple<Tuple<int, double>*, Tuple<int, double>*> : 5TupleIPS_IidES1_E : 5Tuple<I(P-S_<I(i, d)E>, S1_)E>
*/

