#include <math.h>
#include "Disposition.hh"

Disposition::Disposition()
{

}

Disposition::~Disposition()
{

}

void		Disposition::placeChords(MidiManager &_midiManager, const MusicParameters &parameters, std::vector<std::pair<char, char> > chordsGrid)
{
  Chords chords;
  std::vector<Instrument> instruments;
  char scaleAdjust;
  int note;
  double beats;
  std::vector<char> notesFromChord;

  beats = 0;
  int startTime = Time::getMillisecondCounterHiRes() * 0.001;
  instruments = parameters.getInstrumentsChords();
  _midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    beats = 0;
    _midiManager.changeInstrument(instruments[i], 1.0);
    for (unsigned char x = 0; x < chordsGrid.size(); x++){
      notesFromChord = chords.getChordFromName(chordsGrid[x].first);
      scaleAdjust = 0;
      for (unsigned char y = 0; y < notesFromChord.size(); y++){
      	if (y != 0)
      	  scaleAdjust = (notesFromChord[y] < notesFromChord[y-1] ? 0 : 1);
      	note = (notesFromChord[y] / 8) + ((chordsGrid[x].second + scaleAdjust) * 12);
		_midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, beats + 1);
	//	_midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, Time::getMillisecondCounterHiRes() * 0.001 - startTime);
      	_midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, beats + 1 + TIMES_PER_BAR);
          }
	  beats += TIMES_PER_BAR;
    }
  }
}

void    Disposition::placeChords(MidiManager &_midiManager, const MusicParameters &parameters, std::vector<std::vector<t_note> > pattern)
{
  Chords chords;
  std::vector<Instrument> instruments;
  char scaleAdjust;
  int note;
  std::vector<char> notesFromChord;

  instruments = parameters.getInstrumentsChords();
  _midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    _midiManager.changeInstrument(instruments[i], 1.0);
    for (unsigned char x = 0; x < pattern.size(); x++){
      for (unsigned char k = 0; k < pattern[x].size(); k++){
        notesFromChord = chords.getChordFromName(pattern[x][k].note.first);
        scaleAdjust = 0;
        for (unsigned char y = 0; y < notesFromChord.size(); y++){
          if (y != 0)
            scaleAdjust = (notesFromChord[y] < notesFromChord[y-1] ? 1 : 0);
          note = (notesFromChord[y] / 8) + ((pattern[x][k].note.second + scaleAdjust) * 12);
          _midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, pattern[x][k].position);
          _midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, pattern[x][k].position + pattern[x][k].duration);
        }
      }
    }
  }
}

void		Disposition::placeArpeggios(MidiManager &_midiManager, const MusicParameters &parameters, std::vector<std::pair<char, char> > notesList)
{
  std::vector<Instrument> instruments;
  int note;
  double beats;

  instruments = parameters.getInstrumentsArpeggios();
  _midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    beats = 1;
    _midiManager.changeInstrument(instruments[i], beats);
    for (unsigned char x = 0; x < notesList.size(); x++){
      note = (notesList[x].first / 8) + ((notesList[x].second) * 12);
      _midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, beats);
      _midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, beats + 1.2);
      beats += 1;
      beats = (fmod(beats, 4) == 0.0 ? beats + 1 : beats);
    }
  }
}

void    Disposition::placeArpeggios(MidiManager &_midiManager, const MusicParameters &parameters, std::vector<std::vector<t_note> > pattern)
{
  std::vector<Instrument> instruments;
  int note;

  instruments = parameters.getInstrumentsArpeggios();
  _midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    _midiManager.changeInstrument(instruments[i], 0);
    for (unsigned char y = 0; y < pattern.size(); y++){
      for (unsigned char k = 0; k < pattern[y].size(); k++){
        note = (pattern[y][k].note.first / 8) + ((pattern[y][k].note.second) * 12);
		_midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, pattern[y][k].position + 1 + (y * TIMES_PER_BAR));
        _midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, pattern[y][k].position + 1 + (y * TIMES_PER_BAR) + pattern[y][k].duration);
      }
    }
  }
}

void	Disposition::placeDrums(MidiManager &_midiManager, const MusicParameters &parameters, std::vector<std::vector<t_note> > pattern, std::vector<Instrument> drumInstruments)
{
  Instrument				instru;
  t_note					current;
  int						note;

  _midiManager.setTempo(parameters.getBpm());

  for (unsigned char y = 0; y < pattern.size(); y++)
  {
    for (unsigned char k = 0; k < pattern[y].size(); k++)
	{
		current = pattern[y][k];
		instru = drumInstruments[current.note.second];
		note = (current.note.first / 8) + (6 * 12);
		_midiManager.noteOn(instru.channel, note, instru.velocity, current.position + 1 + (y * TIMES_PER_BAR));
		_midiManager.noteOff(instru.channel, note, instru.velocity, current.position + 1 + (y * TIMES_PER_BAR) + current.duration);
    }
  }
}
