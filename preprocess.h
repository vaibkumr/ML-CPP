// Compile using -std=c++17

#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <any>
#include <set>
// #include "CSVReader.h"

#define DATATYPE std::unordered_map<std::string, std::vector<std::any>>
#define CASTSTRING std::any_cast<std::string>
#define CASTINT std::any_cast<int>

namespace pp{
    // class TypeCast{
    //     public:
    //         std::unordered_map<std::string, std::string> typemap;
    // };


    // class Summarizer{
    //     public:
    //         std::unordered_map<std::string, std::vector<float>> mean;
    //         std::unordered_map<std::string, std::vector<float>> std;
    //         std::unordered_map<std::string, int> count;
    //         std::unordered_map<std::string, std::any> min;
    //         std::unordered_map<std::string, std::any> max;

    // };

    class LabelEncoder{
        public:
            DATATYPE encode(DATATYPE data, std::vector<std::string> catcols);
    };

    std::set<std::string> find_unique(std::vector<std::any> v){
        std::string value;
        std::set<std::string> unique_vals;
        for(int i=0; i<v.size(); i++){
            value = std::any_cast<std::string>(v.at(i));
            unique_vals.insert(value);
        }
        return unique_vals;
    }


    std::unordered_map<std::string, int> labelmapper(std::set<std::string> vals){
        std::unordered_map<std::string, int> labelmap;
        int encoded_val = 1;
        for(auto it=vals.begin(); it!=vals.end(); it++){
            labelmap[*it] = encoded_val;
            encoded_val++;
        }
        return labelmap;
    }

    std::vector<std::any> encode_col(std::vector<std::any> col){
        std::set<std::string> unique_vals;
        std::unordered_map<std::string, int> labelmap;
        std::vector<std::any> encoded_col;
        unique_vals = find_unique(col);
        labelmap = labelmapper(unique_vals);
        for(int i=0; i<col.size(); i++)
            encoded_col.push_back(labelmap[std::any_cast<std::string>(col.at(i))]);
        return encoded_col;
    }


    DATATYPE LabelEncoder::encode(DATATYPE data, std::vector<std::string> catcols){
        std::vector<std::any> column;
        std::vector<std::any> encoded_column;
        for(auto c:catcols){
            column = data[c];
            encoded_column = encode_col(column);
            data[c] = encoded_column;
        }
        return data;
    }
}





