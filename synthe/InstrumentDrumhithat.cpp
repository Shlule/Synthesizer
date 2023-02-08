#include "InstrumentDrumhithat.h"

InstrumentDrumhithat::InstrumentDrumhithat() {

	env.setAttackTime(0.01);
	env.setDecayTime(0.05);
	env.setSustainAmplitude(0.0);
	env.setReleaseTime(0.0);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = 1.0;

	dVolume = 0.5;
}
InstrumentDrumhithat::InstrumentDrumhithat(double dVolumeP) {

	env.setAttackTime(0.01);
	env.setDecayTime(0.05);
	env.setSustainAmplitude(0.0);
	env.setReleaseTime(0.0);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = 1.0;
	dVolume = dVolumeP;
}

double InstrumentDrumhithat::sound(const double dTimeP, const Note& n, bool& bNoteFinished)
{
	double dAmplitude = env.GetAmplitude(dTimeP, n.on, n.off);
	if (dAmplitude <= 0.0) bNoteFinished = true;

	double dSound =
		+0.1 * oscillator(dTimeP - n.on, scale(n.id - 12), OscType::OSC_SQUARE, 1.5, 1)
		+ 0.9 * oscillator(dTimeP - n.on, 0, OscType::OSC_NOISE);

	return dAmplitude * dSound * dVolume;
}
