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


namespace models{

    template <class T>
    std::vector<T> cast_vector(std::vector<std::any> col){
        std::vector<T> output;
        T value;
        for(int i=0; i<col.size(); i++){
               try{
                    value = std::any_cast<T>(col[i]);
                    output.push_back(value);
                }
                catch(...){
                    std::cout<<"\nCan't cast: "<< std::any_cast<std::string>(col[i])<<std::endl;
                    std::cout << typeid(col[i]).name() << '\n';
                    continue;
                }
        } 
        return output;   
    }

    class linear{
            std::vector<float> model; //model is just a vector of weights and bias
        public:
            void train(DATATYPE xtrain, std::vector<float> ytrain);
            std::vector<float> predict(DATATYPE xtest);

    };
    void linear::train(DATATYPE xtrain, std::vector<float> ytrain){

    }

      
         
}

