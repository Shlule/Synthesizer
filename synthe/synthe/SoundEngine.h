#pragma once
class SoundEngine
{
public:
	SoundEngine();
	~SoundEngine();

	void init();
	void load();
	void handleInputs();
	void update(float dt);
	void render();
	void clean();

	bool isRunning;

private:
	
};

