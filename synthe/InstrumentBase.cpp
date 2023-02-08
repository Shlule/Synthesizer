#include "InstrumentBase.h"
#include"Note.h"

InstrumentBase::InstrumentBase(double dVolumeP) : dVolume{ dVolumeP } {
}

double InstrumentBase::freqToAngularVelo(double dHertzP) {
	return dHertzP * 2.0 * PI; //2.0 * acos(0.0) this is = PI
}


double InstrumentBase::oscillator(const double dTimeP, const double dHertzP, const OscType nTypeP, const double dLFOHertzP, const double dLFOAmplitudeP, double dCustomP) {

	// now ocilator can only superpose 2 frequency , later we want to get layer of ich influence each other
	double dFreq = freqToAngularVelo(dHertzP) * dTimeP + dLFOAmplitudeP * dHertzP * sin(freqToAngularVelo(dLFOHertzP) * dTimeP); 

	switch (nTypeP) {

	case OscType::OSC_SINE: // Sinewave between -1 and 1
		return sin(dFreq);

	case OscType::OSC_SQUARE: // Sqaure wave betwenn -1 and 1
		return sin(dFreq) > 0 ? 1.0 : -1.0;

	case OscType::OSC_TRIANGLE: // triangle wave between -1 and 1
		return asin(sin(dFreq)) * (2.0 / PI);

	case OscType::OSC_SAW_ANA: {// Saw Wave (Analogue/warm/slow)
		double dOutput = 0.0;
		for (double n = 1.0; n < dCustomP; n++) {
			dOutput += (sin(n * dFreq)) / n;
		}
		return dOutput * (2.0 / PI);
	}

	case OscType::OSC_SAW_DIG:
		return (2.0 / PI) * (dHertzP * PI * fmod(dTimeP, 1.0 / dHertzP) - (PI / 2.0));

	case OscType::OSC_NOISE:
		return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;

	default:
		return 0.0;
	}

}

double InstrumentBase::scale(const int nNoteId) {
	return 256 * pow(1.0594630943592952645618252949463, nNoteId);
}

void InstrumentBase::setEnveloppe(double dAttackTimeP, double dDecayTimeP, double dSustainAmplitudeP, double dReleaseTimeP, double dStartAmplitudeP) {
	env = EnveloppeADSR{ dAttackTimeP, dDecayTimeP, dSustainAmplitudeP, dReleaseTimeP, dStartAmplitudeP };
}
void InstrumentBase::setMaxLifetime(double dMaxlifeTimeP) {
	dMaxlifeTime = dMaxlifeTimeP;
}