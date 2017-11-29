#ifndef DATAMEMORY_H
#define DATAMEMORY_H
#include <systemc.h>
#include <fstream>
using namespace std;
#define instruction_length 6
class DataMemory: public sc_module
{
	public:
		sc_in< sc_uint<4> > dir_in;
		sc_out< sc_uint<instruction_length> >instr_out;
		SC_CTOR(DataMemory)
		{
			SC_METHOD(search);
			sensitive << dir_in;
			memoryFile.open("memoryFile.txt");
		}
		~InstrMemory()
		{
			memoryFile.close();
		}
	private:
		ifstream memoryFile;
		void search()
		{
			unsigned int dir;
			sc_uint<instruction_length> instr;
			char instrTmp[instruction_length];
			dir = dir_in.read();
			memoryFile.seekg(dir*(instruction_length+1), ios::beg);
			memoryFile.getline(instrTmp,instruction_length+1);
			for(int i=0; i < instruction_length;i++)
			{
				if (instrTmp[i] == '1')
				{
					instr[instruction_length-1-i] = 1;
				}
				else
				{
					instr[instruction_length-1-i] = 0;
				}
			}
			instr_out.write(instr);
		}
};
#endif