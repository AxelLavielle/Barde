/*
  ==============================================================================

    Instrument.h
    Created: 15 Mar 2017 3:31:53pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef INSTRUMENT_HH_INCLUDED
#define INSTRUMENT_HH_INCLUDED

/*!
 * \file Instrument.hh
 * \brief File containing the Instrument class and the enums for the instruments with their ID
 */

#include <string>
#include <map>

 /*! Numero d'identification de l'instrument */
enum	NbInstrument
{
	ACOUSTICGRANDPIANO = 1,
	BRIGHTACOUSTICPIANO = 2,
	ELECTRICGRANDPIANO = 3,
	HONKYTONKPIANO = 4,
	ELECTRICPIANO1 = 5,
	ELECTRICPIANO2 = 6,
	HARPSICHORD = 7,
	CLAVINET = 8,
	CELESTA = 9,
	GLOCKENSPIEL = 10,
	MUSICBOX = 11,
	VIBRAPHONE = 12,
	MARIMBA = 13,
	XYLOPHONE = 14,
	TUBULARBELLS = 15,
	DULCIMER = 16,
	DRAWBARORGAN = 17,
	PERCUSSIVEORGAN = 18,
	ROCKORGAN = 19,
	CHURCHORGAN = 20,
	REEDORGAN = 21,
	ACCORDION = 22,
	HARMONICA = 23,
	TANGOACCORDION = 24,
	ACOUSTICGUITARNYLON = 25,
	ACOUSTICGUITARSTEEL = 26,
	ELECTRICGUITARJAZZ = 27,
	ELECTRICGUITARCLEAN = 28,
	ELECTRICGUITARMUTED = 29,
	OVERDRIVENGUITAR = 30,
	DISTORTIONGUITAR = 31,
	GUITARHARMONICS = 32,
	ACOUSTICBASS = 33,
	ELECTRICBASSFINGER = 34,
	ELECTRICBASSPICK = 35,
	FRETLESSBASS = 36,
	SLAPBASS1 = 37,
	SLAPBASS2 = 38,
	SYNTHBASS1 = 39,
	SYNTHBASS2 = 40,
	VIOLIN = 41,
	VIOLA = 42,
	CELLO = 43,
	CONTRABASS = 44,
	TREMOLOSTRINGS = 45,
	PIZZICATOSTRINGS = 46,
	ORCHESTRALHARP = 47,
	TIMPANI = 48,
	STRINGENSEMBLE1 = 49,
	STRINGENSEMBLE2 = 50,
	SYNTHSTRINGS1 = 51,
	SYNTHSTRINGS2 = 52,
	CHOIRAAHS = 53,
	VOICEOOHS = 54,
	SYNTHCHOIR = 55,
	ORCHESTRAHIT = 56,
	TRUMPET = 57,
	TROMBONE = 58,
	TUBA = 59,
	MUTEDTRUMPET = 60,
	FRENCHHORN = 61,
	BRASSSECTION = 62,
	SYNTHBRASS1 = 63,
	SYNTHBRASS2 = 64,
	SOPRANOSAX = 65,
	ALTOSAX = 66,
	TENORSAX = 67,
	BARITONESAX = 68,
	OBOE = 69,
	ENGLISHHORN = 70,
	BASSOON = 71,
	CLARINET = 72,
	PICCOLO = 73,
	FLUTE = 74,
	RECORDER = 75,
	PANFLUTE = 76,
	BLOWNBOTTLE = 77,
	SHAKUHACHI = 78,
	WHISTLE = 79,
	OCARINA = 80,
	//LEAD1SQUARE = 81,
	//LEAD2SAWTOOTH = 82,
	//LEAD3CALLIOPE = 83,
	//LEAD4CHIFF = 84,
	//LEAD5CHARANG = 85,
	//LEAD6VOICE = 86,
	//LEAD7FIFTHS = 87,
	//LEAD8BASS = 88,
	//PAD1NEWAGE = 89,
	//PAD2WARM = 90,
	//PAD3POLYSYNTH = 91,
	//PAD4CHOIR = 92,
	//PAD5BOWED = 93,
	//PAD6METALLIC = 94,
	//PAD7HALO = 95,
	//PAD8SWEEP = 96,
	//FX1RAIN = 97,
	//FX2SOUNDTRACK = 98,
	//FX3CRYSTAL = 99,
	//FXATMOSPHERE = 100,
	//FXBRIGHTNESS = 101,
	//FXGOBLINS = 102,
	//FXECHOES = 103,
	//FXSCIFI = 104,
	//SITAR = 105,
	//BANJO = 106,
	//SHAMISEN = 107,
	//KOTO = 108,
	//KALIMBA = 109,
	//BAGPIPE = 110,
	//FIDDLE = 111,
	//SHANAI = 112,
	//TINKLEBELL = 113,
	//AGOGO = 114,
	//STEELDRUMS = 115,
	//WOODBLOCK = 116,
	//TAIKODRUM = 117,
	//MELODICTOM = 118,
	//SYNTHDRUM = 119,
	//REVERSECYMBAL = 120,
	//GUITARFRETNOISE = 121,
	//BREATHNOISE = 122,
	//SEASHORE = 123,
	//BIRDTWEET = 124,
	//TELEPHONERING = 125,
	//HELICOPTER = 126,
	//APPLAUSE = 127,
	//GUNSHOT = 128,

	BASSDRUM2 = 81,
	BASSDRUM1 = 82,
	SIDESTICKRIMSHOT = 83, // Not Implemented
	SNAREDRUMACOUSTICSNARE = 84,
	HANDCLAP = 85,
	SNAREDRUMELECTRICSNARE = 86,
	LOWTOM2 = 87,
	CLOSEDHIHAT = 88,
	LOWTOM1 = 89,
	PEDALHIHAT = 90,
	MIDTOM2 = 91,
	OPENHIHAT = 92,
	MIDTOM1 = 93,
	HIGHTOM2 = 94,
	CRASHCYMBAL1 = 95,
	HIGHTOM1 = 96,
	RIDECYMBAL1 = 97,
	CHINESECYMBAL = 98,
	RIDEBELL = 99,
	TAMBOURINE = 100, // Not Implemented
	SPLASHCYMBAL = 101,
	COWBELL = 102, // Not Implemented
	CRASHCYMBAL2 = 103,
	VIBRASLAP = 104, // Not Implemented
	RIDECYMBAL2 = 105,
	HIGHBONGO = 106, // Not Implemented
	LOWBONGO = 107, // Not Implemented
	MUTEHIGHCONGA = 108, // Not Implemented
	OPENHIGHCONGA = 109, // Not Implemented
	LOWCONGA = 110, // Not Implemented
	HIGHTIMBALE = 111, // Not Implemented
	LOWTIMBALE = 112, // Not Implemented
	HIGHAGOGO = 113, // Not Implemented
	LOWAGOGO = 114, // Not Implemented
	CABASA = 115, // Not Implemented
	MARACAS = 116, // Not Implemented
	SHORTWHISTLE = 117, // Not Implemented
	LONGWHISTLE = 118, // Not Implemented
	SHORTGUIRO = 119,
	LONGGUIRO = 120,
	CLAVES = 121, // Not Implemented
	HIGHWOODBLOCK = 122, // Not Implemented
	LOWWOODBLOCK = 123, // Not Implemented
	MUTECUICA = 124, // Not Implemented
	OPENCUICA = 125, // Not Implemented
	MUTETRIANGLE = 126,
	OPENTRIANGLE = 127 // Not Implemented
};
/*! Numero d'identification de l'instrument de batterie */
//enum	Drums
//{
//	BASSDRUM2 = 35,
//	BASSDRUM1 = 36,
//	SIDESTICKRIMSHOT = 37, // Not Implemented
//	SNAREDRUMACOUSTICSNARE = 38,
//	HANDCLAP = 39,
//	SNAREDRUMELECTRICSNARE = 40,
//	LOWTOM2 = 41,
//	CLOSEDHIHAT = 42,
//	LOWTOM1 = 43,
//	PEDALHIHAT = 44,
//	MIDTOM2 = 45,
//	OPENHIHAT = 46,
//	MIDTOM1 = 47,
//	HIGHTOM2 = 48,
//	CRASHCYMBAL1 = 49,
//	HIGHTOM1 = 50,
//	RIDECYMBAL1 = 51,
//	CHINESECYMBAL = 52,
//	RIDEBELL = 53,
//	TAMBOURINE = 54, // Not Implemented
//	SPLASHCYMBAL = 55,
//	COWBELL = 56, // Not Implemented
//	CRASHCYMBAL2 = 57,
//	VIBRASLAP = 58, // Not Implemented
//	RIDECYMBAL2 = 59,
//	HIGHBONGO = 60, // Not Implemented
//	LOWBONGO = 61, // Not Implemented
//	MUTEHIGHCONGA = 62, // Not Implemented
//	OPENHIGHCONGA = 63, // Not Implemented
//	LOWCONGA = 64, // Not Implemented
//	HIGHTIMBALE = 65, // Not Implemented
//	LOWTIMBALE = 66, // Not Implemented
//	HIGHAGOGO = 67, // Not Implemented
//	LOWAGOGO = 68, // Not Implemented
//	CABASA = 69, // Not Implemented
//	MARACAS = 70, // Not Implemented
//	SHORTWHISTLE = 71, // Not Implemented
//	LONGWHISTLE = 72, // Not Implemented
//	SHORTGUIRO = 73,
//	LONGGUIRO = 74,
//	CLAVES = 75, // Not Implemented
//	HIGHWOODBLOCK = 76, // Not Implemented
//	LOWWOODBLOCK = 77, // Not Implemented
//	MUTECUICA = 78, // Not Implemented
//	OPENCUICA = 79, // Not Implemented
//	MUTETRIANGLE = 80,
//	OPENTRIANGLE = 81 // Not Implemented
//};

const static std::map<std::string, NbInstrument> instrumentList = {
	{ "ACOUSTICGRANDPIANO", ACOUSTICGRANDPIANO } ,
	{ "FLUTE", FLUTE } ,
	{ "BASSDRUM2", BASSDRUM2 },
	{ "MIDTOM1", MIDTOM1 },
	{ "SIDESTICKRIMSHOT", SIDESTICKRIMSHOT },
	{ "SNAREDRUMACOUSTICSNARE", SNAREDRUMACOUSTICSNARE },
	{ "SNAREDRUMELECTRICSNARE", SNAREDRUMELECTRICSNARE },
	{ "HANDCLAP", HANDCLAP },
	{ "LOWTOM2", LOWTOM2 },
	{ "CLOSEDHIHAT", CLOSEDHIHAT },
	{ "LOWTOM1", LOWTOM1 },
	{ "PEDALHIHAT", PEDALHIHAT },
	{ "MIDTOM2", MIDTOM2 },
	{ "HIGHTOM2", HIGHTOM2 },
	{ "CRASHCYMBAL1", CRASHCYMBAL1 },
	{ "HIGHTOM1", HIGHTOM1 },
	{ "OPENHIHAT", OPENHIHAT },
	{ "RIDECYMBAL1", RIDECYMBAL1 },
	{ "CHINESECYMBAL", CHINESECYMBAL },
	{ "RIDEBELL", RIDEBELL },
	{ "TAMBOURINE", TAMBOURINE },
	{ "SPLASHCYMBAL", SPLASHCYMBAL },
	{ "COWBELL", COWBELL },
	{ "CRASHCYMBAL2", CRASHCYMBAL2 },
	{ "VIBRASLAP", VIBRASLAP },
	{ "RIDECYMBAL2", RIDECYMBAL2 },
	{ "HIGHBONGO", HIGHBONGO },
	{ "LOWBONGO", LOWBONGO },
	{ "MUTEHIGHCONGA", MUTEHIGHCONGA },
	{ "OPENHIGHCONGA", OPENHIGHCONGA },
	{ "LOWCONGA", LOWCONGA },
	{ "HIGHTIMBALE", HIGHTIMBALE },
	{ "LOWTIMBALE", LOWTIMBALE },
	{ "HIGHAGOGO", HIGHAGOGO },
	{ "LOWAGOGO", LOWAGOGO },
	{ "CABASA", CABASA },
	{ "MARACAS", MARACAS },
	{ "SHORTWHISTLE", SHORTWHISTLE },
	{ "LONGWHISTLE", LONGWHISTLE },
	{ "SHORTGUIRO", SHORTGUIRO },
	{ "LONGGUIRO", LONGGUIRO },
	{ "CLAVES", CLAVES },
	{ "HIGHWOODBLOCK", HIGHWOODBLOCK },
	{ "LOWWOODBLOCK", LOWWOODBLOCK },
	{ "MUTECUICA", MUTECUICA },
	{ "OPENCUICA", OPENCUICA },
	{ "MUTETRIANGLE", MUTETRIANGLE },
	{ "OPENTRIANGLE", OPENTRIANGLE },
	{ "TRUMPET", TRUMPET },
	{ "SOPRANOSAX", SOPRANOSAX },
	{ "BASSDRUM1", BASSDRUM1 },
	{ "ACOUSTICGUITARNYLON", ACOUSTICGUITARNYLON },
	{ "ACOUSTICBASS", ACOUSTICBASS }
	};

/*! \class Instrument
 * \brief Instrument class contain instrument data
 *
 *  Instrument class contain instrument data needed for the sound library
 */
class Instrument
{
public:
	std::string		name;  /*!< Name of the instrument */
	NbInstrument	nb;  /*!< Instrument number */
	int				channel;  /*!< Channel corresponding to the instrument */
	float			velocity;  /*!< Default velocity of the instrument */
};

#endif  // INSTRUMENT_HH_INCLUDED
