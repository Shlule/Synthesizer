#include "SoundEngine.h"

SoundEngine::SoundEngine() : isRunning{false}
{}

SoundEngine::~SoundEngine()
{}

void SoundEngine::init() {

}

void SoundEngine::load() {
    devices = olcNoiseMaker<short>::Enumerate();

}

void SoundEngine::handleInputs() {

}

void SoundEngine::update(float dt) {

}

void SoundEngine::render() {

}

void SoundEngine::clean() {

}
double SoundEngine::MakeNoise(double dTime) {
   
        double dOutput = 1.0 * sin(dFrequencyOutput * 2.0 * 3.14159 * dTime);

        if (dOutput > 0.0) {
            return 0.1;
        }
        else {
            return -0.1;
        }

  
}