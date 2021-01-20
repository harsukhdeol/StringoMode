#include <conio.h>

void print(const char* s)
{
	while (*s != 0)
	{
		_putch(*s);
		s++;
	}
}
void read(char* buff, int maxSize)//buffer = large array of unknown size
{
	const char* const pEnd = buff + maxSize - 1;
	for (char c = _getch(); c != 13 && buff<pEnd; c = _getch(), buff++)//while c != enter , add the char to the buffer and increase its size
	{
		_putch(c);
		*buff = c;
	}
	*buff = 0; // need to pass 0 to end printing string
}

int StringtoInt(const char* num)
{
	//scan to start point
	const char* p = num;
	while (*p >= '0' && *p <= '9') { p++; }
	//back up by 1 to get start point
	p--;
	int val = 0;
	int place = 1;
	while (p >= num) {
		val += (*p - '0') * place;
		p--;
		place *= 10;
	}
	return val;
}
void StringRev(char* pl)
{
	char* pr = pl;
	while (*pr != 0)
	{
		pr++;
	}
	pr--;

	while (pl < pr)
	{
		const char temp = *pl;
		*pl = *pr;
		*pr = temp;
		pl++;
		pr--;
	}
	
}
void InttoString(int val, char*buff, int size)
{
	 char* const pStart = buff;
	 char* const pEnd = buff + size-1;
	for (; val > 0 && buff<pEnd; val /= 10, buff++)
	{
		*buff = '0'+val % 10;
	}
	*buff = 0;
	StringRev(pStart);
}

int Sum(int nth, int i, int number1, int number2)
{
	if (i>= nth) {
		if (nth % 2) {

		return number1;
		}
		else {
			return number2;
		}
	}
	else
	{
		Sum(nth, i+=2, number1 + number2, number1 + number2 + number2);
	}
}
int fib(int n)
{
	if (n < 2) {
		return n;
	}
	else {
		return fib(n - 1) + fib(n - 2);
	}
}

int main() {

	//print("im a barbie girl/n"); //string evaluates to pointer, so pass pointer to fxn
	//char inbuf[50];
	//read(inbuf, 50);
	//print("/n You typed:/n");
	//print(inbuf);

	//print("How many Wildes? ");
	//char answer[5];
	//read(answer, 5);
	//const int count = StringtoInt(answer);
	//print("\n");
	//for (int i = 0; i < count; i++) {
	//	print("Wilde! ");
	//}

	print("Which Fibonacci num? ");
	char answer[5];
	read(answer, 5);
	const int count = StringtoInt(answer);
	print("\n");

	InttoString(fib(count),answer,5);
	print(answer);
	while (!_kbhit());
	return 0;
}