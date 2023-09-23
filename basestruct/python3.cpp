template <typename T0, typename T1>
class Tuple;


class outputbox_base;


template <typename T>
class node//�ڵ�ģ�� 
{
public:
	T value;
	node<T>* next = NULL;
	node<T>* before = NULL;
	node(){}//�չ��캯�� 
	node(T input){value = input;}
	node(const node &anode){value = anode.value;}//��������ʱ������T��������ָ�� 
	~node(){}//��ɾ���Ľڵ�ָ����ڴ���ܻ����� 
};


template <typename T0, typename T1>
class Tuple;
template <typename T>
class cyclist//�б�ģ�壨��ʵ��ѭ��˫������
{
public:
	int lsize = 0;//���� 
	node<T>* start = NULL;//ָ����ʼ��
	cyclist(){}
	cyclist(T input)
	{
		start = new node<T>;
		start->value = input;
		start->next = start;
		start->before = start;//ΨһԪ�ص�ǰ�����̾�Ϊ���� 
		lsize = 1;
	}
	cyclist(initializer_list<T> inputs)//��ʼ���б��ʼ�� 
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
		}//����β�������⣬ָ�����������
		start->before = pin;
		pin->next = start;//��β���� 
	}
	cyclist(T* inputs, int valuenum)//�����ʼ�� 
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
		}//����β�������⣬ָ�����������
		start->before = pin;
		pin->next = start;//��β���� 
	}
	cyclist(const cyclist<T> &alist)//�������캯����Ҫ��alist�ǿ� 
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
	~cyclist()//�ڴ��ͷ� 
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
	void append(initializer_list<T> inputs)//�Գ�ʼ���б�����Ԫ��
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
			pin = start->before;//ָ�����һ��Ԫ�� 
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
		start->before = pin;//��β�������� 
		lsize += maxnum;
	}
	void append(T* inputs, int inputnum)//����������Ԫ��
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
			pin = start->before;//ָ�����һ��Ԫ�� 
			for(int num = 0; num < inputnum; num += 1)
			{
				pin->next = new node<T>;
				pin->next->before = pin;
				pin = pin->next;
				pin->value = inputs[num];
			}
		}
		pin->next = start;
		start->before = pin;//��β�������� 
		lsize += inputnum;
	}
	T &operator[](int rank)//Խ����ʽ�ѭ�����±��0��ʼ
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
	cyclist<T> operator+(const cyclist<T_other> &alist)//�ֱ���ӣ�+�����list���㲥��ѭ���� 
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
	cyclist<T> operator-(const cyclist<T_other> &alist)//�ͼӷ����Ƶļ��� 
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
	cyclist<T> operator-()//������������ 
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
	cyclist<T> operator*(const T_other &coef)//�˷�����ֹ�������ࣩ 
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
	cyclist<T> operator/(const T_other &coef)//��������ֹ�������ࣩ 
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
	void extend(cyclist<T> inputs)//�б�ƴ��
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
				pin = start->before;//ָ�����һ��Ԫ�� 
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
	int find(T input)//Ԫ�ز��ң��������±꣬�����򷵻�-1����Ҫ����T����==
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
	bool del(int rank)//ָ���±�Ԫ��ɾ����ɾ���ɹ�����1
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
			for(int num = 0; num < rank; num += 1)//ѭ�����pinָ���ɾ���Ľڵ� 
				pin = pin->next;
			pin->next->before = pin->before;
			pin = pin->next;
			delete pin->before->next;
			pin->before->next = pin;
		}
		lsize -= 1;
		return 1;
	}
	bool* del(initializer_list<T> values)//ָ������Ԫ��ɾ��������һ�������ʾ�Ƿ�ɹ�ɾ������Ҫ����T����==
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
class Tuple//��ԪԪ�� 
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
	Tuple<T0, T1> operator-()//������������ 
	{
		Tuple<T0, T1> outTuple(-elemt_0, -elemt_1);
		return outTuple;
	}
	template <typename T_other>
	Tuple<T0, T1> operator*(const T_other &coef)//�˷�����ֹ�������ࣩ 
	{
		Tuple<T0, T1> outTuple((T0)(elemt_0 * coef), (T1)(elemt_1 * coef));
		return outTuple;
	}
	template <typename T_other>
	Tuple<T0, T1> operator/(const T_other &coef)//��������ֹ�������ࣩ 
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
cyclist<Tuple<T_0, T_1>> merge(cyclist<T_0> list_0, cyclist<T_1> list_1)//�����б�ƴ��ΪԪ���б� 
{
	cyclist<Tuple<T_0, T_1>> list_merge;
	int size = min(list_0.lsize, list_1.lsize);
	for(int id = 0; id < size; id += 1)
		list_merge.append({Tuple<T_0, T_1>(list_0[id], list_1[id])});
	return list_merge;
}


template <typename T_key, typename T_value>
class dict//�ֵ��࣬��������counter 
{
public:
	cyclist<T_key> key;
	cyclist<T_value> value;
	int dsize = 0;
	dict(){}
	dict(initializer_list<T_key> keys, initializer_list<T_value> values)//������ʼ���б���г�ʼ�� 
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
	dict(cyclist<T_key> keys, cyclist<T_value> values)//������ʼ���б���г�ʼ�� 
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
	T_value &operator[](T_key akey)//�����ʲ����ڵ�key�򱨴��˳� 
	{
		for(int id = 0; id < dsize; id += 1)
			if(key[id] == akey)
				return value[id];
		exit(1001);
	}
	bool set(T_key akey, T_value avalue)//���ü���Ӧ��ֵ������0�����������µļ�ֵ�ԣ�����1�� 
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
	bool del(T_key akey)//�����Ƿ�ɹ�ɾ��
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
	bool find(T_key akey){return key.find(akey) != -1;}//���Ҽ�ֵ�Ƿ��Ѵ��� 
	cyclist<T_key> get_keys(){return key;}//���ؼ����б� 
	cyclist<T_value> get_values(){return value;}//����ֵ���б� 
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
class counter//ͳ�Ƽ����� 
{
public:
	dict<T, int> pool;
	counter(){}
	counter(cyclist<T> names)//���ü����б�Ĭ��ȫ����0 
	{
		int length = names.size();
		for(int num = 0; num < length; num += 1)
			pool.set(names[num], 0);
	}
	int size(){return pool.size();}
	void add(T akey)//���ͳ���� 
	{
		if(pool.key.find(akey) == -1)
			pool.set(akey, 0);
	}
	void reset()//ȫ������ 
	{
		int length = pool.size();
		cyclist<T> keys = pool.get_keys();
		for(int id = 0; id < length; id += 1)
			pool.set(keys[id], 0);
	}
	void plus(T aname, int delta)//�������������б��в����ڸ�ֵ�����½���ֵ��ͳ�� 
	{
		this->add(aname);//��������Ч���������򴴽� 
		pool.set(aname, pool[aname] + delta);
	}
	void plus(cyclist<T> names, cyclist<int> values)//һ���Լ������ 
	{
		for(int id = 0; id < pool.size(); id += 1)
		{
			this->add(names[id]);
			pool.set(names[id], pool[names[id]] + values[id]);
		}
	}
	Tuple<cyclist<T>, int> maxlist()//ȡ���ֵ
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
	Tuple<cyclist<T>, int> minlist()//ȡ��Сֵ 
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
//class array_py//numpy���� 
//{
//public:
//	int dimension = 0;//ά�� 
//	cyclist<int> coordinates;//ÿ��ά���ĳ���
//	cyclist<long long int> prods;//�������飬����ϵ���� 
//	int value_num = 1;//�ܹ���Ԫ�ظ��� 
//	T* values = NULL;//Ԫ�ص�һԪ����
//	array_py(){}
//	array_py(int dimen, cyclist<int> coordinatelist)//��Сȷ�� 
//	{
//		dimension = dimen;
//		for(int axis = 0; axis < dimen; axis += 1)
//		{
//			coordinates.append({coordinatelist[axis]});
//			value_num = max(1, value_num * coordinatelist[axis]);
//			prods.append({(long long int)coordinates[axis]});//������������ø�������ﵽ���󳤶� 
//		}
//		values = new T[value_num];
//		prods[dimen - 1] = 1;
//		for(int axis = dimen - 2; axis >= 0; axis -= 1)
//			prods[axis] = coordinates[axis + 1] * prods[axis + 1];
//	}
//	array_py(int dimen, cyclist<int> coordinatelist, cyclist<T> valuelist)//��Сȷ����������䣬˳����ɹ㲥���� 
//	{
//		dimension = dimen;
//		for(int axis = 0; axis < dimen; axis += 1)
//		{
//			coordinates.append({coordinatelist[axis]});
//			value_num = max(1, value_num * coordinatelist[axis]);
//			prods.append({(long long int)coordinates[axis]});//������������ø�������ﵽ���󳤶� 
//		}
//		values = new T[value_num];
//		for(int id = 0; id < value_num; id += 1)
//			values[id] = valuelist[id];
//		prods[dimen - 1] = 1;
//		for(int axis = dimen - 2; axis >= 0; axis -= 1)
//			prods[axis] = coordinates[axis + 1] * prods[axis + 1];
//	}
//	~array_py(){delete[] values;}
//	T &operator[](cyclist<int> subscripts)//Խ����ʽ�ѭ�����±��0��ʼ��Ĭ�����ȱʡ���������Ϊ0����ķ�����Ч 
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


int** product(initializer_list<int> axis)//�ѿ����������ɶ�ά���飬ÿһ�ж���һ���ѿ�����Ԫ�� 
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
string : Ss//����stringͨ�� 
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

