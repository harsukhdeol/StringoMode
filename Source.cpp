#include <conio.h>
#include <fstream>

namespace cheetos 
{


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
		for (char c = _getch(); c != 13 && buff < pEnd; c = _getch(), buff++)//while c != enter , add the char to the buffer and increase its size
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
	void InttoString(int val, char* buff, int size)
	{
		char* const pStart = buff;
		char* const pEnd = buff + size - 1;
		for (; val > 0 && buff < pEnd; val /= 10, buff++)
		{
			*buff = '0' + val % 10;
		}
		*buff = 0;
		StringRev(pStart);
	}

	int Sum(int nth, int i, int number1, int number2)
	{
		if (i >= nth) {
			if (nth % 2) {

				return number1;
			}
			else {
				return number2;
			}
		}
		else
		{
			Sum(nth, i += 2, number1 + number2, number1 + number2 + number2);
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

}
	int main() {
		//std::ifstream in("derp.txt");

		//if (!in)//check if file is open  before doing anything else
		//{
		//	cheetos::print("Failed to open file!!");
		//	while (!_kbhit());

		//	return -1;
		//}
		//in.seekg(0, std::ios::end); //get last char in file
		//const int length = in.tellg(); //get abs pos of get pointer of file

		//cheetos::print("File size: "); //prints out file size in bytes
		//char buffer[255];
		//cheetos::InttoString(length, buffer, 255);
		//cheetos::print(buffer);
		//in.seekg(0, std::ios::beg);
		//cheetos::print("\n");

		//for (char c = in.get(); in.good(); c = in.get())		// get char, check if its not -1, then keep value
		//{
		//	_putch(c);
		//}
			/*if (in.bad())
		{
			cheetos::print("\nyou messed up bro");
		}
		else if (in.eof())
		{
			cheetos::print("\nreached end of file");
		}
		else {
			cheetos::print("\n another error???");
		}*/

		
		//std::ofstream out("data.dat");
		//out.write(reinterpret_cast<const char*>(&myInt), sizeof(myInt));
	
		std::ifstream in("data.dat", std::ios::binary);
		int data;
		in.read(reinterpret_cast<char*>(&data), sizeof(int));// pass interpreted char buffer to in

		char buffer[256];
		cheetos::InttoString(data,buffer, 256);
		cheetos::print(buffer);// print binary data back

		while (!_kbhit());
		return 0;
	}