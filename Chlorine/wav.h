#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

class _WAV
{
public:
	string read(string name);
	void readHead(ifstream& in);
	void readData(ifstream& in);
	void fullData();
	void clear();

	vector<short int> data;

	void add(string name);
	void writeInWav(string name);
	
	struct WAV_Head
	{
		char chunkId[4]; // "RIFF" 
		unsigned long chunkSize;// 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
		char format[4];//"WAVE"
		char subchunk1Id[4];//"fmt"
		unsigned long subchunk1Size; // = 16
		unsigned short audioFormat; // PCM = 1  �������� �����������).
		unsigned short numChannels; // ���� = 1, ������ = 2
		unsigned long sampleRate;// ������� �������������.
		unsigned long byteRate; //�� �������
		unsigned short blockAlign;// ���������� ���� ��� ������ ������, ������� ��� ������.
		unsigned short bitsPerSample; // "��������"
		char subchunk2Id[4]; // "data"	
		unsigned long subchunk2Size = 0;// ���������� ���� � ������� ������.
	} WH;
};