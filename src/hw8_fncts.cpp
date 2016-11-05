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
