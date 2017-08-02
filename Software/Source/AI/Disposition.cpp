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
  instruments = parameters.getInstruments();
  parameters._midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    beats = 0;
    parameters._midiManager.changeInstrument(instruments[i], beats);
    for (unsigned char x = 0; x < chordsGrid.size(); x++){
      notesFromChord = chords.getChordFromName(chordsGrid[x].first);
      scaleAdjust = 1;
      for (unsigned char y = 0; y < notesFromChord.size(); y++){
	if (y != 0)
	  scaleAdjust = (notesFromChord[y] < previousNote ? 0 : 1);
	note = (notesFromChord[y] / 8) + ((chordsGrid[x].second - scaleAdjust) * 12);
	parameters._midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, beats);
	parameters._midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, beats + TIME_PER_TS);
	previousNote = note;
      }
      beats += TIME_PER_TS;
    }
  }
}

void		Disposition::placeArpeggios(MusicParameters &parameters, std::vector<std::pair<char, char> > notesList)
{
  std::vector<Instrument> instruments;
  int note;
  double beats;

  instruments = parameters.getInstruments();
  parameters._midiManager.setTempo(parameters.getBpm());
  for (unsigned char i = 0; i < instruments.size(); i++){
    beats = 1;
    parameters._midiManager.changeInstrument(instruments[i], beats);
    for (unsigned char x = 0; x < notesList.size(); x++){
      note = (notesList[x].first / 8) + ((notesList[x].second - 1) * 12);
      parameters._midiManager.noteOn(instruments[i].channel, note, instruments[i].velocity, beats);
      parameters._midiManager.noteOff(instruments[i].channel, note, instruments[i].velocity, beats + 1.2);
      beats += 1;
      beats = (fmod(beats, 4) == 0.0 ? beats + 1 : beats);
    }
  }
}
