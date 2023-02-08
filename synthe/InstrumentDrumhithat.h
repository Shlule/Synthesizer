#pragma once
#include"InstrumentBase.h"
#include"Note.h"
class InstrumentDrumhithat : public InstrumentBase
{
public:
	InstrumentDrumhithat();
	InstrumentDrumhithat(double dVolumeP);
	virtual double sound(const double dTimeP, const Note& n, bool& bNoteFinished);

private:
};

