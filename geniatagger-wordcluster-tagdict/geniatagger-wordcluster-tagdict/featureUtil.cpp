#include <cstring>
#include <cctype>
#include <fstream>
#include <iostream>
#include "featureUtil.h"

std::set<std::string> featureUtil::specStr;
std::map<std::string, std::string> featureUtil::spellError;
bool featureUtil::setInitialized = false;
bool featureUtil::mapInitialized = false;

void
featureUtil::loadSet(){
    if(!setInitialized){
        setInitialized = true;
        featureUtil::specStr.insert("'s");
        featureUtil::specStr.insert("'S");
        featureUtil::specStr.insert("'m");
        featureUtil::specStr.insert("'M");
        featureUtil::specStr.insert("'d");
        featureUtil::specStr.insert("'D");
        featureUtil::specStr.insert("'ll");
        featureUtil::specStr.insert("'re");
        featureUtil::specStr.insert("'ve");
        featureUtil::specStr.insert("n't");
        featureUtil::specStr.insert("'LL");
        featureUtil::specStr.insert("'RE");
        featureUtil::specStr.insert("'VE");
        featureUtil::specStr.insert("N'T");
        featureUtil::specStr.insert("D'");
        featureUtil::specStr.insert("d'");
        featureUtil::specStr.insert("'n");
        featureUtil::specStr.insert("'T");
        featureUtil::specStr.insert("'t");
    }
}
int
featureUtil::split(std::vector<std::string> & spellerror, std::string & str, std::string s){
    std::string::size_type start = 0, endof = 0;
    while((endof = str.find(s, start)) != std::string::npos){
        spellerror.push_back(str.substr(start, endof - start));
        start = endof + 1;
    }
    spellerror.push_back(str.substr(start));
}

void
featureUtil::loadSpellError(){
    if(!mapInitialized){
        mapInitialized = true;
        std::string filename = "./resources/spell-error.txt";
        std::ifstream infile(filename.c_str());
        std::string line;
        while(getline(infile, line)){
            replace(line, " ", "");
            std::vector<std::string> spellword;
            split(spellword, line, ":");
            if(spellword.size() != 2){
                std::cout<<"spell-error text split error : "<<line<<std::endl;
            }
            std::string word = spellword[0];
            std::string strerror = spellword[1];
            std::vector<std::string> errors;
            split(errors, strerror, ",");
            for(size_t i = 0; i < errors.size(); ++i){
                featureUtil::spellError.insert(std::pair<std::string,std::string>(errors[i],word));
            }
        }
    }
}

int
featureUtil::fuzztoken(std::string & str, std::vector<std::string> & fuzz){

    //this->loadSet();
    //this->loadSpellError();
    std::string str1 = str;
    toLowerCase(str1);
    fuzz.push_back(str1);

    if(str.find("‘") != std::string::npos){
        replace(str, "‘", "'");
        fuzz.push_back(str);
    }
    if(str.find("’") != std::string::npos){
        replace(str, "’", "'");
        fuzz.push_back(str);
    }
    if(str.find("´") != std::string::npos){
        replace(str, "´", "'");
        fuzz.push_back(str);
    }
    if(str.find("`") != std::string::npos){
        replace(str, "`", "'");
        fuzz.push_back(str);
    }
    if(str.find("“") != std::string::npos){
        replace(str, "“", "\"");
        fuzz.push_back(str);
    }
    if(str.find("”") != std::string::npos){
        replace(str, "”", "\"");
        fuzz.push_back(str);
    }
    //deal with ' in str
    if(featureUtil::specStr.find(str) != featureUtil::specStr.end()){
        std::string::size_type pos = str.find("'");
        if(pos == 0 || pos == str.length()-1){
            replace(str, "'", "");
            fuzz.push_back(str);
        }
        else if(pos != std::string::npos){
            std::string str1 = str.substr(0,pos);
            std::string str2 = str.substr(pos + 1);
            fuzz.push_back(str1);
            fuzz.push_back(str2);
        }
    }
    //delete " in str
    if(str.find("\"") != std::string::npos){
        replace(str, "\"", "");
        fuzz.push_back(str);
    }
    //delete . in str
    if(str.find(".") != std::string::npos){
        replace(str, ".", "");
        fuzz.push_back(str);
    }
    //delete , in str
    if(str.find(",") != std::string::npos){
        replace(str, ",", "");
        fuzz.push_back(str);
    }
    //delete ; in str
    if(str.find(";") != std::string::npos){
        replace(str, ";", "");
        fuzz.push_back(str);
    }
    //delete : in str
    if(str.find(":") != std::string::npos){
        replace(str, ":", "");
        fuzz.push_back(str);
    }
    //delete @ in str
    if(str.find("@") != std::string::npos){
        replace(str, "@", "");
        fuzz.push_back(str);
    }
    //delete # in str
    if(str.find("#") != std::string::npos){
        replace(str, "#", "");
        fuzz.push_back(str);
    }
    //delete $ in str
    if(str.find("$") != std::string::npos){
        replace(str, "$", "");
        fuzz.push_back(str);
    }
    //delete % in str
    if(str.find("%") != std::string::npos){
        replace(str, "%", "");
        fuzz.push_back(str);
    }
    //delete & in str
    if(str.find("&") != std::string::npos){
        replace(str, "&", "");
        fuzz.push_back(str);
    }
    //delete ? in str
    if(str.find("?") != std::string::npos){
        replace(str, "?", "");
        fuzz.push_back(str);
    }
    //delete ! in str
    if(str.find("!") != std::string::npos){
        replace(str, "!", "");
        fuzz.push_back(str);
    }
    //delete [ in str
    if(str.find("[") != std::string::npos){
        replace(str, "[", "");
        fuzz.push_back(str);
    }
    //delete ] in str
    if(str.find("]") != std::string::npos){
        replace(str, "]", "");
        fuzz.push_back(str);
    }
    //delete  ( in str
    if(str.find("(") != std::string::npos){
        replace(str, "(", "");
        fuzz.push_back(str);
    }
    //delete ) in str
    if(str.find(")") != std::string::npos){
        replace(str, ")", "");
        fuzz.push_back(str);
    }
    //delete { in str
    if(str.find("{") != std::string::npos){
        replace(str, "{", "");
        fuzz.push_back(str);
    }
    //delete } in str
    if(str.find("}") != std::string::npos){
        replace(str, "}", "");
        fuzz.push_back(str);
    }
    //delete < in str
    if(str.find("<") != std::string::npos){
        replace(str, "<", "");
        fuzz.push_back(str);
    }
    //delete > in str
    if(str.find(">") != std::string::npos){
        replace(str, ">", "");
        fuzz.push_back(str);
    }
    //deal with -racial --> racial or racial- --> racial
    std::string::size_type pos = str.find("-");
    if(0 == pos){
        std::string tmp = str.substr(pos+1);
        fuzz.push_back(tmp);
    }
    if(str.length()-1 == pos){
        std::string tmp = str.substr(0,pos);
        fuzz.push_back(tmp);
    }
    //deal with make\ --> make or \make --> make
    pos = str.find("\\");
    if(0 == pos){
        std::string tmp = str.substr(pos + 1);
        fuzz.push_back(tmp);
    }
    if(str.length() -1 == pos){
        std::string tmp = str.substr(0,str.length()-1);
        fuzz.push_back(tmp);
    }

    //use spell error to construct fuzz collection
    std::map<std::string, std::string>::iterator spellerrorit;
    spellerrorit = spellError.find(str);
    if(spellerrorit != spellError.end()){
        fuzz.push_back(spellerrorit->second);
    }

    return 1;
}

void
featureUtil::replace(std::string & s, const std::string & s1, const std::string & s2, const char skip){
  std::string::size_type pos = 0;
  while (1) {
    std::string::size_type i = s.find(s1, pos);
    if (i == std::string::npos) break;
    if (i > 0 && s[i-1] == skip) {
      pos = i + 1;
      continue;
    }
    s.replace(i, s1.size(), s2);
    pos = i + s2.size();
  }

}

void
featureUtil::toLowerCase(std::string & str){
    for(int i = 0; i < str.length(); ++i){
        str[i] = tolower(str[i]);
    }
}







