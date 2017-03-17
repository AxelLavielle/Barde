#include	<string>
#include	<iostream>
#include	<fstream>
#include	"../Chords.hh"
#include	"../StyleSettings.hh"

void		setupJson(StyleSettings createJson)
{
  std::string	data;
  std::ofstream	file;
  char		chord;
  char		chord2;

  file.open("tree.json", std::fstream::out);
  file << "{\n\t\"note\": {\n\t\t\"begin\": {\n";
  chord = C;
  while (chord != END)
    {
      file << "\t\t\t\"" << static_cast<int>(chord) << "\": " << createJson.getProba(chord) << ",\n";
      chord++;
    }
  file << "\t\t},\n";

  chord2 = C;
  while (chord2 != END)
    {
      file << "\t\t\"" << static_cast<int>(chord2) << "\": {\n";
      chord = C;
      while (chord != END)
	{
	  file << "\t\t\t\"" << static_cast<int>(chord) << "\": " << createJson.getProba(chord) << ",\n";
	  chord++;
	}
      file << "\t\t},\n";
      chord2++;
    }

  file << "\t\"scale\": {\n\t\t\"begin\": {\n\t\t\t\"3\": 100\n\t\t},\n";
  file << "t\t\"3\": {\n\t\t\t\"3\": 100\n\t\t}";
  file << "\t}\n}";
  file.close();
}

int		main()
{
  StyleSettings	createJson;

  createJson.addNote(C, 33);
  createJson.addNote(E, 35);
  createJson.addNote(A, 32);
  createJson.addNoteFromNote(C, C, 33);
  createJson.addNoteFromNote(C, E, 35);
  createJson.addNoteFromNote(C, A, 32);
  createJson.addNoteFromNote(E, C, 33);
  createJson.addNoteFromNote(E, E, 35);
  createJson.addNoteFromNote(E, A, 32);
  createJson.addNoteFromNote(A, C, 33);
  createJson.addNoteFromNote(A, E, 35);
  createJson.addNoteFromNote(A, A, 32);

  setupJson(createJson);
}
