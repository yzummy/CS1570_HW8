/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date:
   File: hw8_fncts.hpp
   Purpose:
*/

#ifndef HW8_FNCTS_H
#define HW8_FNCTS_H

#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

// file name for candidate one's sentences
const char CAND_ONE_SENTENCES[] = "candidate1_sentences.dat";
// file name for candidate one's interjections
const char CAND_ONE_INTERJECTIONS[] = "candidate1_interjections.dat";
// file name for candidate two's sentences
const char CAND_TWO_SENTENCES[] = "candidate2_sentences.dat";
// file name for candidate two's interjections
const char CAND_TWO_INTERJECTIONS[] = "candidate2_interjections.dat";
// file name for prefix expressions for either candidate
const char PREFIX_EXPRESSIONS[] = "prefix_expressions.dat";

// max word length in characters
const short MAX_WORD_LEN = 20;
// max answer/sentence length in characters
const short MAX_SENTENCE_LEN = 1000;

// the upper bound of percentage that would triple letter score
const short TRIPLE_LETTER_CHANCE_UPPER = 2;
// the upper bound of percentage that would double letter score
const short DOUBLE_LETTER_CHANCE_UPPER = TRIPLE_LETTER_CHANCE_UPPER + 3;
// the upper bound of percentage that would triple word score
const short TRIPLE_WORD_CHANCE_UPPER = 2;
// the upper bound of percentage that would double word score
const short DOUBLE_WORD_CHANCE_UPPER = TRIPLE_WORD_CHANCE_UPPER + 5;

// multipliers for score
const short TRIPLE = 3;
const short DOUBLE = 2;

// Desc:
// Pre:
// Post:

template <typename T>
void openFile(T & fileIn, const char fileName[])
{
  fileIn.open( fileName );

  if ( !fileIn )
  {
    // print out error message and exit on failure to open file
    cout << "Error opening file " << fileName << "!" << endl;
    exit( -1 );
  }

  return;
}

// Desc:
// Pre:
// Post:

template <typename T>
void reuseStream( T & fileIn, const char fileName[] )
{
  // get stream object ready for reuse
  fileIn.clear( ); // clear connection
  fileIn.close( ); // close connection

  // connect stream to file
  openFile( fileIn, fileName );

  return;
}

// Desc:
// Pre:
// Post:

long getNumLinesInFile( const char fileName[] );

// Desc:
// Pre:
// Post:

void appendRandomPrefix( char buffer[] );

// Desc:
// Pre:
// Post:

float getScore(const int numCharQue, const char answer[]);


#endif
