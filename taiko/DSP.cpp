#include "DSP.h"

const int c4 = 24, d4b = 26, d4 = 27, e4b = 29, e4 = 31, f4 = 32,
g4b = 34, g4 = 36, a4b = 38, a4 = 40, b4b = 43, b4 = 45,
c5 = 48, d5b = 51, d5 = 54, e5b = 57, e5 = 60, f5 = 64,
g5b = 68, g5 = 72, a5b = 76, a5 = 81, b5b = 85, b5 = 91,
c6 = 96, d6b = 102, d6 = 108, e6b = 114, e6 = 121;

static int Tuning(void* ptr)
{
	DSP* data = (DSP*)ptr;
	data->isSpectrumform = 1;

	int len = data->wav_length / 4;
	int frame = 4096;
	int hop = 512;
	int freq_bin = frame / 2 + 1;
	data->spectrumR = new int* [(len - frame) / hop + 1];
	data->spectrumG = new int* [(len - frame) / hop + 1];
	data->spectrumB = new int* [(len - frame) / hop + 1];
	int k = 0;

	vector<int> freqindex;
	double _c4 = 0, _d4b = 0, _d4 = 0, _e4b = 0, _e4 = 0, _f4 = 0,
		_g4b = 0, _g4 = 0, _a4b = 0, _a4 = 0, _b4b = 0, _b4 = 0,
		_c5 = 0, _d5b = 0, _d5 = 0, _e5b = 0, _e5 = 0, _f5 = 0,
		_g5b = 0, _g5 = 0, _a5b = 0, _a5 = 0, _b5b = 0, _b5 = 0,
		_c6 = 0, _d6b = 0, _d6 = 0, _e6b = 0, _e6 = 0;

	double timePeriod = data->starttime;

	for (int i = 0; i + frame - 1 < len; i += hop)
	{
		vector<Complex> a(frame);
		double* mag = new double[freq_bin];
		double* freq = new double[freq_bin];
		data->spectrumR[k] = new int[freq_bin];
		data->spectrumG[k] = new int[freq_bin];
		data->spectrumB[k] = new int[freq_bin];
		for (int j = 0; j < freq_bin; j++)
			freq[j] = 0;

		for (int j = 0; j < frame; j++)
		{
			Complex c = Complex((double)data->right[i + j], 0);
			a[j] = c;
		}
		data->fft(a, frame);

		for (int j = 0; j < freq_bin; j++)
		{
			double magnitude = sqrt(a[j].real() * a[j].real() + a[j].imag() * a[j].imag());

			if (magnitude != 0)
				switch (j)
				{
				case c4:
					_c4 += 20 * log10(magnitude);
					break;
				case d4:
					_d4 += 20 * log10(magnitude);
					break;
				case e4:
					_e4 += 20 * log10(magnitude);
					break;
				case f4:
					_f4 += 20 * log10(magnitude);
					break;
				case g4:
					_g4 += 20 * log10(magnitude);
					break;
				case a4:
					_a4 += 20 * log10(magnitude);
					break;
				case b4:
					_b4 += 20 * log10(magnitude);
					break;
				case c5:
					_c5 += 20 * log10(magnitude);
					break;
				case d5:
					_d5 += 20 * log10(magnitude);
					break;
				case e5b:
					_e5b += 20 * log10(magnitude);
					break;
				case e5:
					_e5 += 20 * log10(magnitude);
					break;
				case f5:
					_f5 += 20 * log10(magnitude);
					break;
				case g5:
					_g5 += 20 * log10(magnitude);
					break;
				case a5:
					_a5 += 20 * log10(magnitude);
					break;
				case b5:
					_b5 += 20 * log10(magnitude);
					break;
				case c6:
					_c6 += 20 * log10(magnitude);
					break;
				case d6:
					_d6 += 20 * log10(magnitude);
					break;
				case e6:
					_e6 += 20 * log10(magnitude);
					break;
				}


			if (magnitude != 0)
			{
				double db = 20 * log10(magnitude) + 60;
				data->spectrumR[k][j] = (int)((db / 110) * 200);
				data->spectrumG[k][j] = (db > 110) ? (int)(200 - (db - 110) * 200 / 110) : (int)((db / 110) * 200);
				data->spectrumB[k][j] = (int)(((220 - db) / 110) * 200);
				if (data->spectrumR[k][j] > 200) data->spectrumR[k][j] = 200;
				if (data->spectrumB[k][j] > 200) data->spectrumB[k][j] = 200;
			}
			else
			{
				data->spectrumR[k][j] = 0;
				data->spectrumG[k][j] = 0;
				data->spectrumB[k][j] = 200;
			}
		}

		if (timePeriod <= ((k)*hop + (double)frame / 2) / data->wav_spec.freq)
		{
			double max = 0;
			int maxindex = 0;
			for (int j = 0; j < freq_bin; j++)
			{
				switch (j)
				{
				case c4:
					if (_c4 > max)
					{
						max = _c4;
						maxindex = j;
					}
					break;
				case d4:
					if (_d4 > max)
					{
						max = _d4;
						maxindex = j;
					}
					break;
				case e4:
					if (_e4 > max)
					{
						max = _e4;
						maxindex = j;
					}
					break;
				case f4:
					if (_f4 > max)
					{
						max = _f4;
						maxindex = j;
					}
					break;
				case g4:
					if (_g4 > max)
					{
						max = _g4;
						maxindex = j;
					}
					break;
				case a4:
					if (_a4 > max)
					{
						max = _a4;
						maxindex = j;
					}
					break;
				case b4:
					if (_b4 > max)
					{
						max = _b4;
						maxindex = j;
					}
					break;
				case c5:
					if (_c5 > max)
					{
						max = _c5;
						maxindex = j;
					}
					break;
				case d5:
					if (_d5 > max)
					{
						max = _d5;
						maxindex = j;
					}
					break;
				case e5b:
					if (_e5b > max)
					{
						max = _e5b;
						maxindex = j;
					}
					break;
				case e5:
					if (_e5 > max)
					{
						max = _e5;
						maxindex = j;
					}
					break;
				case f5:
					if (_f5 > max)
					{
						max = _f5;
						maxindex = j;
					}
					break;
				case g5:
					if (_g5 > max)
					{
						max = _g5;
						maxindex = j;
					}
					break;
				case a5:
					if (_a5 > max)
					{
						max = _a5;
						maxindex = j;
					}
					break;
				case b5:
					if (_b5 > max)
					{
						max = _b5;
						maxindex = j;
					}
					break;
				case c6:
					if (_c6 > max)
					{
						max = _c6;
						maxindex = j;
					}
					break;
				case d6:
					if (_d6 > max)
					{
						max = _d6;
						maxindex = j;
					}
					break;
				case e6:
					if (_e6 > max)
					{
						max = _e6;
						maxindex = j;
					}
					break;
				}
			}

			if (max > 65)
			{
				data->pitch.push_back(maxindex);
			}
			else
			{
				data->pitch.push_back(0);
			}

			_c4 = 0; _d4b = 0; _d4 = 0; _e4b = 0; _e4 = 0; _f4 = 0;
			_g4b = 0; _g4 = 0; _a4b = 0; _a4 = 0; _b4b = 0; _b4 = 0;
			_c5 = 0; _d5b = 0; _d5 = 0; _e5b = 0; _e5 = 0; _f5 = 0;
			_g5b = 0; _g5 = 0; _a5b = 0; _a5 = 0; _b5b = 0; _b5 = 0;
			_c6 = 0; _d6b = 0; _d6 = 0; _e6b = 0; _e6 = 0;
			timePeriod += 60.0 / data->bpm;

		}

		k++;
	}
	data->isSpectrumform = 2;
	return 0;
}

DSP::DSP() : Object()
{
	iswaveform = false;
	isSpectrumform = 0;
	threadExist = false;
}

float* DSP::inputFile(char* filedir)
{
	Uint8* wav_buffer;
	float* result;

	if (SDL_LoadWAV(filedir, &wav_spec, &wav_buffer, &wav_length) == NULL)
	{
		fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
		return nullptr;
	}
	else
	{
		samp = getWavAmplitudes(wav_buffer);
		result = processAmplitudes(samp);
		iswaveform = true;

		//Byte Rate per second: Sample Rate * Channels * (Bits Per Sample / 8)
		int byte_rate = wav_spec.freq * wav_spec.channels * (SDL_AUDIO_BITSIZE(wav_spec.format) / 8);
		duration = (double)wav_length / byte_rate;
		SDL_FreeWAV(wav_buffer);

		return result;
	}
}

bool DSP::isWaveForm()
{
	return iswaveform;
}

int DSP::isSpectrumForm()
{
	return isSpectrumform;
}

int* DSP::getWavAmplitudes(Uint8* wav_buffer)
{
	printf("Calculting WAV amplitudes\n");

	//const int BUFFER_SIZE = 4096;
	const double WAVEFORM_HEIGHT_COEFFICIENT = 1.0;

	int maximumArrayLength = wav_length;
	int* finalAmplitudes = new int[wav_length / 2];
	right = new int[wav_length / 4];
	int samplesPerPixel = wav_length / maximumArrayLength;

	int currentSampleCounter = 0;
	//int arrayCellPosition = 0;
	float currentCellValue = 0.0f;

	int arrayCellValue = 0;

	//int count = 0;
	//int bufferCount = 0;
	int j = 0;
	for (unsigned int i = 0; i < wav_length - 1; i += 2, j++) {

		arrayCellValue = (int)(((((wav_buffer[i + 1] << 8) | wav_buffer[i] & 0xffff) << 16) / 32767) * WAVEFORM_HEIGHT_COEFFICIENT);
		//finalAmplitudes[i] = finalAmplitudes[i + 1] = currentCellValue;
		finalAmplitudes[j] = arrayCellValue;
		if (currentSampleCounter != samplesPerPixel) {
			++currentSampleCounter;
			currentCellValue += abs(arrayCellValue);
		}
		else {
			currentSampleCounter = 0;
			currentCellValue = 0;
		}
	}

	for (unsigned int i = 0; i < wav_length / 2; i++)
	{
		if (i / 2)
			right[i / 2] = finalAmplitudes[i];
	}

	return finalAmplitudes;
}

float* DSP::processAmplitudes(int* sourcePcmData)
{
	printf("Processing WAV amplitudes\n");

	int width = 1000;
	float* waveData = new float[width];
	int samplesPerPixel = wav_length / (2 * width);

	for (int w = 0; w < width; w++) {

		int c = w * samplesPerPixel;
		float nValue = 0.0f;

		for (int s = 0; s < samplesPerPixel; s++) {
			nValue += (abs(sourcePcmData[c + s]) / 65536.0f);
		}

		waveData[w] = nValue / samplesPerPixel;
	}
	printf("Finished Processing amplitudes\n");
	return waveData;
}


double DSP::getDuration()
{
	return duration;
}


void DSP::tuner(bool g, double b, double s)
{
	graph = g;
	bpm = b;
	starttime = s;

	SDL_Log("Simple SDL_CreateThread test:\n");
	thread = SDL_CreateThread(Tuning, "Tuning", this);
	threadExist = true;
	if (NULL == thread)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateThread failed: %s\n", SDL_GetError());
	}
}

vector<int> DSP::getPitch()
{
	return pitch;
}

void DSP::DetachThread()
{
	threadExist = false;
	SDL_DetachThread(thread);
}


bool DSP::isThreadExist()
{
	return threadExist;
}

void DSP::fft(vector<Complex>& a, int lim)
{
	if (lim == 1)
		return;
	vector<Complex> a0(lim >> 1), a1(lim >> 1);

	for (int i = 0; i < lim; i += 2)
	{
		a0[i >> 1] = a[i];
		a1[i >> 1] = a[i + 1];
	}

	fft(a0, lim >> 1);
	fft(a1, lim >> 1);

	Complex wn(cos(2 * 3.1415926 / lim), -sin(2 * 3.1415926 / lim));
	Complex w(1, 0);

	for (int k = 0; k < (lim >> 1); k++)
	{
		Complex t = w * a1[k];
		a[k] = a0[k] + t;
		a[k + (lim >> 1)] = a0[k] - t;
		w = w * wn;
	}
}


void DSP::drawSpectrum(SDL_Renderer* renderer)
{
	int len = wav_length / 4;
	int frame = 4096;
	int hop = 512;
	int posX = 100, posY = 500;
	int maxX = 1800, maxY = 270;
	int stroke = 10, none = 0;
	Object::modify(posX, posY);
	Object::modify(maxX, maxY);
	Object::modify(stroke, none);
	int freq_bin = frame / 2 + 1;
	double timePeriod = starttime;
	int k = -1;
	boxRGBA(renderer, posX - stroke, posY - stroke, posX + maxX + stroke, posY + maxY + stroke, 0, 0, 0, 255);
	for (int i = 0; i < (len - frame) / hop + 1 && i < maxX; i++)
	{
		if (timePeriod <= (i * hop + (double)frame / 2) / wav_spec.freq)
		{
			k++;
			timePeriod += 60.0 / bpm;
		}
		for (int j = 0; j < freq_bin && j < maxY; j++)
		{
			if (k >= 0)
			{
				pixelRGBA(renderer, i + posX, j + posY, spectrumR[i][j], spectrumG[i][j], spectrumB[i][j], 255);
				if (pitch[k] == j || pitch[k] == j - 1 || pitch[k] == j + 1)
					pixelRGBA(renderer, i + posX, j + posY, (j > 50) ? 101 : 241, (j > 50) ? 190 : 85, (j > 50) ? 188 : 45, 150);
			}
			else
				pixelRGBA(renderer, i + posX, j + posY, spectrumR[i][j], spectrumG[i][j], spectrumB[i][j], 255);
		}

	}

}