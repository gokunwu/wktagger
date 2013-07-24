

#include <fstream>
#include <sstream>
#include "tagDictionary.h"

std::map<std::string, std::map< std::string, double> > tagDictionary::word2pos;
bool tagDictionary::mapInitialized = false;

void
tagDictionary::loadTagDic(){
    if(mapInitialized == false){
        mapInitialized = true;
        std::string filename = "./resources/tagDict4TrainCikuu";
        std::ifstream infile(filename.c_str());
        if(!infile){
            std::cout<<"could not open the file : ./resources/tagDict4TrainCikuu to read!"<<std::endl;
        }
        std::string line;
        while(getline(infile, line)){
            std::string word;
            std::map<std::string, double> poses;
            std::stringstream ss(line);
            std::string pos;            double value;
            ss>>word;
            while(ss >> pos){                ss >> value;
                poses.insert(std::pair<std::string, double>(pos, value));
            }
            tagDictionary::word2pos.insert(std::pair<std::string, std::map<std::string,double> >(word, poses));
        }
    }
}

int
tagDictionary::findWordInWord2Pos(std::map<std::string, double> & poses, std::string &str){
    std::map<std::string, std::map<std::string, double> >::iterator word2posit;
    word2posit = word2pos.find(str);
    if(word2posit != word2pos.end()){
        poses = word2posit->second;        return 1;
    }    else{        return 0;    }
}

























