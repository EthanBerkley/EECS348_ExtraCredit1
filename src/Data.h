#ifndef DATA_H
#define DATA_H
#include <fstream>
#include <iostream>
#include <string>
#define NOTPICKED 0

using namespace std;

typedef int* preference;

// class representing each programmer.
// keeps track of its own preferences by means of a single pointer.
class Programmer
{
  public:
  Programmer(preference firstPref);

  // decide which department wins a conflict
  int getPreferred(int dep1, int dep2);

  private:
  preference pref;
};

// class representing preferences of each department.
// preference changes whenever a more desired department prefers the same programmer.
class Department
{
  public:
  Department(preference firstPref);

  // dereference preference
  int getPreference();

  // conflict lost
  void nextPreference();

  private:
  // pointer to its current preferred programmer
  preference pref;
};

class Data // executive class containing algorithm and its state.
{
  public:
  // read data from matching-data.txt, initialize state.
  Data();

  // free memory allocated
  ~Data();

  // actual algorithm, loops until complete.
  int loop();

  // once looping is finished, format and print output.
  void printFinal();

  private:
  // will have length of 5
  Programmer* programmers;

  // will have length of 5
  Department* departments;

  // will have length of 50
  int* preferenceArray;

  // will have length of 5
  int* current;
};

#endif