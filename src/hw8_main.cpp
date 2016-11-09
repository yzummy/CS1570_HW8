/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date:
   File: hw8_main.cpp
   Purpose:
*/

#include "hw8_fncts.h"

using namespace std;

int main( )
{
  cout << endl << "Welcome to the Presidential Debate on NBC!" << endl
       << "We'll begin with candidate #1!" << endl << endl;

  float candOneScore = 0;
  float candTwoScore = 0;
  float score = 0;
  int questionLen = 0;

  char answer[MAX_SENTENCE_LEN] = { 0 };
  char question[MAX_SENTENCE_LEN] = { 0 };

  srand( time( NULL ) ); // set seed for pseudo-random number generation

  for ( int i = 0; i < NUM_QUESTIONS; ++i )
  {
    cout << "candidate #" << ( i % 2 + 1 ) << ": ";

    cin.getline( question, MAX_SENTENCE_LEN - 1, '\n' );
    getAnswer( answer,
               ( i % 2 ? CAND_TWO_SENTENCES : CAND_ONE_SENTENCES ),
               ( i % 2 ? CAND_TWO_INTERJECTIONS : CAND_ONE_INTERJECTIONS )
             );

    questionLen = strlen( question );
    score = getScore( questionLen, answer );

    cout << "ans: " << answer << endl;
    cout << "score: " << score << endl
         << endl;

    if ( i % 2 )
      candTwoScore += score;
    else
      candOneScore += score;
  }

  if ( candOneScore < candTwoScore )
    cout << endl << "Candidate #1 won! Wooo!" << endl;
  else
    cout << endl << "Candidate #2 won! Yeah!" << endl;

  cout << "Thank y'all for watching! Tune in next year!" << endl << endl;
  return 0;
}
