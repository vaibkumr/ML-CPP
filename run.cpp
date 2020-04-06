// Compile using -std=c++17
#include "CSVReader.h"
#include "preprocess.h"
#include "featureengine.h"
#include <string>
#include <any>


int main(){
    std::string fname = "iris.csv";
    csv::CSV csvobj(fname);
    csvobj.CSVReader();
    // csvobj.PrettyPrint();
    pp::LabelEncoder le;
    std::vector<std::string> catcols{ "species" };
    csvobj.data = le.encode(csvobj.data, catcols);
    csvobj.PrettyPrint();
    pp::Summarizer s;
    std::vector<std::string> numcols{ "sepal_length", "sepal_width", "petal_length", "petal_width" };
    s.summarize(csvobj.data, numcols, catcols);
    pp::fillNA fn;
    csvobj.data = fn.fill_na(csvobj.data, numcols, catcols, "mean");
    csvobj.PrettyPrint();
    fe::correlation c;
    c.pearson(csvobj.data, numcols);
    csvobj.data = csvobj.slice(0, 10, 1, -1);
    csvobj.PrettyPrint();
}
