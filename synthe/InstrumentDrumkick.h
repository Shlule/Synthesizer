#pragma once
#include"InstrumentBase.h"
#include"Note.h"
class InstrumentDrumkick : public InstrumentBase
{

public:

	InstrumentDrumkick();
	InstrumentDrumkick(double dVolumeP);
	virtual double sound(const double dTimeP, const Note& n, bool& bNoteFinished);

private:

};