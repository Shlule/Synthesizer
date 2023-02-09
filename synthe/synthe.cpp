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
#include"sequencer.h"
using namespace std;

#define FTYPE double
#include "NoiseMaker.h"


namespace synth
{


	//////////////////////////////////////////////////////////////////////////////
	// Utilities
	Note note;
	EnveloppeADSR enveloppe;
	// Converts frequency (Hz) to angular velocity
	FTYPE w(const FTYPE dHertz)
	{
		return dHertz * 2.0 * PI;
	}
	

	//////////////////////////////////////////////////////////////////////////////
	// Multi-Function Oscillator
	const int OSC_SINE = 0;
	const int OSC_SQUARE = 1;
	const int OSC_TRIANGLE = 2;
	const int OSC_SAW_ANA = 3;
	const int OSC_SAW_DIG = 4;
	const int OSC_NOISE = 5;

	FTYPE osc(const FTYPE dTime, const FTYPE dHertz, const int nType = OSC_SINE,
		const FTYPE dLFOHertz = 0.0, const FTYPE dLFOAmplitude = 0.0, FTYPE dCustom = 50.0)
	{

		FTYPE dFreq = w(dHertz) * dTime + dLFOAmplitude * dHertz * (sin(w(dLFOHertz) * dTime));// osc(dTime, dLFOHertz, OSC_SINE);

		switch (nType)
		{
		case OSC_SINE: // Sine wave bewteen -1 and +1
			return sin(dFreq);

		case OSC_SQUARE: // Square wave between -1 and +1
			return sin(dFreq) > 0 ? 1.0 : -1.0;

		case OSC_TRIANGLE: // Triangle wave between -1 and +1
			return asin(sin(dFreq)) * (2.0 / PI);

		case OSC_SAW_ANA: // Saw wave (analogue / warm / slow)
		{
			FTYPE dOutput = 0.0;
			for (FTYPE n = 1.0; n < dCustom; n++)
				dOutput += (sin(n * dFreq)) / n;
			return dOutput * (2.0 / PI);
		}

		case OSC_SAW_DIG:
			return (2.0 / PI) * (dHertz * PI * fmod(dTime, 1.0 / dHertz) - (PI / 2.0));

		case OSC_NOISE:
			return 2.0 * ((FTYPE)rand() / (FTYPE)RAND_MAX) - 1.0;

		default:
			return 0.0;
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	// Scale to Frequency conversion

	const int SCALE_DEFAULT = 0;

	FTYPE scale(const int nNoteID, const int nScaleID = SCALE_DEFAULT)
	{
		switch (nScaleID)
		{
		case SCALE_DEFAULT: default:
			return 256 * pow(1.0594630943592952645618252949463, nNoteID);
		}
	}


	//////////////////////////////////////////////////////////////////////////////
	// Envelopes


	struct instrument_base
	{
		FTYPE dVolume;
		EnveloppeADSR env;
		virtual FTYPE sound(const FTYPE dTime,const Note& n, bool& bNoteFinished) = 0;
	};

	struct instrument_bell : public instrument_base
	{
		instrument_bell()
		{
			env.setAttackTime(0.1);
			env.setDecayTime(0.2);
			env.setSustainAmplitude(0.0);
			env.setReleaseTime(1.0);

			dVolume = 1.0;
		}

		virtual FTYPE sound(const FTYPE dTime,const Note& n, bool& bNoteFinished)
		{
			FTYPE dAmplitude = env.GetAmplitude(dTime, n.on, n.off);
			if (dAmplitude <= 0.0) bNoteFinished = true;

			FTYPE dSound =
				+1.00 * synth::osc(n.on - dTime, synth::scale(n.id + 12), synth::OSC_SINE, 5.0, 0.001)
				+ 0.50 * synth::osc(n.on - dTime, synth::scale(n.id + 24))
				+ 0.25 * synth::osc(n.on - dTime, synth::scale(n.id + 36));

			return dAmplitude * dSound * dVolume;
		}

	};

	struct instrument_bell8 : public instrument_base
	{
		instrument_bell8()
		{
			env.setAttackTime(0.01);
			env.setDecayTime(0.5);
			env.setSustainAmplitude(0.8);
			env.setStartAmplitude(1.0);

			dVolume = 1.0;
		}

		virtual FTYPE sound(const FTYPE dTime,const Note& n, bool& bNoteFinished)
		{
			FTYPE dAmplitude = env.GetAmplitude(dTime, n.on, n.off);
			if (dAmplitude <= 0.0) bNoteFinished = true;

			FTYPE dSound =
				+1.00 * synth::osc(n.on - dTime, synth::scale(n.id), synth::OSC_SQUARE, 5.0, 0.001)
				+ 0.50 * synth::osc(n.on - dTime, synth::scale(n.id + 12))
				+ 0.25 * synth::osc(n.on - dTime, synth::scale(n.id + 24));

			return dAmplitude * dSound * dVolume;
		}

	};

	struct instrument_harmonica : public instrument_base
	{
		instrument_harmonica()
		{
			env.setAttackTime(0.05);
			env.setDecayTime(1.0);
			env.setSustainAmplitude(0.95);
			env.setReleaseTime(0.3);

			dVolume = 1.0;
		}

		virtual FTYPE sound(const FTYPE dTime,const Note& n, bool& bNoteFinished)
		{
			FTYPE dAmplitude = env.GetAmplitude(dTime, n.on, n.off);
			if (dAmplitude <= 0.0) bNoteFinished = true;

			FTYPE dSound =
				//+ 1.0  * synth::osc(n.on - dTime, synth::scale(n.id-12), synth::OSC_SAW_ANA, 5.0, 0.001, 100)
				+1.00 * synth::osc(n.on - dTime, synth::scale(n.id), synth::OSC_SQUARE, 5.0, 0.001)
				+ 0.50 * synth::osc(n.on - dTime, synth::scale(n.id + 12), synth::OSC_SQUARE)
				+ 0.05 * synth::osc(n.on - dTime, synth::scale(n.id + 24), synth::OSC_NOISE);

			return dAmplitude * dSound * dVolume;
		}

	};

	struct Harmonica : public InstrumentBase
	{
		Harmonica() {
			setEnveloppe(0.05, 1.0, 0.95, 0.3, 1.0);
			dVolume = 1.0;
		}
		virtual FTYPE sound(const FTYPE dTime, const Note& n, bool& bNoteFinished)
		{
			FTYPE dAmplitude = env.GetAmplitude(dTime, n.on, n.off);
			if (dAmplitude <= 0.0) bNoteFinished = true;

			FTYPE dSound =
				//+ 1.0  * synth::osc(n.on - dTime, synth::scale(n.id-12), synth::OSC_SAW_ANA, 5.0, 0.001, 100)
				+1.00 * synth::osc(n.on - dTime, synth::scale(n.id), synth::OSC_SQUARE, 5.0, 0.001)
				+ 0.50 * synth::osc(n.on - dTime, synth::scale(n.id + 12), synth::OSC_SQUARE)
				+ 0.05 * synth::osc(n.on - dTime, synth::scale(n.id + 24), synth::OSC_NOISE);

			return dAmplitude * dSound * dVolume;
		}

	};

}



vector<Note> vecNotes;
mutex muxNotes;
synth::instrument_bell instBell;
synth::instrument_harmonica instHarm;
synth::Harmonica harmonica;
InstrumentHarmonica harmonicas;
InstrumentDrumsnare drumsnare;
InstrumentDrumkick drumkick;
InstrumentDrumhithat drumhithat;





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
	FTYPE dMixedOutput = 0.0;

	for (auto& n : vecNotes)
	{
		bool bNoteFinished = false;
		FTYPE dSound = 0;
		if (n.channel == 2)
			dSound = instBell.sound(dTime, n, bNoteFinished);
		if (n.channel == 1)
			dSound = instHarm.sound(dTime, n, bNoteFinished) * 0.5;
		if(n.channel == 3)
			dSound = harmonicas.sound(dTime, n, bNoteFinished) * 0.5;
		dMixedOutput += dSound;
		if (n.channel == 4)
			dSound = drumkick.sound(dTime, n, bNoteFinished);
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

	// Link noise function with sound machine
	sound.SetUserFunction(MakeNoise);

	

	char keyboard[129];
	memset(keyboard, ' ', 127);
	keyboard[128] = '\0';

	auto clock_old_time = chrono::high_resolution_clock::now();
	auto clock_real_time = chrono::high_resolution_clock::now();
	double dElapsedTime = 0.0;
	double dWallTime = 0.0;

	// Establish Sequencer
	Sequencer seq(90.0);
	seq.addInstrument(&drumkick);
	seq.addInstrument(&drumsnare);
	seq.addInstrument(&drumhithat);

	seq.vecChannel.at(0).sbeat = L"X...X...X..X.X..";
	seq.vecChannel.at(1).sbeat = L"..X...X...X...X.";
	seq.vecChannel.at(2).sbeat = L"X.X.X.X.X.X.X.XX";

	while (1)
	{

		/*// Update Timing =================================================================

		clock_real_time = chrono::high_resolution_clock::now();
		auto time_last_loop = clock_real_time - clock_old_time;
		clock_old_time = clock_real_time;
		dElapsedTime = chrono::duration<double>(time_last_loop).count();
		dWallTime += dElapsedTime;
		double dTimeNow = sound.GetTime();

		// sequencer (generate and remove Notes depending on key state =========================

		int newNotes = seq.update(dElapsedTime);
		muxNotes.lock();

		for (int i = 0; i < newNotes; i++) {
			seq.vecNotes[i].on = dTimeNow;
			vecNotes.emplace_back(seq.vecNotes[i]);
		}
		muxNotes.unlock();*/

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
					n.channel = 3;
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
