/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date: 11/8/2016
   File: hw8_fncts.cpp
   Purpose: Contains function definitions for generating the content of the
            debate and scoring the candidates' responses.
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

void getline( ifstream& in, const int lineNum, char line[] )
{
  // ignore all lines until the line in lineNum position
  for (int i = 0; i < lineNum - 1; i++)
    in.ignore( MAX_SENTENCE_LEN, '\n' );

  // get the desired line and store it in the line param
  in.getline( line, MAX_SENTENCE_LEN - 1 );
  return;
}

void appendRandomPrefix( char buffer[], const char prefixFile[] )
{
  // numPrefixes only needs to be computed once, hence the static qualifier
  static const int numPrefixes = getNumLinesInFile( prefixFile );
  char temp[MAX_SENTENCE_LEN] = { 0 };
  ifstream in;

  openFile( in, prefixFile );
  // get random prefix from file
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
  // return pseudo-random number in range [min, max]
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

float getScore( const int questionLen, const char answer[] )
{
  float totScore = 0;
  int wordScore = 0;
  int multiplier = 1;
  int letterScore = 1;
  int i = 0;

  do
  {
    // add wordScore to totScore when the end of a word is detected
    if ( answer[i] == ' ' || answer[i] == '\0' )
    {
      multiplier = getScoreMult( DOUBLE_WORD_CHANCE, TRIPLE_WORD_CHANCE );
      totScore += wordScore * multiplier;
      wordScore = 0;
    }
    // if letter, add letter score to wordScore
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

  // divide total answer score by length of question
  totScore /= questionLen;

  return totScore;
}

void getAnswer( char answer[], const char sentenceFile[],
                const char interjectionFile[] )
{
  // number of sentences to read from file/number of parts to break them into
  short numSentencesToRead = myRand( MIN_SENTENCES, MAX_SENTENCES );
  // number of sentences in file
  int numSentences = 0;
  // line position
  int lineNum = 0;

  char line[MAX_SENTENCE_LEN] = { 0 }; // stores random line from sentence file
  char part[MAX_SENTENCE_LEN / 2] = { 0 }; // stores random sentence chunk
  ifstream in; // sentence file stream

  // zero out the answer buffer with line.
  strncpy( answer, line, MAX_SENTENCE_LEN );
  // open candidate's sentence file
  openFile( in, sentenceFile );

  // get number of lines in the sentence file
  in >> numSentences;

  // add part of the line to the answer and add interjection by chance
  for (int i = 0; i < numSentencesToRead; i++)
  {
    // set in to beginning of file
    reuseStream( in, sentenceFile );

    // get random line from candidate's sentence file
    lineNum = myRand( 2, numSentences );
    getline( in, lineNum, line );

    // concatenate sentence chunk onto candidate's response.
    getPart( line, part, numSentencesToRead, i );
    strncat( answer, part, MAX_SENTENCE_LEN - 1 );

    // append interjection by chance until last iteration
    if ( i < numSentencesToRead - 1 )
      addInterjection( answer, interjectionFile );
  }

  // append random prefix to file by chance.
  if ( myRand( 1, 100 ) <= APPEND_PREFIX_CHANCE )
    appendRandomPrefix( answer, PREFIX_EXPRESSIONS );

  changePunct( answer );

  in.close( );
  return;
}

void getPart( const char line[], char part[], const int numParts, const int partIndex )
{
  const int len = strlen( line ); // line length
  int numWords = 0; // total number of words
  int numWordsPerPart = 0; // number of words in chunk
  int leftIndex = 0; // starting index for copy
  int ctr = 0; // word counter

  for ( int i = 0; i < len; ++i )
    if ( line[i] == ' ' ) // count words based on number of spaces
      ++numWords;
    else if ( !isspace( line[i] ) && line[i + 1] == '\0' ) // count last word
      ++numWords;

  // divide sentence into "equal" chunks
  numWordsPerPart = numWords / numParts;

  if ( !numWordsPerPart ) // display error and terminate if 0
  {
    cout << "Sorry champ, I can't split that text into THAT many parts!"
         << endl;

    exit( -1 );
  }

  // while we have not reached the desired word
  while ( ctr < numWordsPerPart * partIndex && leftIndex < len )
    ctr += ( line[leftIndex++] == ' ' ); // count each word as we pass

  // make sure that we can get the chunk specified by partIndex
  if ( ctr == numWordsPerPart * partIndex && leftIndex < len )
  {
    // set ctr to zero for the while-loop.
    ctr = 0;

    // make the last chunk get the leftover bits of the sentence
    if ( partIndex == numParts - 1 )
      numWordsPerPart = numWords - numWordsPerPart * ( numParts - 1 );

    // make the first character of the chunk a space
    part[ctr++] = ' ';

    // copy the chunk into part until we reach the end of the line or we copy
    // the desired number of words.
    do
    {
      part[ctr++] = line[leftIndex++];

      numWordsPerPart -= ( line[leftIndex] == ' ' );
    } while ( numWordsPerPart && leftIndex < len );
  }
  else // display an error message and terminate if partIndex was invalid.
  {
    cout << "Could not get the word(s) at index " << partIndex << "!" << endl;
    exit( -1 );
  }

  // nul-terminate the string
  part[ctr] = '\0';
  return;
}

void addInterjection( char answer[], const char interjectionFile[] )
{
  int numLines = 0;
  int lineNum = 0;
  char interjection[MAX_SENTENCE_LEN] = { 0 };
  ifstream in;

  // add interjection by chance
  if ( myRand( 1, 100 ) <= INTERJECTION_CHANCE )
  {
    // open interjection file and get number of interjections
    openFile( in, interjectionFile );
    in >> numLines;

    // get interjection at random position in file
    lineNum = myRand( 1, numLines );

    // ignore all interjections till we reach the desired one
    for ( int i = 0; i < lineNum - 1; i++ )
      in.ignore( MAX_SENTENCE_LEN, '\n' );

    // get the interjection we want.
    in.getline( interjection, MAX_SENTENCE_LEN - 1, '\n' );

    // concatenate the interjection to the answer
    strncat( answer, interjection, MAX_SENTENCE_LEN - 1 );
  }

  in.close( );
  return;
}

void changePunct( char answer[] )
{
  // assume that the last character is punctuation
  int punctIndex = strlen( answer ) - 1;
  int randNum = myRand( 1, 100 );

  // set the last character to the same or different character randomly.
  if ( randNum <= PERIOD_CHANCE )
    answer[punctIndex] = '.';
  else if ( randNum <= PERIOD_CHANCE + QUESTION_MARK_CHANCE )
    answer[punctIndex] = '?';
  else
    answer[punctIndex] = '!';

  return;
}
