/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date:
   File: hw8_fncts.cpp
   Purpose:
*/

#include "hw8_fncts.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
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
  // get a random number between min and max inclusively
  return rand() % ( max - min + 1 ) + min;
}

long getScoreMult( int doubleChance, int tripleChance )
{
  int scoreMult = 1;

  // set scoreMult to double or triple by chance
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
    // add wordScore to totScore when it's space
    if ( answer[i] == ' ' || answer[i] == '\0' ) 
    {
      multiplier = getScoreMult( DOUBLE_WORD_CHANCE, TRIPLE_WORD_CHANCE );
      totScore += wordScore * multiplier;
      wordScore = 0;
    }
    // if it is a letter, add letter score to wordScore
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

void getAnswer(char answer[], const char sentenceFile[], 
               const char interjectionFile[])
{
  // get number of sentences to take from the file
  short randNum = myRand(MIN_SENTENCES, MAX_SENTENCES);
  int numSentences;
  int lineNum;
  char line[MAX_SENTENCE_LEN] = { 0 };
  
  // open the sentence and interjection files
  ifstream inSentence, inInterject;
  openFile(inInterject, interjectionFile);
  openFile(inSentence, sentenceFile);

  // get number of lines in the sentence file
  inSentence >> numSentences;

  // add part of the line to the answer and add interjection by chance
  for (int i = 0; i < randNum; i++)
  {
    char part[MAX_SENTENCE_LEN / 2] = { 0 };
    reuseStream(inSentence, sentenceFile);
    lineNum = myRand(1, numSentences) + 1;
    getLine(inSentence, lineNum, line);
    getPart(line, part, randNum, i);
    strcat(answer, part);
    if(i < randNum - 1)
      addInterject(answer, inInterject);
  }

  // close file streams
  inSentence.close();
  inInterject.close();
  return;
}

void getLine(ifstream & in, const int lineNum, char line[])
{
  // ignore all lines until lineNum-th line in the file
  for (int i = 1; i < lineNum; i++)
    in.ignore(MAX_SENTENCE_LEN,'\n');
  in.getline(line, MAX_SENTENCE_LEN-1);
  return;
}



void getPart(const char line[], char part[], const int totParts, const int partNum)
{
  int length = strlen(line);
  int left = length / totParts * partNum;
  int right = length;
  int count=0;
 
  // get left index of the white space
  if (partNum != totParts-1)
  {
    right = length / totParts * (partNum + 1);
    while (line[right] != ' ')
      right--;
  }

  // get right index of the white space 
  if (partNum != 0)
  {
    while (line[left] != ' ')
      left--;
  }
  
  // store that part of the line into the part[]
  while (left < right)
  {
    part[count] = line[left++];
    count++;
  }

  // add null character to the part[]
  part[count] = '\0';

  return;
}

void addInterject(char answer[], ifstream & inInterject)
{
    int randNum = myRand(1, 100);
    int numLines;
    int lineNum;
    char interjection[MAX_SENTENCE_LEN];

    // add interjection by chance
    if (randNum <= CHANCE_INTERJECTION)
    {
      inInterject >> numLines;
      lineNum = myRand(1, numLines) + 1;
      for (int i = 0; i < lineNum; i++)
        inInterject.ignore(MAX_SENTENCE_LEN, '\n');
      
      // ignore the three dots at the beginning
      inInterject.ignore(3);

      // read until reaches the dot at the end
      inInterject.getline(interjection, MAX_SENTENCE_LEN - 1,'.');
      
      // add white space to the end of the interjection
      strcat(answer, " ");

      // concatenate the interjection to the answer
      strcat(answer, interjection);        
    }
    return;
  
}

void changePunct(char answer[])
{
  int endIndex = strlen(answer) - 1;
  cout << answer[endIndex];
  return;
}
