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
		}
		_graph2genM.unlock();
		_gen2playM.lock();
		if (b && _gen2playQ.size() < 3)
		{
			Midi m = createMusic(p);
			_gen2playQ.push_back(std::make_pair(m, p.getBpm()));
		}
		_gen2playM.unlock();
		Tools::sleepActive(1000);
	}
}

Midi			MusicGenerator::createMusic(const MusicParameters &parameters)
{
	if (!parameters.getStyleName().compare("Blues"))
		return (createMusic_blues(parameters));
	else if (!parameters.getStyleName().compare("Reggae"))
		return (createMusic_reggae(parameters));
	return (*(new Midi()));
}

Midi			MusicGenerator::createMusic_reggae(const MusicParameters &parameters)
{
	MidiManager	_midiManager;

	_midiManager.setTempo(parameters.getBpm());
	std::cout << "INITIALISATION" << std::endl;
	/* INITIALISATION */
	ObjectMarkov						markovObj(SOURCEMARKOV + std::string("reggae.json"), 1, parameters.getSeed());
	std::vector<std::pair<char, char> >			markovChords;
	std::vector<std::pair<char, char> >			markovTmp;
	StyleSettings						style;
	std::vector<std::pair<char, char> >			chord;
	Chords						allChords;
	/* INITIALISATION */
	std::cout << "CHORDS" << std::endl;
	/* CHORDS */
	markovObj.callLua();
	markovChords = markovObj.getVectorFromJson();
	style = markovObj.getStyleFromJson();
	Resolution::parsingMarkov(style, &markovChords);

	std::pair<char, char> noteA = std::make_pair(markovChords[0].first, 6);
	std::pair<char, char> noteB = std::make_pair(static_cast<char>(AI::searchNoteFromDist((markovChords[0].first / 8 * 8), 5) + markovChords[0].first % 8), static_cast<char>(6));
	if (noteB.first > noteA.first)
		noteB.second--;
	markovChords.push_back(noteA);
	markovChords.push_back(noteA);
	markovChords.push_back(noteB);
	markovChords.push_back(noteB);
	markovChords.push_back(noteA);
	markovChords.push_back(noteA);
	markovChords.push_back(noteB);
	markovChords.push_back(noteB);

	Disposition::placeChords(_midiManager, parameters, markovChords, 0.5);

	/* CHORDS */

	/* DRUMS */

	std::vector<Instrument>				drumInstruments;
	std::vector<std::vector<t_note>>		drumSequence;

	if (parameters.getInstrumentsDrums() == true)
	{
		Drums::initialize(_midiManager, drumInstruments);
		Drums::prepareDrums(parameters, drumSequence);
		Disposition::placeDrums(_midiManager, parameters, drumSequence, drumInstruments);
	}

	/* DRUMS */

	std::cout << "MTG" << std::endl;
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

	std::cout << "ARPEGGIOS" << std::endl;
	/* ARPEGGIOS */
	int arpN = rand() % 2 + 3;
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
		markovPattern->addNote(std::make_pair(markovTmp[n].first, static_cast<char>(scale)), n*3.0f / arpN + 1, 3.0f / arpN, 0);
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

	std::cout << "END" << std::endl;
	///* END */
	_midiManager.writeToFile("./test.mid");
	delete markovPattern;
	return (_midiManager.createMidi(48));
	/* END */
}

Midi			MusicGenerator::createMusic_blues(const MusicParameters &parameters)
{
  MidiManager	_midiManager;

  _midiManager.setTempo(parameters.getBpm());
  std::cout << "INITIALISATION" << std::endl;
  /* INITIALISATION */
  ObjectMarkov						markovObj(SOURCEMARKOV + std::string("blues.json"), 1, parameters.getSeed());
  std::vector<std::pair<char, char> >			markovChords;
  std::vector<std::pair<char, char> >			markovTmp;
  StyleSettings						style;
  std::vector<std::pair<char, char> >			chord;
  Chords						allChords;
  /* INITIALISATION */
  std::cout << "CHORDS" << std::endl;
  /* CHORDS */
  markovObj.callLua();
  markovChords = markovObj.getVectorFromJson();
  style = markovObj.getStyleFromJson();
  Resolution::parsingMarkov(style, &markovChords);

  std::pair<char, char> noteA = std::make_pair(markovChords[0].first, 6);
  std::pair<char, char> noteB = std::make_pair(static_cast<char>(AI::searchNoteFromDist((markovChords[0].first / 8 * 8), 5) + markovChords[0].first % 8), static_cast<char>(6));
  std::pair<char, char> noteC = std::make_pair(static_cast<char>(AI::searchNoteFromDist((markovChords[0].first / 8 * 8), 7) + markovChords[0].first % 8), static_cast<char>(6));
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

  Disposition::placeChords(_midiManager, parameters, markovChords, 0);

  /* CHORDS */

  /* DRUMS */

  std::vector<Instrument>				drumInstruments;
  std::vector<std::vector<t_note>>		drumSequence;

  if (parameters.getInstrumentsDrums() == true)
  {
	  Drums::initialize(_midiManager, drumInstruments);
	  Drums::prepareDrums(parameters, drumSequence);
	  Disposition::placeDrums(_midiManager, parameters, drumSequence, drumInstruments);
  }

  /* DRUMS */

  std::cout << "MTG" << std::endl;
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

  std::cout << "ARPEGGIOS" << std::endl;
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

  std::cout << "END" << std::endl;
  ///* END */
  _midiManager.writeToFile("./test.mid");
	delete markovPattern;
  return (_midiManager.createMidi(48));
  /* END */
}
