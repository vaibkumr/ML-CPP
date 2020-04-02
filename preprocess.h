// Compile using -std=c++17

#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <any>
#include <set>
#include <limits>
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include <cstdlib>
#include <iomanip>

// #include "CSVReader.h"

#define DATATYPE std::unordered_map<std::string, std::vector<std::any>>
// #define MAPOFMAP std::unordered_map<std::string, std::unordered_map<std::string, std::any>>
#define MAPOFMAP std::unordered_map<std::string, std::unordered_map<std::string, float>>
#define CASTSTRING std::any_cast<std::string>
#define CASTINT std::any_cast<int>
#define CASTFLOAT std::any_cast<float>

namespace pp{

    class Summarizer{
        public:
            MAPOFMAP summarize(DATATYPE data, std::vector<std::string> numcols);
    };

    template <class T>
    std::vector<T> cast_vector(std::vector<std::any> col){
        std::vector<T> output;
        T value;
        // for(auto it=col.begin(); it!=col.end(); it++){
        for(int i=0; i<col.size(); i++){
               try{
                    value = atof(std::any_cast<std::string>(col[i]).c_str());
                    output.push_back(value);
                }
                catch(...){
                    // value = std::any_cast<T>(*it);
                    // output.push_back(value);
                    std::cout<<"\nCan't cast: "<< std::any_cast<std::string>(col[i])<<std::endl;
                    std::cout << typeid(col[i]).name() << '\n';
                    continue;
                }
        } 
        return output;   
    }    

    std::vector<float> calc_col_summary(std::vector<std::any> col){
        float mean=0, stdv=0, nunique=0;
        float median_20, median_40, median_50, median_60, median_80;
        float min=std::numeric_limits<float>::max();
        float max=std::numeric_limits<float>::min();
        float value, prev_value;
        float sum=0, sum_sq=0;
        std::vector<float> fcol;
        
        fcol = cast_vector<float>(col);
        size_t size=fcol.size();
        
        // std::sort(fcol.begin(), fcol.end()); //Sort



        median_20 = fcol[int(size*0.2)];    
        median_40 = fcol[int(size*0.4)];    
        median_50 = fcol[int(size*0.5)];    
        median_60 = fcol[int(size*0.6)];    
        median_80 = fcol[int(size*0.8)];    

        prev_value = std::numeric_limits<float>::min();

        for(int i=0; i<size; i++){
            value = fcol[i];
            sum += value; //for mean and std
            sum_sq += pow(value, 2); //for std
            
            if(value>prev_value) //for nunique
                nunique++;
            prev_value = value;    

            if(value < min) //for min
                min = value;
            if(value > max) //for max
                max = value;     
        }

        mean = sum/size;
        stdv = sqrt((sum_sq/size) - pow((sum/size), 2));
        std::vector<float> result;
        result.push_back(mean);
        result.push_back(stdv);
        result.push_back(median_20);
        result.push_back(median_40);
        result.push_back(median_50);
        result.push_back(median_60);
        result.push_back(median_80);
        result.push_back(nunique);
        result.push_back(min);
        result.push_back(max);
        return result;
    }
    
    void print_summary(MAPOFMAP summary, std::vector<std::string> numcols){
        std::cout << std::fixed;
        std::cout << std::setprecision(4);
        std::cout<<std::endl<<"Value\t\t";
        std::vector<std::string> rows {"mean", "stdv", "count", "min", "20%", "40%", "50%", "60%", "80%", "max"};
        for(auto c: numcols)
            std::cout<<c<<"\t\t";
            
        for(auto row:rows){
            std::cout<<std::endl;
            std::cout<<row<<"\t\t";
            for(auto c: numcols)
                std::cout<<summary[c][row]<<"\t\t";
        }
        std::cout<<std::endl;
    }

    MAPOFMAP Summarizer::summarize(DATATYPE data, std::vector<std::string> numcols){
        MAPOFMAP summary;
        std::vector<float> col_summary;
        for(auto c:numcols){
            col_summary = calc_col_summary(data[c]);
            summary[c]["mean"] = col_summary.at(0);
            summary[c]["stdv"] = col_summary.at(1);
            summary[c]["20%"] = col_summary.at(2);
            summary[c]["40%"] = col_summary.at(3);
            summary[c]["50%"] = col_summary.at(4);
            summary[c]["60%"] = col_summary.at(5);
            summary[c]["80%"] = col_summary.at(6);
            summary[c]["count"] = col_summary.at(7);
            summary[c]["min"] = col_summary.at(8);
            summary[c]["max"] = col_summary.at(9);
        }
        print_summary(summary, numcols);
        return summary;
    }


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





