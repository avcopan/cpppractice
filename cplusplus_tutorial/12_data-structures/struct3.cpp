#include <stdio.h>
#include <string>

struct movie {
  std::string title;
  int year;
};

struct person {
  std::string name;
  movie       favorite_movie;
};


int main()
{
  person joe;
  joe.name = "Joe";
  joe.favorite_movie.title = "Invasion of the body snatchers";
  joe.favorite_movie.year  = 1978;

  printf("%s's favorite movie is %s (%d)\n", joe.name.c_str()
                                           , joe.favorite_movie.title.c_str()
                                           , joe.favorite_movie.year);
}
