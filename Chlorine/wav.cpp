#include "wav.h"


string _WAV::read(string name)
{
	ifstream in;
	in.open(name, std::ios::in | std::ios::binary);
	if (!in.is_open()) return "Файл не найден\n";

	readHead(in);

	if (size_simple != 2) return "размер семпла не равен 2 байт\n";
	if (dimension>1e7) return "файл сильно большой\n";
	if (WH.audioFormat != 1) return "Файл использует сжатие\n";

	readData(in);
	
	in.close();
	return "Успешное открытие\n";
}

void _WAV::readHead(ifstream& in)
{
	in.read((char*)& WH, sizeof(WH));

	size_simple = WH.bitsPerSample / 8;
	dimension = WH.subchunk2Size / WH.blockAlign;
	
}

void _WAV::readData(ifstream& in)
{
	int i;
	//short a, b, c;
	//bool is_ext;

	one_simple.resize(WH.blockAlign);
	//ext.clear();

	first_treak.resize(dimension);
	second_treak.resize(dimension);

	for (i = 0; i < dimension; i++)
	{
		in.read(&(*one_simple.begin()), WH.blockAlign);
		first_treak[i] = one_simple[0];
		second_treak[i] = one_simple[1];
	}
		//Проверяем только первый канал передачи
		//c = one_simple[1] * 256 + unsigned char(one_simple[0]);
		//if (i == 0) {a = c; continue;}
		//if (i == 1) {b = c; continue; }
		//is_ext = ((a > b) && (c > b)); //минимум
		//is_ext = is_ext || ((a < b) && (c < b)); //максимум
		//a = b;
		//b = c;
		//if (b <= 0) continue; //Проверяем только фазу
		//if (is_ext) ext.push_back(b);
	
}

void _WAV::add(string name)
{
	ifstream in;
	in.open(name, std::ios::in | std::ios::binary);
	_WAV dop;
	dop.read(name);
	first_treak.insert(first_treak.end(), dop.first_treak.begin(), dop.first_treak.end());
	second_treak.insert(second_treak.end(), dop.second_treak.begin(), dop.second_treak.end());

	if (WH.subchunk2Size == 0)
	{
		WH = dop.WH;
	}
	else
	{
		WH.subchunk2Size += dop.WH.subchunk2Size;
	}
	dimension = WH.subchunk2Size / WH.blockAlign;
}

//size_t _WAV::getSize()
//{
//	return ext.size();
//}

//tuple<int, int> _WAV::getMiddle()
//{
//	if (ext.size() < 2) return std::make_tuple(0, 0);
//	size_t r = ext.size() / 2;
//
//	vector< size_t> sort_ext = ext;
//	sort(sort_ext.begin(), sort_ext.end());
//	return make_tuple(sort_ext[r - 1], sort_ext[r]);
//
//
//}

void _WAV::writeInWav(string name)
{
	size_t i;
	dimension = WH.subchunk2Size / WH.blockAlign;
	ofstream out;
	out.open(name, ios::out | ios::binary);

	out.write((char*)& WH, sizeof(WH));
	for (i = 0; i < dimension; i++)
	{
		out.write((char*)& (first_treak[i]), 1);
		out.write((char*)& (second_treak[i]), 1);
	}
}