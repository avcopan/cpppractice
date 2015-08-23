int main()
{
/* EXAMPLE 1 */
  int var;
  var = 4; // OKAY
  4 = var; // ERROR
// error: lvalue required as left operand of assignment
//   foo() = 2;
//         ^

  int a, b, c;
  a = b * c; // OKAY
  a * b = c; // ERROR
// error: lvalue required as left operand of assignment
//    a * b = c;
//          ^

}

// An lvalue (locator value) represents an object that occupies some identifiable location in memory (i.e. has an address).
// An rvalue is an expression that does not represent an object occupying some identifiable location in memory.

// var, a, b, and c are lvales.
// 4 and a * b are rvalues -- temporary objects which are evaluated during run-time but are not associated with a block in memory
// operator= cannot have an rvalue as its left operand, because they have no memory location to which a value can be assigned,
// but it can have an rvalue as its right operand and assign it to an lvalue

// NOTE: const int a; would be an lvalue that still couldn't serve as left operand to operator=; valid left operands of operator=
// must be *modifiable lvalues* -- objects with memory addresses and write access (i.e. objects that are not read-only)

