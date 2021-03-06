//
// Created by oquechy on 12.04.17.
//
#include <cstring>
#include "huffman.h"

using namespace std;

// exceptions

const char* file_exception::what() const throw() {
    return "file can't be opened\n";
}

const char* format_exception::what() const throw() {
    return "file doesn't match the format\n";
}

// huff_tree::node

huff_tree::node::node(int freq)
        : freq(freq)
{}

huff_tree::node::~node() {}

huff_tree::path_node::path_node(node *zero, node *one)
        : node(zero->freq + one->freq), to{zero, one}
{}

huff_tree::path_node::~path_node() {
    delete to[0];
    delete to[1];
}

huff_tree::symbol_node::symbol_node(int freq, char alpha)
        : node(freq), alpha(alpha)
{}

bool huff_tree::cmp_nodes::operator()(const node *n1, const node *n2) {
    return (n1->freq > n2->freq);
}

// huff_tree

huff_tree::huff_tree()
        : root(0)
{}

void huff_tree::build(const std::vector<int> &met){
    priority_queue<node*, std::vector<node *>, cmp_nodes> freqs;

    for (int i = 0; i < MAXS; ++i)
        if (met[i])
            freqs.push(new symbol_node(met[i], static_cast<char>(i)));

    if (!freqs.size())
        return;

    if (freqs.size() == 1) {
        root = new path_node(freqs.top(), new symbol_node(0, 0));
        huff_code[static_cast<symbol_node *>(freqs.top())->alpha].push_back(0);
        return;
    }

    while (freqs.size() > 1) {
        node* zero = freqs.top();
        freqs.pop();
        node* one = freqs.top();
        freqs.pop();
        freqs.push(new path_node(zero, one));
    }

    root = freqs.top();
    gen_codes();
}

void huff_tree::walk(const node* cur, sequence& cur_code) {
    if (dynamic_cast<const symbol_node *>(cur))
        huff_code[static_cast<const symbol_node *>(cur)->alpha] = sequence(cur_code);

    else if (dynamic_cast<const path_node *>(cur)) {
        cur_code.push_back(0);
        walk(static_cast<const path_node *>(cur)->to[0], cur_code);
        cur_code.pop_back();
        cur_code.push_back(1);
        walk(static_cast<const path_node *>(cur)->to[1], cur_code);
        cur_code.pop_back();
    }
}

void huff_tree::gen_codes() {
    sequence cur_code;
    walk(root, cur_code);
}

huff_tree::sequence& huff_tree::operator[](char c) {
    return huff_code[c];
}

void huff_tree::start_decode(char &res) {
    res_alpha = &res;
    cur_code.clear();
    cur_node = root;
}

bool huff_tree::do_step(bool b) {
    cur_node = static_cast<path_node *>(cur_node)->to[b];
    bool res = 0;
    if (dynamic_cast<symbol_node *>(cur_node)) {
        *res_alpha = static_cast<symbol_node *>(cur_node)->alpha;
        cur_node = root;
        res = 1;
    }
    return res;
}

huff_tree::~huff_tree() {
    delete root;
}

// huff_archiver

huff_archiver::huff_archiver()
        : freqs(MAXS, 0)
{}

void huff_archiver::load(ifstream &f) {
    if (!f)
        throw file_exception();

    f.seekg(0, ios::end);
    input_size = static_cast<int>(f.tellg());
    f.seekg(0, ios::beg);
}

void huff_archiver::get_freqs(ifstream &f) {
    for (int i = 0; i < input_size; ++i) {
        unsigned char c;
        f.read(reinterpret_cast<char *>(&c), sizeof(c));
        if (!freqs[c])
            symbols.push_back(c);
        ++freqs[c];
    }
}

void huff_archiver::stats() {
    cout << input_size << '\n' << tree_size << '\n' << result_size << '\n';
}

void huff_archiver::compress(string infile, string outfile) {
    ifstream in(infile, ios::binary);
    load(in);
    get_freqs(in);

    tree.build(freqs);

    ofstream out(outfile, ios::binary);
    int uniq = static_cast<int>(symbols.size());

    if (!uniq) {
        tree_size = result_size = 0;
        stats();
        return;
    }

    out.write(reinterpret_cast<char *>(&uniq), sizeof(uniq));
    tree_size = sizeof(uniq);
    for (auto i : symbols)
        if (tree[i].size()) {
            out.write(reinterpret_cast<char *>(&i), sizeof(i));
            out.write(reinterpret_cast<char *>(&freqs[i]), sizeof(freqs[i]));
            tree_size += sizeof(i) + sizeof(freqs[i]);
        }
    out.close();

    result_size = 0;
    for (int i = 0; i < MAXS; ++i)
        result_size += freqs[i] * tree[i].size();

    result_size = (result_size + 7) / 8;
    in.seekg(ios::beg);
    obitstream bout(outfile, ios::app);
    if (!bout)
        throw file_exception();

    for (int i = 0; i < input_size; ++i) {
        char c;
        in.read(&c, sizeof(c));
        bout << tree[c];
    }

    stats();
}

void huff_archiver::decode(ibitstream &bin, std::ofstream &out, int all) {
    char alpha;
    tree.start_decode(alpha);
    result_size = 0;
    for (int i = 0; i < all; ++i) {
        bool b;
        do {
            bin >> b;
            if (!bin)
                throw format_exception();
        }
        while (!tree.do_step(b));
        out.write(&alpha, sizeof(alpha));
        result_size += sizeof(alpha);
    }
}

void huff_archiver::decompress(string infile, string outfile) {
    ifstream in(infile, ios::binary);
    load(in);

    int uniq, all = 0;

    ofstream out(outfile, ios::binary);
    if (!out)
        throw file_exception();

    if (!input_size){
        tree_size = result_size = 0;
        stats();
        return;
    }

    if (!in.read(reinterpret_cast<char *>(&uniq), sizeof(uniq)))
       throw format_exception();

    tree_size = sizeof(uniq);
    for (int i = 0; i < uniq; ++i) {
        unsigned char c;
        if (!in.read(reinterpret_cast<char *>(&c), sizeof(c)))
            throw format_exception();
        if (!in.read(reinterpret_cast<char *>(&freqs[c]), sizeof(freqs[c])))
            throw format_exception();
        all += freqs[c];
        tree_size += sizeof(c) + sizeof(freqs[c]);
    }

    streamoff bin_start = in.tellg();
    in.close();
    tree.build(freqs);

    ibitstream bin(infile);
    if (!bin)
        throw file_exception();
    bin.seekg(bin_start);

    decode(bin, out, all);

    stats();
}

