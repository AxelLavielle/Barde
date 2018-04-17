#include "Drums.hh"

Drums::Drums()
{
}

Drums::~Drums()
{

}

void			Drums::pulse(MusicParameters &parameters, Instrument instru, double time)
{
	std::cout << instru.name << " at time " << time << std::endl;
	//parameters._midiManager.noteOn(instru.channel, 72, instru.velocity, beats);
	//parameters._midiManager.noteOff(instru.channel, 72, instru.velocity, beats + TIMES_PER_BAR);
}

void			Drums::bluesHihat(MusicParameters &parameters, double start, double end, int style)
{
	double		beats;
	Instrument	hihat;

	hihat.name = "Pedal Hihat";
	hihat.nb = PEDALHIHAT;
	hihat.channel = 11;
	hihat.velocity = 100;

	if (style == 1)
		for (beats = start; beats <= end; beats += 0.5)
			pulse(parameters, hihat, beats);
	else
		for (beats = start; beats <= end; beats += 1.0)
			pulse(parameters, hihat, beats);
}

void			Drums::bluesBassdrum(MusicParameters &parameters, double start, double end, int style)
{
	double		beats;
	Instrument	bass;

	bass.name = "Bass Drum";
	bass.nb = BASSDRUM1;
	bass.channel = 10;
	bass.velocity = 100;

	if (style == 1)
		for (beats = start; beats <= end; beats += 1.0)
			pulse(parameters, bass, beats);
	else if (style == 2)
		for (beats = start; beats <= end; beats += 2.0)
		{
			pulse(parameters, bass, beats);
			pulse(parameters, bass, beats + 0.5);
		}
	else
		for (beats = start; beats <= end; beats += 2.0)
		{
			pulse(parameters, bass, beats);
			pulse(parameters, bass, beats + 0.5);
			pulse(parameters, bass, beats + 1.5);
		}
}

void			Drums::bluesSnare(MusicParameters &parameters, double start, double end, int style)
{
	double		beats;
	Instrument	tom;

	tom.name = "Mid Tom";
	tom.nb = MIDTOM1;
	tom.channel = 12;
	tom.velocity = 100;

	if (style == 1)
		for (beats = start; beats <= end; beats += 2.0)
			pulse(parameters, tom, beats);
	else if (style == 2)
		for (beats = start; beats <= end; beats += 2.0)
		{
			pulse(parameters, tom, beats);
			pulse(parameters, tom, beats + 0.5);
		}
	else
		for (beats = start; beats <= end; beats += 2.0)
		{
			pulse(parameters, tom, beats);
			pulse(parameters, tom, beats + 0.5);
			pulse(parameters, tom, beats + 1.5);
		}
}

void		Drums::blues(MusicParameters &parameters, double time)
{
	double	beats;
	int		i = 1;
	int		style[3];

	style[0] = (rand() % 2) + 1;
	style[1] = (rand() % 3) + 1;
	style[2] = (rand() % 2) + 1;

	std::cout << "Charleston rythm style " << style[0] << std::endl;
	std::cout << "Bass drum rythm style " << style[1] << std::endl;
	std::cout << "Snare rythm style " << style[2] << std::endl;

	for (beats = 0.0; beats <= time; beats = beats + TIMES_PER_TRIPLET)
	{
		std::cout << "[Generating eigth note triplet number " << i << "]" << std::endl;
		bluesHihat(parameters, beats, beats + TIMES_PER_TRIPLET, style[0]);
		bluesBassdrum(parameters, beats, beats + TIMES_PER_TRIPLET, style[1]);
		bluesSnare(parameters, beats, beats + TIMES_PER_TRIPLET, style[2]);
		i++;
	}
}

void		Drums::placeDrums(MusicParameters &parameters)
{
	if (parameters.getStyleName() == "Blues")
		blues(parameters, 48.0);
}