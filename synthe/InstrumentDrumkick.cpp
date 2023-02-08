#include "InstrumentDrumkick.h"

InstrumentDrumkick::InstrumentDrumkick() {

	env.setAttackTime(0.01);
	env.setDecayTime(0.15);
	env.setSustainAmplitude(0.0);
	env.setReleaseTime(0.01);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = 1.5;

	dVolume = 1.0;
}
InstrumentDrumkick::InstrumentDrumkick(double dVolumeP) {

	env.setAttackTime(0.01);
	env.setDecayTime(0.15);
	env.setSustainAmplitude(0.0);
	env.setReleaseTime(0.01);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = 1.5;

	dVolume = dVolumeP;
}

double InstrumentDrumkick::sound(const double dTimeP, const Note& n, bool& bNoteFinished)
{
	double dAmplitude = env.GetAmplitude(dTimeP, n.on, n.off);
	if (dAmplitude <= 0.0) bNoteFinished = true;

	double dSound =
		+0.99 * oscillator(dTimeP - n.on, scale(n.id - 36), OscType::OSC_SINE, 1.0, 1.0)
		+ 0.01 * oscillator(dTimeP - n.on, 0, OscType::OSC_NOISE);

	return dAmplitude * dSound * dVolume;
}
