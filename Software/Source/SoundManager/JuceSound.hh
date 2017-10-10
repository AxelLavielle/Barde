/*
  ==============================================================================

    JuceSound.h
    Created: 13 Mar 2017 1:42:58pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef JUCESOUND_HH_INCLUDED
#define JUCESOUND_HH_INCLUDED

/*!
* \file JuceSound.hh
* \brief This file contain the class that manage the playing of sound
*/


#include "JuceHeader.h"
#include "ASoundManager.hh"
#include "../Tools.hh"

/*! \class SoundManager
 * \brief SoundManager manage the playing of sound
 *
 *  This class allows to play midi data, stop playing, pause playing and set the volume
 */

 struct SineWaveSound : public SynthesiserSound
 {
     SineWaveSound() {}

     bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
     bool appliesToChannel (int /*midiChannel*/) override        { return true; }
 };

 //==============================================================================
/** Our demo synth voice just plays a sine wave.. */
struct SineWaveVoice  : public SynthesiserVoice
{
    SineWaveVoice()   : currentAngle (0), angleDelta (0), level (0), tailOff (0)
    {
      _amplitude = 0.5;
      _frequency = 500;
      _phase = 0.0;
      _time = 0.0;
      _deltaTime = 1 / getSampleRate();
    }

    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
    //     currentAngle = 0.0;
    //     level = velocity * 0.15;
    //     tailOff = 0.0;
    //
    //     double cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    //     double cyclesPerSample = cyclesPerSecond / getSampleRate();
    //
    //     angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
    //     if (allowTailOff)
    //     {
    //         // start a tail-off by setting this flag. The render callback will pick up on
    //         // this and do a fade out, calling clearCurrentNote() when it's finished.
    //
    //         if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
    //                             // stopNote method could be called more than once.
    //             tailOff = 1.0;
    //     }
    //     else
    //     {
    //         // we're being told to stop playing immediately, so reset everything..
    //
    //         clearCurrentNote();
    //         angleDelta = 0.0;
    //     }
    }

    void pitchWheelMoved (int /*newValue*/) override
    {
        // can't be bothered implementing this for the demo!
    }

    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
    {
        // not interested in controllers in this case.
    }

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
		float *monoBuffer = new float[numSamples];

		for (int sample = 0; sample < numSamples; ++sample) {
			float value = _amplitude * sin(2 * double_Pi * _frequency * _time + _phase);

			monoBuffer[sample] = value;
			_time += _deltaTime;
		}

		for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
		{
			for (int sample = 0; sample < numSamples; ++sample) {
				outputBuffer.addSample(channel, sample, monoBuffer[sample]);
			}
		}
    }

private:
    double currentAngle, angleDelta, level, tailOff;

    float _amplitude;
    float _frequency;
    float _phase;
    float _time;
    float _deltaTime;
};


 struct SynthAudioSource  : public AudioSource
 {
     SynthAudioSource ()
     {
         // Add some voices to our synth, to play the sounds..
         for (int i = 4; --i >= 0;)
         {
             synth.addVoice (new SineWaveVoice());   // These voices will play our custom sine-wave sounds..
            //  synth.addVoice (new SamplerVoice());    // and these ones play the sampled sounds
         }

         synth.noteOn(10, 10, (uint8)100);
         std::cout << "NOTE ON !!!" << std::endl;


         // ..and add a sound for them to play...
         setUsingSineWaveSound();
     }

     void setUsingSineWaveSound()
     {
       // std::cout << "------------------------------------------------" << std::endl;
       // std::cout << "COUCOU" << std::endl;
       // std::cout << "------------------------------------------------" << std::endl;

         synth.clearSounds();
         synth.addSound (new SineWaveSound());
     }

     void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
     {
         midiCollector.reset (sampleRate);

         std::cout << sampleRate << std::endl;
         synth.setCurrentPlaybackSampleRate (sampleRate);
     }

     void releaseResources() override
     {
     }

     void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
     {
         // the synth always adds its output to the audio buffer, so we have to clear it
         // first..
         // std::cout << "getNextAudioBlock" << std::endl;
         bufferToFill.clearActiveBufferRegion();

         MidiBuffer incomingMidi;
         midiCollector.removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples);
         // fill a midi buffer with incoming messages from the midi input.

         // pass these messages to the keyboard state so that it can update the component
         // to show on-screen which keys are being pressed on the physical midi keyboard.
         // This call will also add midi messages to the buffer which were generated by
         // the mouse-clicking on the on-screen keyboard.
         // keyboardState.processNextMidiBuffer (incomingMidi, 0, bufferToFill.numSamples, true);

         // and now get the synth to process the midi events and generate its output.
         std::cout << bufferToFill.numSamples << std::endl;
				 std::cout << "COUCOU !!!" << std::endl;
				//  MidiMessage message = MidiMessage::noteOn(1, 10, (uint8)100);
				//  MidiMessage message = MidiMessage::noteOff(1, 10, (uint8)100);
				 //
        //  synth.renderNextBlock (*bufferToFill.buffer, MidiBuffer(message), 0, bufferToFill.numSamples);
         synth.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
     }

     //==============================================================================
     // this collects real-time midi messages from the midi input device, and
     // turns them into blocks that we can process in our audio callback
     MidiMessageCollector midiCollector;

     // the synth itself!
     Synthesiser synth;
 };

class SoundManager : public ASoundManager
{
public:
	/*!
 *  \brief Constructor
 *
 *  Set the Midi device who play sound
 *
 */
	SoundManager();
	/*!
   *  \brief Destructor
   *
   *  Empty
   *
   */
	virtual ~SoundManager();
	/*!
	*  \brief Play all the notes contained in the midi data
	*
	*  This method send all the notes events contained in the midi data to the midi device
	*
	*  \param midi : midi data send to the midi device
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool play(const Midi &midi);
	/*!
	*  \brief Stop the song who is being played
	*
	*  This method stop all the event send to the midi device and provoke the stop of the playing
	*
	*  \param midi : midi object need to stop
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool stop(const Midi &midi) const;
	/*!
	*  \brief Pause the song who is being played
	*
	*  This method pause all the event send to the midi device and provoke the pause of the playing
	*
	*  \param midi : midi object need to pause
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool pause(const Midi &midi) const;
	/*!
	*  \brief Stop all the songs who is being played
	*
	*  This method stop all the event send to the midi device and provoke the stop of the playing
	*
	*
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool stopAll() const;
	/*!
	*  \brief Set the volume of the sound
	*
	*  This method allow to set the volume of the midi device
	*
	*  \param volume : the value of the volume
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool setVolume(const int volume);
	/*!
	*  \brief Set the volume of a specific Midi
	*
	*  This method allow to set the volume of the midi device
	*
	*  \param volume : the value of the volume
	*  \return true in case of success playing and false in the others case
	*/
	virtual bool setVolume(const Midi &midi) const;

private:
	int									volume = 0; /*!< current volume of the midi device*/
	MidiOutput					*_midiOutput; /*!< pointer to the midi devce*/
	MidiFile						_midiBuff; /*!< Buffer containing all the midi data*/
	AudioDeviceManager	_audioManager;
	AudioSourcePlayer 	_audioSourcePlayer;
	SynthAudioSource 		_synthAudioSource;
	AudioDeviceManager 	*_deviceManager;

	const MidiMessageSequence		*MidiToMessageSequence(const Midi &midi);
};



#endif  // JUCESOUND_HH_INCLUDED
