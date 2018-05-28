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

	static void					prepareDrums(MusicParameters &parameters, std::vector<std::vector<t_note>> &pattern);
	static void					initialize(MidiManager &_midiManager, MusicParameters &parameters);

private:
	static	void				createPattern(std::array<std::array<int, 12>, 3> &drumPattern);
	static	t_note				createNote(char instru, int bar_pos);
	static	std::vector<t_note>	createBar(std::array<std::array<int, 12>, 3> drumPattern);
	static void					blues(std::vector<std::vector<t_note>> &pattern, int total_bar);
};

#endif // DRUMS_HH_