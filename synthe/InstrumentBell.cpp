#include "InstrumentBell.h"

InstrumentBell::InstrumentBell() {

	env.setAttackTime(0.01);
	env.setDecayTime(1.0);
	env.setSustainAmplitude(0.0);
	env.setReleaseTime(1.0);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = 3.0;

	dVolume = 1.0;
}
InstrumentBell::InstrumentBell(double dVolumeP) {

	env.setAttackTime(0.01);
	env.setDecayTime(1.0);
	env.setSustainAmplitude(0.0);
	env.setReleaseTime(1.0);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = 3.0;

	dVolume = dVolumeP;
}

double InstrumentBell::sound(const double dTimeP, const Note& n, bool& bNoteFinished)
{
	double dAmplitude = env.GetAmplitude(dTimeP, n.on, n.off);
	if (dAmplitude <= 0.0) bNoteFinished = true;

	double dSound =
		+1.0 * oscillator(dTimeP - n.on, scale(n.id + 12), OscType::OSC_SINE, 5.0, 0.001)
		+ 0.5 * oscillator(dTimeP - n.on, scale(n.id + 24))
		+0.25 * oscillator(dTimeP - n.on, scale(n.id + 36));

	return dAmplitude * dSound * dVolume;
}

