#pragma once
#include<vector>
#include"Note.h"
#include<mutex>
#include"InstrumentHarmonica.h"


using std::vector;


class Synthesizer
{
public:
	Synthesizer();

	double MakeNoise(int nChannelP, double dTimeP);

	vector<Note> vecNote;
	InstrumentHarmonica harmonica;
	std::mutex muxNotes;
};

