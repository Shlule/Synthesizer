#pragma once
#include<cmath>
#include<atomic>
#include"EnveloppeADSR.h"

class Note;


enum class OscType
{
	OSC_SINE,
	OSC_SQUARE,
	OSC_TRIANGLE,
	OSC_SAW_ANA,
	OSC_SAW_DIG,
	OSC_NOISE
};

class InstrumentBase
{

public:
	InstrumentBase() {}
	InstrumentBase(double dVolumeP);

	//convert Frequency to angular velocity
	double freqToAngularVelo(double dHertzP);
	double oscillator(const double dTimeP, const double dHertzP, const OscType nTypeP = OscType::OSC_SINE, const double dLFOHertzP = 0.0, const double dLFOAmplitudeP = 0.0, double dCustomP =50.0);
	double scale(const int nNoteId);

	void setEnveloppe(double dAttackTimeP, double dDecayTimeP, double dSustainAmplitudeP, double dReleaseTimeP, double dStartAmplitudeP = 1.0);
	void setMaxLifetime(double dMaxlifeTimeP);

	virtual double sound(const double dTimeP,const Note& n, bool& bNoteFinished)=0;


protected:
	
	double dVolume{ 0.2 };
	EnveloppeADSR env = EnveloppeADSR{ 0.0, 0.0, 0.0, 0.0, 0.0 };
	double dMaxlifeTime{ 0.0 };
	double PI = 2.0 * acos(0.0);
};

