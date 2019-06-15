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
	data.resize(WH.subchunk2Size);
	in.read(&(*data.begin()), WH.subchunk2Size);
	
}

void _WAV::add(string name)
{
	ifstream in;
	in.open(name, std::ios::in | std::ios::binary);
	_WAV dop;
	dop.read(name);
	data.insert(data.end(), dop.data.begin(), dop.data.end());

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
	size_t i;

	ofstream out;
	out.open(name, ios::out | ios::binary);

	out.write((char*)& WH, sizeof(WH));
	out.write(&(*data.begin()), WH.subchunk2Size);
}

void _WAV::clear()
{
	this->WH.subchunk2Size = 0;
	data.clear();
}