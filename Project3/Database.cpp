//
// Created by isaac on 5/20/2021.
//

#include "Database.h"

Database::Database(){
    counter = 0;
}

Database::~Database(){}

void Database::AddRelation(Relation relation){

    if(database.find(relation.GetName()) == database.end()){
        database.insert({relation.GetName(), counter});
        relationVector.push_back(relation);
        counter++;
    }

}

void Database::AddFact(std::string name, std::vector<std::string> values){
    for(int i=0; i < int(relationVector.size()); i++){
        if(name == relationVector.at(i).GetName()){
            relationVector.at(i).AddTuple(values);
        }
    }
}

int Database::GetRelationIndex(std::string name){
    std::map<std::string, int>::iterator it;
    for (it = database.begin(); it != database.end(); it++)
    {
        if(it->first == name){
            return(it->second);
        }
    }
    return(-1);
}

Relation Database::GetRelation(int pos){
    return(relationVector.at(pos));
}




