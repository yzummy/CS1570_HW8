/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date:
   File: hw8_fncts.hpp
   Purpose:
*/

#ifndef HW8_FNCTS_H
#define HW8_FNCTS_H

#include <string>
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
// percent chance for appending prefix
const short APPEND_PREFIX_CHANCE = 50;
// percent chance for inserting interjection
const short INTERJECTION_CHANCE = 25;
// percent chance for changing punctuation to period
const short PERIOD_CHANCE = 40;
// percent chance for changing punctuation to question mark
const short QUESTION_MARK_CHANCE = 30;
// percent chance for changing punctuation to exclamation point
const short EXCLAMATION_POINT_CHANCE = 30;

// number of questions to ask the "candidates"
const short NUM_QUESTIONS = 8;

// multipliers for score
const short TRIPLE = 3;
const short DOUBLE = 2;

// minimum and maximum number of sentences chosen from file
const short MIN_SENTENCES = 2;
const short MAX_SENTENCES = 4;


// Desc: the getLine() function will store the specific line in the file
//       into line[]
// Pre:  in has to be open already and lineNum has to be positive
// Post: the lineNum-th line in the file would be stored in line[]

void getline( ifstream & in, const int lineNum, char line[] );

// Desc:
// Pre:
// Post:

int getNumLinesInFile( const char fileName[] );

// Desc:
// Pre:
// Post:

void appendRandomPrefix( char buffer[] );

// Desc: the myRand() function will generate a random int within the range
// Pre: none
// Post: A random int within the range would be generated

int myRand( const int min, const int max );

// Desc: the getScoreMult() function will get a random multiplier
// Pre: both doubleChance and tripleChance have to be bigger between 0 and 100
// Post: A random score multiplier will be returned

int getScoreMult( int doubleChance, int tripleChance );

// Desc: the getScore() function will return a score according to the answer
// Pre: numCharQue has to be positive
// Post: a score corresponding to the will be returned

float getScore(const int numCharQue, const char answer[]);

// Desc: the getAnswer() function will generate the answer for candidates
// Pre: the files with file name sentenceFile and interjectionFile have to
//      exist
// Post: the answer generated for that candidate will be stored in answer[]

void getAnswer(char answer[], const char sentenceFile[],
                const char interjectionFile[]);

// Desc: the getPart() function will separate the line into approximately
//       equal parts and store the partNum-th part into part[]
// Pre:  totParts and partNum have to be positive
// Post: the partNum-th part of the line would be stored in part[]

void getPart( const char line[], char part[], const int numParts, const int partIndex );

// Desc: the addinterject() function will append an interjection phrase
//       to the answer
// Pre:  inInterject file input stream has to be open
// Post: an interjection phrase would be append to the answer

void addInterject(char answer[], const char interjectionFile[] );

// Desc:
// Pre:
// Post:

void changePunct( char answer[] );

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
