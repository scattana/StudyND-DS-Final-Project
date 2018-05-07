#!/usr/bin/env python3
import json
FILE = "../data/schedule.json"
BUILDINGS_PATH = "../data/"
BUILDINGS = ["cushing.txt", "fitzpatrick.txt", "duncan.txt", "stinson.txt"]
OUT_PATH = "/tmp/input.txt"
write_file = open(OUT_PATH, "w")
data = json.load(open(FILE))
keys = []
for building in BUILDINGS:
	odd = True;
	for room in open(BUILDINGS_PATH+building):
		if odd:
			keys.append(room)
		odd = not odd
for key in keys:
	if len(key) == 1:
		continue
	print(key)
	curr = data[key.rstrip()]
	write_file.write(str(key[:-1])+'\n')
	write_file.write(str(curr['capacity'])+'\n')
	for i in range(48):
		write_file.write(str(curr['hour{}'.format(i+1)]['people'])+'\n')
		write_file.write(','.join(curr['hour{}'.format(i+1)]['names'])+'\n')

write_file.close()
