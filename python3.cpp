template <typename T>
class tostr
{
public:
	static string tostring(int anum){return to_string(anum);}
	static string tostring(string astr){return "\"" + astr + "\"";}
	static string tostring(char achar)
	{
		string str = "";
		str = achar;
		return "\'" + str + "\'";
	}
	static string tostring(T* aT){T at = *aT; return at.output();}
};



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
	cyclist(cyclist &alist)//�������캯����Ҫ��alist�ǿ� 
	{
		lsize = alist.lsize;
		start = new node<T>;
		start->value = alist[0];
		start->before = start;
		start->next = start;
		node<T>* pin = start;
		for(int num = 1; num < lsize; num += 1)
		{
			pin->next = new node<T>;
			pin->next->before = pin;
			pin = pin->next;
			pin->value = alist[num];
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
	string output()//���
	{
		string outs = "[";
		node<T>* pin = start;
		for(int num = 0; num < lsize; num += 1)
		{
			outs = outs + tostr<T>::tostring(&(pin->value));
			if(num < lsize - 1)
				outs = outs + ", ";
			pin = pin->next;
		}
		return outs + "]";
	}
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
	Tuple(Tuple<T0, T1> &atuple)
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
	friend ostream &operator<<(ostream &output, const Tuple &atuple)
	{
		output<<"("<<atuple.elemt_0<<", "<<atuple.elemt_1<<")";
		return output;
	}
	Tuple<T1, T0> swap(){return Tuple(elemt_1, elemt_0);}
	string output()
	{
		string outs = "(";
		outs = outs + tostr<T0>::tostring(&elemt_0);
		outs = outs + ", ";
		outs = outs + tostr<T1>::tostring(&elemt_1);
		return outs + ")";
	}
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
	string output()//����ֵ�����м�ֵ�ԣ���ҪT_key��T_value��������<<
	{
		string outs = "{";
		for(int id = 0; id < dsize; id += 1)
		{
			outs = outs + tostr<T_key>::tostring(&key[id]) + ": " + tostr<T_value>::tostring(&value[id]);
			if(id < dsize - 1)
				outs = outs + ", ";
		}
		return outs + "}";
	}
	cyclist<Tuple<T_key, T_value>> items()
	{
		cyclist<Tuple<T_key, T_value>> item;
		for(int id = 0; id < dsize; id += 1)
			item.append({Tuple<T_key, T_value>(key[id], value[id])});
		return item;
	}
};
template <typename T>
class counter//ͳ�Ƽ����� 
{
	dict<T, int> pool;
	counter(){}
	counter(cyclist<T> names)//���ü����б�Ĭ��ȫ����0 
	{
		auto* pin = names.start;
		int length = names.size();
		for(int num = 0; num < length; num += 1)
		{
			pool.set(*pin, 0);
			pin++;
		}
	}
	void set_zero()//ȫ������ 
	{
		int length = pool.size();
		cyclist<T> keys = pool.get_keys();
		for(int id = 0; id < length; id += 1)
			pool.set(keys[id], 0);
	}
	void output(){pool.output();}
	void plus(T aname){pool.set(aname, pool[aname] + 1);}//�������������б��в����ڸ�ֵ���򱨴��˳� 
	void plus(cyclist<T> names)//һ���Լ������ 
	{
		int length = names.size();
		for(int id = 0; id < length; id += 1)
			pool.set(names[id], pool[names[id]] + 1);
	}
};


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

