#include "Drums.hh"

Drums::Drums()
{
}

Drums::~Drums()
{

}

void					Drums::createPattern(std::array<std::array<int, 12>, 3> &drumPattern)
{
	int					hihat_shuffle;
	int					type;

	hihat_shuffle = rand() % 100;
	if (hihat_shuffle >= 40)
	{
		drumPattern[0] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		type = rand() % 5;
		switch (type)
		{
		case 0 : drumPattern[1] = { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 };
				 break;
		case 1 : drumPattern[1] = { 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0 };
				 break;
		case 2 : drumPattern[1] = { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 };
				 break;
		case 3 : drumPattern[1] = { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1 };
				 break;
		case 4 : drumPattern[1] = { 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1 };
				 break;
		}
	}
	else
	{
		drumPattern[0] = { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 };
		type = rand() % 4;
		switch (type)
		{
		case 0: drumPattern[1] = { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 };
				break;
		case 1: drumPattern[1] = { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1 };
				break;
		case 2: drumPattern[1] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
				break;
		case 3: drumPattern[1] = { 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1 };
				break;
		}
	}

	drumPattern[2] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 };
	return;
}

t_note					Drums::createNote(char instru, int bar_pos)
{
	t_note				ret;

	ret.note.first = 0;
	ret.note.second = instru;
	ret.position = bar_pos * 0.3333;
	ret.duration = 0.2;
	return (ret);
}

std::vector<t_note>		Drums::createBar(std::array<std::array<int, 12>, 3> drumPattern)
{
	std::vector<t_note>	bar;
	char				i;
	int					j;


	for (j = 0; j < 12; j++)
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

void		Drums::blues(std::vector<std::vector<t_note>> &pattern, int total_bar)
{
	int		bar_nb;
	std::array<std::array<int, 12>,3> patternBar;

	bar_nb = 0;
	createPattern(patternBar);
	while (bar_nb < total_bar)
	{
		pattern.push_back(createBar(patternBar));
		bar_nb++;
	}
}

void		Drums::prepareDrums(MusicParameters &parameters, std::vector<std::vector<t_note>> &pattern)
{
	if (parameters.getStyleName() == "Blues")
		blues(pattern, 12);
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