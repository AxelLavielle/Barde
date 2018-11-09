#ifndef		DRUMS_HH
	#define DRUMS_HH_

#include	"../MusicParameters.hh"
#include	"../MidiManager/MidiManager.hh"
#include	"Pattern.hh"
#include	<array>

class Drums
{
public:
	Drums();
	~Drums();

	static void					prepareDrums(const MusicParameters &parameters, std::vector<std::vector<t_note>> &pattern);
	static void					initialize(MidiManager &_midiManager, std::vector<Instrument> &drumInstruments);

private:
	static	void				createPatternBlues(std::array<std::vector<bool>, 3> &drumPattern, int size);
	static	void				createPatternReggae(std::array<std::vector<bool>, 3> &drumPattern, int size);
	static	t_note				createNote(char instru, int bar_pos);
	static	std::vector<t_note>	createBar(std::array<std::vector<bool>, 3> drumPattern, int size, int bar_nb);
	static void					blues(std::vector<std::vector<t_note>> &pattern);
	static void					reggae(std::vector<std::vector<t_note>> &pattern);
};

#endif // DRUMS_HH_
