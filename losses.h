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


namespace losses{
    
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

    template <class T>
    T abs(T a){
        return ( a > 0 ? a : -a);
    }

    template <class T> 
    float mae(std::vector<T> y1, std::vector<T> y2){
        std::vector<float> y;
        std::vector<float> y_pred;
        y = cast_vector<float>(y1);
        y_pred = cast_vector<float>(y2);
        assertm(y1.size()==y2.size(), "Vectors must have equal length\n");
    
        size_t n = y.size();
        float mae=0;
        for(int i=0; i<n; i++)
            mae += abs(y[i] - y_pred[i])/n;
        return mae;
    }

    template <class T> 
    float mse(std::vector<T> y1, std::vector<T> y2){
        std::vector<float> y;
        std::vector<float> y_pred;
        y = cast_vector<float>(y1);
        y_pred = cast_vector<float>(y2);
        assertm(y1.size()==y2.size(), "Vectors must have equal length\n");
        size_t n = y.size();
        float mse=0;
        for(int i=0; i<n; i++)
            mse += pow((y[i] - y_pred[i]), 2)/n;
        return mse;
    }

    template <class T> 
    float rmse(std::vector<T> y1, std::vector<T> y2){
        return sqrt(mse<T>(y1, y2));
    }

    template <class T> 
    float huber(std::vector<T> y1, std::vector<T> y2, float delta=1){
        std::vector<float> y;
        std::vector<float> y_pred;
        y = cast_vector<float>(y1);
        y_pred = cast_vector<float>(y2);
        assertm(y1.size()==y2.size(), "Vectors must have equal length\n");
        size_t n = y.size();
        float loss=0;
        float a = 0;

        for(int i=0; i<n; i++){
            a = abs(y[i] - y_pred[i]);
            if(a<delta)
                loss += pow(a, 2)/2;
            else
                loss += delta*(a-(delta/2));    
        }
        return loss/n;
    }    
}