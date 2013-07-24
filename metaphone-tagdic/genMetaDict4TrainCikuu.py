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
		if(len(wordpos_list) != 2):
			print line
			continue
		word = wordpos_list[0]
		pos = wordpos_list[1]
		if(word not in wordposdic.keys()):
			tmpdic = dict()
			tmpdic[pos] = 1
			wordposdic[word] = tmpdic
		elif(pos not in wordposdic[word].keys()):
			wordposdic[word][pos] = 1
		else:
			wordposdic[word][pos] += 1
	for word in wordposdic.keys():
		count = 0
		for pos in wordposdic[word].keys():
			count = count + wordposdic[word][pos]
		items = wordposdic[word].items()
		backitems = [[v[1],v[0]] for v in items]
		backitems.sort(reverse = True)
		s = ""
		s = s + word + " "
		for v in backitems:
			tmp = float(v[0])/count
			tmp = float('%0.4f'%tmp)
			s = s + v[1] + " " + str(tmp) + " "
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
