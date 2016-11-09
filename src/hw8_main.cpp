/*
   Programmers: Christopher O'Toole and Yunchao Zhang
   Date: 11/8/2016
   File: hw8_main.cpp
   Purpose: To host a debate between two wonderful candidates in order to
            help the citizens of this country decide who they would like to
            vote for.
*/

#include "hw8_fncts.h"

using namespace std;

int main( )
{
  // greeting
  cout << endl << "Welcome to the Presidential Debate on NBC!" << endl
       << "We'll begin with candidate #1!" << endl << endl;

  float candOneScore = 0; // candidate one's score
  float candTwoScore = 0; // candidate two's score
  float score = 0;        // temporary score holder for both candidates
  int questionLen = 0;    // length of question asked

  char answer[MAX_SENTENCE_LEN] = { 0 }; // either candidate's response
  char question[MAX_SENTENCE_LEN] = { 0 }; // user's question

  srand( time( NULL ) ); // set seed for pseudo-random number generation

  for ( int i = 0; i < NUM_QUESTIONS; ++i )
  {
    // display which candidate is being asked
    cout << "candidate #" << ( i % 2 + 1 ) << ": ";

    // allow user to ask question
    cin.getline( question, MAX_SENTENCE_LEN - 1, '\n' );

    // retrieve candidate's answer
    getAnswer( answer,
               ( i % 2 ? CAND_TWO_SENTENCES : CAND_ONE_SENTENCES ),
               ( i % 2 ? CAND_TWO_INTERJECTIONS : CAND_ONE_INTERJECTIONS )
             );
    questionLen = strlen( question );
    score = getScore( questionLen, answer );

    // display answer
    cout << "ans: " << answer << endl;
    // display answer's score
    cout << "score: " << score << endl
         << endl;

    // add score to either candidate's total
    if ( i % 2 )
      candTwoScore += score;
    else
      candOneScore += score;
  }

  // announce winner (candidate with least points wins)
  if ( candOneScore < candTwoScore )
    cout << endl << "Candidate #1 won! Wooo!" << endl;
  else
    cout << endl << "Candidate #2 won! Yeah!" << endl;

  // salutation
  cout << "Thank y'all for watching! Tune in next year!" << endl << endl;
  return 0;
}
