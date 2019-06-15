#include "Loop.h"
#include <experimental/filesystem>
#include "lame.h"
namespace fs = std::experimental::filesystem;

#define endl "\n"

vector<string> Loop::extractWAV(string path)
{
	//Обработка всех файлов в папке scaning формата wav
	const fs::path workdir = fs::current_path() / path;

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

	size_t i, n = Files.size();
	vector<string> all_dir(n);
	for (i = 0; i < n; i++)
	{
		string dir;
		dir = Files[i].string();
		std::size_t found = dir.rfind("\\");
		all_dir[i] = dir.substr(found+1);
	}
	return all_dir;
}

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


void Loop::concat()
{

	cout << "Подождите, идёт анализ\n";

	vector<string> all_dir = extractWAV("biblio");

	while (true)
	{
		cout << "Введите название файла (! - выйти) \n";
		string nameFile = "";
		cin >> nameFile;
		if (nameFile == "!") break;
		cout << "Из скольки семплов сделать склейку? (0 - выйти)\n";
		size_t lenght = 0;
		cin >> lenght;
		if (!lenght) break;


		size_t k, i, n = all_dir.size();
		wav.clear();
		for (i = 0; i < lenght; ++i)
		{
			cout << "Склеен " + to_string(i + 1) + " файл\n";
			k = rand() % n;
			wav.add("biblio\\" + all_dir[k]);
		}
		cout << "Происходит общая склейка \n";
		wav.writeInWav(nameFile + string(".wav"));
		conwert(nameFile);
	}
}