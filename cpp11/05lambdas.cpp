#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

struct Hero {
  /* member variables */
  std::string name;
  unsigned int gold;
  unsigned int honor;
  /* constructor */
  Hero(const std::string& n, int g, int h) : name(n), gold(g), honor(h) {}
  /* member functions */
  void print() {
    std::cout << std::setw(12) << std::left  << name  << ": "     <<
                 std::setw( 3) << std::right << gold  << " gold, " <<
                 std::setw( 3) << std::right << honor << " honor"  << std::endl;
  }
};

/* the C++03 way of sorting */

bool has_more_gold(const Hero& h1, const Hero& h2) {
  return h1.gold < h2.gold;
}

bool has_more_honor(const Hero& h1, const Hero& h2) {
  return h1.honor < h2.honor;
}

/* C++03 function object for removing */
struct HasLessGoldThan {
  /* member variables */
  unsigned int threshold;
  /* constructor */
  HasLessGoldThan(unsigned thresh) : threshold(thresh) {}
  /* member functions */
  bool operator()(const Hero& hero) {
    return hero.gold < threshold;
  }
};

/* C++03 function object for removing */
struct HasMoreHonorThan {
  /* member variables */
  unsigned int threshold;
  /* constructor */
  HasMoreHonorThan(unsigned thresh) : threshold(thresh) {}
  /* member functions */
  bool operator()(const Hero& hero) {
    return hero.honor > threshold;
  }
};
 
int main() { 
  Hero hercules("Hercules", 0, 100);
  hercules.print();

  std::vector<Hero> heroes;

  std::cout << "\nThe Heroes:" << std::endl;
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

  std::vector<Hero> heroes_copy1 = heroes;
  std::vector<Hero> heroes_copy2 = heroes;

  for(std::vector<Hero>::iterator h = heroes.begin(); h != heroes.end(); ++h)
    h->print();

  std::sort(heroes.begin(), heroes.end(), has_more_gold);

  std::cout << "\nThe Heroes (sorted by wealth):" << std::endl;
  for(std::vector<Hero>::iterator h = heroes.begin(); h != heroes.end(); ++h)
    h->print();

  std::sort(heroes.begin(), heroes.end(), has_more_honor);

  std::cout << "\nThe Heroes (sorted by honor):" << std::endl;
  for(std::vector<Hero>::iterator h = heroes.begin(); h != heroes.end(); ++h)
    h->print();

  std::vector<Hero>::iterator end = std::remove_if(heroes_copy1.begin(), heroes_copy1.end(), HasLessGoldThan(100));
  heroes_copy1.erase(end, heroes_copy1.end()); // this will delete the remaining elements

  std::cout << "\nRich Heroes:" << std::endl;
  for(std::vector<Hero>::iterator h = heroes_copy1.begin(); h != heroes_copy1.end(); ++h)
    h->print();

  end = std::remove_if(heroes_copy2.begin(), heroes_copy2.end(), HasMoreHonorThan(50));
  heroes_copy2.erase(end, heroes_copy2.end()); // this will delete the remaining elements

  std::cout << "\nHeroes with shit for honor:" << std::endl;
  for(std::vector<Hero>::iterator h = heroes_copy2.begin(); h != heroes_copy2.end(); ++h)
    h->print();
}

