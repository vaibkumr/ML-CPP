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


    int n_classes(std::vector<int> v){
        std::sort(v.begin(), v.end());
        return std::unique(v.begin(), v.end()) - v.begin();
    }

    // template <typename TwoD>
    // int sum_row(TwoD& arr){
    //     return 1;
    // }

    template <class T> 
    std::pair<float, float> confusion_matrix(std::vector<T> y1, std::vector<T> y2, bool verbose=true){
        std::vector<int> y;
        std::vector<int> y_pred;
        y = cast_vector<int>(y1);
        y_pred = cast_vector<int>(y2);
        assertm(y1.size()==y2.size(), "Vectors must have equal length\n");
        size_t n = y.size();
        int nc = n_classes(y);
        int cmatrix[nc][nc]; //rows are preds, columns are actual
  
        // init to zero
        for(int i=0; i<nc; i++){
            for(int j=0; j<nc; j++)
                cmatrix[i][j] = 0;
        }

        for(int i=0; i<n; i++)
            cmatrix[(y_pred[i]-1)][(y[i]-1)]++;
        float precision = 0;
        float recall = 0;

        if(verbose){
            std::cout<<"\n++++++++++++++++++++++++++++\n";
            std::cout<<"Confusion matrix \t\n";
            for(int i=0; i<nc; i++){
                for(int j=0; j<nc; j++)
                    std::cout<<cmatrix[i][j]<<"\t";
                std::cout<<std::endl;    
            }
            std::cout<<"++++++++++++++++++++++++++++\n";
        }    
        
        for(int i=0; i<nc; i++){
            float sum_row = 0;
            float sum_column = 0;
            for(int k=0; k<nc; k++){
                sum_row += cmatrix[i][k];
                sum_column += cmatrix[k][i];
            }
            
            precision += cmatrix[i][i]/(nc*sum_row);
            recall += cmatrix[i][i]/(nc*sum_column);
        }    
        std::pair<float, float> pr = std::make_pair(precision, recall);
        return pr;
    }
    
    template <class T> 
    float f1(std::vector<T> y1, std::vector<T> y2){
        std::pair<float, float> pr = confusion_matrix(y1, y2, false);
        return 2*pr.first*pr.second/(pr.first+pr.second);
        }

    template <class T> 
    float fbeta(std::vector<T> y1, std::vector<T> y2, float beta=1){
        std::pair<float, float> pr = confusion_matrix(y1, y2, false);
        return (1+pow(beta, 2))*pr.first*pr.second/(pow(beta, 2)*pr.first+pr.second);
        }        
         
}