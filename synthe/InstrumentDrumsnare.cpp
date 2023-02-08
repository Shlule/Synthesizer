#include "InstrumentDrumsnare.h"

InstrumentDrumsnare::InstrumentDrumsnare() {

	env.setAttackTime(0.0);
	env.setDecayTime(0.2);
	env.setSustainAmplitude(0.0);
	env.setReleaseTime(0.01);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = 1.0;

	dVolume = 1.0;
}
InstrumentDrumsnare::InstrumentDrumsnare(double dVolumeP) {

	env.setAttackTime(0.0);
	env.setDecayTime(0.2);
	env.setSustainAmplitude(0.0);
	env.setReleaseTime(0.01);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = 1.0;
	dVolume = dVolumeP;
}

double InstrumentDrumsnare::sound(const double dTimeP, const Note& n, bool& bNoteFinished)
{
	double dAmplitude = env.GetAmplitude(dTimeP, n.on, n.off);
	if (dAmplitude <= 0.0) bNoteFinished = true;

	double dSound =
		+ 0.5 * oscillator(dTimeP - n.on, scale(n.id - 24), OscType::OSC_SINE ,0.5, 1.0)
		+ 0.5 * oscillator(dTimeP - n.on, 0, OscType::OSC_NOISE);

	return dAmplitude * dSound * dVolume;
}

