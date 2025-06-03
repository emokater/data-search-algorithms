/// \file main.cpp
/// \brief Entry point: parses multiple dataset CSVs and runs search algorithms on each.

#include "../headers/io.h"

int main() {
    vector<Flower> tmp;
    string base = "/Users/ekaterinagridneva/Desktop/hse/mp/data-search-algorithms/datasets/dataset_";
    string sizes[10] = {"100", "200", "500", "1000", "2000", "5000", "10000", "20000", "50000", "100000"};
    
    for (int i = 0; i < 10; ++i) {
        string path = base + sizes[i] + ".csv";
        tmp = parserCSV(path);
        saveRes(tmp, tmp.size(), tmp[0]);
    }
}