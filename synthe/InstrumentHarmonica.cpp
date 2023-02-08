#include "InstrumentHarmonica.h"

InstrumentHarmonica::InstrumentHarmonica() {

	env.setAttackTime(0.05);
	env.setDecayTime(1.0);
	env.setSustainAmplitude(0.95);
	env.setReleaseTime(0.3);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = -1.0;

	dVolume = 0.3;
}
InstrumentHarmonica::InstrumentHarmonica(double dVolumeP) {

	env.setAttackTime(0.05);
	env.setDecayTime(1.0);
	env.setSustainAmplitude(0.95);
	env.setReleaseTime(0.1);
	env.setStartAmplitude(1.0);
	dMaxlifeTime = -1.0;

	dVolume = dVolumeP;
}

double InstrumentHarmonica::sound(const double dTimeP,const Note& n, bool& bNoteFinished)
{
	double dAmplitude = env.GetAmplitude(dTimeP, n.on, n.off);
	if (dAmplitude <= 0.0) bNoteFinished = true;

	double dSound =
		//+ 1.0  * synth::osc(n.on - dTime, synth::scale(n.id-12), synth::OSC_SAW_ANA, 5.0, 0.001, 100)
		+1.00 * oscillator(n.on - dTimeP, scale(n.id), OscType::OSC_SQUARE, 5.0, 0.001)
		+ 0.50 * oscillator(n.on - dTimeP, scale(n.id + 12), OscType::OSC_SQUARE)
		+ 0.05 * oscillator(n.on - dTimeP, scale(n.id + 24),OscType::OSC_NOISE);

	return dAmplitude * dSound * dVolume;
}
