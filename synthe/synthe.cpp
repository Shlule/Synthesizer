#include <list>
#include <iostream>
#include <algorithm>
#include<functional>
#include"Note.h"
#include"EnveloppeADSR.h"
#include"InstrumentBase.h"
#include"InstrumentHarmonica.h"
#include"Synthesizer.h"
#include"InstrumentDrumhithat.h"
#include"InstrumentDrumkick.h"
#include"InstrumentDrumsnare.h"
#include"InstrumentBell.h"
#include"sequencer.h"
using namespace std;

#define FTYPE double
#include "NoiseMaker.h"



vector<Note> vecNotes;
mutex muxNotes;

InstrumentHarmonica harmonicas;
InstrumentDrumsnare drumsnare;
InstrumentDrumkick drumkick;
InstrumentDrumhithat drumhithat;
InstrumentBell bell;





typedef bool(*lambda)(Note const& item);
template<class T>
void safe_remove(T& v, lambda f)
{
	auto n = v.begin();
	while (n != v.end())
		if (!f(*n))
			n = v.erase(n);
		else
			++n;
}

// Function used by olcNoiseMaker to generate sound waves
// Returns amplitude (-1.0 to +1.0) as a function of time
FTYPE MakeNoise(int nChannel, FTYPE dTime)
{
	unique_lock<mutex> lm(muxNotes);
	double dMixedOutput = 0.0;

	for (auto& n : vecNotes)
	{
		bool bNoteFinished = false;
		double dSound = 0;
		
		if (n.instChannel != nullptr) {
			dSound = n.instChannel->sound(dTime, n, bNoteFinished)*3.0;
		}
		
		dMixedOutput += dSound;

		if (bNoteFinished && n.off > n.on)
			n.isActive = false;
	}

	// Woah! Modern C++ Overload!!!
	safe_remove<vector<Note>>(vecNotes, [](Note const& item) { return item.isActive; });


	return dMixedOutput * 0.2;
}



int main()
{

	// Get all sound hardware
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	// Display findings
	for (auto d : devices) wcout << "Found Output Device: " << d << endl;
	wcout << "Using Device: " << devices[0] << endl;

	// Create sound machine!!
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	// create a std function to get the member function aof synthe
	Synthesizer synthe;
	std::function<double(int, double)> syntheMakeNoise = [&](int nChannelP, double dTimeP) {
		return synthe.MakeNoise(nChannelP, dTimeP);
	};

	// Link noise function with sound machine
	sound.SetUserFunctionOld(MakeNoise);

	char keyboard[129];
	memset(keyboard, ' ', 127);
	keyboard[128] = '\0';

	auto clock_old_time = chrono::high_resolution_clock::now();
	auto clock_real_time = chrono::high_resolution_clock::now();
	double dElapsedTime = 0.0;

	while (1)
	{
		for (int k = 0; k < 16; k++)
		{
			short nKeyState = GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe\xbf"[k]));

			double dTimeNow = sound.GetTime();

			// Check if note already exists in currently playing notes
			muxNotes.lock();
			auto noteFound = find_if(vecNotes.begin(), vecNotes.end(), [&k](Note const& item) { return item.id == k; });
			if (noteFound == vecNotes.end())
			{
				// Note not found in vector

				if (nKeyState & 0x8000)
				{
					// Key has been pressed so create a new note
					Note n;
					n.id = k;
					n.on = dTimeNow;
					n.channel = 2;
					n.instChannel = &bell;
					n.isActive = true;

					// Add note to vector
					vecNotes.emplace_back(n);
				}
				else
				{
					// Note not in vector, but key has been released...
					// ...nothing to do
				}
			}
			else
			{
				// Note exists in vector
				if (nKeyState & 0x8000)
				{
					// Key is still held, so do nothing
					if (noteFound->off > noteFound->on)
					{
						// Key has been pressed again during release phase
						noteFound->on = dTimeNow;
						noteFound->isActive = true;
					}
				}
				else
				{
					// Key has been released, so switch off
					if (noteFound->off < noteFound->on)
					{
						noteFound->off = dTimeNow;
					}
				}
			}
			muxNotes.unlock();
		}
		wcout << "\rNotes: " << vecNotes.size() << "    ";

		//this_thread::sleep_for(5ms);
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
