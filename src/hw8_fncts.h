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

// percent chance triple letter score
const short TRIPLE_LETTER_CHANCE = 2;
// percent chance double letter score
const short DOUBLE_LETTER_CHANCE = 3;
// percent chance triple word score
const short TRIPLE_WORD_CHANCE = 2;
// percent chance double word score
const short DOUBLE_WORD_CHANCE = 5;
// percent chance apending Prefix
const short CHANCE_APPENDING = 50;
// percent chance adding interjection
const short CHANCE_INTERJECTION = 25;

// multipliers for score
const short TRIPLE = 3;
const short DOUBLE = 2;

//minimum and maximum number of sentences chosen from file
const short MIN_SENTENCES = 2;
const short MAX_SENTENCES = 4;

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

long myRand( const long min, const long max );

// Desc:
// Pre:
// Post:

long getScoreMult( int doubleChance, int tripleChance );

// Desc:
// Pre:
// Post:

float getScore(const int numCharQue, const char answer[]);

// Desc:
// Pre:
// Post:

void getAnswer(char answer[], const char sentenceFile[], const char interjectionFile[]);

// Desc:
// Pre:
// Post:

void getLine(ifstream & in, const int lineNum, char line[]);

// Desc:
// Pre:
// Post:

void getPart(const char line[], char part[], const int totParts, const int partNum);

// Desc:
// Pre:
// Post:

void addInterject(char answer[], ifstream & inInterject);


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

#endif
