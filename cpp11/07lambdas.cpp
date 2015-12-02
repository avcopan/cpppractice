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

  std::vector<Hero> heroes_copy1 = heroes;

  /*
  // this fails to compile, since gold_thresh is not in the scope of the function
  // body:
  unsigned int gold_thresh = 100u;
  auto end = std::remove_if(std::begin(heroes_copy1), std::end(heroes_copy1),
    [](const Hero& hero) -> bool { return hero.gold < gold_thresh; });
  */

  // instead we can pass a "capture list" that effectively creates a temporary
  // function object with member variable gold_thresh
  unsigned int gold_thresh = 100u;
  auto end = std::remove_if(std::begin(heroes_copy1), std::end(heroes_copy1),
    [gold_thresh](const Hero& hero) -> bool { return hero.gold < gold_thresh; });
  // another way to think of it is that it puts gold_thresh into the function scope
  heroes_copy1.erase(end, std::end(heroes_copy1));

  std::cout << "\nRich Heroes:" << std::endl;
  for(std::vector<Hero>::iterator h = heroes_copy1.begin(); h != heroes_copy1.end(); ++h)
    h->print();

  std::vector<Hero> heroes_copy2 = heroes;

  unsigned int honor_thresh = 50u;
  unsigned int offset       = 10u;
  // you can also pass multiple variables into the capture list
  end = std::remove_if(std::begin(heroes_copy2), std::end(heroes_copy2),
    [honor_thresh, offset](const Hero& hero) { return hero.honor > (honor_thresh - offset); });
  heroes_copy2.erase(end, std::end(heroes_copy2));

  std::cout << "\nHeroes with shit for honor:" << std::endl;
  for(std::vector<Hero>::iterator h = heroes_copy2.begin(); h != heroes_copy2.end(); ++h)
    h->print();
}
