#include <fstream>
#include <iostream>
#include <stdint.h>

// #define ENABLE_DEBUG // comment out to disable debugging

using namespace std;

void output_byte(uint8_t &b, ofstream &outf) {
    outf.write(reinterpret_cast<char *>(&b), sizeof(b));
#ifdef ENABLE_DEBUG
    cout << (int)b << '\n';
#endif
}

// vbyte encoding
void encode_integer(uint64_t i, ofstream &outf) {
    while (true) {
        uint8_t b = i % 128;
        if (i < 128) {
            b += 128;
            output_byte(b, outf);
            break;
        }
        output_byte(b, outf);
        i /= 128;
    }
}

void encode_file(ifstream &inf, ofstream &outf) {
    uint64_t i;
    long n{};
    inf.seekg(0, ios::beg);

    while (inf) {
        inf.read(reinterpret_cast<char *>(&i), sizeof(i));
#ifdef ENABLE_DEBUG
        if (n > 9) break;
        n++;
        cout << "read int: " << i << '\n';
#endif
        encode_integer(i, outf);
    }

#ifdef ENABLE_DEBUG
    cout << "encoded " << n << " integers \n"; // F0: 1048577 integers
#endif
}

int main(int argc, char **argv) {
    // if (argc < 2) throw logic_error("Please provide a filename"); // might not compile on your machine
    string filename = argv[1];
    ifstream inf(filename, ios::in | ios::binary);
    ofstream outf(filename + ".vb", ios::out | ios::binary);

    if (inf.is_open() && outf.is_open()) {
        encode_file(inf, outf);
    } else {
        cout << "Unable to open file \n";
    }
    
    inf.close();
    outf.close();

#ifdef ENABLE_DEBUG
    cout << "test read from .vb-file: \n";
    uint8_t i;
    ifstream inf_2(filename + ".vb", ios::in | ios::binary);
    inf_2.seekg(0, ios::beg);
    inf_2.read(reinterpret_cast<char *>(&i), sizeof(i));
    cout << (int)i << '\n';
    inf_2.close();
#endif
}
