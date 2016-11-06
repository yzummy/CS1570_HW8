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

long myRand( const long min, const long max )
{
  return rand() % ( max - min + 1 ) + min;
}

long getScoreMult( int doubleChance, int tripleChance )
{
  int scoreMult = 1;

  if ( myRand( 1, 100 ) <= doubleChance )
    scoreMult = DOUBLE;
  else if ( myRand( 1, 100 ) <= tripleChance )
    scoreMult = TRIPLE;

  return scoreMult;
}

float getScore(const int numCharQue, const char answer[])
{
  float totScore = 0;
  int wordScore = 0;
  int multiplier = 1;
  int letterScore = 1;

  int i = 0;

  do
  {
    if ( answer[i] == ' ' || answer[i] == '\0' )
    {
      multiplier = getScoreMult( DOUBLE_WORD_CHANCE, TRIPLE_WORD_CHANCE );
      totScore += wordScore * multiplier;
      wordScore = 0;
    }
    else if ( isalpha( answer[i] ) )
    {
      multiplier = getScoreMult( DOUBLE_LETTER_CHANCE, TRIPLE_LETTER_CHANCE );

      switch( tolower( answer[i] ) )
      {
        case 'd': case 'g':
          letterScore = 2;
        break;

        case 'b': case 'c': case 'm': case 'p':
         letterScore = 3;
        break;

        case 'f': case 'h': case 'v': case 'w': case 'y':
          letterScore = 4;
        break;

        case 'k':
          letterScore = 5;
        break;

        case 'j': case 'x':
          letterScore = 8;
        break;

        case 'q': case 'z':
          letterScore = 10;
        break;

        default:
          letterScore = 1;
      }

      wordScore += multiplier * letterScore;
    }
  } while ( answer[i++] != '\0' );

  totScore /= numCharQue;

  return totScore;
}
