#include "EnveloppeADSR.h"
EnveloppeADSR::EnveloppeADSR() {
    dAttackTime = 0.1;
    dDecayTime = 0.1;
    dSustainAmplitude = 1.0;
    dReleaseTime = 0.2;
    dStartAmplitude = 1.0;
}

EnveloppeADSR::EnveloppeADSR(double dAttackTimeP, double dDecayTimeP, double dSustainAmplitudeP, double dReleaseTimeP, double dStartAmplitudeP) :
	dAttackTime{ dAttackTimeP }, dDecayTime{ dDecayTimeP }, dSustainAmplitude{ dSustainAmplitudeP }, dReleaseTime{ dReleaseTimeP }, dStartAmplitude{ dStartAmplitudeP }
{

}

void EnveloppeADSR::setAttackTime(double dAttackTimeP) {
	dAttackTime = dAttackTimeP;

}

void EnveloppeADSR::setReleaseTime(double dReleaseTimeP) {
	dReleaseTime = dReleaseTimeP;
}
void EnveloppeADSR::setDecayTime(double dDecayTimeP) {
	dDecayTime = dDecayTimeP;
}
void EnveloppeADSR::setStartAmplitude(double dStartAmplitudeP) {
	dStartAmplitude = dStartAmplitudeP;
}
void EnveloppeADSR::setSustainAmplitude(double dSustainAmplitudeP) {
	dSustainAmplitude = dSustainAmplitudeP;
}
/*This funtion is the core of this class.
that function return the amplitude of the sound during the time wich the sound live and describe the sound behavior.*/
double EnveloppeADSR::GetAmplitude(const double dTime, const double dTimeOn, const double dTimeOff) {

    double dAmplitude = 0.0;
    double dReleaseAmplitude = 0.0;

    if (dTimeOn > dTimeOff) // Note On 
    {
        double dLifeTime = dTime - dTimeOn;

        // attack phase 
        // we are in attack phase when deltaTime is inferior to attack set
        if (dLifeTime <= dAttackTime) {
            dAmplitude = (dLifeTime / dAttackTime) * dStartAmplitude;
        }
        // decay phase
        // we are in decay phase after we passed attackTime  and  when delaTime is inferior the addition of attackTime and decayTime
        if (dLifeTime > dAttackTime && dLifeTime <= (dAttackTime + dDecayTime)) {
            dAmplitude = ((dLifeTime - dAttackTime) / dDecayTime) * (dSustainAmplitude - dStartAmplitude) + dStartAmplitude;
        }

        // sustain phase
        // we are in sustain phase  when deltaTime is > to the addition of the attackTime and decayTime 
        if (dLifeTime > (dAttackTime + dDecayTime)) {
            dAmplitude = dSustainAmplitude;
        }
    }
    else // note is Off 
    {
        double dLifeTime = dTimeOff - dTimeOn;

        if (dLifeTime <= dAttackTime) {
            dReleaseAmplitude = (dLifeTime / dAttackTime) * dStartAmplitude;
        }
        // decay phase
       // we are in decay phase after we passed attackTime  and  when delaTime is inferior the addition of attackTime and decayTime
        if (dLifeTime > dAttackTime && dLifeTime <= (dAttackTime + dDecayTime)) {
            dReleaseAmplitude = ((dLifeTime - dAttackTime) / dDecayTime) * (dSustainAmplitude - dStartAmplitude) + dStartAmplitude;
        }

        // sustain phase
        // we are in sustain phase  when deltaTime is > to the addition of the attackTime and decayTime 
        if (dLifeTime > (dAttackTime + dDecayTime)) {
            dReleaseAmplitude = dSustainAmplitude;
        }
        // realease phase

        dAmplitude = ((dTime - dTimeOff) / dReleaseTime) * (0.0 - dReleaseAmplitude) + dSustainAmplitude;
    }

    if (dAmplitude <= 0.0001) {
        dAmplitude = 0;
    }


    return dAmplitude;
}
