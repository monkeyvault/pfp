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
  // cout << n;
  // // end test

  streampos size;
  uint64_t read_int;

  if (infile.is_open())
  {
    // // check is output file empty
    // cout << "tellg size" << infile.tellg() << '\n';
    // if (infile.tellg() > 0) {
    //   outfile.write("",0);
    //   cout << "erased output file \n";
    // }
    // read first integer
    size = sizeof(uint64_t); // 8
    infile.seekg(0, ios::beg);
    infile.read(reinterpret_cast<char*>(&read_int), size);
    cout << "read int: " << read_int << '\n';

    // vbyte encryption
    // VByteEncodeInteger(i): (INPUT: one integer, OUTPUT: one or more bytes)
    // while true do
    //   b = i mod 128
    //   if i < 128 then
    //     OutputByte(b+128) and BREAK
    //   OutputByte(b)
    //   i ← i div 128
    // end
    uint64_t i = read_int;
    int loops = 0;
    while (loops < 10) {
    // while (true) { // change to this from loop safeguard before submit
      uint64_t b = i % 128;
      if (i < 128) {
        b += 128;
        cout << b << '\n';
        // write byte
        outfile.write(reinterpret_cast<char*>(&b), size);
        break;
      }
      cout << b << '\n';
      outfile.write(reinterpret_cast<char*>(&b), size);
      i /= 128;
      loops++;
    }
    if (loops > 8) cout << "loops maxed \n";

    // write integer
    // outfile.write(reinterpret_cast<char*>(&read_int), size);
    
    // // read another integer
    // infile.seekg(sizeof(uint64_t));
    // infile.read(reinterpret_cast<char*>(&read_int), size);
    // cout << read_int << '\n';

    cout << "done";
  }
  else cout << "Unable to open file";

  infile.close();
  outfile.close();

  cout << "test read from .vb-file" << '\n';
  uint64_t read_int_2;
  ifstream infile_2(filename + ".vb", ios::in | ios::binary);
  infile_2.seekg(8);
  infile_2.read(reinterpret_cast<char*>(&read_int_2), size);
  cout << read_int_2 << '\n';
  infile_2.close();
}
