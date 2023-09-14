template <typename T>
T absolute(T input){return input < (T)(0) ? -input : input;}


//���ļ��ǶԸ߾��ȵ�֧�� 
const int MAX_NUMBER_LENGTH = 9;//��ȫ�����ÿһλlong long int���9λ10������
const long long int CARRY = 1000000000;//��MAX_NUMBER_LENGTHƥ�� 
class pint//�߾������� 
{
public:
	short sign = 1;//1:>0, 0:=0, -1:<0
	cyclist<long long int> pin;
	pint()
	{
		sign = 0;
		pin.apppend({0});
	}
	pint(int input)
	{
		sign = (input == 0 ? 0 : (input > 0 ? 1 : -1));
		input = absolute<int>(input);
		if(input >= CARRY)
			pin.append({input / CARRY, input % CARRY});
		else
			pin.apppend({input});
	}
	pint(long long int input)
	{
		sign = (input == 0 ? 0 : (input > 0 ? 1 : -1));
		input = absolute<long long int>(input);
		if(input / CARRY >= CARRY)
			pin.append({input / (CARRY * CARRY), (input / CARRY) % CARRY, input % CARRY});
		else if(input >= CARRY)
			pin.append({input / CARRY, input % CARRY});
		else
			pin.apppend({input});
	}
	pint(const pint &apint)
	{
		pin = apint.pin;
		sign = apint.sign;
	}
	void set(int input)
	{
		sign = (input == 0 ? 0 : (input > 0 ? 1 : -1));
		input = absolute<int>(input);
		if(input >= CARRY)
			pin.append({input / CARRY, input % CARRY});
		else
			pin.apppend({input});
	}
	void set(long long int input)
	{
		sign = (input == 0 ? 0 : (input > 0 ? 1 : -1));
		input = absolute<long long int>(input);
		if(input / CARRY >= CARRY)
			pin.append({input / (CARRY * CARRY), (input / CARRY) % CARRY, input % CARRY});
		else if(input >= CARRY)
			pin.append({input / CARRY, input % CARRY});
		else
			pin.apppend({input});
	}
	void set(pint input)
	{
		sign = input.sign;
		pin.empty();
		pin = input.pin;
	}
	void operator=(const pint &apint)//��ֵ 
	{
		pin = apint.pin;
		sign = apint.sign;
	}
	pint operator+(const pint &apint)//�ӷ�(TODO
	{
		if(this->sign == 0)
			return apint;
		if(apint.sign == 0)
			return *this;
		if(this->sign == -1)
			return -((-*this) + (-apint));
		int length_1 = pin.size();
		int length_2 = apint.pin.size();
		pint outpint = *this;
		if(apint.sign == -1)
		{
			
		}
		else
		{
			
		}
		return apint;
	}
	pint operator-(const pint &apint)//���� 
	{
		return *this + (-apint);
	}
	pint operator-()//���� 
	{
		pint outpint = *this;
		outpint.sign = -outpint.sign;
		return outpint;
	}
	pint operator*(const pint &apint)//�˷���TODO 
	{
		if(sign == 0 || apint.sign == 0)
			return (pint)(0);
		pint outpint;
		outpint.sign = sign * apint.sign;
		return outpint;
	}
	bool operator==(const pint &apint)
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
	bool operator<(const pint &apint)
	{
		if(sign == 0)
			return (apint.sign == 1);
		if(sign == -1)
			return (-*this > -apint);
		if(apint.sign != 1)
			return 0;
		if(pin.lsize != apint.pin.lsize)
			return (apint.pin.lsize > pin.lsize);
		node<long long int>* pin_0 = pin.start;
		node<long long int>* pin_1 = apint.pin.start;
		int length = pin.lsize;
		for(int id = 0; id < length; id += 1)
		{
			if(pin_0->value > pin_1->value)
				return 0;
			if(pin_0->value < pin_1->value)
				return 1;
			pin_0 = pin_0->next;
			pin_1 = pin_1->next;
		}
		return 0;
	}
	bool operator<=(const pint &apint){return (*this < apint || *this == apint);}
	bool operator>(const pint &apint){return !(*this <= apint);}
	bool operator>=(const pint &apint){return !(*this < apint);}
	bool operator!=(const pint &apint){return !(*this == apint);}
};


class pfraction//�߾��ȷ��� 
{
	pint upper;//���� 
	pint lower;//��ĸ 
};

class root//�߾��ȸ���
{
	
};
