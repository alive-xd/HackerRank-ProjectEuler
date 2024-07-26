#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>

int main()
{
  // four-sided dices ?
  unsigned int diceSize = 4;
  std::cin >> diceSize;
  // print the 3 most frequent fields
  unsigned int showFields = 3;
  std::cin >> showFields;

  // number of simulated moves
  const unsigned int Rolls = 1000000;//50000000;

  // always the same random numbers
  srand(0);

  // board setup
  const unsigned int NumFields = 40;
  // special field positions
  const unsigned int Go        =  0;
  const unsigned int Jail      = 10;
  const unsigned int GoToJail  = 30;
  const unsigned int Community  [3] = {  2, 17, 33 };
  const unsigned int Chance     [3] = {  7, 22, 36 };
  const unsigned int NextRailway[3] = { 15, 25,  5 }; // index x corresponds to Chance[x]
  const unsigned int NextUtility[3] = { 12, 28, 12 }; // index x corresponds to Chance[x]

  // random setup of community and chance cards, give them IDs 0..15
  std::vector<unsigned int> chance, community;
  for (unsigned int i = 0; i < 16; i++)
  {
    chance   .push_back(i);
    community.push_back(i);
  }
  std::random_shuffle(chance.begin(),    chance.end());
  std::random_shuffle(community.begin(), community.end());

  // Monte-Carlo simulation
  unsigned int current = Go;
  unsigned int doubles = 0;
  std::vector<unsigned long long> count(NumFields, 0);
  for (unsigned int rolls = 0; rolls < Rolls; rolls++)
  {
    // roll the dice ...
    unsigned int dice1 = (rand() % diceSize) + 1;
    unsigned int dice2 = (rand() % diceSize) + 1;
    // next field
    unsigned int next = (current + dice1 + dice2) % NumFields;

    // double ?
    if (dice1 == dice2)
      doubles++;
    else
      doubles = 0;

    if (doubles == 3)
    {
      next = Jail;
      doubles = 0;
    }

    // chance
    if (next == Chance[0] || next == Chance[1] || next == Chance[2])
    {
      // ID of current chance field (needed to figure out next railway / utility)
      int id = 0;
      if (next == Chance[1])
        id = 1;
      if (next == Chance[2])
        id = 2;

      // check card ID of the topmost card
      switch (chance.front())
      {
      case 0: next = Go; break;
      case 1: next = Jail; break;
      case 2: next = 11; break; // C1
      case 3: next = 24; break; // E3
      case 4: next = 39; break; // H2
      case 5: next =  5; break; // R1
              // go back 3 squares (might land on GoToJail, too)
              // awkward formula needs to take care of CC1 which redirects to H2
      case 6: next = (next + NumFields - 3) % NumFields; break;
      case 7: // two railway cards
      case 8: next = NextRailway[id]; break;
      case 9: next = NextUtility[id]; break;
      default: break;
      }

      // move card to the bottom
      std::rotate(chance.begin(), chance.begin() + 1, chance.end());
    }

    // community
    if (next == Community[0] || next == Community[1] || next == Community[2])
    {
      // check card ID of the topmost card
      switch (community.front())
      {
      case 0: next = Go;   break;
      case 1: next = Jail; break;
      default: break;
      }

      // move card to the bottom
      std::rotate(community.begin(), community.begin() + 1, community.end());
    }

    if (next == GoToJail)
      next = Jail;

    count[next]++;
    current = next;
  }

  // normalize (actually not needed, just to ease debugging)
  unsigned long long sum = 0;
  for (auto x : count)
    sum += x;

  // use std::map's implicit sorting
  std::multimap<double, unsigned int> sorted; // multimap in case of identical probabilities
  for (unsigned int i = 0; i < count.size(); i++)
    sorted.insert(std::make_pair(count[i] * 100.0 / sum, i));

  // extract the field positions
  std::vector<unsigned int> result;
  for (auto x : sorted)
    result.push_back(x.second);

  // and show the most frequent ones (they are at the end of the container)
  auto i = result.rbegin();


  // field names
  const char* names[] = { "GO",   "A1", "CC1", "A2",  "T1", "R1", "B1",  "CH1", "B2", "B3",
                          "JAIL", "C1", "U1",  "C2",  "C3", "R2", "D1",  "CC2", "D2", "D3",
                          "FP",   "E1", "CH2", "E2",  "E3", "R3", "F1",  "F2",  "U2", "F3",
                          "G2J",  "G1", "G2",  "CC3", "G3", "R4", "CH3", "H1",  "T2", "H2" };
  for (unsigned int j = 0; j < showFields; j++)
    std::cout << names[*i++] << " ";


  return 0;
}
