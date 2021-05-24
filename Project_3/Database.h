//
// Created by isaac on 5/20/2021.
//

#include <set>
#include <map>
#include <string>
#include <vector>
#include "Relation.h"

#ifndef DATABASE_H
#define DATABASE_H


class Database {

private:
    std::map<std::string, int> database;
    std::vector<Relation> relationVector;
    int counter;
public:
    Database();
    ~Database();
    void AddRelation(Relation relation);
    void AddFact(std::string name, std::vector<std::string> values);
    int GetRelationIndex(std::string name);
    Relation GetRelation(int pos);



};


#endif //DATABASE_H
