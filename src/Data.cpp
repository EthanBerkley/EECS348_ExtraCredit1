#include "Data.h"

Data::Data()
{
  string path = "matching-data.txt";
  ifstream matching_data(path);
  if (!matching_data)
  {
    cerr << "Cannot locate matching-data.txt file!" << endl;
    exit(1);
  }

  preferenceArray = (int*)malloc(sizeof(int) * 50);

  string line;
  int i = 0;
  while (getline(matching_data, line))
  {
    const char* cLine;
    cLine = line.c_str();
    sscanf(cLine, "%d %d %d %d %d",
           preferenceArray + (i * 5),
           preferenceArray + (i * 5) + 1,
           preferenceArray + (i * 5) + 2,
           preferenceArray + (i * 5) + 3,
           preferenceArray + (i * 5) + 4);
    i++;
  }
  matching_data.close();
  current = (int*)malloc(sizeof(int) * 5);
  departments = (Department*)malloc(sizeof(Department) * 5);
  programmers = (Programmer*)malloc(sizeof(Programmer) * 5);
  for (int it = 0; it < 5; it++)
  {
    current[it] = NOTPICKED;
    departments[it] = {preferenceArray + it};
    programmers[it] = {preferenceArray + 25 + it};
  }
}

Programmer::Programmer(preference firstPref)
{
  pref = firstPref;
}

int Programmer::getPreferred(int dep1, int dep2)
{
  for (int i = 0; i < 5; i++)
  {
    int ithPreferred = *(pref + i * 5);
    if (ithPreferred == dep1)
      return dep1;
    if (ithPreferred == dep2)
      return dep2;
  }

  return 0;
}
Department::Department(preference firstPref)
{
  pref = firstPref;
}
int Department::getPreference()
{
  return *pref;
}
void Department::nextPreference()
{
  pref += 5;
}

int Data::loop()
{
  int finished = 1;
  for (int i = 1; i <= 5; i++)
  {
    int depPref = departments[i - 1].getPreference();
    int& proPref = current[depPref - 1];
    if (proPref == NOTPICKED)
    {
      proPref = i;
      continue;
    }
    if (proPref == i)
      continue;

    finished = 0;

    int newPref = programmers[depPref - 1].getPreferred(i, proPref);
    if (newPref == i)
    {
      departments[proPref - 1].nextPreference();
      proPref = newPref;
    }
    else
    {
      departments[i - 1].nextPreference();
    }
    continue;
  }
  return finished;
}

void Data::printFinal()
{
  for (int depI = 0; depI < 5; depI++)
  {
    cout << " Department #" << depI + 1 << " will get Programmer #" << departments[depI].getPreference() << endl;
  }
}