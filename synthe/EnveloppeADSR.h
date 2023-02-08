#pragma once
/* the enveloppe permit to decompose the sound in differente phase , attack, Decay, Sustain, Release

that also permit to change the time of live of each phase et create signature to the sound 

for exemple a sound  wich no sustain phase cannot persist insted of pressing the button.*/
class EnveloppeADSR
{
public:
    EnveloppeADSR();
    EnveloppeADSR(double dAttackTimeP, double dDecayTimeP, double dSustainAmplitudeP, double dReleaseTimeP, double dStartAmplitudeP);

    double getAttackTime()const { return dAttackTime; }
    double getDacayTime()const { return dDecayTime; }
    double getReleaseTime()const { return dReleaseTime; }
    double getStartAmplitude()const { return dStartAmplitude; }
    double getSustainAmplitude()const { return dSustainAmplitude; }

    void setAttackTime(double dAttackTimeP);
    void setReleaseTime(double dAttackTimeP);
    void setDecayTime(double dAttackTimeP);
    void setStartAmplitude(double dAttackTimeP);
    void setSustainAmplitude(double dAttackTimeP);

    double GetAmplitude(const double dTime, const double dTimeOn, const double dTimeOff );
    void NoteOn(double dtimeOn);
    void NoteOff(double dtimeOff);

private:
    // Time to grow upp to mximum value
    double dAttackTime;

    // time when Maximum frequency go to frequency demand
    double dDecayTime;

    // time to demand frequency to no sound 
    double dReleaseTime;


    //amplitude that program sustain while key pressed
    double dSustainAmplitude;
    double dStartAmplitude;

};

