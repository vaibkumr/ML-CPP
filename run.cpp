// Compile using -std=c++17
#include "CSVReader.h"
#include "preprocess.h"
#include <string>
#include <any>


int main(){
    std::string fname = "iris.csv";
    csv::CSV csvobj(fname);
    csvobj.CSVReader();
    csvobj.PrettyPrint();
    pp::LabelEncoder le;
    std::vector<std::string> catcols{ "species" };
    csvobj.data = le.encode(csvobj.data, catcols);
    csvobj.PrettyPrint();
}