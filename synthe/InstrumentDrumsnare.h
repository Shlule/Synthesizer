#pragma once
#include"InstrumentBase.h"
#include"Note.h"
class InstrumentDrumsnare : public InstrumentBase
{
public:

	InstrumentDrumsnare();
	InstrumentDrumsnare(double dVolumeP);
	virtual double sound(const double dTimeP, const Note& n, bool& bNoteFinished);

private:
};

