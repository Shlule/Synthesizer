#include "Note.h"
Note::Note(int idP) : id{ idP } {

}
void Note::setInstChannel(InstrumentBase* instP) {
	instChannel = instP;
}