#include <iostream>
#include <fstream>
#include <stdint.h>

using namespace std;

void encrypt_file(ifstream &infile, ofstream &outfile)
{
    streampos size;
    uint64_t read_int;

    // read first integer
    size = sizeof(uint64_t); // 8
    infile.seekg(0, ios::beg);
    infile.read(reinterpret_cast<char *>(&read_int), size);
    cout << "read int: " << read_int << '\n';

    // vbyte encryption
    uint64_t i = read_int;
    // int loops = 0;
    // while (loops < 10) {
    while (true)
    {
        uint64_t b = i % 128;
        if (i < 128)
        {
            b += 128;
            cout << b << '\n';
            // write byte
            outfile.write(reinterpret_cast<char *>(&b), size);
            break;
        }
        cout << b << '\n';
        outfile.write(reinterpret_cast<char *>(&b), size);
        i /= 128;
        // loops++;
    }
    // if (loops > 8) cout << "loops maxed \n";

    // // read another integer
    // infile.seekg(sizeof(uint64_t));
    // infile.read(reinterpret_cast<char*>(&read_int), size);
    // cout << read_int << '\n';

    cout << "done \n";
}

int main(int argc, char **argv)
{
    if (argc < 2)
        throw logic_error("Please provide an input filename as a parameter.");
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

    if (infile.is_open())
    {
        encrypt_file(infile, outfile);
    }
    else
        cout << "Unable to open file \n";
    infile.close();
    outfile.close();

    cout << "test read from .vb-file \n";
    uint64_t read_int_2;
    ifstream infile_2(filename + ".vb", ios::in | ios::binary);
    infile_2.seekg(8);
    infile_2.read(reinterpret_cast<char *>(&read_int_2), 8);
    cout << read_int_2 << '\n';
    infile_2.close();
}
