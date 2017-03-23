#include		"Resolution.hh"

Resolution::Resolution()
{

}

Resolution::~Resolution()
{

}

char	Resolution::which_state(const char note, const std::vector<char> &strong, const std::vector<char> &medium)
{
  unsigned char	i;

  i = -1;
  while (++i != strong.size())
    if (note == strong[i])
      return (1);
  i = -1;
  while (++i != medium.size())
    if (note == medium[i])
      return (2);
  return (3);
}

void	Resolution::parsingMarkov(std::vector<std::pair<char, char> > *sequence, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak)
{
  unsigned char	i;
  unsigned char	state;
  unsigned char	percentage;

  i = -1;
  state = 0;
  while (++i != sequence->size())
    {
      if (state == which_state((*sequence)[i].first, strong, medium))
	{
	  percentage = percentage * state / 100;
	  if (percentage < NOT_ENOUGH_CHANCE)
	    {
	      state = 100 - (*sequence)[i].first - ((*sequence)[i + 1].first != (*sequence)[i].first ? (*sequence)[i + 1].first : ((*sequence)[i + 1].first == (*sequence)[i].first ? 2 : (*sequence)[i + 1].first - 1));
	      (*sequence)[i].first = fixingMarkov(state, strong, medium, weak);
	    }
	}
      if (state != which_state((*sequence)[i].first, strong, medium))
	{
	  if (state == 0)
	    state = which_state((*sequence)[i].first, strong, medium);
	  percentage = state;
	}
    }
}

void	Resolution::parsingMarkov(StyleSettings &style, std::vector<std::pair<char, char> > *sequence)
{
  unsigned char	i;
  unsigned char	save;
  unsigned char	percentage;

  i = -1;
  save = -1;
  while (++i != sequence->size())
    {
      if (save == (*sequence)[i].first)
	{
	  percentage = percentage * style.getProbaFromNote(save, save) / 100;
	  if (percentage < NOT_ENOUGH_CHANCE)
	    {
	      (*sequence)[i].first = fixingMarkov(style, save, i + static_cast<unsigned int>(1) == sequence->size() ? -1 : (*sequence)[i + 1].first);
	    }
	}
      if (save != (*sequence)[i].first)
	{
	  save = (*sequence)[i].first;
	  percentage = style.getProbaFromNote(save, save);
	}
    }
}

char		Resolution::fixingMarkov(StyleSettings &style, const char prev, const char next)
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

char		Resolution::fixingMarkov(const char state, const std::vector<char> &strong, const std::vector<char> &medium, const std::vector<char> &weak)
{
  if (state == PROBASTRONG)
    return (strong[rand() % strong.size()]);
  else if (state == PROBAMEDIUM)
    return (medium[rand() % medium.size()]);
  else
    return (weak[rand() % weak.size()]);
}
