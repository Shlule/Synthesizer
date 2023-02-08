// synthe.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include"NoiseMaker.h"

using namespace std;

//========================================================

//global variable

atomic<double> dFrequencyOutput{ 0.0 };
// this will be our base note
double dOctabeBaseFrequency = 110.0; // a2

// in western convention we get 12 tons in one octave
// but each time we will get the same highter note we double frequency
// a2 =110 a3=220 a4=440 etc.
// our ration is 2 pow 1/12 beacuse we have 12 tons in one octave and for one octave we multiplie by 2 frequency
//=======================================================
double d12thRootof2 = pow(2.0, 1.0 / 12.0);


double w(double dHertz) {
    return dHertz * 2.0 * PI;
}
double oscillator(double dHertz, double dTime, int nType){
    switch (nType) {

    case 0: // sine Wave
        return sin(w(dHertz) * dTime);

    case 1: // square wave
        return sin(w(dHertz) * dTime) > 0.0 ? 1.0 : -1.0;

    case 2:// triangle wave
        return asin(sin(w(dHertz) * dTime)) * 2.0 / PI;

    default: 
        return 0;
    }
}
// the eveloppe permit to grow up up the sound when key pressed on when key release go down progressively 
struct sEnvelopeADSR {
    // Yime to grow upp to mximum value
    double dAttackTime;

    // time when Maximum frequency go to frequency demand
    double dDecayTime;

    // time to demand frequency to no sound 
    double dReleaseTime;


    //amplitude that program sustain while key pressed
    double dSustainAmplitude;
    double dStartAmplitude;

    double dTriggerOnTime;
    double dTriggerOffTime;

    sEnvelopeADSR() {
        dAttackTime = 0.01;
        dDecayTime =0.01;
        dStartAmplitude = 1.0;
        dSustainAmplitude = 0.8;
        dReleaseTime = 0.02;
        dTriggerOnTime = 0.0;
        dTriggerOffTime = 0.0;
    }

    double GetAmplitude(double dTime) {
        double dAmplitude = 0.0;
        return dAmplitude;
    }
};



double MakeNoise(double dTime) {

    double dOutput = oscillator(dFrequencyOutput, dTime, 2);

    return dOutput * 0.4; // master volume


}

int main()
{


    //get all audio ouput
    vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

    // display findings
    for (auto d : devices) wcout << "found output devices: " << d << '\n';

    olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);
    sound.SetUserFunction(MakeNoise);

   

    

    while(1){
        bool bKeyPressed = false;


        //add key like a piano

        for (int i = 0; i < 15; i++) {

            if (GetAsyncKeyState((unsigned char)("WSXCFVGBNJ?K\xbcL\xbe"[i])) & 0x8000) {
                dFrequencyOutput = dOctabeBaseFrequency * pow(d12thRootof2, i);
                bKeyPressed = true;

            }
        }
        if(!bKeyPressed) {
            dFrequencyOutput = 0.0;
        }
    }

    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
