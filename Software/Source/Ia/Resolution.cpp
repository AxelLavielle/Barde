#include		"Resolution.hh"

Resolution::Resolution()
{

}

Resolution::~Resolution()
{

}

std::vector<std::pair<char, char> >	Resolution::parsingMarkov(const StyleSettings &style, std::vector<std::pair<char, char> > &sequence)
{
  char	i;
  char	save;
  int	percentage;

  i = -1;
  save = -1;
  while (++i != sequence.size())
    {
      if (save == sequence[i].first)
	{
	  percentage = percentage * style.getProbaFromNote(save, save) / 100;
	  if (percentage < NOT_ENOUGH_CHANCE)
	    sequence[i].first = fixingMarkov(style, save, i + 1 == sequence.size() ? -1 : sequence[i + 1].first);
	}
      if (save != sequence[i].first)
	{
	  save = sequence[i].first;
	  percentage = style.getProbaFromNote(save, save);
	}
    }
  return (sequence);
}

char		Resolution::fixingMarkov(const StyleSettings &style, const char prev, const char next)
{
  char		tmp;
  std::vector<char> 	save;
  float		prob;
  float		probSave;

  tmp = prev ? 0 : 1;
  save.push_back(prev);
  probSave = 0;
  while (tmp != END)
    {
      prob = style.getProbaFromNote(prev, tmp);
      if (next != -1)
	prob *= style.getProbaFromNote(tmp, next);
      if (prob > probSave)
	{
	  probSave = prob;
	  save.clear();
	  save.push_back(tmp);
	}
      else if (prob == probSave)
	save.push_back(tmp);
      tmp += tmp == prev ? 2 : 1;
    }
  return (save[rand() % save.size()]);
}
