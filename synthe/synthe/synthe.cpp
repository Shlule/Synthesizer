// synthe.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include"NoiseMaker.h"

using namespace std;

atomic<double> dFrequencyOutput = 0.0;

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


    // this is the base frequency a A2
    double dBaseOctaveFrequency = 110.0; //A2

    //there is usually 12 semi tons in one octave
    double semitonRatio = pow(2.0, 1.0 / 12.0);
    cout << semitonRatio << '\n';
    

    while(1){

        // add a keyboard like a piano
        bool bKeyPressed = false;
        for (int i = 0; i < 15; i++) {
            if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcl\xbe"[i])) & 0x8000) {
                dFrequencyOutput = dBaseOctaveFrequency * pow(semitonRatio, i);
                cout << pow(semitonRatio, i) << '\n';
                cout << dFrequencyOutput << '\n';
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
