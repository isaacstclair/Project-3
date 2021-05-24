//
// Created by isaac on 5/20/2021.
//

#include <string>
#include <vector>
#include <set>
#include "Tuple.h"
#include "Header.h"

#ifndef RELATION_H
#define RELATION_H


class Relation {

private:
    std::string name;
    Header header;
    std::set<Tuple> tuples;

public:
    Relation(std::string name, Header header);
    Relation(std::string name, Header header, std::set<Tuple> tuples);
    ~Relation();
    void AddTuple(Tuple newTuple);
    Relation Select(int index, std::string value);
    Relation Select(int index1, int index2);
    Relation Project(std::vector<int> columns);
    Relation Rename(std::vector<std::string> newName);
    std::string GetName();
    void RelationToString();
    int GetTupleSize();

};


#endif //RELATION_H
