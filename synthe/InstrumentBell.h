#pragma once
#include"InstrumentBase.h"
#include"Note.h"
class InstrumentBell : public InstrumentBase
{

public:

	InstrumentBell();
	InstrumentBell(double dVolumeP);
	virtual double sound(const double dTimeP, const Note& n, bool& bNoteFinished);

private:

};