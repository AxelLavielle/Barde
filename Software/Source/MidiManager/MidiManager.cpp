/*
  ==============================================================================

    MidiManager.cpp
    Created: 7 Mar 2017 5:25:20pm
    Author:  Anthony

  ==============================================================================
*/

#include "MidiManager.hh"

MidiManager::MidiManager() : AMidiManager()
{
}

MidiManager::~MidiManager()
{
}

void MidiManager::noteOn(const int channel, const int noteNumber, const float velocity, const double time) noexcept
{
	MidiMessage message = MidiMessage::noteOn(channel, noteNumber, (uint8)velocity);

	message.setTimeStamp(time * 1000);
	//addMessageToList(message);
	_midiSequence.addEvent(message);
	_midiSequence.updateMatchedPairs();
}

void MidiManager::noteOn(const Instrument & instrument, const int noteNumber, const float velocity, const double time) noexcept
{
	MidiMessage message = MidiMessage::noteOn(instrument.channel, noteNumber, (uint8)velocity);

	changeInstrument(instrument, time);
	message.setTimeStamp(time);
	//addMessageToList(message);
	_midiSequence.addEvent(message);
	_midiSequence.updateMatchedPairs();
}

void MidiManager::noteOff(const int channel, const int noteNumber, const float velocity, const double time) noexcept
{
	MidiMessage message = MidiMessage::noteOff(channel, noteNumber, (uint8)velocity);

	message.setTimeStamp(time * 1000);
	//addMessageToList(message);
	_midiSequence.addEvent(message);
	//_midiSequence.updateMatchedPairs();
}

void MidiManager::noteOff(const Instrument & instrument, const int noteNumber, const float velocity, const double time) noexcept
{
	MidiMessage message = MidiMessage::noteOff(instrument.channel, noteNumber, (uint8)velocity);

	changeInstrument(instrument, time);
	message.setTimeStamp(time);
	//addMessageToList(message);
	_midiSequence.addEvent(message);
	//_midiSequence.updateMatchedPairs();
}


Midi MidiManager::createMidi(const double time)
{
	MidiMessage			message;
	Midi				midi;

	message = MidiMessage::endOfTrack();
	message.setTimeStamp(time * 1000);
	//addMessageToList(message);
	_midiSequence.addEvent(message);
	_midiBuff.addTrack(_midiSequence);
	//_midiBuff.setTicksPerQuarterNote(4); // 80 tick dans une minute

	//MidiOutput *midiOutput;
	//midiOutput = MidiOutput::openDevice(0);
	//std::cout << "nombre of event " << _midiSequence.getNumEvents() << std::endl;
	//for (int i = 0; i<_midiSequence.getNumEvents(); i++)
	//{
	//	/*std::cout << "coucuo " << (_midiSequence.getEventPointer(i)->message) << std::endl;*/
	//	midiOutput->sendMessageNow((_midiSequence.getEventPointer(i)->message));
	//}

	//_midiBuff.convertTimestampTicksToSeconds();
	_midiBuff.writeTo(_midiStream, 1);
	midi.setMidiSize(_midiStream.getDataSize());
	midi.setMidiArray((char *)_midiStream.getData());
	//midi.setMidiArray((char *)std::memcpy(midi.getMidiArray(), midiStream.getData(), midiStream.getDataSize()));
	_midiSequence.clear();


	//MidiFile			midiBuff;
	//MemoryInputStream	stream(midi.getMidiArray(), midi.getMidiSize(), false);

	//midiBuff.readFrom(stream);
	//if (midiBuff.getNumTracks() > 0)
	//	exit(1);


	//std::cout << "LALALALA = " << Time::getHighResolutionTicksPerSecond() << std::endl;
	return (midi);
}

void		MidiManager::writeToFile(const std::string &filePath)
{
	File				testFile(File::getCurrentWorkingDirectory().getChildFile(String(filePath)));

	if (testFile.exists())
		testFile.deleteFile();
	FileOutputStream	file(testFile);

	_midiBuff.writeTo(file, 1);
	//file.write(_midi.getMidiArray(), _midi.getMidiSize());
}

void MidiManager::setSignature(const unsigned int numerator, const unsigned int denominator, const double time)
{
	MidiMessage message = MidiMessage::timeSignatureMetaEvent(4, 4);

	message.setTimeStamp(time);
	_midiSequence.addEvent(message);
}

void MidiManager::setTempo(const unsigned int bpm, const double time)
{
	//MidiMessage message = MidiMessage::tempoMetaEvent(1000000);// On dit que 1 quarterNote dure 1 min

	//message.setTimeStamp(time);
	//setSignature(4, 4, 0);
	//std::cout << "Tick Lenght ===" << message.getTempoMetaEventTickLength(message.getTimeStamp()) << std::endl;
	//_midiSequence.addEvent(message);
}

void MidiManager::changeInstrument(const int channel, const int instrumentNb, const double time)
{
	MidiMessage message = MidiMessage::programChange(channel, instrumentNb);

	message.setTimeStamp(time);
	_midiSequence.addEvent(message);
}

void MidiManager::changeInstrument(const Instrument & instrument, const double time)
{
	MidiMessage message = MidiMessage::programChange(instrument.channel, instrument.nb);

	message.setTimeStamp(time);
	_midiSequence.addEvent(message);
}

String		MidiManager::getMidiMessageDescription(const MidiMessage& m)
{
	if (m.isNoteOn())           return "Note on " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
	if (m.isNoteOff())          return "Note off " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
	if (m.isProgramChange())    return "Program change " + String(m.getProgramChangeNumber());
	if (m.isPitchWheel())       return "Pitch wheel " + String(m.getPitchWheelValue());
	if (m.isAftertouch())       return "After touch " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3) + ": " + String(m.getAfterTouchValue());
	if (m.isChannelPressure())  return "Channel pressure " + String(m.getChannelPressureValue());
	if (m.isAllNotesOff())      return "All notes off";
	if (m.isAllSoundOff())      return "All sound off";
	if (m.isMetaEvent())        return "Meta event";

	if (m.isController())
	{
		String name(MidiMessage::getControllerName(m.getControllerNumber()));

		if (name.isEmpty())
			name = "[" + String(m.getControllerNumber()) + "]";

		return "Controller " + name + ": " + String(m.getControllerValue());
	}

	return String::toHexString(m.getRawData(), m.getRawDataSize());
}

void	MidiManager::addMessageToList(const MidiMessage& message)
{
    const double time = message.getTimeStamp();
    const int hours   = ((int) (time / 3600.0)) % 24;
    const int minutes = ((int) (time / 60.0)) % 60;
    const int seconds = ((int) time) % 60;
    const int millis  = ((int) (time * 1000.0)) % 1000;
    const String timecode (String::formatted ("%02d:%02d:%02d.%03d",
                                              hours,
                                              minutes,
                                              seconds,
                                              millis));
	//File file(File::getCurrentWorkingDirectory().getChildFile(String("./test.log")));

	//FileLogger test(file, "COUCOU", 4096);

	//test.writeToLog(timecode + "  -  " + getMidiMessageDescription(message));
}
