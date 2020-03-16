#include <iostream>
#include <fstream>
#include <stdint.h>

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2) throw logic_error("Please provide an input filename as a parameter.");
  uint64_t i;
  long n = 0;
  string filename = argv[1];
  ifstream infile(filename, ios::in | ios::binary);
  ofstream outfile(filename + ".vb", ios::out | ios::binary);
  
  // // test
  // string test = "";
  // infile >> test;
  // cout << test << "\n";
  // // end test

  // while (infile >> i) {
  //   outfile << i;
  //   n++;
  // }

  streampos size;
  char * memblock;

  if (infile.is_open())
  {
    size = infile.tellg();
    memblock = new char[size];
    infile.seekg(0, ios::beg);
    infile.read(memblock, size);
    outfile.write(memblock, size);
    // infile.close();

    cout << "the entire file content is in memory";

    delete[] memblock;
  }
  else cout << "Unable to open file";

  infile.close();
  outfile.close();
  // cout << n;
}
