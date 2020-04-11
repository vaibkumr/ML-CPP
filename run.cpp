// Compile using -std=c++17
#include "CSVReader.h"
#include "preprocess.h"
#include "featureengine.h"
#include "losses.h"
#include "metric.h"
#include <string>
#include <any>


int main(){
    std::string fname = "iris2.csv";
    csv::CSV csvobj(fname);
    csvobj.CSVReader();
    // csvobj.PrettyPrint();
    pp::LabelEncoder le; 
    // std::vector<std::string> catcols{ "species" };
    std::vector<std::string> catcols{ "species", "species_guess" };
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
    // csvobj.data = csvobj.slice(0, 10, 1, -1);
    // csvobj.PrettyPrint();
    std::cout<<"MSE: "<<losses::mse(csvobj.data["sepal_length"], csvobj.data["sepal_width"]) << "\n";
    std::cout<<"RMSE: "<<losses::rmse(csvobj.data["sepal_length"], csvobj.data["sepal_width"]) << "\n";
    std::cout<<"MAE: "<<losses::mae(csvobj.data["sepal_length"], csvobj.data["sepal_width"]) << "\n";
    std::cout<<"Huber: "<<losses::huber(csvobj.data["sepal_length"], csvobj.data["sepal_width"]) << "\n";
    std::cout<<"Accracy: "<<metric::accuracy(csvobj.data["species"], csvobj.data["species_guess"]) << "\n";
    std::pair<float, float> pr = metric::confusion_matrix(csvobj.data["species"], csvobj.data["species_guess"]);
    std::cout<<"Precision: "<< pr.first << "\n";
    std::cout<<"Recall: "<< pr.second << "\n";
    std::cout<<"F1: "<<metric::accuracy(csvobj.data["species"], csvobj.data["species_guess"]) << "\n";
    int beta = 2;
    std::cout<<"Fbeta: "<<metric::fbeta(csvobj.data["species"], csvobj.data["species_guess"], beta) << "\n";

    
}
