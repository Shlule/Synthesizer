// synthe.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include"NoiseMaker.h"

using namespace std;

atomic<double> dFrequencyOutput{ 0.0 };

double MakeNoise(double dTime) {

    double dOutput = 1.0 * sin(dFrequencyOutput * 2.0 * 3.14159 * dTime);

    if (dOutput > 0.0) {
        return 0.1;
    }
    else {
        return -0.1;
    }


}

int main()
{


    //get all audio ouput
    vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

    // display findings
    for (auto d : devices) wcout << "found output devices: " << d << '\n';

    olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);
    sound.SetUserFunction(MakeNoise);

    // this will be our base note
    double dOctabeBaseFrequency = 110.0; // a2

    // in western convention we get 12 tons in one octave
    // but each time we will get the same highter note we double frequency
    // a2 =110 a3=220 a4=440 etc.
    // our ration is 2 pow 1/12 beacuse we have 12 tons in one octave and for one octave we multiplie by 2 frequency

    double d12thRootof2 = pow(2.0, 1.0 / 12.0);

    

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
