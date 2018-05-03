#include <math.h>
#include "Disposition.hh"

Disposition::Disposition()
{

}

Disposition::~Disposition()
{

}

void		Disposition::placeChords(MusicParameters &parameters, std::vector<std::pair<char, char> > chordsGrid)
{
  Chords chords;
  std::vector<Instrument> instruments;
  char scaleAdjust;
  char previousNote;
  int note;
  double beats;
  std::vector<char> notesFromChord;

  beats = 0;
  instruments = parameters.getInstrumentsChords();
  parameters._midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    beats = 0;
    parameters._midiManager.changeInstrument(instruments[i], beats);
    for (unsigned char x = 0; x < chordsGrid.size(); x++){
      notesFromChord = chords.getChordFromName(chordsGrid[x].first);
      scaleAdjust = 0;
      for (unsigned char y = 0; y < notesFromChord.size(); y++){
      	if (y != 0)
      	  scaleAdjust = (notesFromChord[y] < previousNote ? 0 : 1);
      	note = (notesFromChord[y] / 8) + ((chordsGrid[x].second + scaleAdjust) * 12);
      	parameters._midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, beats + 1);
      	parameters._midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, beats + 1 + TIMES_PER_BAR);
      	previousNote = note;
          }
	  std::cout << "Chord " << (int)x << " at time " << beats << std::endl;
	  beats += TIMES_PER_BAR;
    }
  }
}

void    Disposition::placeChords(MusicParameters &parameters, std::vector<std::vector<t_note> > pattern)
{
  Chords chords;
  std::vector<Instrument> instruments;
  char scaleAdjust;
  char previousNote;
  int note;
  std::vector<char> notesFromChord;

  instruments = parameters.getInstrumentsChords();
  parameters._midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    parameters._midiManager.changeInstrument(instruments[i], 0);
    for (unsigned char x = 0; x < pattern.size(); x++){
      for (unsigned char k = 0; k < pattern[x].size(); k++){
        notesFromChord = chords.getChordFromName(pattern[x][k].note.first);
        scaleAdjust = 0;
        for (unsigned char y = 0; y < notesFromChord.size(); y++){
          if (y != 0)
            scaleAdjust = (notesFromChord[y] < previousNote ? 1 : 0);
          note = (notesFromChord[y] / 8) + ((pattern[x][k].note.second + scaleAdjust) * 12);
          parameters._midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, pattern[x][k].position);
          parameters._midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, pattern[x][k].position + pattern[x][k].duration);
          previousNote = note;
        }
      }
    }
  }
}

void		Disposition::placeArpeggios(MusicParameters &parameters, std::vector<std::pair<char, char> > notesList)
{
  std::vector<Instrument> instruments;
  int note;
  double beats;

  instruments = parameters.getInstrumentsArpeggios();
  parameters._midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    beats = 1;
    parameters._midiManager.changeInstrument(instruments[i], beats);
    for (unsigned char x = 0; x < notesList.size(); x++){
      note = (notesList[x].first / 8) + ((notesList[x].second) * 12);
      parameters._midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, beats);
      parameters._midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, beats + 1.2);
      beats += 1;
      beats = (fmod(beats, 4) == 0.0 ? beats + 1 : beats);
    }
  }
}

void    Disposition::placeArpeggios(MusicParameters &parameters, std::vector<std::vector<t_note> > pattern)
{
  std::vector<Instrument> instruments;
  int note;

  instruments = parameters.getInstrumentsArpeggios();
  parameters._midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    parameters._midiManager.changeInstrument(instruments[i], 0);
    for (unsigned char y = 0; y < pattern.size(); y++){
      for (unsigned char k = 0; k < pattern[y].size(); k++){
        note = (pattern[y][k].note.first / 8) + ((pattern[y][k].note.second) * 12);
		std::cout << "Arpeggio: " << (int)y << " Note: " << (float)(pattern[y][k].position + (y * TIMES_PER_BAR)) << " - " << (float)(pattern[y][k].duration) << std::endl;
		parameters._midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, pattern[y][k].position + 1 + (y * TIMES_PER_BAR));
        parameters._midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, pattern[y][k].position + 1 + (y * TIMES_PER_BAR) + pattern[y][k].duration);
      }
    }
  }
}

void	Disposition::placeDrums(MusicParameters &parameters, std::vector<std::vector<t_note> > pattern)
{
  if (!parameters.getInstrumentsDrums())
    return;
  std::vector<Instrument> instruments;
  int note;
  
  parameters._midiManager.setTempo(parameters.getBpm());
  for (unsigned char y = 0; y < pattern.size(); y++){
    for (unsigned char k = 0; k < pattern[y].size(); k++){
      parameters._midiManager.changeInstrument(instruments[pattern[y][k].note.second], 0);
      note = (pattern[y][k].note.first / 8) + (5 * 12);
      std::cout << "Drum: " << (int)y << " Note: " << (float)(pattern[y][k].position + (y * TIMES_PER_BAR)) << std::endl;
      parameters._midiManager.noteOn(instruments[pattern[y][k].note.second].channel, note, instruments[pattern[y][k].note.second].velocity, pattern[y][k].position + 1 + (y * TIMES_PER_BAR));
      parameters._midiManager.noteOff(instruments[pattern[y][k].note.second].channel, note, instruments[pattern[y][k].note.second].velocity, pattern[y][k].position + 1 + (y * TIMES_PER_BAR) + pattern[y][k].duration);
    }
  }
}
