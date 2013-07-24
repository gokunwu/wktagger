#!/usr/bin/env python
import sys
import signal

def genTagDict4TrainCikuu(infilename, outfilename):
	infile = open(infilename, "r")
	outfile = open(outfilename, "w")
	wordposdic = dict()
	posdic = dict()
	for line in infile:
		line = line.strip()
		wordpos_list = line.split(" ")
		for wordpos in wordpos_list:
			word_pos_list = wordpos.split("_",1)
			if(len(word_pos_list) != 2):
				print "FUCK"
				print line
				print wordpos
				sys.exit()
			word = word_pos_list[0]
			pos = word_pos_list[1]
			if(word not in wordposdic.keys()):
				tmpdic = dict()
				tmpdic[pos] = 1
				wordposdic[word] = tmpdic
			elif(pos not in wordposdic[word].keys()):
				wordposdic[word][pos] = 1
			else:
				wordposdic[word][pos] += 1
	for word in wordposdic.keys():
		items = wordposdic[word].items()
		backitems = [[v[1],v[0]] for v in items]
		backitems.sort()
		s = ""
		s = s + word + " "
		for v in backitems:
			s = s + v[1] + " "
		s = s.strip()
		outfile.write(s + "\n")
		

				

def main():
	if(len(sys.argv) != 3):
		print "\nusage : python program infilename outfilename\n"
	infilename = sys.argv[1]
	outfilename = sys.argv[2]
	genTagDict4TrainCikuu(infilename, outfilename)

if __name__ == "__main__":
	signal.signal(signal.SIGINT, lambda x, y:sys.exit())
	main()
