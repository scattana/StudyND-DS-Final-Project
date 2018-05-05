#!/usr/bin/env python3
FILE = "schedule.json"
BUILDINGS_PATH = "/afs/nd.edu/user24/scattana/Public/"
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
	curr = data[key[:-1]]
	write_file.write(write(key[:-1]+'\n'))
	write_file.write(curr['year']+'\n')
	write_file.write(curr['month']+'\n')
	write_file.write(curr['day']+'\n')
	write_file.write(curr['hour']+'\n')
	write_file.write(curr['capacity']+'\n')
	for i in range(48):
		write_file.write(curr['hour{}'.format(i+1)]['people'])
		write_file.write(','.join(curr['hour{}'.format(i+1)]['names']))
