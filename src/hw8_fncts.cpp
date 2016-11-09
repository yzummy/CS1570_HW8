/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date:
   File: hw8_fncts.cpp
   Purpose:
*/

#include "hw8_fncts.h"

using namespace std;

int getNumLinesInFile( const char fileName[] )
{
  ifstream in;
  int numLines = 0;

  openFile( in, fileName );

  // ignore each line until eof is reached
  while ( in.ignore( MAX_SENTENCE_LEN, '\n' ) ) ++numLines;

  in.close( );
  return numLines;
}

void getline( ifstream & in, const int lineNum, char line[] )
{
  // ignore all lines until lineNum-th line in the file
  for (int i = 0; i < lineNum - 1; i++)
    in.ignore( MAX_SENTENCE_LEN, '\n' );

  in.getline( line, MAX_SENTENCE_LEN - 1 );
  return;
}

void appendRandomPrefix( char buffer[] )
{
  // numPrefixes only needs to be computed once, hence the static qualifier
  static const int numPrefixes = getNumLinesInFile( PREFIX_EXPRESSIONS );
  char temp[MAX_SENTENCE_LEN] = { 0 };
  ifstream in;

  openFile( in, PREFIX_EXPRESSIONS );
  getline( in, myRand( 1, numPrefixes ), temp );

  // use temp to store concatenation
  strncat( temp, buffer, MAX_SENTENCE_LEN - 1 );
  // transfer result to buffer
  strncpy( buffer, temp, MAX_SENTENCE_LEN - 1 );

  in.close( );
  return;
}

int myRand( const int min, const int max )
{
  // get a random number between min and max inclusively
  return rand() % ( max - min + 1 ) + min;
}

int getScoreMult( int doubleChance, int tripleChance )
{
  int scoreMult = 1;
  int randNum = myRand( 1, 100 );

  // set scoreMult to double or triple by chance
  if ( randNum <= doubleChance )
    scoreMult = DOUBLE;
  else if ( randNum <= doubleChance + tripleChance )
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

void getAnswer( char answer[], const char sentenceFile[],
                const char interjectionFile[] )
{
  // get number of sentences to take from the file
  short numSentencesToRead = myRand( MIN_SENTENCES, MAX_SENTENCES );
  int numSentences = 0;
  int lineNum = 0;

  char line[MAX_SENTENCE_LEN] = { 0 };
  char part[MAX_SENTENCE_LEN / 2] = { 0 };
  ifstream in;

  strncpy( answer, line, MAX_SENTENCE_LEN );
  openFile( in, sentenceFile );

  // get number of lines in the sentence file
  in >> numSentences;

  // add part of the line to the answer and add interjection by chance
  for (int i = 0; i < numSentencesToRead; i++)
  {
    reuseStream( in, sentenceFile );

    lineNum = myRand( 2, numSentences );
    getline( in, lineNum, line );
    getPart( line, part, numSentencesToRead, i );
    strncat( answer, part, MAX_SENTENCE_LEN - 1 );

    if ( i < numSentencesToRead - 1 )
      addInterject( answer, interjectionFile );
  }

  if ( myRand( 1, 100 ) <= APPEND_PREFIX_CHANCE )
    appendRandomPrefix( answer );

  changePunct( answer );

  in.close( );
  return;
}

void getPart( const char line[], char part[], const int numParts, const int partIndex )
{
  const int len = strlen( line );
  int numWords = 0;
  int numWordsPerPart = 0;
  int leftIndex = 0;
  int ctr = 0;

  for ( int i = 0; i < len; ++i )
    if ( line[i] == ' ' )
      ++numWords;
    else if ( !isspace( line[i] ) && line[i + 1] == '\0' )
      ++numWords;

  numWordsPerPart = numWords / numParts;

  if ( !numWordsPerPart )
  {
    cout << "Sorry champ, I can't split that text into THAT many parts!"
         << endl;

    exit( -1 );
  }

  while ( ctr < numWordsPerPart * partIndex && leftIndex < len )
    ctr += ( line[leftIndex++] == ' ' );

  if ( ctr == numWordsPerPart * partIndex && leftIndex < len )
  {
    ctr = 0;

    if ( partIndex == numParts - 1 )
      numWordsPerPart = numWords - numWordsPerPart * ( numParts - 1 );

    part[ctr++] = ' ';

    do
    {
      part[ctr++] = line[leftIndex++];

      numWordsPerPart -= ( line[leftIndex] == ' ' );
    } while ( numWordsPerPart && leftIndex < len );
  }
  else
  {
    cout << "Could not get the word(s) at index " << partIndex << "!" << endl;
    exit( -1 );
  }

  part[ctr] = '\0';
  return;
}

void addInterject( char answer[], const char interjectionFile[] )
{
  int numLines = 0;
  int lineNum = 0;
  char interjection[MAX_SENTENCE_LEN];
  ifstream in;

  // add interjection by chance
  if ( myRand( 1, 100 ) <= INTERJECTION_CHANCE )
  {
    openFile( in, interjectionFile );
    in >> numLines;
    lineNum = myRand( 1, numLines );

    for ( int i = 0; i < lineNum - 1; i++ )
      in.ignore( MAX_SENTENCE_LEN, '\n' );

    in.getline( interjection, MAX_SENTENCE_LEN - 1, '\n' );

    // concatenate the interjection to the answer
    strncat( answer, interjection, MAX_SENTENCE_LEN - 1 );
  }

  in.close( );
  return;
}

void changePunct( char answer[] )
{
  int punctIndex = strlen( answer ) - 1;
  int randNum = myRand( 1, 100 );

  if ( randNum <= PERIOD_CHANCE )
    answer[punctIndex] = '.';
  else if ( randNum <= PERIOD_CHANCE + QUESTION_MARK_CHANCE )
    answer[punctIndex] = '?';
  else
    answer[punctIndex] = '!';

  return;
}
