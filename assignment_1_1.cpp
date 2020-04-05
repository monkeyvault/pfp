#include <stdint.h>
#include <fstream>
#include <iostream>

using namespace std;

// vbyte encryption
void encrypt_integer(uint64_t i, ofstream &outf) {
    while (true) {
        uint8_t b = i % 128;
        if (i < 128) {
            b += 128;
            cout << (int)b << '\n';
            // write byte
            outf.write(reinterpret_cast<char *>(&b), sizeof(b));
            break;
        }
        cout << (int)b << '\n';
        outf.write(reinterpret_cast<char *>(&b), sizeof(b));
        i /= 128;
    }
}

void encrypt_file(ifstream &inf, ofstream &outf) {
    uint64_t i;
    long n{};
    // read first integer
    inf.seekg(0, ios::beg);
    // while (inf) {
    // DEBUG: swap "i < 100" to "inf" before submitting or testing on turso
    while (n < 100) {
        // inf.seekg(i * size);
        inf.read(reinterpret_cast<char *>(&i), sizeof(i));
        cout << "read int: " << i << '\n';
        encrypt_integer(i, outf);
        n++;
    }
    cout << "read " << n << " integers \n"; // F0: "read 1048577 integers"

    // // read another integer
    // inf.seekg(size);
    // inf.read(reinterpret_cast<char*>(&i), sizeof(i));
    // cout << i << '\n';

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
    uint8_t i;
    ifstream inf_2(filename + ".vb", ios::in | ios::binary);
    inf_2.seekg(0, ios::beg);
    inf_2.read(reinterpret_cast<char *>(&i), sizeof(i));
    cout << (int)i << '\n';
    inf_2.close();
}
