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
  char buffer[MAX_SENTENCE_LEN] = " Did it work?";
  char answer[MAX_SENTENCE_LEN] = { 0 };
  srand( time( NULL ) ); // set seed for pseudo-random number generation

  getAnswer(answer, CAND_ONE_SENTENCES, CAND_ONE_INTERJECTIONS); \

    cout << "answer: " << answer << endl;
  //Append hte prefix the the answer
  if(myRand(1,100)<=CHANCE_APPENDING)
    appendRandomPrefix( buffer );


  cout << buffer << endl;

  cout << "score: " << getScore(5, buffer);
  
  int a;
  cin >> a;
  return 0;
}
