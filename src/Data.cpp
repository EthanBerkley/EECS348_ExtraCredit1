#include "Data.h"

Data::Data()
{
  // ----- init variable containing file data -----
  const string path = "matching-data.txt";
  ifstream matching_data(path);
  if (!matching_data)
  {
    cerr << "Cannot locate matching-data.txt file!" << endl;
    exit(1);
  }

  // ----- move data from file variable to array -----
  preferenceArray = (int*)malloc(sizeof(int) * 50);

  string line;
  int i = 0;
  while (getline(matching_data, line))
  {
    const char* cLine;
    cLine = line.c_str();

    // for each line, fill 5 elements of array.
    sscanf(cLine, "%d %d %d %d %d",
           preferenceArray + (i * 5),
           preferenceArray + (i * 5) + 1,
           preferenceArray + (i * 5) + 2,
           preferenceArray + (i * 5) + 3,
           preferenceArray + (i * 5) + 4);
    i++;
  }
  // stop reading from file.
  matching_data.close();

  // set up other arrays
  current = (int*)malloc(sizeof(int) * 5);
  departments = (Department*)malloc(sizeof(Department) * 5);
  programmers = (Programmer*)malloc(sizeof(Programmer) * 5);
  for (int it = 0; it < 5; it++)
  {
    // say that currently no programmers have been preferred.
    current[it] = NOTPICKED;
    // set up the pointer variables.
    departments[it] = {preferenceArray + it};
    programmers[it] = {preferenceArray + 25 + it};
  }
}

Data::~Data()
{
  free(preferenceArray);
  free(current);
  free(departments);
  free(programmers);
}

Programmer::Programmer(preference firstPref)
{
  pref = firstPref;
}

int Programmer::getPreferred(int dep1, int dep2)
{
  // get first dept of the two.
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
  // if no conflict in current iteration, return 1.
  int finished = 1;

  // algorithmically speaking, loop could terminate the instant
  // all 5 programmers are marked as preferred by a department
  // but terminating when no more conflicts exist is basically the same
  // and easier to implement / read.

  // iterate through each department
  for (int i = 1; i <= 5; i++)
  {
    // who does that department want to hire?
    int depPref = departments[i - 1].getPreference();

    // is that programmer already wanted by a different department? (reference, so it can be changed)
    int& proPref = current[depPref - 1];

    // if not, great!
    if (proPref == NOTPICKED)
    {
      proPref = i;
      continue;
    }

    // if its wanted by the current department, great!
    if (proPref == i)
      continue;

    // otherwise, there has been a conflict.

    // iterate at least one more time.
    finished = 0;

    // which of the two departments does the programmer prefer?
    int newPref = programmers[depPref - 1].getPreferred(i, proPref);

    // if current department won the conflict
    if (newPref == i)
    {
      // make other department change preference
      departments[proPref - 1].nextPreference();

      // set the index in the array to current department
      proPref = newPref;
    }
    // if current department loses conflict
    else
    {
      // current department must change preference
      departments[i - 1].nextPreference();
    }
    continue;
  }
  return finished;
}

void Data::printFinal()
{
  // iterate through departments
  for (int depI = 0; depI < 5; depI++)
  {
    // Department #{} will get Programmer #{}
    cout << " Department #" << depI + 1 << " will get Programmer #" << departments[depI].getPreference() << endl;
  }
}
