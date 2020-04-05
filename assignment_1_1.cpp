#include <stdint.h>
#include <fstream>
#include <iostream>

#define size 8

using namespace std;

// vbyte encryption
void encrypt_integer(uint64_t &read_int, ofstream &outf) {
    uint64_t i = read_int;
    // int loops = 0;
    // while (loops < 10) {
    while (true) {
        uint64_t b = i % 128;
        if (i < 128) {
            b += 128;
            cout << b << '\n';
            // write byte
            outf.write(reinterpret_cast<char *>(&b), size);
            break;
        }
        cout << b << '\n';
        outf.write(reinterpret_cast<char *>(&b), size);
        i /= 128;
        // loops++;
    }
    // if (loops > 8) cout << "loops maxed \n";
}

void encrypt_file(ifstream &inf, ofstream &outf) {
    uint64_t read_int;
    long i{};
    // read first integer
    inf.seekg(0, ios::beg);
    // while (inf) {
    // DEBUG: swap "i < 100" to "inf" before submitting or testing on turso
    while (i < 100) {
        // inf.seekg(i * size);
        inf.read(reinterpret_cast<char *>(&read_int), size);
        cout << "read int: " << read_int << '\n';
        encrypt_integer(read_int, outf);
        i++;
    }
    cout << "read " << i << " integers";

    // // read another integer
    // inf.seekg(size);
    // inf.read(reinterpret_cast<char*>(&read_int), size);
    // cout << read_int << '\n';

    cout << "done \n";
}

int main(int argc, char **argv) {
    if (argc < 2) throw logic_error("Please provide a filename");
    string filename = argv[1];
    ifstream inf(filename, ios::in | ios::binary);
    ofstream outf(filename + ".vb", ios::out | ios::binary);

    // // test
    // uint64_t i;
    // long n = 0;
    // string test = "";
    // inf >> test;
    // cout << test << "\n";
    //
    // while (inf >> i) {
    //   outf << i;
    //   n++;
    // }
    // cout << n;
    // // end test

    if (inf.is_open() && outf.is_open()) {
        encrypt_file(inf, outf);
    } else {
        cout << "Unable to open file \n";
    }
    inf.close();
    outf.close();

    cout << "test read from .vb-file \n";
    uint64_t read_int_2;
    ifstream inf_2(filename + ".vb", ios::in | ios::binary);
    inf_2.seekg(size);
    inf_2.read(reinterpret_cast<char *>(&read_int_2), size);
    cout << read_int_2 << '\n';
    inf_2.close();
}
