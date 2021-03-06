//
// Created by oquechy on 12.04.17.
//

#ifndef HW03_HUFFMAN_H
#define HW03_HUFFMAN_H

#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <deque>
#include <fstream>
#include <sstream>
#include <exception>

#include "bitstream.h"

class file_exception: public std::exception {
public:
    virtual const char* what() const throw();
};

class format_exception: public std::exception {
public:
    virtual const char* what() const throw();
};

class huff_tree{
public:
    typedef std::deque<bool> sequence;

private:

    typedef std::map<char, sequence> code_map;

    class node {
    public:
        const int freq;
        node(int freq);
        virtual ~node();
    };

    class path_node : public node {
    public:
        node *to[2];
        path_node(node *zero, node *one);
        virtual ~path_node() override;
    };

    class symbol_node : public node {
    public:
        const char alpha;
        symbol_node(int freq, char alpha);
    };

    struct cmp_nodes {
        bool operator()(const node* n1, const node* n2);
    };

    node *root, *cur_node;
    code_map huff_code;
    sequence cur_code;
    char *res_alpha;
    void walk(const node* cur, sequence& cur_code);
    void gen_codes();

public:
    huff_tree();
    void build(const std::vector<int> &met);
    void start_decode(char &res);
    bool do_step(bool b);
    sequence& operator[](char c);
    ~huff_tree();
};

class huff_archiver{
private:

    void load(std::ifstream &f);
    void get_freqs(std::ifstream &f);
    void decode(ibitstream &bin, std::ofstream &out, int all);
    static const int MAXS = 1 << 8;

    huff_tree tree;
    int input_size, result_size, tree_size;
    std::vector<int> freqs;
    std::vector<unsigned char> symbols;
    void stats();

public:
    huff_archiver();
    void compress(std::string infile, std::string outfile);
    void decompress(std::string infile, std::string outfile);
};

#endif //HW03_HUFFMAN_H
