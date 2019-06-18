#include "wav.h"


string _WAV::read(string name)
{
	ifstream in;
	in.open(name, std::ios::in | std::ios::binary);
	if (!in.is_open()) return "Файл не найден\n";

	readHead(in);

	if (WH.bitsPerSample != 16) return "размер семпла не равен 2 байт\n";
	if (WH.subchunk2Size >1e7) return "файл сильно большой\n";
	if (WH.audioFormat != 1) return "Файл использует сжатие\n";

	readData(in);
	
	in.close();
	return "Успешное открытие\n";
}

void _WAV::readHead(ifstream& in)
{
	in.read((char*)& WH, sizeof(WH));
}

void _WAV::readData(ifstream& in)
{
	data.resize(WH.subchunk2Size/ 2); //Так как стерео
	in.read((char*) &(*data.begin()), WH.subchunk2Size);
	
}

void _WAV::add(string name)
{
	ifstream in;
	in.open(name, std::ios::in | std::ios::binary);
	_WAV dop;
	dop.read(name);

	data.insert(
		data.end(),
		std::make_move_iterator(dop.data.begin()),
		std::make_move_iterator(dop.data.end())
	);

	if (WH.subchunk2Size == 0)
	{
		WH = dop.WH;
	}
	else
	{
		WH.subchunk2Size += dop.WH.subchunk2Size;
	}
}

void _WAV::writeInWav(string name)
{
	ofstream out;
	out.open(name, ios::out | ios::binary);

	out.write((char*)& WH, sizeof(WH));
	out.write((char*) &(*data.begin()), WH.subchunk2Size);
}

void _WAV::clear()
{
	this->WH.subchunk2Size = 0;
	data.clear();
}


void _WAV::fullData()
{
	vector<short int> buffer(22);
	memcpy(&(*buffer.begin()), (short int*)& WH, sizeof(WH));

	buffer.insert(
		buffer.end(),
		std::make_move_iterator(data.begin()),
		std::make_move_iterator(data.end())
	);

	data = buffer;
}