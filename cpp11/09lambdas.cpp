#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> // std::for_each, std::begin, std::end

struct Hero {
  /* member variables */
  std::string name;
  int         gold;
  int         health;
  /* constructor */
  Hero(const std::string& n, int g, int h) : name(n), gold(g), health(h) {}
  /* member functions */
  void apply_damage (unsigned int strength) {
    float loss_factor = float(100u - strength % 101u) / 100.f;
    health *= loss_factor;
  }

  void print() {
    std::cout << std::setw(12) << std::left  << name   << ": "     <<
                 std::setw( 3) << std::right << gold   << " gold, " <<
                 std::setw( 3) << std::right << health << " health"  << std::endl;
  }
};


/* in order to allow a lambda access to member variables,
   add *this* to the capture list -- this effectively extends
   the scope of the class into the lambda, so member variables
   can be accessed without the this-> prefix. */
struct Beast {
  /* member variables */
  std::string  name;
  unsigned int strength;
  /* constructor */
  Beast(std::string n, unsigned int s) : name(n), strength(s) {}
  /* member functions */
  void attack(std::vector<Hero>& heroes) {
    std::for_each (std::begin(heroes), std::end(heroes),
      [this](Hero& hero) {
        hero.apply_damage(strength);
      }
    );
  }
};

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

  Beast mimon    ("Mimon"    ,  20);
  Beast charybdis("Charybdis", 100);

  mimon.attack(heroes);

  std::cout << "\nThe Heroes (after attack by Mimon):" << std::endl;
  for(std::vector<Hero>::iterator h = heroes.begin(); h != heroes.end(); ++h)
    h->print();

  mimon.attack(heroes);

  std::cout << "\nThe Heroes (after second attack by Mimon):" << std::endl;
  for(std::vector<Hero>::iterator h = heroes.begin(); h != heroes.end(); ++h)
    h->print();

  charybdis.attack(heroes);

  std::cout << "\nThe Heroes (after being swallowed by Charybdis):" << std::endl;
  for(std::vector<Hero>::iterator h = heroes.begin(); h != heroes.end(); ++h)
    h->print();
}
