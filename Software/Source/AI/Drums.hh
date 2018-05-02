#ifndef		DRUMS_HH
	#define DRUMS_HH_

#include "../MusicParameters.hh"
#include "../MidiManager/MidiManager.hh"

#define TIMES_PER_TRIPLET 12

class Drums
{
public:
	Drums();
	~Drums();

	static void					placeDrums(MusicParameters &parameters);

private:
	static void					pulse(MusicParameters &parameters, Instrument instru, double time);
	static void					bluesHihat(MusicParameters &parameters, double start, double end, int style);
	static void					bluesBassdrum(MusicParameters &parameters, double start, double end, int style);
	static void					bluesSnare(MusicParameters &parameters, double start, double end, int style);
	static void					blues(MusicParameters &parameters, double time);
};

#endif // DRUMS_HH_