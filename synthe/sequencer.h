#pragma once
#include"InstrumentBase.h"
#include"Note.h"
#include<string>
#include<vector>

using std::wstring;

class Sequencer
{
public:
	struct Channel
	{
		InstrumentBase* instrument;
		std::wstring sbeat;

	};

	Sequencer(double tempo = 120.0f, int beats = 4, int subBeats = 4);
	int update(double dElapsedTimeP);
	void addInstrument(InstrumentBase* instP);

public:
	int beats;
	int subBeats;
	double tempo;
	double beatTime;
	double accumulate;
	int currentBeat;
	int totalBeats;

public:
	std::vector<Channel> vecChannel;
	std::vector<Note> vecNotes;



};
