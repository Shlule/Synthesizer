#include "Synthesizer.h"


typedef bool(*lambda)(Note const& item);
template<class T>
void safe_remove(T& v ,lambda f) {
	auto n = v.begin();

	while (n != v.end()) {
		if (!f(*n)) {
			n = v.erase(n);
		}
		else {
			n++;
		}
	}
}

double Synthesizer::MakeNoise(int nChannelP, double dTimeP) {
	std::unique_lock<std::mutex> lm(muxNotes);
	double dMixedOutput = 0.0;

	for (auto& n : vecNote) {
		bool bNoteFinished = false;
		double dSound = 0;
		if (n.channel == 1) {
			dSound = harmonica.sound(dTimeP, n, bNoteFinished) * 0.5;
		}

		dMixedOutput += dSound;

		if (bNoteFinished && n.off > n.on) {
			n.isActive = false;
		}
	}

	safe_remove<std::vector <Note>>(vecNote, [](Note const& item) {return item.isActive; });

	return dMixedOutput * 0.2;
}