
int main()
{
  int arr[5] = {0, 1, 2, 3, 4}; // regular array declaration
  int* parr = new int [5];      // pointer declaration with 5 int-sized blocks of dynamically allocated memory
  /* difference: the size of a regular array needs to be a constant expression explicitly written into the code of the program,
                 whereas the dynamic memory allocation allows memory to be assigned during runtime with any variable value as size */
  /* also, the regular array declaration allocates memory on the stack -- fast memory that is autmatically freed when it goes out of
     scope -- whereas dynamic allocation uses memory on the heap -- slower memory that must be explicitly freed by the code */
  delete[] parr; // free the memory allocated for parr
}
