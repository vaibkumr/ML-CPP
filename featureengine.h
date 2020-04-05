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
#define MAPOFMAPSTRING std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
#define CASTSTRING std::any_cast<std::string>
#define CASTINT std::any_cast<int>
#define CASTFLOAT std::any_cast<float>

namespace fe{
    
    class correlation{
        public:
            void pearson(DATATYPE data, std::vector<std::string> numcols);
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


    void correlation::pearson(DATATYPE data, std::vector<std::string> numcols){
        /*
        Using this: https://wikimedia.org/api/rest_v1/media/math/render/svg/435a23c499a2450f0752112e69a9b808336a7cce
        */
        std::vector<float> c1;
        std::vector<float> c2;
        float mean1;
        float mean2;
        float corr;
        for(auto col1: numcols){
            for(auto col2: numcols){
                size_t n = col1.size();
                c1 = cast_vector<float>(data[col1]);
                c2 = cast_vector<float>(data[col2]);
                float sum1=0, sumsq1=0, sum2=0, sumsq2=0;
                float prodsum=0;
                for(int i=0; i<n; i++){
                    sum1 += c1[i];
                    sum2 += c2[i];
                    prodsum += c1[i]*c2[i];
                    sumsq1 += c1[i]*c1[i];
                    sumsq2 += c2[i]*c2[i];
                }
            corr = (n*prodsum - sum1*sum2)/(sqrt((n*sumsq1 - sum1*sum1)*(n*sumsq2 - sum2*sum2)));
            std::cout<<col1<<"\t"<<col2<<"\t"<<corr<<std::endl;
            }
        }
    }
}





