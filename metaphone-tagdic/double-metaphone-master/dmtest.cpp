#include <vector>
#include <string>
#include "double_metaphone.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf ("Usage: dmtest <filename> <outfilename>\n"
            "  where <filename> contains one word per line, will print\n"
            "  each word with its 2 double metaphone values.\n");
    exit(1);
  }
  string infilename = argv[1];
  string outfilename = argv[2];
  ifstream infile(infilename.c_str());
  ofstream outfile(outfilename.c_str());
  string str;
  while(getline(infile,str)){
    string word;
    string pos;
    string code;
    vector<string> codes;

	stringstream ss(str);
	ss >> word;
	ss >> pos;
	DoubleMetaphone(word, &codes);
	code = "**MP**" + codes[0] + " " + pos;
	cout<<code<<endl;
	outfile<<code<<endl;
  }
  
#if 0
  FILE* f = fopen(argv[1], "r");

  while (!feof(f)) {
    word = fgets(line, sizeof(line), f);
    if (word && strlen(word)) {
      vector<string> codes;
      if (word[strlen(word) - 1] == '\n') {
        word[strlen(word) - 1] = '\0';
      }
      string s = string(word);
      DoubleMetaphone(s, &codes);
      printf ("%s,%s,%s\n", word, codes[0].c_str(), codes[1].c_str());
    }
  }
#endif
}
