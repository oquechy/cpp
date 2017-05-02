#include <string>
#include <cstring>
#include <fstream>
#include "huffman.h"

using namespace std;

void usage() {
    cout << "usage:\n"
            "\t\t./huffman -c -f myfile.txt -o result.bin\n"
            "\t\t./huffman -u -f result.bin -o myfile_new.txt\n";
}

int main(int argc, char **argv) {
    if (argc != 6) {
        usage();
        return 1;
    }
    string infile, outfile;
    char mode;
    bool md = 0, inf = 0, ouf = 0;
    for (int i = 1; i < 6; ++i) {
        if (!md && !strcmp("-c", argv[i])) {
            mode = 'c';
            md = 1;
        } else if (!md && !strcmp("-u", argv[i])) {
            mode = 'u';
            md = 1;
        } else if (!inf && (!strcmp("-f", argv[i]) || !strcmp("--file", argv[i]))) {
            infile = argv[++i];
            inf = 1;
        } else if (!ouf && (!strcmp("-o", argv[i]) || !strcmp("--output", argv[i]))) {
            outfile = argv[++i];
            ouf = 1;
        } else {
            usage();
            return 1;
        }
    }

    huff_archiver arc;
    try {
        if (mode == 'c')
            arc.compress(infile, outfile);
        else
            arc.decompress(infile, outfile);
    } catch (exception &e) {
            cout << e.what() << '\n';
    }
    return 0;
}
