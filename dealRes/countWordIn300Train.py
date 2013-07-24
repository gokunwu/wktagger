#! /usr/local/env python

import sys
import signal

def main():
	ifilename = "300.train.pos.cikuu"
	ifile = open(ifilename, "r")
	count = 0
	for line in ifile:
		line = line.strip()
		word_list = line.split(" ")
		for word in word_list:
			count += 1
	print count


if __name__ == "__main__":
	signal.signal(signal.SIGINT, lambda x,y:sys.exit())
	main()
