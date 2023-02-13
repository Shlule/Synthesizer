#pragma once
#include"InstrumentBase.h"
class Note
{
public:
	Note() {}
	Note(int idP);
	
	void setInstChannel(InstrumentBase* instP);

	int id{ 0 };
	double on{ 0.0 };
	double off{ 0.0 };
	bool isActive{ false };
	int channel{ 0 };
	InstrumentBase* instChannel{ nullptr };
};

