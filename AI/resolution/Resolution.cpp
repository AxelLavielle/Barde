#include		"Resolution.hh"

Resolution::Resolution(// const Style &style, Disposition &disposition
	   )
{

}

Resolution::~Resolution()
{

}

void		Resolution::setStyleSettings(StyleSettings style)
{
  _style = style;
}

std::vector<std::pair<char, char> >	Resolution::parsingMarkov(std::vector<std::pair<char, char> > sequence)
{
  char	i;
  char	save;
  int	percentage;

  srand(time(NULL));
  i = 0;
  save = -1;
  while (i != sequence.size())
    {
      if (save == sequence[i].first)
	{
	  percentage = percentage * _style.getProbaFromNote(save, save) / 100;
	  if (percentage < NOT_ENOUGH_CHANCE)
	    sequence[i].first = fixingMarkov(save, i + 1 == sequence.size() ? -1 : sequence[i + 1].first);
	}
      if (save != sequence[i].first)
	{
	  save = sequence[i].first;
	  percentage = _style.getProbaFromNote(save, save);
	}
      i++;
    }
  return (sequence);
}

char		Resolution::fixingMarkov(char prev, char next)
{
  return (0);
}

void		Resolution::addBridge()
{

}

void		Resolution::parsingDisposition()
{

}

void		Resolution::fixingDisposition()
{
  
}

int		main()
{
  Resolution				res;
  std::vector<std::pair<char, char> >	test;
  StyleSettings				blues;

  blues.addNote('A', 75);
  blues.addNote('C', 75);
  blues.addNote('E', 75);
  blues.addNote('F', 75);
  blues.addNoteFromNote('A', 'A', 75);
  blues.addNoteFromNote('A', 'C', 75);
  blues.addNoteFromNote('A', 'E', 75);
  blues.addNoteFromNote('A', 'F', 75);
  blues.addNoteFromNote('C', 'A', 75);
  blues.addNoteFromNote('C', 'C', 75);
  blues.addNoteFromNote('C', 'E', 75);
  blues.addNoteFromNote('C', 'F', 75);
  blues.addNoteFromNote('E', 'A', 75);
  blues.addNoteFromNote('E', 'C', 75);
  blues.addNoteFromNote('E', 'E', 75);
  blues.addNoteFromNote('E', 'F', 75);
  blues.addNoteFromNote('F', 'A', 75);
  blues.addNoteFromNote('F', 'C', 75);
  blues.addNoteFromNote('F', 'E', 75);
  blues.addNoteFromNote('F', 'F', 75);

  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 
  test.push_back(std::pair<char, char>('A', 3)); 

  res.setStyleSettings(blues);
  test = res.parsingMarkov(test);

  int	i = -1;
  while (++i != test.size())
    std::cout << test[i].first << std::endl;
  return (0);
}
