// there are two types of *'constexpr' values*:
//  - variables
//  - 'static' data members of 'class' or 'struct'
// these can be objects of a custom class or struct, but this class
// or struct must satisfy the definition of a *literal type*
// (http://www.cplusplus.com/reference/type_traits/is_literal_type/)
// *literal type* includes floating point types, character literals,
// pointer literals, and literal objects

// *'constexpr' values* can be used anywhere a literal may be used
//  - non-type template parameters
//  - array dimensions
//  - enum initialization
//  - standard runtime code
// they are implicitly 'const' -- casting away 'const' is bad

void free_func() {
  constexpr float  pi     = 3.14159265; // static 
  static_assert((3.1 < pi) && (pi < 3.2), "Yipe!");
//static_assert((3.1 > pi) && (pi > 3.2), "Yipe!");
}

/* constexpr class variables must be 'static'! */
struct Dumbo {
  // static data members of literal type
  static constexpr char who[] = "Gabriel Dos Reis";
  static_assert(who[0] == 'G', "Yipe!");
//static_assert(who[0] != 'G', "Yipe!");

  static constexpr const char* a = &who[1];
  static_assert(*a == 'a', "Yipe!");
//static_assert(*a != 'a', "Yipe!");
};

int main() {
  constexpr int    const3 = 3  ;               // constexpr object dfn
  constexpr double half   = 0.5;               // constexpr object dfn
  static_assert(half < const3, "Yipe!");
//static_assert(half > const3, "Yipe!");

  constexpr char title_fixative[] = "grout"; // constexpr object dfn
  static_assert(title_fixative[5] == '\0', "Yipe!");
//static_assert(title_fixative[5] != '\0', "Yipe!");
}
