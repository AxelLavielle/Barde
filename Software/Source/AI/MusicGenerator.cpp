/*
  ==============================================================================

    MusicGenerator.cpp
    Created: 13 Mar 2017 1:46:35pm
    Author:  Anthony

  ==============================================================================
*/

#include "MusicGenerator.hh"

MusicGenerator::MusicGenerator()
{

}

MusicGenerator::~MusicGenerator()
{

}
/*
void			MusicGenerator::drumsPOC(MusicParameters &parameters)
{
	Instrument	bassdrum;
	Instrument	midtom;
	Instrument	hihat;
	Instrument	rcymbal;
	Instrument	ccymbal;
	//	int			i = 0;
	double		beats = 0.0;

	std::cout << "IN DRUMSPOC" << std::endl;

	bassdrum.name = "Bass Drum";
	bassdrum.nb = BASSDRUM1;
	bassdrum.channel = 10;
	bassdrum.velocity = 100;

	hihat.name = "Pedal Hihat";
	hihat.nb = PEDALHIHAT;
	hihat.channel = 11;
	hihat.velocity = 100;

	midtom.name = "Mid Tom";
	midtom.nb = MIDTOM1;
	midtom.channel = 12;
	midtom.velocity = 100;

	rcymbal.name = "Ride Cymbal";
	rcymbal.nb = RIDECYMBAL1;
	rcymbal.channel = 13;
	rcymbal.velocity = 100;

	ccymbal.name = "Crash Cymbal";
	ccymbal.nb = CRASHCYMBAL1;
	ccymbal.channel = 14;
	ccymbal.velocity = 100;

	parameters._midiManager.changeInstrument(hihat, 1.0);
	for (beats = 1.0; beats <= 48.0; beats = beats + 0.5)
	{
		parameters._midiManager.noteOn(hihat.channel, 72, hihat.velocity, beats);
		parameters._midiManager.noteOff(hihat.channel, 72, hihat.velocity, beats + TIMES_PER_BAR);
	}

	parameters._midiManager.changeInstrument(bassdrum, 1.0);
	for (beats = 1.0; beats <= 48.0; beats = beats + 1.0)
	{
		parameters._midiManager.noteOn(bassdrum.channel, 72, bassdrum.velocity, beats);
		parameters._midiManager.noteOff(bassdrum.channel, 72, bassdrum.velocity, beats + TIMES_PER_BAR);
	}

	/*
	parameters._midiManager.changeInstrument(midtom, 0.0);
	for (beats = 0.0; beats <= 48.0; beats = beats + 1.0)
	{
		parameters._midiManager.noteOn(hihat, 72, hihat.velocity, beats);
		parameters._midiManager.noteOff(hihat, 72, hihat.velocity, beats + TIMES_PER_BAR);
	}

	parameters._midiManager.changeInstrument(rcymbal, 1.0);
	for (beats = 8.0; beats <= 48.0; beats = beats + 16.0)
	{
		parameters._midiManager.noteOn(rcymbal.channel, 72, rcymbal.velocity, beats);
		parameters._midiManager.noteOff(rcymbal.channel, 72, rcymbal.velocity, beats + 8.0);
	}

	parameters._midiManager.changeInstrument(ccymbal, 1.0);
	for (beats = 16.0; beats <= 48.0; beats = beats + 16.0)
	{
		parameters._midiManager.noteOn(ccymbal.channel, 72, ccymbal.velocity, beats);
		parameters._midiManager.noteOff(ccymbal.channel, 72, ccymbal.velocity, beats + 8.0);
	}
}
*/

void			MusicGenerator::launch(std::vector<MusicParameters> &_graph2genQ, std::vector<std::pair<Midi, int> > &_gen2playQ, std::mutex &_graph2genM, std::mutex &_gen2playM, bool &stop)
{
	MusicParameters p;
	bool b = false;

	while (!stop)
	{
		_graph2genM.lock();
		if (_graph2genQ.size() > 0)
		{
			p = _graph2genQ[0];
			b = true;
			_graph2genQ.erase(_graph2genQ.begin());
			_gen2playM.lock();
			_gen2playQ.clear();
			_gen2playM.unlock();
		}
		_graph2genM.unlock();
		_gen2playM.lock();
		if (b && _gen2playQ.size() < 3)
		{
			Midi m = createMusic(p);
			_gen2playQ.push_back(std::make_pair(m, p.getBpm()));
		}
		_gen2playM.unlock();
		Tools::sleep(100);
	}
}

Midi			MusicGenerator::createMusic(MusicParameters &parameters)
{
  MidiManager	_midiManager;

  /* DRUMS */

  /*
  drumsPOC(parameters);
  bool		onlydrums = true;
  if (onlydrums == true)
  {
	  parameters.setMidi(parameters._midiManager.createMidi(48));
	  parameters._midiManager.writeToFile("./test.mid");
	  return (Midi());
  }
  */

//  Drums::placeDrums(parameters);

  /* DRUMS */

  /* INITIALISATION */
  ObjectMarkov						markovObj(SOURCEMARKOV + std::string("blues.json"), 1, parameters.getSeed());
  std::vector<std::pair<char, char> >			markovChords;
  std::vector<std::pair<char, char> >			markovTmp;
  StyleSettings						style;
  std::vector<std::pair<char, char> >			chord;
  Chords						allChords;
  /* INITIALISATION */

  /* CHORDS */
  markovObj.callLua();
  markovChords = markovObj.getVectorFromJson();
  style = markovObj.getStyleFromJson();
  Resolution::parsingMarkov(style, &markovChords);

  std::pair<char, char> noteA = markovChords[0];
  std::pair<char, char> noteB = std::make_pair(static_cast<char>(AI::searchNoteFromDist((markovChords[0].first / 8 * 8), 5) + markovChords[0].first % 8), static_cast<char>(4));
  std::pair<char, char> noteC = std::make_pair(static_cast<char>(AI::searchNoteFromDist((markovChords[0].first / 8 * 8), 7) + markovChords[0].first % 8), static_cast<char>(4));
  std::cout << "##########################BITE " << (int)noteA.first << " " << (int)noteB.first << " " << (int)noteC.first << std::endl;
  if (noteB.first < noteA.first)
    noteB.second++;
  if (noteC.first < noteA.first)
    noteC.second++;
  markovChords.push_back(noteA);
  markovChords.push_back(noteA);
  markovChords.push_back(noteA);
  markovChords.push_back(noteB);
  markovChords.push_back(noteB);
  markovChords.push_back(noteA);
  markovChords.push_back(noteA);
  markovChords.push_back(noteC);
  markovChords.push_back(noteB);
  markovChords.push_back(noteA);
  markovChords.push_back(noteC);

  Disposition::placeChords(_midiManager, parameters, markovChords);

  /* CHORDS */
  
  /* MARKOVIAN TREE GENERATION */		
  StyleSettings						proba;
  std::vector<char>					strong;
  std::vector<char>					medium;
  std::vector<char>					weak;
  chord = allChords.getChordPairFromName(markovChords[0].first);
  AI::classifyNotes(chord, &strong, &medium, &weak);
  AI::calculateProbaToNote(&proba, strong, PROBASTRONG);
  AI::calculateProbaToNote(&proba, medium, PROBAMEDIUM);
  AI::calculateProbaToNote(&proba, weak, PROBAWEAK);
  AI::calculateProbaToScaleFromNote(&proba, strong, medium, weak);
  /* MARKOVIAN TREE GENERATION */		

  /* ARPEGGIOS */
  int arpN = rand() % 3 + 4;
  Pattern					*markovPattern = new Pattern(chord);
  ObjectMarkov				       	markovObj2(proba, arpN++, parameters.getSeed());
  markovObj2.callLua();
  markovTmp = markovObj2.getVectorFromJson();
  Resolution::parsingMarkov(&markovTmp, strong, medium, weak);
  char						n;
  n = -1;
  int lastScale = 5;
  while (++n != static_cast<char>(markovTmp.size()))
    {
      int scale = lastScale;
      if (n != 0 && ABS(markovTmp[n].first - markovTmp[n - 1].first) / 8 > 6)
	      scale = (markovTmp[n].first > markovTmp[n - 1].first) ? (lastScale - 1) : (lastScale + 1);
      markovPattern->addNote(std::make_pair(markovTmp[n].first, static_cast<char>(scale)), n*3.0f/arpN + 1, 3.0f/arpN, 0);
	  lastScale = scale;
  }
  std::vector<std::vector<t_note> >		arpeggios;
  std::vector<std::vector<t_note> >		tmparpeggios;
  n = -1;
  while (++n != static_cast<char>(markovChords.size()))
    {
      tmparpeggios = markovPattern->correlatePattern(*markovPattern, chord, allChords.getChordPairFromName(markovChords[n].first));
      arpeggios.insert(arpeggios.end(), tmparpeggios.begin(), tmparpeggios.end());
    }
  Disposition::placeArpeggios(_midiManager, parameters, arpeggios);
  ///* ARPEGGIOS */

  ///* END */
  _midiManager.writeToFile("./test.mid");
  return (_midiManager.createMidi(48));
  /* ED*/
}
