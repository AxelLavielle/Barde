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
  MidiManager midi;
  std::vector<Instrument> instruments;
  int scaleAdjust;
  char previousNote;
  char note;
  double beats;
  std::vector<char> notesFromChord;

  instruments = parameters.getInstruments();
  midi.setTempo(parameters.getBpm());
  std::cout << "MUSIC SHEET OVERVIEW :" << std::endl;
  for (int i = 0; i < instruments.size(); i++){
      beats = 0;
      midi.changeInstrument(instruments[i], beats);
      for (int x = 0; x < chordsGrid.size(); x++){
        notesFromChord = chords.getChordFromName(chordsGrid[x].first);
        for (int y = 0; y < notesFromChord.size(); y++){
          if (y != 0)
            scaleAdjust = (notesFromChord[y] < previousNote ? 0 : 1);
          note = (notesFromChord[y] / 8) + ((chordsGrid[x].second - scaleAdjust) * 12);
          midi.noteOn(instruments[i].channel, note, instruments[i].velocity, beats);
          std::cout << "TICK " << beats << " : " << note << " [ON]" << std::endl;
          midi.noteOff(instruments[i].channel, note, instruments[i].velocity, beats + TIME_PER_TS);
          std::cout << "TICK " << beats + TIME_PER_TS << " : " << note << " [OFF]" << std::endl;
          previousNote = note;
        }
        beats += TIME_PER_TS;
      }
    }
  }

void		Disposition::placeArpeggios(MusicParameters &parameters)
{
  (void)parameters;
}
