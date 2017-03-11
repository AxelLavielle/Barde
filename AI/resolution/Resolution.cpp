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
  char		tmp;
  std::vector<char> 	save;
  float		prob;
  float		probSave;

  tmp = 'A' == prev ? 'B' : 'A';
  save.push_back(prev);
  probSave = 0;
  while (tmp != 'H')
    {
      prob = _style.getProbaFromNote(prev, tmp);
      if (next != -1)
	prob *= _style.getProbaFromNote(tmp, next);
      if (prob > probSave)
	{
	  probSave = prob;
	  save.clear();
	  save.push_back(tmp);
	}
      else if (prob == probSave)
	{
	  save.push_back(tmp);
	}
      tmp++;
      if (tmp == prev)
	tmp++;
    }
  return (save[rand() % save.size()]);
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
