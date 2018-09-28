#include "Drums.hh"

Drums::Drums()
{
}

Drums::~Drums()
{

}

void					Drums::createPatternBlues(std::array<std::vector<bool>, 3> &drumPattern, int size)
{
	int bass = rand() % 4;
	int snare = rand() % 4;
	while (snare == bass)
		snare = rand() % 4;
	int hihat = rand() % 2;

	for (int i = 0; i < size; i++)
	{
		drumPattern[0].push_back((hihat || (i % 4 != bass && i % 4 != snare)) ? 1 : 0);
		drumPattern[1].push_back((i % 4 == bass) ? 1 : 0);
		drumPattern[2].push_back((i % 4 == snare) ? 1 : 0);
	}
}

void					Drums::createPatternReggae(std::array<std::vector<bool>, 3> &drumPattern, int size)
{
	int hihat = rand() % 2;
	for (int i = 0; i < size; i++)
	{
//		drumPattern[0].push_back((hihat || (i % 4 != 2 && !(i % 2))) ? 1 : 0);
		drumPattern[0].push_back(1);
		drumPattern[1].push_back((i % 2) ? 0 : 1);
		drumPattern[2].push_back((i % 4 == 2) ? 1 : 0);
	}
}

t_note					Drums::createNote(char instru, int bar_pos)
{
	t_note				ret;

	ret.note.first = 0;
	ret.note.second = instru;
	ret.position = bar_pos / 3;
	ret.duration = 0.2;
	return (ret);
}

std::vector<t_note>		Drums::createBar(std::array<std::vector<bool>, 3> drumPattern, int size)
{
	std::vector<t_note>	bar;
	char				i;
	int					j;

	for (j = 0; j < size; j++)
	{
		i = 0;
		while (i < 3)
		{
			if (drumPattern[i][j] == 1)
				bar.push_back(createNote(i, j));
			i++;
		}
	}
	return (bar);
}

void		Drums::blues(std::vector<std::vector<t_note>> &pattern)
{
	int		bar_nb;
	std::array<std::vector<bool>, 3> patternBar;

	bar_nb = 0;
	createPatternBlues(patternBar, 12);
	while (bar_nb < 12)
	{
		pattern.push_back(createBar(patternBar, 12));
		bar_nb++;
	}
}

void		Drums::reggae(std::vector<std::vector<t_note>> &pattern)
{
	int		bar_nb;
	std::array<std::vector<bool>, 3> patternBar;

	bar_nb = 0;
	createPatternReggae(patternBar, 8);
	while (bar_nb < 8)
	{
		pattern.push_back(createBar(patternBar, 8));
		bar_nb++;
	}
}

void		Drums::prepareDrums(const MusicParameters &parameters, std::vector<std::vector<t_note>> &pattern)
{
	if (parameters.getStyleName() == "Blues")
		blues(pattern);
	else if (parameters.getStyleName() == "Reggae")
		reggae(pattern);
}

void		Drums::initialize(MidiManager &_midiManager, std::vector<Instrument> &drumInstruments)
{
	Instrument	hihat;
	Instrument	bass;
	Instrument	snare;

	hihat.name = "Pedal Hihat";
	hihat.nb = PEDALHIHAT;
	hihat.channel = 10;
	hihat.velocity = 100;

	bass.name = "Bass Drum";
	bass.nb = BASSDRUM1;
	bass.channel = 11;
	bass.velocity = 100;

	snare.name = "Snare Drum";
	snare.nb = SNAREDRUMACOUSTICSNARE;
	snare.channel = 12;
	snare.velocity = 100;

	drumInstruments.push_back(hihat);
	drumInstruments.push_back(bass);
	drumInstruments.push_back(snare);

	_midiManager.changeInstrument(hihat, 1.0);
	_midiManager.changeInstrument(bass, 1.0);
	_midiManager.changeInstrument(snare, 1.0);
}
