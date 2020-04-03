#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <any>

#define DATATYPE std::unordered_map<std::string, std::vector<std::any>>
#define CASTSTRING std::any_cast<std::string>
#define CASTINT std::any_cast<int>

void print_v(std::vector<std::string> v){
    for(int i=0; i<v.size(); i++)
        std::cout << v.at(i) << std::endl;
}

namespace csv{
    class CSV{
        public:
            int test = 10;
            std::pair<int, int> size;
            std::any a=1;
            // std::unordered_map<std::string, std::vector<std::string>> data;
            DATATYPE data;
            std::string fname;
            std::vector<std::string> cnames;
            std::ifstream CSVStream;
            std::vector<std::string> GetVals(std::string cline);
            void CSVReader();
            CSV(std::string);
            void PrettyPrint();
            void PrintSize();
    };

    CSV::CSV(std::string filename){
        CSV::fname = filename;
    }

    void CSV::PrintSize(){
        std::cout<<"Size: ("<<size.first<<", "<<size.second<<")\n";
    }

    void CSV::PrettyPrint(){
        int row_i=0;   

        for(auto c:cnames)
            std::cout<<c<<"\t";
        std::cout<<std::endl;   

        while(row_i<size.first){
            for(auto c:cnames){
                try{
                    std::cout<<CASTSTRING(data[c].at(row_i))<<"\t";
                }
                catch(...){
                    std::cout<<CASTINT(data[c].at(row_i))<<"\t";
                }
            }
            std::cout<<std::endl;  
            row_i++;  
        }
        CSV::PrintSize();
    }


    std::vector<std::string> CSV::GetVals(std::string cline){
        std::string delim = ",";
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos=cline.find(delim)) != std::string::npos){
            token = cline.substr(0, pos);
            if(token.length() == 0 || token == " ")
                std::cout << "weird\n";
            tokens.push_back(token);
            cline.erase(0, pos+delim.length());
        }
        tokens.push_back(cline);
        return tokens;
    }

    void CSV::CSVReader(){
        std::string line;
        int row_i = 0;
        int col_i = 0;
        std::vector<std::string> vals;
        std::string col;
        std::ifstream CSVStream(fname); 

        while (getline(CSVStream, line)){
            if(!row_i){
                cnames = GetVals(line);
                col_i = cnames.size();
                // print_v(cnames);
                row_i++;
                continue;
            }
            // std::cout << line << std::endl;
            vals = GetVals(line);
            for(int i=0; i<cnames.size(); i++){
                CSV::data[cnames.at(i)].push_back(vals.at(i));
            }
            row_i++;
        }
        size.first = row_i-1;
        size.second = col_i;
    }
}
