#include <iostream>
using namespace std ;

class Two {
public:
  int part1 ;
  int part2 ;
} ;


int main() {

  Two * dp[10] ;

  // fill in code here
  for (int i = 0; i < 10; i++){
    Two * temp = new Two;
    temp->part1 = 0;
    temp->part2 = 0;
    dp[i] = temp;
  }

  return 0 ;
}
