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
	void output()//�������Ҫ����T������<< 
	{
		cout<<"[";
		node<T>* pin = start;
		for(int num = 0; num < lsize; num += 1)
		{
			cout<<(pin->value);
			if(num < lsize - 1)
				cout<<", ";
			pin = pin->next;
		}
		cout<<"]";
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


template <typename T_key, typename T_value>
class dict//�ֵ��� 
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
	bool del(T_value avalue)//�����Ƿ�ɹ�ɾ��
	{
		bool* pin = new bool[dsize];
		int dels = 0;
		for(int id = 0; id < dsize; id += 1)
		{
			pin[id] = (avalue == value[id]);
			dels += 1;
		}
		for(int id = dsize - 1; id >= 0; id -= 1)
			if(pin[id])
			{
				key.del(id);
				value.del(id);
			}
		dsize -= dels;
		return dels;
	}
	bool find(T_key akey){return key.find(akey) != -1;}//���Ҽ�ֵ�Ƿ��Ѵ��� 
	cyclist<T_key> get_keys(){return key;}//���ؼ����б� 
	cyclist<T_value> get_values(){return value;}//����ֵ���б� 
	void check()//����ֵ�����м�ֵ�ԣ���ҪT_key��T_value��������<<
	{
		cout<<"{";
		for(int id = 0; id < dsize; id += 1)
		{
			cout<<key[id]<<": "<<value[id];
			if(id < dsize - 1)
				cout<<", ";
		}
		cout<<"}";
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

