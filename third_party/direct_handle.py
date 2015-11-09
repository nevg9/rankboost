#!/usr/bin/python
# encoding=utf-8

# Author: Ruimin Wang
import sys

if __name__ == '__main__':
	file_name = sys.argv[1]
	out_name = sys.argv[2]
	outfile = open(out_name,'w')
	dic = {}
	with open(file_name) as fp:
		for line in fp:
			data = line.rstrip().split(' ')
			# label = int(data[0])
			# qid = int(int(data[1].split(':')[1]))
			# dic.setdefault(qid,[])
			s = ''
			for d in data:
				if d[0]=='#':
					outfile.write('\n')
					break
				else:
					outfile.write(' '.join(d.split(':'))+' ')
				# s = s+' '.join(d.split(':'))+' '
			# dic[qid].append((label,s))