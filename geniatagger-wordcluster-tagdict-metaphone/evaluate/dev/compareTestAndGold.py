#!/usr/bin/env python
import sys,signal

def compareTestAndGold(ifilename1,ifilename2,ofilename1,ofilename2):
	dict = {}
	ifile1 = open(ifilename1,"r")
	ifile2 = open(ifilename2,"r")
	ofile1 = open(ofilename1,"w")
	#ofile2 = open(ofilename2,"w")
	line1 = ifile1.readline()
	line2 = ifile2.readline()
	line1 = line1.strip()
	line2 = line2.strip()
	while(line1 and line2):
		sent1 = ""
		sent2 = ""
		if(line1 != line2):
			word_pos_list1 = line1.split(" ") 
			word_pos_list2 = line2.split(" ") 
			if(len(word_pos_list1) == len(word_pos_list2)):
				for i in range(0,len(word_pos_list1)):
					if(word_pos_list1[i] == word_pos_list2[i]):
						sent1 = sent1 + word_pos_list1[i] +" "
						sent2 = sent2 + word_pos_list2[i] +" "
					else:
						sent1 = sent1 + "<SPAN style='color:red'>"+ word_pos_list1[i] + "</SPAN>" + " "
						sent2 = sent2 + "<SPAN style='color:red'>"+ word_pos_list2[i] + "</SPAN>" + " "
			else:
				print line1 + "\n" + line2 + "\n"
			sent1 = sent1.strip()
			sent2 = sent2.strip()
			#ofile1.write("<tr><td></td><td>" + sent1 + "</td>\n</tr>" + "" + sent2 + "</td>\n\n</tr>")
			ofile1.write("<SPAN style='color:blue'>gold: </SPAN>" +sent1 + "<br>" +"<SPAN style='color:blue'>test: </SPAN>"+ sent2 + "<br><br>")
		line1 = ifile1.readline()
		line2 = ifile2.readline()
		line1 = line1.strip()
		line2 = line2.strip()

def main():
	ifilename1 = "gold.pos.cikuu"
	ifilename2 = "test.pos.cikuu"
	ofilename1 = "compare.sent.gold.test"
	ofilename2 = "compare.word.gold.test"
	compareTestAndGold(ifilename1,ifilename2,ofilename1,ofilename2)

if __name__ == "__main__":
	signal.signal(signal.SIGINT,lambda x,y:sys.exit())
	main()
