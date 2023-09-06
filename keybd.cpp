//"0"~"9", "a"("A")~"z"("Z"), "{f1}"~"{f12}", "enter", "alt", "tab", "shift", "esc"
int keybd_id(string str)//给特定按键对应编码 
{
	int value = 0;
	string trans = "";
	if(str.size() == 1)//a~z,0~9
	{
		if(str[0] >= 'a' && str[0] <= 'z')
			value = str[0] - 'a' + 65;
		else if(str[0] >= 'A' && str[0] <= 'Z')
			value = str[0] - 'A' + 65;
		else if(str[0] >= '0' && str[0] <= '9')
			value = str[0] - '0' + 48;//96也可，是小键盘 
	}
	else if((str.size() == 4 || str.size() == 5) && (str[1] == 'F' || str[1] == 'f') && str[2] <= '9' && str[2] >= '0')//f1~f12
	{
		trans = str.substr(2, str.size() - 2);
		for(int num = 0; ; num += 1)
			if(trans[num] <= '9' && trans[num] >= '0')
				value = value * 10 + trans[num] - '0';
			else
				break;
		value = value + 111;
	}
	else switch((str[1] - 'a') * 100 + (str[2] - 'a'))
	{
		case ('e' - 'a') * 100 + ('n' - 'a')://enter
			value = 13;
			break;
		case ('a' - 'a') * 100 + ('l' - 'a')://alt
			value = 18;
			break;
		case ('t' - 'a') * 100 + ('a' - 'a')://tab
			value = 9;
			break;
		case ('s' - 'a') * 100 + ('h' - 'a')://shift
			value = 16;
			break;
		case ('e' - 'a') * 100 + ('s' - 'a')://esc
			value = 27;
			break;
	}
	return value;
}
void press_down(string str)//按下某按键 
{
	keybd_event(keybd_id(str), 0, 0, 0);
}
void press_up(string str)//弹起某按键 
{
	keybd_event(keybd_id(str), 0, KEYEVENTF_KEYUP, 0);
}
void press(string str, int delay)//按下并弹起，以给定的延迟 
{
	press_down(str);
	Sleep(delay);
	press_up(str);
}
