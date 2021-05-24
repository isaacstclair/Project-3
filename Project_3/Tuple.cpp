//
// Created by isaac on 5/20/2021.
//

#include "Tuple.h"

Tuple::Tuple(std::vector<std::string> values){
    this->values = values;
}


Tuple::~Tuple(){
    values.clear();
}

bool Tuple::operator< (const Tuple & other) const {
    return this->values < other.values;
}

std::string Tuple::TupleToString(int pos){

    std::string tupleString = values.at(pos);
    return tupleString;

}

std::string Tuple::GetValue(int pos){

    return this->values.at(pos);

}

bool Tuple::SelectTuple(int pos, std::string match){

    if(this->values.at(pos) == match){
        return true;
    } else {
        return false;
    }

}



