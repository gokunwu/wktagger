#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

static void
replace(string & s, const string & s1, const string & s2, const char skip = 0);
void
tokenize(const string & s1, list<string> & lt);

void
tokenize(const string &s1, string &s2)
{
	s2 = "";
	std::list<std::string> lt;
	tokenize(s1,lt);
	for(std::list<std::string>::iterator it = lt.begin();it != lt.end();++it)
	{
		if(it == lt.begin())
		{
			s2 = s2 + *it;
		}
		else
		{
			s2 = s2 + " " + *it;
		}
	}

	return;
}

void
tokenize(const string & s1, list<string> & lt)
{
  lt.clear();

  string s(s1);

  if (s[0] == '"') s.replace(0, 1, "`` ");
  replace(s, " \"", "  `` ");
  replace(s, "(\"", "( `` ");
  replace(s, "[\"", "[ `` ");
  replace(s, "{\"", "{ `` ");
  replace(s, "<\"", "< `` ");

  replace(s, "...", " ... ");

  replace(s, ",", " , ");
  replace(s, ";", " ; ");
  replace(s, ":", " : ");
  replace(s, "@", " @ ");
  replace(s, "#", " # ");
  replace(s, "$", " $ ");
  replace(s, "%", " % ");
  replace(s, "&", " & ");

  int pos = s.size() - 1;
  while (pos > 0 && s[pos] == ' ') pos--;
  while (pos > 0) {
    char c = s[pos];
    if (c == '[' || c == ']' || c == ')' || c == '}' || c == '>' ||
        c == '"' || c == '\'') {
      pos--; continue;
    }
    break;
  }
  if (s[pos] == '.' && !(pos > 0 && s[pos-1] == '.')) s.replace(pos, 1, " .");

  replace(s, "?", " ? ");
  replace(s, "!", " ! ");

  replace(s, "[", " [ ");
  replace(s, "]", " ] ");
  replace(s, "(", " ( ");
  replace(s, ")", " ) ");
  replace(s, "{", " { ");
  replace(s, "}", " } ");
  replace(s, "<", " < ");
  replace(s, ">", " > ");

  /****modified by wukun*/
  //replace(s, "`", " '");
  //replace(s, "_", " - ");
  if(s.find("------------") != std::string::npos)
	  replace(s, "------------", " ------------ ");
  else if(s.find("-----------") != std::string::npos)
	  replace(s, "-----------", " ----------- ");
  else if(s.find("----------") != std::string::npos)
	  replace(s, "----------", " ---------- ");
  else if(s.find("---------") != std::string::npos)
	  replace(s, "---------", " --------- ");
  else if(s.find("--------") != std::string::npos)
	  replace(s, "--------", " -------- ");
  else if(s.find("-------") != std::string::npos)
	  replace(s, "-------", " ------- ");
  else if(s.find("------") != std::string::npos)
	  replace(s, "------", " ------ ");
  else if(s.find("-----") != std::string::npos)
	  replace(s, "-----", " ----- ");
  else if(s.find("----") != std::string::npos)
	  replace(s, "----", " ---- ");
  else if(s.find("---") != std::string::npos)
	  replace(s, "---", " --- ");
  else if(s.find("--") != std::string::npos)
	  replace(s, "--", " -- ");
  //replace(s, "*", " * ");
  //replace(s, "i.e", " i.e ");
  //replace(s, "a.m.", " a.m.");
  //replace(s, "p.m.", " p.m.");
  //replace(s, "a.k.a", " a.k.a ")
  //replace(s, "@", " @ ");
  /****modified by wukun*/

  s.replace(string::size_type(0), 0, " ");
  s.replace(s.size(), 0, " ");

  replace(s, "\"", " '' ");

  replace(s, "' ", " ' ", '\'');
  replace(s, "'s ", " 's ");
  replace(s, "'S ", " 'S ");
  replace(s, "'m ", " 'm ");
  replace(s, "'M ", " 'M ");
  replace(s, "'d ", " 'd ");
  replace(s, "'D ", " 'D ");
  replace(s, "'ll ", " 'll ");
  replace(s, "'re ", " 're ");
  replace(s, "'ve ", " 've ");
  replace(s, "n't ", " n't ");
  replace(s, "'LL ", " 'LL ");
  replace(s, "'RE ", " 'RE ");
  replace(s, "'VE ", " 'VE ");
  replace(s, "N'T ", " N'T ");

  replace(s, " Cannot ", " Can not ");
  replace(s, " cannot ", " can not ");
  replace(s, " D'ye ", " D' ye ");
  replace(s, " d'ye ", " d' ye ");
  replace(s, " Gimme ", " Gim me ");
  replace(s, " gimme ", " gim me ");
  replace(s, " Gonna ", " Gon na ");
  replace(s, " gonna ", " gon na ");
  replace(s, " Gotta ", " Got ta ");
  replace(s, " gotta ", " got ta ");
  replace(s, " Lemme ", " Lem me ");
  replace(s, " lemme ", " lem me ");
  replace(s, " More'n ", " More 'n ");
  replace(s, " more'n ", " more 'n ");
  replace(s, "'Tis ", " 'T is ");
  replace(s, "'tis ", " 't is ");
  replace(s, "'Twas ", " 'T was ");
  replace(s, "'twas ", " 't was ");
  replace(s, " Wanna ", " Wan na ");
  replace(s, " wanna ", " wanna ");
/*  
  pos = s.find("'");
  if(pos != std::string::npos){
    if(pos != 0 && s[pos-1] != " " && s[pos-1] != "n" && s[pos-1] != "N" && s[pos-1] != "d" && s[pos-1] !="D" && s[pos-1] != "'"){
	  replace(s, "'", " '");	
	}	  
  }
 */
  istringstream is(s);
  string t;
  while (is >> t) {
    lt.push_back(t);
  }

}

static void
replace(string & s, const string & s1, const string & s2, const char skip)
{
  string::size_type pos = 0;
  while (1) {
    string::size_type i = s.find(s1, pos);
    if (i == string::npos) break;
    if (i > 0 && s[i-1] == skip) {
      pos = i + 1;
      continue;
    }
    s.replace(i, s1.size(), s2);
    pos = i + s2.size();
  }

}

#if 0
int main(int argc, char *argv[])
{
	std::string inputfile = "";
	std::string outputfile = "";
	std::string str = "";
	std::string res = "";
	//parse the cmd parameter
	if(argc != 3)
		std::cout<<"invalid cmd parameter!"<<std::endl;
	else
	{
		inputfile = argv[1];
		outputfile = argv[2];
		std::cout<<"inputfile : "<<inputfile<<std::endl;
		std::cout<<"outputfile : "<<outputfile<<std::endl;
	}
	ifstream ifile;
	ifile.open(inputfile.c_str());
	ofstream ofile;
	ofile.open(outputfile.c_str());
	while(getline(ifile,str))
	{
		tokenize(str,res);
		ofile<<res<<std::endl;
		std::cout<<res<<std::endl;
	}


	return 0;
}

#endif


