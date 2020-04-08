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
#include <cassert>


#define DATATYPE std::unordered_map<std::string, std::vector<std::any>>
// #define MAPOFMAP std::unordered_map<std::string, std::unordered_map<std::string, std::any>>
#define MAPOFMAP std::unordered_map<std::string, std::unordered_map<std::string, float>>
#define MAPOFMAPSTRING std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
#define CASTSTRING std::any_cast<std::string>
#define CASTINT std::any_cast<int>
#define CASTFLOAT std::any_cast<float>
#define assertm(exp, msg) assert(((void)msg, exp))


namespace metric{

    template <class T>
    std::vector<T> cast_vector(std::vector<std::any> col){
        std::vector<T> output;
        T value;
        // for(auto it=col.begin(); it!=col.end(); it++){
        for(int i=0; i<col.size(); i++){
               try{
                    value = std::any_cast<T>(col[i]);
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

    template <class T> 
    float accuracy(std::vector<T> y1, std::vector<T> y2){
        std::vector<int> y;
        std::vector<int> y_pred;
        y = cast_vector<int>(y1);
        y_pred = cast_vector<int>(y2);
        assertm(y1.size()==y2.size(), "Vectors must have equal length\n");
        size_t n = y.size();
        float acc=0;
        for(int i=0; i<n; i++){
            if(y[i] == y_pred[i]){
                acc += 1;
            }                
        }
        return acc/n;
    }
    
   
}