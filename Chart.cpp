#include <fstream>
#include <conio.h>


void print(const char* s)
{
	while (*s != 0)
	{
		_putch(*s);
		s++;
	}
}
void printFixed(const char* s, int w)
{
	int n = 0;
	while (*s != 0)
	{
		_putch(*s);
		n++;
		s++;
	}
	while (n < w)
	{
		_putch(' ');
		n++;
	}
}

void StrCopy(const char* source, char* dest, int max)
{
	int n = 0;
	while (*source != 0 && n<max-1)
	{
		*dest = *source;
		n++;
		source++;
		dest++;
	}
	*dest = 0;
}

class Database
{
public:
	void Load(const char* fileName) {
		std::ifstream in(fileName, std::ios::binary);
		in.read(reinterpret_cast< char*>(&curNumEntries), sizeof(curNumEntries));
		for (int i = 0; i < curNumEntries; i++)
		{
			entries[i].Deserialize(in);
		}
	}
	void Save(const char* fileName) const {
		std::ofstream out(fileName, std::ios::binary);
		out.write(reinterpret_cast<const char*>(&curNumEntries), sizeof(curNumEntries));
		for (int i = 0; i < curNumEntries; i++)
		{
			entries[i].Serialize(out);
		}
	}
	void Print() const {
		for (int i = 0; i < curNumEntries; i++)
		{
			entries[i].Print();
		}
	}
	void Add(const char* name, int val)
	{
		if (curNumEntries < maxEntries)
		{

			entries[curNumEntries++] = { name,val };
		}
	}
private:
	class Entry {
		public:
			Entry() = default;
			Entry(const char* name, int val):
				val(val)
			{
				StrCopy(name, this->name, sizeof(this->name));
			}
			void Print()const
			{
				printFixed(name, nameBufferSize - 1);
				_putch('|');
				for (int i = 0; i < val; i++)
				{
					_putch('=');
				}
				_putch('\n');

			}
			void Serialize(std::ostream& out) const // pass reference to out stream
			{
				out.write(name, sizeof(name));
				out.write(reinterpret_cast<const char*>(&val), sizeof(val));
			}
			void Deserialize(std::ifstream& in)
			{
				in.read(name, sizeof(name));
				in.read(reinterpret_cast<char*>(&val), sizeof(val));
			}
		private:
			static constexpr int nameBufferSize = 10;
			char name[nameBufferSize];
			int val;
	};

private:
	static constexpr int maxEntries = 16;
	Entry entries[maxEntries];
	int curNumEntries = 0;
};
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

void doDb()
{
	bool quit = false;
	Database* db = new Database; //create dynamic heap

	char val[256];
	char val2[256];

	while (!quit) {
	print("(l)oad (s)ave (a)dd (q)uit (p)rint? \n");
	char choice = _getch();
		switch (choice)
		{
		case 'l':///load file
			print("\nEnter file name: ");
			read(val, sizeof(val));
			db->Load(val);
			_putch('\n');
		
		break;
		case 's'://save file
			print("\nEnter file name: ");
			read(val, sizeof(val));
			db->Save(val);
			_putch('\n');
			break;
		case 'a':
			
			print("\nEnter Name: ");
			read(val, sizeof(val));
			print("\nEnter Value: ");
			read(val2, sizeof(val2));
			db->Add(val, StringtoInt(val2));
			_putch('\n');

			break;
		case 'q':
			quit = true;
			break;
		case 'p'://display graph
			print("\n         You got bars??\n");
			print("         ------------------\n");
			db->Print();
			break;
		}
	}
	delete db;// free memory
	while (!_kbhit());

}

int main()
{
	char buffer[256];
	print("Enter File Name: ");
	read(buffer, sizeof(buffer));
	std::ifstream wap(buffer);
	wap.seekg(0, std::ios::end);
	const int fileSize = wap.tellg();
	wap.seekg(0, std::ios::beg);
	char* wapString = new char[fileSize+1];//only use the size of file

	int i = 0;
	for (char c = wap.get(); wap.good(); c = wap.get())
	{
		wapString[i++] = c;
	}
	wapString[i] = 0;
	print("\n File Size: ");
	InttoString(i, buffer, sizeof(buffer));
	print(buffer);

	delete[] wapString; //delete arr of chars 
	

}