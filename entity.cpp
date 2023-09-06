const int min_injur = 1;//�����˺� 
class buff//Ч����
{
public:
	int bufftype = 0;//1���� 2���� 3���� 4������ 5�������� 6Ѫ�� 7Ѫ������ 8���� 9���� 10���� 
	int plus_mult = 0;//1������ 2������ 3��ֵ�Ӽ�
	double value = 0;//��������ͳһ��������*(1+sigma)����������ֱ��*(value)����ֵ��ֱ��+value��
	int start_time = 0;//��ʼʱ�䣨0Ϊ������Ч����Ϊ0�����ٻغϺ���Ч�� 
	int duration = 0;//��Ч�غ��� 
	buff(){}
	buff(int btype, bool p_m, double val, int s_t, int dur)//��ʼ�� 
	{
		bufftype = btype;
		plus_mult = p_m;
		value = val;
		start_time = s_t;
		duration = dur;
	}
	buff(initializer_list<double> values)//��ʼ���б��ʼ��
	{
		int length = (int)min((double)values.size(), 5.0);
		auto* avalue = values.begin();
		double valuess[5] = {0, 0, 0, 0, 0};
		for(int num = 0; num < length; num += 1)
		{
			valuess[num] = *avalue;
			avalue++;
		}
		bufftype = (0 < (int)valuess[0] && (int)valuess[0] < 7) ? (int)valuess[0] : 0;
		plus_mult = (0 < (int)valuess[1] && (int)valuess[1] < 4) ? (int)valuess[1] : 0;
		value = valuess[2];
		start_time = (int)valuess[3];
		duration = (int)valuess[4];
	}
	bool update()//״̬���£�buff�����򷵻�1
	{
		if(start_time > 0)
		{
			start_time -= 1;
			return 0;
		}
		else if(duration > 0)
		{
			duration -= 1;
			return 0;
		}
		else
			return 1;
	}
	string check()//������buff
	{
		string out = "";
		switch(bufftype)
		{
			case 1:
				out += "attack:";
				break;
			case 2:
				out += "def-ph:";
				break;
			case 3:
				out += "res-ma:";
				break;
			case 4:
				out += "s-posi:";
				break;
			case 5:
				out += "s-rate";
				break;
			case 6:
				out += "health:";
				break;
			}
			switch(plus_mult)
			{
				case 1:
					out = out + "+" + to_string((int)(100 * value)) + "%";
					break;
				case 2:
					out = out + "*" + to_string((int)(100 * value)) + "%";
					break;
				case 3:
					if(value >= 0)
						out = out + "+" + to_string((int)value);
					else
						out = out + to_string((int)value);
					break;
			}
	}
	friend ostream &operator<<(ostream &output, buff &abuff)
	{
		output<<abuff.check();
		return output;
	}
	bool operator==(const buff &abuff)
	{
		return this->bufftype == abuff.bufftype && this->plus_mult == abuff.plus_mult && this->value == abuff.value;
	}
};
class buffpool
{
public:
	cyclist<buff> buffs;
	buffpool(){}
	buffpool(initializer_list<buff> buffes){buffs.append(buffes);}
	void update()//������� 
	{
		int length = buffs.size();
		bool* dels = new bool[length];
		for(int id = 0; id < length; id += 1)
			dels[id] = buffs[id].update();
		for(int id = length - 1; id >= 0; id -= 1)
			if(dels[id])
				buffs.del(id);
	}
	string check(int max_num)//��ʾ����buff������ǰ����max_num�� 
	{
		int length = min(max_num, buffs.size());
		string str = "";
		for(int id = 0; id < length; id += 1)
		{
			if(id > 0)
				str = str + "\n";
			str = str + buffs[id].check();
		}
		return str;
	}
	double addition(int buff_type, int plusmult)//����ĳһ���Ե�ĳһ�ӳ� 
	{
		double base = (buff_type == 2 ? 1 : 0);
		int buffnum = buffs.size();
		for(int id = 0; id < buffnum; id += 1)
			if(buffs[id].bufftype == buff_type && buffs[id].plus_mult == plusmult)
			{
				if(plusmult == 2)
					base *= buffs[id].value;
				else
					base += buffs[id].value;
			}
		return base;
	}
	double buffed_state(double base_value, int buff_type)//����ĳһ���Ե�ȫ���ӳ� 
	{
		return base_value * (1 + this->addition(buff_type, 1)) * this->addition(buff_type, 2) + this->addition(buff_type, 3);
	}
	int attack(int base_atk, double base_sph, double base_spr)//����һ�ι���
	{
		double atk = this->buffed_state(base_atk, 1);
		double sph = this->buffed_state(base_sph, 4);
		double spr = this->buffed_state(base_spr, 5);
		return max(0, (int)(atk * (rand() < sph ? spr : 1)));
	}
	int injur(int base_inj, int defense, double resistance, double reduceinj, double skiphit, int atk_type)//����һ���ܻ� 
	{
		double def = this->buffed_state(defense, 1);//����
		double res = this->buffed_state(resistance, 1);//����
		double red = this->buffed_state(reduceinj, 1);//����
		double skip = this->buffed_state(skiphit, 1);//���� 
	}
};
class states//���������� 
{
	int atk_type = 1;//��������(1:����, 2:����, 3:��ʵ) 
	int atk = 0;//������ 
	int def_ph = 0;//������� 
	double res_ma = 0;//�������� 
	double superhit = 0;//������ 
	double superhit_rate = 1;//�������� 
	int hp = 0;//Ѫ�� 
	int hp_max = 0;//Ѫ������
	int shield = 0;//���� 
	double skip = 0;//����
	double reduce = 0;//���� 
	states();
	states(int attack_type, int attack, int def, double res, double sph,\
			double spr, int hp, int hp_max, int shields, double skipp, double red);
	states(initializer_list<double> values);
	void set(int attack_type, int attack, int def, double res, double sph,\
			double spr, int hp, int hp_max, int shields, double skipp, double red);
	void set(initializer_list<double> values);
};
class entity//ʵ����
{
public:
	string name = "";//���� 
	states state();//״̬ 
	buffpool buffs;//buff 
	entity();
	void update();
	int attack();//���㹥��
	int injur();//�����ܻ� 
};

