#include "CppUnitTest.h"
#include "../Chlorine/wav.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


TEST_CLASS(Wav)
{
public:
		
	TEST_METHOD(TestData)
	{
		_WAV first;
		ifstream in;
		in.open("test.wav", std::ios::in | std::ios::binary);
		if (!in.is_open()) Assert::AreEqual(L"", L"не найден проверочный файл");
		first.readHead(in);

		short data;
		vector<char> one_simple;
		one_simple.resize(4);
		in.read(&(*one_simple.begin()), 4);
		data = one_simple[2 - 1];
		for (int j = 2 - 2; j >= 0; j--)
		{
			data = data * 256 + unsigned char(one_simple[j]);
		}
		Assert::AreEqual(to_string(-439), to_string(data));

	}
	TEST_METHOD(TestData2)
	{
		_WAV first;
		ifstream in;
		in.open("test.wav", std::ios::in | std::ios::binary);
		if (!in.is_open()) Assert::AreEqual(L"", L"не найден проверочный файл");
		first.readHead(in);

		short data;
		vector<char> one_simple;
		one_simple.resize(4);
		for (int i = 0; i < 2; i++)
		{
			in.read(&(*one_simple.begin()), 4);
			data = one_simple[2 - 1];
			for (int j = 2 - 2; j >= 0; j--)
			{
				data = data * 256 + unsigned char(one_simple[j]);
			}
		}
		Assert::AreEqual(to_string(-423), to_string(data));

	}

	TEST_METHOD(Ok)
	{
		_WAV first;
		Assert::AreEqual(string("Успешное открытие\n"), first.read("test.wav"));
	}
};

