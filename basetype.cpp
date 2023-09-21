template <typename T>
T absolute(T input){return input < (T)(0) ? -input : input;}
template <typename T>
T gcd(T input_1, T input_2)
{
	input_1 = absolute<T>(absolute);
	input_2 = absolute<T>(absolute);
	return input_2 == (T)(0) ? input_1 : gcd(input_2, input_1 % input_2);
}
long long int toll(string input)
{
	long long int sum = 0;
	int length = input.size();
	for(int chara = 0; chara < length; chara += 1)
		sum = sum * 10 + input[chara] - '0';
	return sum;
}


//以下是对高精度的支持 
const int MAX_NUMBER_LENGTH = 9;//安全起见，每一位long long int存放9位10进制数
const long long int CARRY = 1000000000;//和MAX_NUMBER_LENGTH匹配 
class p_frac;
string full(int length, char chara);
class p_int//高精度整数 
{
public:
	short sign = 1;//1:>0, 0:=0, -1:<0
	cyclist<long long int> pin;//pin[0]存储最低位 
	p_int(){sign = 0; pin.append({0});}
	p_int(int input)
	{
		sign = (input == 0 ? 0 : (input > 0 ? 1 : -1));
		input = absolute<int>(input);
		if(input >= CARRY) pin.append({input % CARRY, input / CARRY});
		else pin.append({input});
	}
	p_int(long long int input)
	{
		sign = (input == 0 ? 0 : (input > 0 ? 1 : -1));
		input = absolute<long long int>(input);
		if(input / CARRY >= CARRY) pin.append({input % CARRY, (input / CARRY) % CARRY, input / (CARRY * CARRY)});
		else if(input >= CARRY) pin.append({input % CARRY, input / CARRY});
		else pin.append({input});
	}
	p_int(string input)
	{
		int length = input.size();
		if(length == 0){sign = 0; pin.append({0});}
		else if(length == 1)
		{
			if(input[0] == '-'){sign = -1; pin.append({1});}
			else if(input[0] >= '0' && input[0] <= '9'){sign = (input[0] != '0'); pin.append({input[0] - '0'});}
			else exit(1010);
		}
		else
		{
			if(input[0] == '-'){sign = -1; input = input.substr(1, input.size() - 1);}
			for(int chara = 0; chara < input.size(); chara += 1)
				if(input[chara] < '0' || input[chara] > '9') exit(1010);
			for(; ; )
			{
				if(input.size() > 9){pin.append({toll(input.substr(input.size() - 9, 9))}); input = input.substr(0, input.size() - 9);}
				else{pin.append({toll(input)}); break;}
			}
		}
	}
	p_int(const p_int &apint)
	{
		pin = apint.pin;
		sign = apint.sign;
	}
	void set(int input)
	{
		sign = (input == 0 ? 0 : (input > 0 ? 1 : -1));
		input = absolute<int>(input);
		if(input >= CARRY)
			pin.append({input % CARRY, input / CARRY});
		else
			pin.append({input});
	}
	void set(long long int input)
	{
		sign = (input == 0 ? 0 : (input > 0 ? 1 : -1));
		input = absolute<long long int>(input);
		if(input / CARRY >= CARRY)
			pin.append({input % CARRY, (input / CARRY) % CARRY, input / (CARRY * CARRY)});
		else if(input >= CARRY)
			pin.append({input % CARRY, input / CARRY});
		else
			pin.append({input});
	}
	void set(p_int input)
	{
		sign = input.sign;
		pin.empty();
		pin = input.pin;
	}
	void push(int pows)//进行位移，移动一位相等于乘以10 ^ MAX_NUMBER_LENGTH = CARRY
	{
		cyclist<long long int> newpin;
		for(int id = 0; id < pows; id += 1)
			newpin.append({0});
		newpin.extend(pin);
		pin.empty();
		pin = newpin;
	}
	int size()//长度 
	{
		return this->tostring().size();
	}
	string tostring()
	{
		string out = "";
		if(sign == 0)
			return "0";
		if(sign == -1)
			out = "-";
		int length = pin.size();
		int sublength = 0;
		out = out + to_string(pin[length - 1]);
		for(int id = length - 2; id >= 0; id -= 1)
		{
			sublength = to_string(pin[id]).size();
			out = out + full(MAX_NUMBER_LENGTH - sublength, '0');
			out = out + to_string(pin[id]);
		}
		return out;
	}
	void operator=(const p_int &apint)//赋值 
	{
		pin = apint.pin;
		sign = apint.sign;
	}
	void operator=(const string &apint)//赋值
	{
		string input = apint;
		pin.empty();
		sign = 1;
		int length = input.size();
		if(length == 0){sign = 0; pin.append({0});}
		else if(length == 1)
		{
			if(input[0] == '-'){sign = -1; pin.append({1});}
			else if(input[0] >= '0' && input[0] <= '9'){sign = (input[0] != '0'); pin.append({input[0] - '0'});}
			else exit(1010);
		}
		else
		{
			if(input[0] == '-'){sign = -1; input = input.substr(1, input.size() - 1);}
			for(int chara = 0; chara < input.size(); chara += 1)
				if(input[chara] < '0' || input[chara] > '9') exit(1010);
			for(; ; )
			{
				if(input.size() > 9){pin.append({toll(input.substr(input.size() - 9, 9))}); input = input.substr(0, input.size() - 9);}
				else{pin.append({toll(input)}); break;}
			}
		}
	}
	p_int operator+(const p_int &apint)//加法
	{
		p_int trans = apint;
		if(sign == 0)
			return trans;
		if(trans.sign == 0)
			return *this;
		if(*this == -trans)//保证结果非0，减少接下来的讨论 
			return p_int(0);
		if(pin.size() < trans.pin.size())
			return trans + *this;
		if(sign == -1)
			return -((-*this) + (-trans));
		//此时保证*this为正，*this不短于trans 
		int length_1 = pin.size();
		int length_2 = trans.pin.size();
		if(*this < -trans)
			return -((-trans) + (-*this));
		//此时保证*this为正，*this不短于trans，且结果为正
		p_int outpint = *this;
		for(int id = 0; id < length_1; id += 1)
			outpint.pin[id] = pin[id] + (id < length_2 ? trans.sign * trans.pin[id] : 0);
		long long int subtr;
		for(int id = 1; id < length_1; id += 1)
			if(outpint.pin[id - 1] < 0)
			{
				subtr = (absolute<long long int>(outpint.pin[id - 1]) - 1) / CARRY + 1;
				outpint.pin[id] = outpint.pin[id] - subtr;
				outpint.pin[id - 1] = outpint.pin[id - 1] + subtr * CARRY;
			}
			else if(outpint.pin[id - 1] >= CARRY)
			{
				outpint.pin[id] = outpint.pin[id] + outpint.pin[id - 1] / CARRY;
				outpint.pin[id - 1] = outpint.pin[id - 1] % CARRY;
			}
		for(int id = outpint.pin.size() - 1; id >= 0; id -= 1)
			if(outpint.pin[id] == 0) outpint.pin.del(id);
		return outpint;
	}
	p_int operator-(const p_int &apint)//减法
	{
		p_int trans = apint;
		return *this + (-trans);
	}
	p_int operator-()//负号 
	{
		p_int outpint = *this;
		outpint.sign = -outpint.sign;
		return outpint;
	}
	p_int operator*(const p_int &apint)//乘法（TODO 
	{
		/*if(sign == 0 || apint.sign == 0)
			return (p_int)(0);
		p_int pint_1 = *this, pint_2 = apint, outpint;
		outpint.sign = pint_1.sign * pint_2.sign;
		int length_1 = pint_1
		return outpint;*/
	}
	p_frac operator/(const p_int &apint);//在分数后面定义
	p_int operator%(const p_int &apint)//取模 
	{
		static p_int base = *this;
		p_int mod = apint;
		int length_1 = base.pin.size();
		int length_2 = mod.pin.size();
		p_int trans = mod;
		for(int delta = length_1 - length_2; delta > 0; delta -= 1)
		{
			trans = mod;
			trans.push(delta);
			cout<<base<<" "<<trans<<"\n";
			for(; base < 0; base = base + trans);
			for(; base > trans; base = base - trans);
			cout<<base<<" "<<trans<<"\n";
		}
		for(; base < 0; base = base + mod);
		for(; base >= mod; base = base - mod);
		return base;
	}
	bool operator==(const p_int &apint)
	{
		if(sign != apint.sign || pin.lsize != apint.pin.lsize)
			return 0;
		node<long long int>* pin_0 = pin.start;
		node<long long int>* pin_1 = apint.pin.start;
		int length = pin.lsize;
		for(int id = 0; id < length; id += 1)
		{
			if(pin_0->value != pin_1->value)
				return 0;
			pin_0 = pin_0->next;
			pin_1 = pin_1->next;
		}
		return 1;
	}
	bool operator<(const p_int &apint)
	{
		if(sign == 0)
			return (apint.sign == 1);
		p_int trans = apint;
		if(sign == -1)
			return ((-*this) > (-trans));
		if(trans.sign != 1)
			return 0;
		if(pin.size() != trans.pin.size())
			return (apint.pin.lsize > pin.lsize);
		//此时*this和apint都是整数且pin等长 
		int length = pin.size();
		for(int id = length - 1; id >= 0; id -= 1)
			if(pin[id] != trans.pin[id])
				return pin[id] < trans.pin[id];
		return 0;
	}
	bool operator<=(const p_int &apint){return (*this < apint || *this == apint);}
	bool operator>(const p_int &apint){return !(*this <= apint);}
	bool operator>=(const p_int &apint){return !(*this < apint);}
	bool operator!=(const p_int &apint){return !(*this == apint);}
	friend ostream &operator<<(ostream &output, const p_int &apint)
	{
		p_int trans = apint;
		if(trans.sign == 0)
		{
			output<<0;
			return output;
		}
		if(trans.sign == -1)
			output<<"-";
		int length = trans.pin.size();
		int sublength = 0;
		output<<trans.pin[length - 1];
		for(int id = length - 2; id >= 0; id -= 1)
		{
			sublength = to_string(trans.pin[id]).size();
			for(int num = 0; num < MAX_NUMBER_LENGTH - sublength; num += 1)
				output<<0;
			output<<trans.pin[id];
		}
		return output;
	}
};


class pfrac//高精度分数 
{
	p_int upper;//分子 
	p_int lower;//分母 
};

class root//高精度根号
{
	
};
