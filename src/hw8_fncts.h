/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date: 11/8/2016
   File: hw8_fncts.h
   Purpose: Contains function declarations for generating the content of the debate
            and scoring the candidates' responses.
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

// Desc: The getline( ) function retrieves a line at the lineNum pos in a file
// Pre:  lineNum > 0 and <= the total number of lines in the file
//       The in param is an open file stream
// Post: The line[] array is updated in the calling function with the line at
//     the lineNum pos from the file associated with in.

void getline( ifstream& in, const int lineNum, char line[] );

// Desc: The getNumLinesInFile( ) function computes the total number of lines
//    in the file named by the fileName param.
// Pre: The file referred to by fileName exists.
// Post: The total number of lines in the given file is returned.

int getNumLinesInFile( const char fileName[] );

// Desc: The appendRandomPrefix( ) function appends a random prefix
//    contained in the file described by the prefixFile param.
// Pre: The file referred to by prefixFile exists.
// Post: The buffer param is prepended in the calling function with a random
//    prefix retrieved from the file.

void appendRandomPrefix( char buffer[], const char prefixFile[] );

// Desc: The myRand( ) function generates a pseudo-random number within the
//    interval [min, max].
// Pre: max > min, max > 0 and min >= 0
// Post: A pseudo-random number within the interval [min, max] is returned.

int myRand( const int min, const int max );

// Desc: The getScoreMult( ) function will return a score multiplier at random
//    given the chance for the double and triple multiplier.
// Pre: 0 < doubleChance, tripleChance < 100
// Post: A random score multiplier will be returned.

int getScoreMult( int doubleChance, int tripleChance );

// Desc: The getScore( ) function will return a score of the candidate's
//    answer based upon its content and the question length.
// Pre: questionLen > 0
// Post: The score for the candidate's response is returned.

float getScore( const int questionLen, const char answer[] );

// Desc: The getAnswer( ) function generates a response for both candidates.
// Pre: The files named by the sentenceFile and interjectionFile params must
//    exist.
// Post: The answer param will be updated with the candidate's response in the
//    calling function.

void getAnswer( char answer[], const char sentenceFile[],
                const char interjectionFile[] );

// Desc: The getPart() function will separate the line into approximately
//    equal parts and update the part param with the chunk of the sentence
//    referred to by partIndex.
// Pre: partIndex < numParts, numParts and partIndex must be > 0
// Post: Part will be updated in the calling function with the specified
//    sentence chunk.

void getPart( const char line[], char part[], const int numParts, const int partIndex );

// Desc: The addInterject() function will append an interjection to the answer
//     param.
// Pre:  The file named by interjectionFile exists.
// Post: The answer param is appended to in the calling function with an
//     interjection.

void addInterjection( char answer[], const char interjectionFile[] );

// Desc: The changePunct() function changes the punctuation at the end of
//     of the answer param to a '?', '.', or '!' character randomly.
// Pre: answer[strlen(answer)-1] is a punctuation character
// Post: The answer param has its punctuation changed in the calling function
//    or keeps its original punctuation.

void changePunct( char answer[] );

// Desc: The openFile() function opens a stream given a fileName.
// Pre:  T is of type ifstream or ofstream
//       If T is of type ifstream, the file referred to by fileName must exist.
// Post: fileIn is opened in the calling function and connected to the
//    specified file.

template <typename T>
void openFile( T& fileIn, const char fileName[] )
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

// Desc: The reuseStream() function reopens the given file stream for reuse
//    with either the same or a different file.
// Pre: T is of type ifstream or ofstream.
//      If T is of type ifstream, the file referred to by fileName must exist.
// Post: fileIn is reopened in the calling function and connected to the
//    specified file.

template <typename T>
void reuseStream( T& fileIn, const char fileName[] )
{
  // get stream object ready for reuse
  fileIn.clear( ); // clear connection
  fileIn.close( ); // close connection

  // connect stream to file
  openFile( fileIn, fileName );

  return;
}

#endif
