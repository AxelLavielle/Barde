#ifndef		__CHORDS__
# define	__CHORDS__

# include	<iostream>
# include	<vector>
# include	<map>

enum		ChordsName : char
  {
    C,
    Cm,
    Cdim,
    Csus,
    Cplus,
    C4,
    C6,
    C7,
    CS,
    CSm,
    CSdim,
    CSsus,
    CSplus,
    CS4,
    CS6,
    CS7,
    D,
    Dm,
    Ddim,
    Dsus,
    Dplus,
    D4,
    D6,
    D7,
    DS,
    DSm,
    DSdim,
    DSsus,
    DSplus,
    DS4,
    DS6,
    DS7,
    E,
    Em,
    Edim,
    Esus,
    Eplus,
    E4,
    E6,
    E7,
    F,
    Fm,
    Fdim,
    Fsus,
    Fplus,
    F4,
    F6,
    F7,
    FS,
    FSm,
    FSdim,
    FSsus,
    FSplus,
    FS4,
    FS6,
    FS7,
    G,
    Gm,
    Gdim,
    Gsus,
    Gplus,
    G4,
    G6,
    G7,
    GS,
    GSm,
    GSdim,
    GSsus,
    GSplus,
    GS4,
    GS6,
    GS7,
    A,
    Am,
    Adim,
    Asus,
    Aplus,
    A4,
    A6,
    A7,
    AS,
    ASm,
    ASdim,
    ASsus,
    ASplus,
    AS4,
    AS6,
    AS7,
    B,
    Bm,
    Bdim,
    Bsus,
    Bplus,
    B4,
    B6,
    B7,
    END
  };

class		Chords
{
public:
  Chords();
  ~Chords();
  std::vector<char>	getChordFromName(const char name) const;

private:
  std::map<char, std::vector<char> >	_chords;
};

#endif	//	__CHORDS__
