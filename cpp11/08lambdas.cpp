#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

struct Hero {
  /* member variables */
  std::string name;
  int         gold;
  int         honor;
  /* constructor */
  Hero(const std::string& n, int g, int h) : name(n), gold(g), honor(h) {}
  /* member functions */
  void print() {
    std::cout << std::setw(12) << std::left  << name  << ": "     <<
                 std::setw( 3) << std::right << gold  << " gold, " <<
                 std::setw( 3) << std::right << honor << " honor"  << std::endl;
  }
};

/* the C++11 way of sorting */

int main() { 
  std::vector<Hero> heroes;

  heroes.push_back(Hero("Achilles"   ,  1, 58));
  heroes.push_back(Hero("Bellerophon",513,327));
  heroes.push_back(Hero("Cadmus"     , 27,815));
  heroes.push_back(Hero("Cecrops"    ,234,  3));
  heroes.push_back(Hero("Pollux"     ,242,507));
  heroes.push_back(Hero("Hektor"     , 59, 22));
  heroes.push_back(Hero("Diomedes"   , 62,  7));
  heroes.push_back(Hero("Herakles"   ,270, 31));
  heroes.push_back(Hero("Odysseus"   , 84,910));
  heroes.push_back(Hero("Palamedes"  ,192, 73));
  heroes.push_back(Hero("Perseus"    ,128,636));
  heroes.push_back(Hero("Phoroneus"  , 35, 42));
  heroes.push_back(Hero("Prometheus" , 27, 99));
  heroes.push_back(Hero("Theseus"    ,  4,201));
  heroes.push_back(Hero("Triptolemos", 28, 90));

  std::cout << "\nThe Heroes:" << std::endl;
  for(std::vector<Hero>::iterator h = heroes.begin(); h != heroes.end(); ++h)
    h->print();

  // sometimes it may better to capture by reference rather than by value
  unsigned int num_rich = 0;
  unsigned int num_poor = 0;
  unsigned int gold_thresh = 100u;

  std::for_each (std::begin(heroes), std::end(heroes),
    [&num_rich, &num_poor, gold_thresh](const Hero& hero) {
      const unsigned int& gold = hero.gold;
      if      (gold >= gold_thresh) ++num_rich;
      else if (gold <  gold_thresh) ++num_poor;
    }
  );

  std::cout << "\nThere are " << num_rich << " rich heroes and " <<
                                 num_poor << " poor heroes."     << std::endl;
}
