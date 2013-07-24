#!/usr/bin/env python

import sys
import signal

def line2wordspacepos(line):
	wordspacepos_list = list()
	word_pos_list = line.split(" ")
	for word_pos in word_pos_list:
		word_list = word_pos.split("_",1)
		if(len(word_list) != 2):
			print line
			print word_pos
			sys.exit()
		wordspacepos_list.append(word_list[0] + " " +word_list[1])
	return wordspacepos_list

def metaphoneFormat(infilename, outfilename):
	infile = open(infilename, "r")
	outfile = open(outfilename, "w")
	for line in infile:
		line = line.strip()
		wordspacepos_list = line2wordspacepos(line)
		for wordspacepos in wordspacepos_list:
			outfile.write(wordspacepos + "\n")

def main():
	if(len(sys.argv) != 3):
		print "\nusage : python program infilename outfilename\n"
		sys.exit()
	infilename = sys.argv[1]
	outfilename = sys.argv[2]
	metaphoneFormat(infilename, outfilename)

if __name__ == "__main__":
	signal.signal(signal.SIGINT, lambda x,y:sys.exit())
	main()
