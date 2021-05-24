//
// Created by isaac on 5/20/2021.
//

#include <iostream>
#include "Relation.h"

Relation::Relation(std::string name, Header header){
    this->name = name;
    this->header = header;
}

Relation::Relation(std::string name, Header header, std::set<Tuple> tuples){
    this->name = name;
    this->header = header;
    this->tuples = tuples;
}

Relation::~Relation(){
    tuples.clear();
}

void Relation::AddTuple(Tuple newTuple){
    tuples.insert(newTuple);
}

Relation Relation::Select(int index, std::string value){
    //TODO return a tuple with only the string value
    std::set<Tuple> matchedTuples;
    for(Tuple t : tuples){
        if(t.SelectTuple(index, value)){
            matchedTuples.insert(t);
        }
    }

    Relation newRelation = Relation(this->name, this->header, matchedTuples);
    return newRelation;
}

Relation Relation::Select(int index1, int index2){
    std::set<Tuple> matchedTuples;
    for(Tuple t : tuples){
        if(t.GetValue(index1) == t.GetValue(index2)){matchedTuples.insert(t);}
    }

    Relation newRelation = Relation(this->name, this->header, matchedTuples);
    return newRelation;
}

Relation Relation::Project(std::vector<int> columns){
    std::set<Tuple> matchedTuples;
    std::vector<std::string> tupleVect;
    for(Tuple t : tuples){
        for(int i=0; i < int(columns.size()); i++) {
            std::string value = t.GetValue(columns.at(i));
            tupleVect.push_back(value);
        }
        Tuple newTuple = Tuple(tupleVect);
        matchedTuples.insert(newTuple);
        tupleVect.clear();
    }

    Relation newRelation = Relation(this->name, this->header, matchedTuples);
    return newRelation;
}

Relation Relation::Rename(std::vector<std::string> newName){
    Relation newRelation = Relation(this->name, this->header, this->tuples);
    newRelation.header.ChangeHeader(newName);
    return newRelation;
}

void Relation::RelationToString(){

    for(Tuple t : tuples){

        for(int i=0; i < this->header.Size(); i++){

            if(i < this->header.Size()-1) {
                std::cout << this->header.GetAttribute(i) << "=" << t.TupleToString(i) << ", ";
            } else{
                std::cout << this->header.GetAttribute(i) << "=" << t.TupleToString(i) << std::endl;
            }
        }
    }
}

std::string Relation::GetName(){
    return this->name;
}

int Relation::GetTupleSize(){
    return int(tuples.size());
}




