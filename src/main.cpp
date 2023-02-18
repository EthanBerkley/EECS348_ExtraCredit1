/*
algorithm:
  have array of length 5, representing each programmer
  have each department try to enter write itself to their preferred programmers index.
  if the index is empty, insert it and continue.
  if the index contains itself, continue.
  if the index contains a different department:
    whichever department is less preferred by the programmer loses the bid for that programmer.
    more preferred inserts itself to that index
    less preferred moves on to their next preference
    more preferred gets to write themself to that index

  when every index contains a department, the algorithm is complete.
*/
#include "Data.h"
int main()
{
  // initialize exec class
  Data data;

  // run algorithm until its complete
  while (!data.loop())
  {
  };
  // once its complete, print formatted output.
  data.printFinal();

  // terminate, data object should be destroyed and deallocate all memory.
  return 0;
}