#include "Loop.h"
#include <experimental/filesystem>
#include "lame.h"
#include <time.h>
namespace fs = std::experimental::filesystem;

#define endl "\n"

void conwert(string name)
{
	int read, write;

	string inpName = name + string(".wav"), outName = name + string(".mp3");
	FILE* pcm = fopen(inpName.c_str(), "rb");
	FILE* mp3 = fopen(outName.c_str(), "wb");

	const int PCM_SIZE = 8192;
	const int MP3_SIZE = 8192;

	short int pcm_buffer[PCM_SIZE * 2];
	unsigned char mp3_buffer[MP3_SIZE];

	lame_t lame = lame_init();
	lame_set_in_samplerate(lame, 44100);
	lame_set_VBR(lame, vbr_default);
	lame_init_params(lame);

	do {
		read = fread(pcm_buffer, 2 * sizeof(short int), PCM_SIZE, pcm);
		if (read == 0)
			write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
		else
			write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
		fwrite(mp3_buffer, write, 1, mp3);
	} while (read != 0);

	lame_close(lame);
	fclose(mp3);
	fclose(pcm);
}



Loop::Loop()
{
	out.open("out.txt");
}

Loop::~Loop()
{
	out.close();
}
//void Loop::ma()
//{
//
//	//Обработка всех файлов в папке scaning формата wav
//	const fs::path workdir = fs::current_path() / "scaning";
//
//	fs::recursive_directory_iterator begin(workdir);
//	fs::recursive_directory_iterator end;
//	// Получаем список подкаталогов с помощью алгоритма copy_if
//	vector<fs::path> Files;
//	copy_if
//	(
//		begin, end, std::back_inserter(Files), [](const fs::path & path)
//		{
//			return fs::is_regular_file(path) && (path.extension() == ".wav");
//		}
//	);
//
//
//	for (int i =0 ; i < Files.size();i++)
//	{
//		string dir;
//		dir = Files[i].string();
//		string::size_type n = -1;
//		while (dir.find("scaning", n+1) != string::npos)
//		{
//			n = dir.find("scaning", n+1);
//		}
//		dir = dir.substr(n);
//		out << "Работа с файлом :" << dir << endl;
//		string res = wav.read(dir);
//		out << res;
//		if (res == "Успешное открытие\n")
//		{
//			cout << i+1<<" ок \n";
//			out << "Кол-во экстремумов: " << wav.getSize() << endl;
//			out << "Середина между экстремумами: " << ToString(wav.getMiddle())<< endl;
//		}
//		else
//		{
//			cout << i + 1 << " нет \n";
//		}
//		out << "-----------" << endl << endl;
//
//	}
//}


void Loop::concat()
{

	cout << "Подождите, идёт анализ\n";

	//Обработка всех файлов в папке scaning формата wav
	const fs::path workdir = fs::current_path() / "biblio";

	fs::recursive_directory_iterator begin(workdir);
	fs::recursive_directory_iterator end;
	// Получаем список подкаталогов с помощью алгоритма copy_if
	vector<fs::path> Files;
	copy_if
	(
		begin, end, std::back_inserter(Files), [](const fs::path & path)
		{
			return fs::is_regular_file(path) && (path.extension() == ".wav");
		}
	);
	
	cout << "Введите название файла\n";
	string nameFile;
	cin >> nameFile;
	cout << "Из скольки семплов сделать склейку?\n";
	size_t lenght;
	cin >> lenght;

	size_t k, i, n = Files.size();
	vector<string> all_dir(n);
	for (i = 0; i < n; i++)
	{
		string dir;
		dir = Files[i].string();
		string::size_type n = -1;
		while (dir.find("biblio", n + 1) != string::npos)
		{
			n = dir.find("biblio", n + 1);
		}
		all_dir[i] = dir.substr(n);
	}

	srand(time(0));
	for (i = 0; i < lenght; ++i)
	{
		cout << "Склеен " +to_string(i+1) + " файл\n";
		k = rand() % n;
		wav.add(all_dir[k]);
	}
	cout << "Происходит общая склейка \n";
	wav.writeInWav(nameFile+string(".wav"));
	conwert(nameFile);
}