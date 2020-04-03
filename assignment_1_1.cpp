#include <iostream>
#include <fstream>
#include <stdint.h>

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2) throw logic_error("Please provide an input filename as a parameter.");
  // uint64_t i;
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
  uint64_t read_int;

  if (infile.is_open())
  {
    // size = infile.tellg();
    memblock = new char[64];
    infile.seekg(0, ios::beg);
    // infile.read(memblock, 64);

    size = sizeof(uint64_t); // 8
    infile.read(reinterpret_cast<char*>(&read_int), size);
    cout << read_int << '\n';
    outfile.write(reinterpret_cast<char*>(&read_int), size);

    // ifstream infile(filename, ios::in | ios::binary);

    // infile.seekg(sizeof(uint64_t));
    // infile.read(reinterpret_cast<char*>(&read_int), size);
    // cout << read_int << '\n';

    // outfile.write(memblock, 64);
    infile.close();

    // cout << "the entire file content is in memory";
    cout << "done";

    delete[] memblock;
  }
  else cout << "Unable to open file";

  infile.close();
  outfile.close();
  // cout << n;
}
