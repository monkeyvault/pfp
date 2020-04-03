#include <iostream>
#include <fstream>
#include <stdint.h>

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2) throw logic_error("Please provide an input filename as a parameter.");
  string filename = argv[1];
  ifstream infile(filename, ios::in | ios::binary);
  ofstream outfile(filename + ".vb", ios::out | ios::binary);

  // // test
  // uint64_t i;
  // long n = 0;
  // string test = "";
  // infile >> test;
  // cout << test << "\n";
  //
  // while (infile >> i) {
  //   outfile << i;
  //   n++;
  // }
  // // end test

  streampos size;
  char* memblock;
  uint64_t read_int;

  if (infile.is_open())
  {
    // size = infile.tellg();
    // memblock = new char[64];
    infile.seekg(0, ios::beg);
    // infile.read(memblock, 64);

    size = sizeof(uint64_t); // 8
    infile.read(reinterpret_cast<char*>(&read_int), size);
    cout << read_int << '\n';
    cout << "writing" << '\n';
    outfile.write(reinterpret_cast<char*>(&read_int), size);

    cout << "test read from .vb-file" << '\n';
    ifstream infile_2(filename + ".vb", ios::in | ios::binary);
    infile_2.seekg(0, ios::beg);
    infile_2.read(reinterpret_cast<char*>(&read_int), size);
    cout << read_int << '\n';
    infile_2.close();

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
