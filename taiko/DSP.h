#pragma once
#include <stdio.h>
#include <SDL.h>
#include "Complex.h"
#include <vector>
#include "SDL2_gfxPrimitives.h"
#include "Object.h"

using namespace std;

class DSP : public Object
{
private:
	SDL_Thread* thread;
	bool graph;//
	double starttime;//
	double bpm;//
	bool iswaveform;
	int isSpectrumform;		// 0: idle, 1: forming, 2: formed
	bool threadExist;
	int* samp;
	int* right;
	double duration;
	int** spectrumR;
	int** spectrumG;
	int** spectrumB;
	vector<int> pitch;
	Uint32 wav_length;
	SDL_AudioSpec wav_spec;
	int* getWavAmplitudes(Uint8* wav_buffer);
	float* processAmplitudes(int* sourcePcmData);
	void fft(vector<Complex>& a, int lim);
	friend static int Tuning(void* ptr);

public:
	DSP();
	float* inputFile(char* filedir);
	bool isThreadExist();
	bool isWaveForm();
	int isSpectrumForm();
	double getDuration();
	void drawSpectrum(SDL_Renderer* renderer);
	void tuner(bool graph, double bpm, double starttime);
	void DetachThread();
	vector<int> getPitch();
};

