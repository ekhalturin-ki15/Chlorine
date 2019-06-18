#include "Loop.h"
#include <experimental/filesystem>
#include "lame.h"
namespace fs = std::experimental::filesystem;

#define endl "\n"

vector<string> Loop::extractWAV(string path)
{
	//��������� ���� ������ � ����� scaning ������� wav
	const fs::path workdir = fs::current_path() / path;

	fs::recursive_directory_iterator begin(workdir);
	fs::recursive_directory_iterator end;
	// �������� ������ ������������ � ������� ��������� copy_if
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
		size_t found1 = dir.rfind("\\")+1;
		size_t found2 = dir.rfind(".");
		all_dir[i] = dir.substr(found1, found2- found1);

	}
	return all_dir;
}

void Loop::conwert(string name)
{
	int write;

	string outName = name + string(".mp3");
	FILE* mp3 = fopen(outName.c_str(), "wb");

	vector<unsigned char> mp3_buffer(wav.data.size()/2);

	lame_t lame = lame_init();
	lame_set_in_samplerate(lame, 44100);
	lame_set_VBR(lame, vbr_default);
	lame_init_params(lame);
		
	write = lame_encode_buffer_interleaved(lame, &(*wav.data.begin()), wav.data.size() / 2, &(*mp3_buffer.begin()), mp3_buffer.size());

	fwrite(&(*mp3_buffer.begin()), write, 1, mp3);
	
	write = lame_encode_flush(lame, &(*mp3_buffer.begin()), mp3_buffer.size());

	fwrite(&(*mp3_buffer.begin()), write, 1, mp3);

	lame_close(lame);
	fclose(mp3);
}

int Loop::getRand(int state)
{
	int r = rand() % sum[state], i;
	for (i = 0; i < probability[state].size(); ++i)
	{
		r -= probability[state][i];
		if (r < 0) return i;
			
	}
	return 0;
}

void Loop::parsingProbability()
{
	ifstream in;
	in.open("����������\\����������.txt");

	all_dir.push_back("�����"); all_dir.push_back("�����");

	size_t i, name, who, num, n = all_dir.size();
	probability.resize(n); sum.resize(n);
	i = 0;
	for (const auto& it : all_dir)
	{
		if (i>=n-2)
			probability[i].resize(n - 2, 0);
		else
			probability[i].resize(n-2,1);
		conformity[it] = i++;
	}

	string line;

	in >> line;
	while (true)
	{
		in >> line;
		if (line == "���������:") break;
		name = conformity[line];
		in >> line;
		if (line == "���������:")
			while (true)
			{
				in >> line;
				if (line == "���:") break;
				in >> num;
				who = conformity[line];
				probability[name][who] = num*10;
			}
	}

	i = 0;
	for (const auto& it : probability)
	{
		
		num = 0;
		for (const auto& it2 : it)
		{
			num += it2;
		}
		sum[i++] = num;
	}

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

	cout << "���������, ��� ������\n";

	all_dir = extractWAV("����������");

	parsingProbability();

	ifstream in; in.open("����� ������.txt");

	string nameFile = "", line, message; bool work;
	getline(in, line);
	in >> nameFile;
	getline(in, line);
	getline(in, line);
	getline(in, line);
	in >> work;
	getline(in, line);
	getline(in, line); 
	getline(in, line);

	size_t lenght = 0;
	while (getline(in, line))	message += line;
	lenght = line.size();

	size_t  i, n = all_dir.size(), state = n-1;
	wav.clear();
	for (i = 0; i < lenght; ++i)
	{
		cout << "������ " + to_string(i + 1) + " ����\n";
		if (i == lenght - 1)	state = n - 2;//��������
		state = getRand(state);
		wav.add("����������\\" + all_dir[state] + ".wav");
	}
	cout << "���������� ����� ������� \n";
	//wav.writeInWav(nameFile + string(".wav"));
	conwert(nameFile);
	
}