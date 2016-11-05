/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date:
   File: hw8_main.cpp
   Purpose:
*/

#include "hw8_fncts.h"

using namespace std;

int main( )
{
  char buffer[MAX_SENTENCE_LEN] = " Did it work?";

  srand( time( NULL ) ); // set seed for pseudo-random number generation

  appendRandomPrefix( buffer );
  cout << buffer << endl;

  cout << "score: " << getScore(5, buffer);
  return 0;
}
