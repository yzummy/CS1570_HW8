/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date:
   File: hw8_fncts.cpp
   Purpose:
*/

#include "hw8_fncts.h"

using namespace std;

long getNumLinesInFile( const char fileName[] )
{
  ifstream in;
  long numLines = 0;

  openFile( in, fileName );

  // ignore each line until eof is reached
  while ( in.ignore( MAX_SENTENCE_LEN, '\n' ) ) ++numLines;

  in.close( );
  return numLines;
}

void appendRandomPrefix( char buffer[] )
{
  // numPrefixes only needs to be computed once, hence the static qualifier
  static const long numPrefixes = getNumLinesInFile( PREFIX_EXPRESSIONS );

  // max sentence length should be more than enough to store a prefix
  char temp[MAX_SENTENCE_LEN] = { 0 };

  long chosenPrefixIndex = rand() % numPrefixes;
  long i;

  ifstream in;

  openFile( in, PREFIX_EXPRESSIONS );

  // ignore all lines until we reach our randomly chosen line
  for ( i = 0; i < numPrefixes && i != chosenPrefixIndex; ++i )
    in.ignore( MAX_SENTENCE_LEN, '\n' );

  // get the line we chose
  in.getline( temp, MAX_SENTENCE_LEN - 1 );

  // use temp to store concatenation
  strncat( temp, buffer, MAX_SENTENCE_LEN - 1 );
  // transfer result to buffer
  strncpy( buffer, temp, MAX_SENTENCE_LEN - 1 );

  in.close( );
  return;
}

float getScore(const int numCharQue, const char answer[])
{
  float totScore = 0;;
  int wordScore = 0;
  int count = 0;
  int multiplier; 
  int random;
  char c;
  c = answer[count];
  while (c != 0)
  {
    if (c == ' ')
    {
      random = rand() % 100 + 1;
      if (random <= TRIPLE_WORD_CHANCE_UPPER)
        multiplier = TRIPLE;
      else if (random <= DOUBLE_WORD_CHANCE_UPPER)
        multiplier = DOUBLE;
      wordScore *= multiplier;
      totScore += wordScore;
      wordScore = 0;
    }
    else
    {
      multiplier = 1;
      random = rand() % 100 + 1;
      if (random <= TRIPLE_LETTER_CHANCE_UPPER)
        multiplier = TRIPLE;
      else if (random <= DOUBLE_LETTER_CHANCE_UPPER)
        multiplier = DOUBLE;
      c = tolower(c);
      if (c == 'e' || c == 'a' || c == 'i' || c == 'o' || c == 'n'
        || c == 'r' || c == 't' || c == 'l' || c == 's' || c == 'u')
        wordScore += multiplier * 1;
      else if (c == 'd' || c == 'g')
        wordScore += multiplier * 2;
      else if (c == 'b' || c == 'c' || c == 'm' || c == 'p')
        wordScore += multiplier * 3;
      else if (c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y')
        wordScore += multiplier * 4;
      else if (c == 'k')
        wordScore += multiplier * 5;
      else if (c == 'j' || c == 'x')
        wordScore += multiplier * 8;
      else if (c == 'q' || c == 'z')
        wordScore += multiplier * 10;
    }

    c = answer[++count];
  }

  totScore /= numCharQue;

  return totScore;
}
