#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <any>
#include <cassert>

#define DATATYPE std::unordered_map<std::string, std::vector<std::any>>
#define CASTSTRING std::any_cast<std::string>
#define CASTINT std::any_cast<int>
#define assertm(exp, msg) assert(((void)msg, exp))

void print_v(std::vector<std::string> v){
    for(int i=0; i<v.size(); i++)
        std::cout << v.at(i) << std::endl;
}

namespace csv{
    class CSV{
        public:
            int test = 10;
            std::pair<size_t, size_t> size;
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
            DATATYPE slice(int ri1, int ri2, int ci1, int ci2);
    };

    DATATYPE CSV::slice(int ri1=0, int ri2=0, int ci1=0, int ci2=0){
        if(!ri2) // if ri2 is zero, set it to last index
            ri2 = size.first;
        if(!ci2) // if ci2 is zero, set it to last index
            ci2 = size.second;    


        if(ri1 < 0)
            ri1 = size.first + ri1;
        if(ri2 < 0)
            ri2 = size.first + ri2;
        if(ci1 < 0)
            ci1 = size.second + ci1;
        if(ci2 < 0)
            ci2 = size.second + ci2;

        if(ri1 > size.first)
            ri1 = size.first; 
        if(ri2 > size.first)
            ri2 = size.first; 
        if(ci1 > size.second)
            ci1 = size.second; 
        if(ci2 > size.second)
            ci2 = size.second;                                     

        assertm(ri1<=ri2, "Row starting index can't be bigger than ending index\n");   
        assertm(ci1<=ci2, "Row starting index can't be bigger than ending index\n");   

        if(ri1>0 || ri2<size.first){ //slice rows
            for(auto it=data.begin(); it!=data.end(); ++it){
                auto key = it->first;
                data[key] = std::vector<std::any>(it->second.begin()+ri1, it->second.begin()+ri2);
            }
        }
  

        if(ci1>0||ci2<size.second){ //slice columns
            size_t curi=0;
            std::vector<std::string> newcols;
            for(auto c:cnames){ //I iterate over map using columns (keys) and not an iterator in order to preserve order of columns
                if(curi>=ci1 && curi<ci2){
                    newcols.push_back(c);
                    curi++;
                    continue;
                }           
                auto it = data.find(c);
                data.erase(it);     
                curi++;
            }
            cnames = newcols;
        }
        size.first = ri2-ri1;
        size.second = ci2-ci1;
        return data;
     }

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

        std::cout<<"Size: "<<size.first<<"\n";
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
