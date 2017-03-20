#!/usr/bin/python

import re
import sys

class ListStream():
	def __init__(self):
		self.data = []
	def write(self, s):
		self.data.append(s)

class App():
	def get_input(self):
		return sys.argv[1]

	def process_input(self, filename):
		f = open(filename, 'r')
		d = {}
		l = []
		for line in f:
			match =  self.find_match(line)
			if match:
				for m in match:
					key, val = self.parse_exp(m)
					d[key] = val
		l = sorted(d.items())
		for k, v in l:
			sys.stdout = stream = ListStream()
			exec v
			d[k] = ''.join(stream.data).strip('\n')
			if d[k] == '':
				d[k] = '\b'
		sys.stdout = sys.__stdout__
		f.close()
		return d
			
	def replace(self, filename, results):
		try:
			erase = open('output', 'r+')
			erase.truncate()
			erase.close()
		except:
			pass
		of = open('output', 'w')
		inf = open(filename, 'r')
		for line in inf:
			match = self.find_match(line)
			if match:
				for m in match:
					old_str = '{%'+m+'%}'
					key, val = self.parse_exp(m)
					line = line.replace(old_str, results[key].strip('\n'))
			of.write(line)
			of.flush()
		of.close()
		inf.close()
				 	

	def find_match(self,line):
		match = re.findall('(?<={%)(.+?)(?=%})', line)
		return match

	def parse_exp(self, line):
		line = line.split(')', 1)
		key = line[0][2]
		val = line[1].strip()
		return key, val

	def main(self):
		filename = self.get_input()
		results = self.process_input(filename)
		self.replace(filename, results)

if __name__ == '__main__':
	APP = App()
	APP.main()

