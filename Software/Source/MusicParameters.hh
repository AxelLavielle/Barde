/*
  ==============================================================================

    MusicParameters.h
    Created: 13 Mar 2017 1:47:13pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MUSICPARAMETERS_HH_INCLUDED
#define MUSICPARAMETERS_HH_INCLUDED

class MusicParameter
{
public:
	MusicParameter();
	~MusicParameter();
	int getBpm() const;
	void setBpm(const int bpm);
	int getSeed() const;
	void setSeed(const int seed);

private:
	int		_seed;
	int		_bpm;

};


#endif  // MUSICPARAMETERS_HH_INCLUDED
