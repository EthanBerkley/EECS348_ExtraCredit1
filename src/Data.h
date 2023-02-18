#ifndef DATA_H
#define DATA_H
#include <fstream>
#include <iostream>
#include <string>
#define NOTPICKED 0

using namespace std;

typedef int* preference;

class Programmer
{
  public:
  Programmer(preference firstPref);
  int getPreferred(int dep1, int dep2);

  private:
  preference pref;
};

class Department
{
  public:
  Department(preference firstPref);
  int getPreference();
  void nextPreference();

  private:
  preference pref;
};

class Data
{
  public:
  Data();

  int loop();
  void printFinal();

  private:
  Programmer* programmers;
  Department* departments;
  int* preferenceArray;
  int* current;
};

#endif