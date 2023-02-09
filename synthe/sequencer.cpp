#include "sequencer.h"

Sequencer::Sequencer(double tempoP, int beatsP, int subBeatsP) : tempo{ tempoP }, beats{ beatsP }, subBeats{ subBeatsP }{
	beatTime = (60.f / tempo) / (float)subBeats;
	currentBeat = 0;
	totalBeats = subBeats * beats;
	accumulate = 0;
}

int Sequencer::update(double dElapsedTimeP) {
	vecNotes.clear();
	accumulate += dElapsedTimeP;
	while (accumulate >= beatTime) {
		accumulate -= beatTime;
		currentBeat++;

		if (currentBeat >= totalBeats) {
			currentBeat = 0;
		}

		int c = 0;
		for (auto v : vecChannel) {
			if (v.sbeat[currentBeat] == L'X') {
				Note n;
				n.instChannel = vecChannel[c].instrument;
				n.isActive = true;
				n.id = 64;
				vecNotes.emplace_back(n);
			}
		}

	}
	return vecNotes.size();
}

void Sequencer::addInstrument(InstrumentBase* instP) {
	Channel c;
	c.instrument = instP;
	vecChannel.emplace_back(c);
}