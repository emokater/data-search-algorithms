/// \file  io.cpp
/// \brief Implements CSV parsing for Flower objects and saves search results from various algorithms.

#include "../headers/io.h"
#include "../headers/linear.h"
#include "../headers/binary_tree.h"
#include "../headers/rb_tree.h"
#include "../headers/hash.h"

#include <fstream>
#include <chrono>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <map>

vector<Flower> parserCSV(string filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open CSV file: " + filename);
    }

    vector<Flower> tmp_vector;
    string line;

    if (!getline(file, line)) {
        return tmp_vector;
    }

    string name, color, smell, regions_str;
    vector<string> regions;

    while(getline(file, line)) {
        regions.clear();
        int ind1 = -1, ind2 = -1, ind3 = -1; 

        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == ',') {
                if (ind1 == -1) {
                    ind1 = i;
                } else if (ind2 == -1) {
                    ind2 = i;
                } else {
                    ind3 = i;
                    break;
                }
            }
        }

        name = line.substr(0, ind1);
        color = line.substr(ind1 + 1, ind2 - ind1 - 1);
        smell = line.substr(ind2 + 1, ind3 - ind2 - 1);
        regions_str = line.substr(ind3 + 3, line.size() - 2 - ind3 - 3);

        ind1 = -1, ind2 = -1;

        for (int j = 0; j < regions_str.size(); ++j) {
            if (regions_str[j] == ',') {
                if (ind1 == -1) {
                    ind1 = j;
                } else {
                    ind2 = j;
                    break;
                } 
            }
        }

        if (ind1 == -1) {
            string region1 = regions_str;
            regions.push_back(region1);
        } else if (ind2 == -1) {
            string region1 = regions_str.substr(1, ind1 - 2);
            string region2 = regions_str.substr(ind1 + 3, regions_str.size() - ind1 - 4);
            regions.push_back(region1);
            regions.push_back(region2);
        } else {
            string region1 = regions_str.substr(1, ind1 - 2);
            string region2 = regions_str.substr(ind1 + 3, ind2 - ind1 - 4);
            string region3 = regions_str.substr(ind2 + 3, regions_str.size() - ind2 - 4);
            regions.push_back(region1);
            regions.push_back(region2);
            regions.push_back(region3);
        }

        Flower tmp(name, color, smell, regions);
        tmp_vector.push_back(tmp);
    }

    return tmp_vector;
}

void saveRes(vector<Flower>& source, long size, Flower target) {
    Flower* data = source.data();
    string size_str = to_string(size);
    int cntReg = 0;

    vector<int> res_a;

    string base = "/Users/ekaterinagridneva/Desktop/hse/mp/data-search-algorithms/out/" + size_str;
    string a, b, c, d, e;
    a = base + "_linear.txt";
    b = base + "_binary.txt";
    c = base + "_rb.txt";
    d = base + "_hash.txt";
    e = base + "_multimap.txt";



    ofstream fout("/Users/ekaterinagridneva/Desktop/hse/mp/data-search-algorithms/info_time.txt", ofstream::app);
    if (!fout.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }

    fout << "Datasets" << size << ":" << endl;

    ofstream fout1(a);
    if (!fout1.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + a);
    }

    auto start = chrono::high_resolution_clock::now();
    res_a = searchAll(data, size, target);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;

    fout << "1. Linear search time: " << duration.count() << endl;

    for (long i = 0; i < res_a.size(); ++i) {
        fout1 << res_a[i] << ": \t" << data[res_a[i]].GetName() << ";" << data[res_a[i]].GetColor() << ";" << data[res_a[i]].GetSmell() << ";";

        cntReg = data[res_a[i]].GetRegions().size();
        for (int j = 0; j < cntReg; ++j) {
            fout1 << data[res_a[i]].GetRegions()[j];
            if (j != cntReg-1) {
                fout1 << ",";
            }
        }

        fout1 << endl;
    }

    fout1.close();



    ofstream fout2(b);
    if (!fout2.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + b);
    }

    Tree<Flower> tree_b(data[0]);
    for (int i = 1; i < size; ++i) {
        tree_b.Insert(data[i]);
    }

    vector<Node<Flower>*> res_b;

    start = chrono::high_resolution_clock::now();
    res_b = tree_b.SearchAll(target);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    fout << "2. Binary search tree time: " << duration.count() << endl;

    for (long i = 0; i < res_b.size(); ++i) {
        fout2 << i+1 << " " << res_b[i] << ": " << res_b[i]->value_.GetName() << ";" << res_b[i]->value_.GetColor() << ";" << res_b[i]->value_.GetSmell() << ";";

        cntReg = res_b[i]->value_.GetRegions().size();
        for (int j = 0; j < cntReg; ++j) {
            fout2 << res_b[i]->value_.GetRegions()[j];
            if (j != cntReg-1) {
                fout2 << ",";
            }
        }

        fout2 << endl;
    }

    fout2.close();



    ofstream fout3(c);
    if (!fout3.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + c);
    } 

    RBTree<Flower> tree_c(data[0]);
    for (int i = 1; i < size; ++i) {
        tree_c.Insert(data[i]);
    }

    RBNode<Flower> *res_c;

    start = chrono::high_resolution_clock::now();
    res_c = tree_c.SearchAll(target);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    fout << "3. RB Tree search time: " << duration.count() << endl;

    fout3 << "Адрес узла, где хранятся все объекты с искомым ключом: " << res_c << endl;
    fout3 << "Сами объекты: " << endl;
    for (long i = 0; i < res_c->values_.size(); ++i) {
        fout3 << i + 1 << ": " << res_c->values_[i].GetName() << ";" << res_c->values_[i].GetColor() << ";" << res_c->values_[i].GetSmell() << ";";

        cntReg = res_c->values_[i].GetRegions().size();
        for (int j = 0; j < cntReg; ++j) {
            fout3 << res_c->values_[i].GetRegions()[j];
            if (j != cntReg-1) {
                fout3 << ",";
            }
        }

        fout3 << endl;
    }

    fout3.close();



    ofstream fout4(d);
    if (!fout4.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + d);
    }

    HashTable table(source);
    vector<Flower>* res_d;

    start = chrono::high_resolution_clock::now();
    res_d = table.Search(target.GetName());
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    fout << "4. HASH search time: " << duration.count() << endl << "Collisions: " << table.GetCollisions() << endl;

    for (int i = 0; i < SIZE; ++i) {
        Item *cur = table.GetItems()[i];

        fout4 << i << "   \t";
        if (!cur) {
            fout4 << "-" << endl;
        } else {
            while (cur) {
                fout4 << cur->key_ << "(" << cur->values_->size() << ")" << "   \t";
                cur = cur->next_;
            }
            fout4 << endl;
        }

        fout4 << endl;
    }
    
    fout4 << endl << "Key: " << target.GetName() << endl << "Unique count: " << table.GetCountUnq() << endl << "Collisions: " << table.GetCollisions();
    fout4.close();


    
    ofstream fout5(e);
    if (!fout5.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + e);
    }

    std::multimap<string, Flower> mmap;
    for (int i = 0; i < size; ++i) {
        mmap.insert({data[i].GetName(), data[i]});
    }

    start = chrono::high_resolution_clock::now();
    auto res = mmap.equal_range(target.GetName());
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    fout << "5. Multimap time: " << duration.count() << endl;


    for (auto it = res.first; it != res.second; ++it) {
        fout5 << it->first << " -> " << it->second.GetName() << ";" << it->second.GetColor() << ";" << it->second.GetSmell() << ";";
        cntReg = it->second.GetRegions().size();
        for (int j = 0; j < cntReg; ++j) {
            fout5 << it->second.GetRegions()[j];
            if (j != cntReg-1) {
                fout5 << ",";
            }
        }

        fout5 << endl;
    }
    
    fout5.close();


    
    fout << endl << endl;
    fout.close();
}

