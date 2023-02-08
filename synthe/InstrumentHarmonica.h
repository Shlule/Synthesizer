#pragma once
#include"InstrumentBase.h"
#include"Note.h"
class InstrumentHarmonica : public InstrumentBase
{

public:

	InstrumentHarmonica();
	InstrumentHarmonica(double dVolumeP);
	virtual double sound(const double dTimeP,const Note& n, bool& bNoteFinished);

private:

};

