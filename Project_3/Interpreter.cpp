
#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram datalog, Database database){
    this->datalog = datalog;
    this->database = database;
}

Interpreter::~Interpreter() {
    VectorSeenBefore.clear();
    VectorToProject.clear();
}

Relation Interpreter::EvaluatePredicate(Predicate p){
    std::string name = p.GetName();
    Header header = Header(p.GetParameters());
    Relation relation = Relation(name, header);
    return(relation);
}

bool Interpreter::CheckDuplicate(Parameter par){
    for(int i=0; i < int(VectorSeenBefore.size()); i++){
        if(VectorSeenBefore.at(i) == par.GetParameter()){
            return true;
        }
    }
    return false;
}

int Interpreter::GetFirstInstance(Parameter par){

    for(int i=0; i < int(VectorSeenBefore.size()); i++){
        if(VectorSeenBefore.at(i) == par.GetParameter()){
            return(i);
        }
    }
    return(-1);
}

void Interpreter::Interpret(){

    for(int i=0; i < int(datalog.SchemesPredicates.size()); i++){
        Relation relation = EvaluatePredicate(datalog.SchemesPredicates.at(i));
        database.AddRelation(relation);
    }

    for(int i=0; i < int(datalog.FactsPredicates.size()); i++){
        std::string name = datalog.FactsPredicates.at(i).GetName();
        std::vector<std::string> values = datalog.FactsPredicates.at(i).GetParameters();
        database.AddFact(name, values);
    }

    for(int i=0; i < int(datalog.QueriesPredicates.size()); i++){

        VectorSeenBefore.clear();
        VectorToProject.clear();

        std::string name = datalog.QueriesPredicates.at(i).GetName();
        int pos = database.GetRelationIndex(name);
        Relation relation = database.GetRelation(pos);
        std::vector<std::string> parameters = datalog.QueriesPredicates.at(i).GetParameters();


        for(int j=0; j < int(parameters.size()); j++) {
            //if is a string
            if (parameters.at(j).at(0) == '\'') {
                relation = relation.Select(j, parameters.at(j));
            } else if (CheckDuplicate(parameters.at(j))) {
                relation = relation.Select(GetFirstInstance(parameters.at(j)),j);
            } else if (!CheckDuplicate(parameters.at(j))) {
                VectorSeenBefore.push_back(parameters.at(j));
                VectorToProject.push_back(j);
            }
        }

        relation = relation.Project(VectorToProject);
        relation = relation.Rename(VectorSeenBefore);

        bool allStrings = QueryCheck(datalog.QueriesPredicates.at(i).GetParameters());

        if(relation.GetTupleSize() > 0){ //&& !allStrings){
            std::cout << datalog.QueriesPredicates.at(i).QueryToString() << " Yes(" << relation.GetTupleSize() << ")" << std::endl;
            relation.RelationToString();
        } else if(relation.GetTupleSize() > 0 && allStrings){
            std::cout << datalog.QueriesPredicates.at(i).QueryToString() << " Yes(" << relation.GetTupleSize() << ")" << std::endl;
        } else{
            std::cout << datalog.QueriesPredicates.at(i).QueryToString() << " No" << std::endl;
            relation.RelationToString();
        }
    }
}


bool Interpreter::QueryCheck(std::vector<std::string> parameters){
    int sum = 0;
    for(int i=0; i < int(parameters.size()); i++){
        if(parameters.at(i)[0] == '\''){
            sum++;
        }
    }
    if(sum == int(parameters.size())){
        return true;
    } else{
        return false;
    }
}