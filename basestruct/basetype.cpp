template <typename T>
T absolute(T input){return input < (T)(0) ? -input : input;}//����ֵ 
template <typename T>
T gcd(T input_1, T input_2)//������ 
{
	input_1 = absolute<T>(input_1); input_2 = absolute<T>(input_2);
	return input_2 == (T)(0) ? input_1 : gcd(input_2, input_1 % input_2);
}
long long int toll(string input)//�ַ���תll 
{
	long long int sum = 0;
	int length = input.size();
	for(int chara = 0; chara < length; chara += 1)
		sum = sum * 10 + input[chara] - '0';
	return sum;
}
string string_zeros(int length)//���س���Ϊlength��ȫ0�� 
{
	string trans;
	if(length == 0) return "";
	if(length == 1) return "0";
	trans = string_zeros(length / 2);
	if(length % 2) return trans + trans + "0";
	else return trans + trans;
}


//�����ǶԸ߾��ȵ�֧�� 
const int MAX_NUMBER_LENGTH = 9;//��ȫ�����ÿһλlong long int���9λ10������
const long long int CARRY = 1000000000;//��MAX_NUMBER_LENGTHƥ�� 
class p_frac;
string full(int length, char chara);
class p_int//�߾������� 
{
public:
	short sign = 1;//1:>0, 0:=0, -1:<0
	cyclist<long long int> pin;//pin[0]�洢���λ
	//sign == 0��ʾ0��|sign| == 1��ʾһ�����֣���pin��Ϊ��ֵ��
	//sign == 3��ʾINFTY��pin[0]Ϊ0�����ţ�������pin[0]ͬ�ţ�
	//sign == 4��ʾuncertain��pin[0]Ϊ0�����ţ�������pin[0]ͬ�� 
	p_int(){sign = 0; pin.append({0});}
	p_int(int signal, int number)//��������ר�� 
	{
		sign = signal;
		pin.append({(long long int)number});
	}
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
	p_int(const p_int &apint){pin = apint.pin; sign = apint.sign;}
	static p_int INFTY(int sign)//p_int::INFTY(sign)�õ������sign��ʾ������sign==0��ʾ��ȷ�����ţ�sign == 3��ʾinfty
	{
		return p_int(3, (sign == 0 ? 0 : (sign > 0 ? 1 : -1)));
	}
	static p_int UNCERTAIN(int sign)//p_int::UNCERTAIN()�õ�����ʽ��sign��ʾ������sign==0��ʾ��ȷ�����ţ�sign == 4��ʾuncertain
	{
		return p_int(4, (sign == 0 ? 0 : (sign > 0 ? 1 : -1)));
	}
	void push(int pows)//����λ�ƣ��ƶ�һλ����ڳ���10 ^ MAX_NUMBER_LENGTH = CARRY
	{
		if(sign != 1 && sign != -1) return;
		//0 and infty and INFTY and UNCERTAIN
		cyclist<long long int> newpin;
		for(int id = 0; id < pows; id += 1)
			newpin.append({0});
		newpin.extend(pin); pin.empty(); pin = newpin;
	}
	int size(){return this->tostring().size();}//���� 
	string tostring()
	{
		if(sign == 3) return (pin[0] == 0 ? "pint_INF" : (pin[0] == 1 ? "(+)pint_INF" : "(-)pint_INF"));
		if(sign == 4) return (pin[0] == 0 ? "pint_???" : (pin[0] == 1 ? "(+)pint_???" : "(-)pint_???"));
		if(sign == 0) return "0";
		//sign == 0��ʾ0��|sign| == 1��ʾһ�����֣���pin��Ϊ��ֵ��
		//sign == 3��ʾINFTY��pin[0]Ϊ0�����ţ�������pin[0]ͬ�ţ�
		//sign == 4��ʾuncertain��pin[0]Ϊ0�����ţ�������pin[0]ͬ�� 
		//0 and INFTY and UNCERTAIN
		string out = "";
		if(sign == -1) out = "-";
		int length = pin.size();
		int sublength = 0;
		out = out + to_string(pin[length - 1]);
		for(int id = length - 2; id >= 0; id -= 1)
		{
			sublength = to_string(pin[id]).size();
			out = out + full(MAX_NUMBER_LENGTH - sublength, '0') + to_string(pin[id]);
		}
		return out;
	}
	void operator=(const p_int &apint){pin = apint.pin; sign = apint.sign;}//��ֵ
	void operator=(const int &apint){p_int trans(apint); *this = trans;}//��ֵ
	void operator=(const long long int &apint){p_int trans(apint); *this = trans;}//��ֵ
	void operator=(const string &apint){p_int trans(apint); *this = trans;}//��ֵ
	p_int operator+(const p_int &apint)//�ӷ�
	{
		p_int trans = apint;
		//sign == 0��ʾ0��|sign| == 1��ʾһ�����֣���pin��Ϊ��ֵ��
		//sign == 3��ʾINFTY��pin[0]Ϊ0�����ţ�������pin[0]ͬ�ţ�
		//sign == 4��ʾuncertain��pin[0]Ϊ0�����ţ�������pin[0]ͬ��
		if(sign == 0)       return trans;
		if(trans.sign == 0) return *this;
		//������0
		if(sign == 4 && trans.sign >= 3)                       return (pin[0] == trans.pin[0] ? *this : p_int::UNCERTAIN(0));
		if(sign >= 3 && trans.sign == 4)                       return (pin[0] == trans.pin[0] ? trans : p_int::UNCERTAIN(0));
		if(sign == 4 && (trans.sign == 1 || trans.sign == -1)) return (pin[0] == trans.sign ? *this : p_int::UNCERTAIN(0));
		if((sign == 1 || sign == -1) && trans.sign == 4)       return (sign == trans.pin[0] ? trans : p_int::UNCERTAIN(0));
		//����uncertain
		if(sign == 3 && trans.sign == 3) return (pin[0] == trans.pin[0] ? *this : p_int::UNCERTAIN(0));
		if(sign == 3 && trans.sign < 3)  return *this;
		if(sign < 3 && trans.sign == 3)  return trans;
		//����INF
		//0 and infty and INFTY and UNCERTAIN
		if(*this == -trans) return p_int(0);//��֤�����0�����ٽ����������� 
		if(pin.size() < trans.pin.size()) return trans + *this;
		if(sign == -1) return -((-*this) + (-trans));
		//��ʱ��֤*thisΪ����*this������trans 
		int length_1 = pin.size(), length_2 = trans.pin.size();
		if(*this < -trans) return -((-trans) + (-*this));
		//��ʱ��֤*thisΪ����*this������trans���ҽ��Ϊ��
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
			else break;
		return outpint;
	}
	p_int operator-(const p_int &apint){p_int trans = apint; return *this + (-trans);}//����
	p_int operator-()//���� 
	{
		p_int outpint = *this;
		//sign == 0��ʾ0��|sign| == 1��ʾһ�����֣���pin��Ϊ��ֵ��
		//sign == 3��ʾINFTY��pin[0]Ϊ0�����ţ�������pin[0]ͬ�ţ�
		//sign == 4��ʾuncertain��pin[0]Ϊ0�����ţ�������pin[0]ͬ��
		if(sign >= 3 || sign == 0) outpint.pin[0] = -outpint.pin[0];
		//0 and INFTY and UNCERTAIN
		if(sign <= 1) outpint.sign = -outpint.sign;
		return outpint;
	}
	p_int operator*(const p_int &apint)//�˷�
	{
		p_int pint_1 = *this, pint_2 = apint;
		int sign_1 = (pint_1.sign >= 3 ? pint_1.pin[0] : pint_1.sign);
		int sign_2 = (pint_2.sign >= 3 ? pint_2.pin[0] : pint_2.sign);
		//sign == 0��ʾ0��|sign| == 1��ʾһ�����֣���pin��Ϊ��ֵ��
		//sign == 3��ʾINFTY��pin[0]Ϊ0�����ţ�������pin[0]ͬ�ţ�
		//sign == 4��ʾuncertain��pin[0]Ϊ0�����ţ�������pin[0]ͬ��
		if(pint_1.sign == 0 || pint_2.sign == 0) return p_int(0);
		//������0
		if(pint_1.sign == 4 || pint_2.sign == 4) return p_int::UNCERTAIN(sign_1 * sign_2);
		//����uncertain
		if(pint_1.sign == 3 || pint_2.sign == 3) return p_int::INFTY(sign_1 * sign_2);
		//����INF
		//0 and infty and INFTY and UNCERTAIN
		int length_1 = pint_1.pin.size(), length_2 = pint_2.pin.size();
		if(length_2 < length_1) return pint_2 * pint_1;
		p_int outpint, trans;
		long long int coef = 0;
		for(int delta = 0; delta < length_1; delta += 1)
		{
			trans = pint_2;
			coef = pint_1.pin[delta];
			for(int id = 0; id < length_2; id += 1)
				trans.pin[id] *= coef;
			for(int id = 1; id < length_2; id += 1)
			{
				trans.pin[id] += trans.pin[id - 1] / CARRY;
				trans.pin[id - 1] %= CARRY;
			}
			if(trans.pin[length_2 - 1] >= CARRY){trans.pin.append({trans.pin[length_2 - 1] / CARRY}); trans.pin[length_2 - 1] %= CARRY;}
			trans.push(delta);
			outpint = outpint + trans;
		}
		outpint.sign = pint_1.sign * pint_2.sign;
		return outpint;
	}
	p_int operator/(const p_int &apint)//������������ 
	{
		p_int upper(*this), lower(apint);
		//sign == 0��ʾ0��|sign| == 1��ʾһ�����֣���pin��Ϊ��ֵ��
		//sign == 3��ʾINFTY��pin[0]Ϊ0�����ţ�������pin[0]ͬ�ţ�
		//sign == 4��ʾuncertain��pin[0]Ϊ0�����ţ�������pin[0]ͬ��
		if(lower.sign == 0) exit(1003);//0������Ϊ����
		if(upper.sign == 0) return p_int(0);
		//������0
		if(upper.sign == 4 || lower.sign == 4) return p_int::UNCERTAIN(sign_1 * sign_2);
		//����uncertain
		if(upper.sign == 3 && lower.sign == 3) return p_int::UNCERTAIN(sign_1 * sign_2);
		if(upper.sign == 3 && lower.sign != 3) return p_int::INFTY(sign_1 * sign_2);
		if(upper.sign != 3 && lower.sign == 3) return p_int(0);
		//����INF
		//0 and infty and INFTY and UNCERTAIN
		bool signal = (upper.sign * lower.sign);//����ķ���
		upper = absolute<p_int>(upper); lower = absolute<p_int>(lower);//ȡ����ֵ 
		if(upper < lower) return 0;
		int length_1 = upper.tostring().size(), length_2 = lower.tostring().size();//length_1 >= length_2
		if(length_1 <= length_2 + 2)
			for(int div = 0; ; div += 1)
				if(upper < lower) {p_int outpint = (signal ? -div : div); return outpint;}
				else upper = upper - lower;
		else
		{
			string delta = string_zeros(length_1 - length_2 - 2);
			p_int maxout = p_int("1" + delta) * (upper / p_int(lower.tostring() + delta));
			p_int outpint = maxout + (upper - lower * maxout) / lower;
			if(outpint != p_int(0)) outpint.sign = (signal ? -1 : 1);
			return outpint;
		}
	}
	p_int operator%(const p_int &apint)//ȡģ
	{
		p_int upper(*this), lower(apint);
		//sign == 0��ʾ0��|sign| == 1��ʾһ�����֣���pin��Ϊ��ֵ��
		//sign == 3��ʾINFTY��pin[0]Ϊ0�����ţ�������pin[0]ͬ�ţ�
		//sign == 4��ʾuncertain��pin[0]Ϊ0�����ţ�������pin[0]ͬ��
		if(lower.sign == 0) exit(1003);//0������Ϊ����
		if(upper.sign == 0) return p_int(0);
		//������0
		if(upper.sign == 4 || lower.sign == 4) return p_int::UNCERTAIN(sign_1 * sign_2);
		//����uncertain
		if(upper.sign == 3) return p_int::UNCERTAIN(sign_1 * sign_2);
		if(upper.sign != 3 && lower.sign == 3) return upper;
		//����INF
		//0 and INFTY and UNCERTAIN
		p_int outpint = *this - (*this / lower) * lower;
		for(; outpint < (p_int)(0); outpint = outpint + lower);
		for(; outpint >= mod; outpint = outpint - lower);
		return outpint;
	}
	bool operator==(const p_int &apint)
	{
		p_int pint = apint;
		if(pint.sign != sign) return 0;
		//sign == 0��ʾ0��|sign| == 1��ʾһ�����֣���pin��Ϊ��ֵ��
		//sign == 3��ʾINFTY��pin[0]Ϊ0�����ţ�������pin[0]ͬ�ţ�
		//sign == 4��ʾuncertain��pin[0]Ϊ0�����ţ�������pin[0]ͬ��
		if(sign == 4 || sign == 3) return 0;
		//����uncertain
		//����INF
		if(sign == 0) return 1;
		//������0
		//0 and INFTY and UNCERTAIN
		return pint.tostring() == this->tostring();
	}
	bool operator!=(const p_int &apint){return !(*this == apint);}
	bool operator<(const p_int &apint)
	{
		p_int trans = apint;
		//sign == 0��ʾ0��|sign| == 1��ʾһ�����֣���pin��Ϊ��ֵ��
		//sign == 3��ʾINFTY��pin[0]Ϊ0�����ţ�������pin[0]ͬ�ţ�
		//sign == 4��ʾuncertain��pin[0]Ϊ0�����ţ�������pin[0]ͬ��
		if(sign == 4 || trans.sign == 4) return 0;
		//����uncertain
		if(sign == 3)
		//����INF
		//������0
		//0 and INFTY and UNCERTAIN
		//��ʱ*this��apint����������pin�ȳ� 
		int length = pin.size();
		for(int id = length - 1; id >= 0; id -= 1)
			if(pin[id] != trans.pin[id]) return pin[id] < trans.pin[id];
		return 0;
	}
	bool operator>(const p_int &apint){return !(*this <= apint);}
	bool operator<=(const p_int &apint){return (*this < apint || *this == apint);}
	bool operator>=(const p_int &apint){return !(*this < apint);}
	friend ostream &operator<<(ostream &output, const p_int &apint){p_int trans = apint; output<<trans.tostring(); return output;}
};


class p_frac//�߾��ȷ��� 
{
public:
	p_int upper;//���� 
	p_int lower;//��ĸ
	p_frac(){upper = 0; lower = 1;}
	template <typename T1, typename T2>
	p_frac(T1 upp, T2 low)
	{
		upper = p_int(upp);
		lower = p_int(low);
		//if(upper == p_int(0) && p_int)
	}
	template <typename T>
	p_frac(T apint)
	{
		upper = p_int(apint);
		lower = 1;
	}
};
//const p_frac PFRAC_NOTSURE(0, 0), PFRAC_POSINFTY(1, 0), PFRAC_NEGINFTY(-1, 0), PFRAC_POSZERO(0, 1), PFRAC_NEGZERO(0, -1);


class p_double//�߾�����������ע���߾������������е�ʱҪ�����⣩
{
	p_frac value;//����ֵ
	p_int delta;//�������
};
