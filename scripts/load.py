#!/usr/bin/env python3
import json
FILE = "../data/schedule.json"
BUILDINGS_PATH = "../data/"
BUILDINGS = [["cushing.txt", "Cushing"], ["fitzpatrick.txt", "Fitzpatrick"], ["duncan.txt", "Duncan Student Center"], ["stinson.txt", "Stinson-Remick"]]
OUT_PATH = "/tmp/input.txt"
write_file = open(OUT_PATH, "w")
data = json.load(open(FILE))
keys = {}
for building in BUILDINGS:
	keys[building[1]] = []
	odd = True;
	for room in open(BUILDINGS_PATH+building[0]):
		if odd and len(room) > 1:
			keys[building[1]].append(room)
		odd = not odd
for building in keys:
	write_file.write(str(len(keys[building]))+'\n')
	write_file.write(building+'\n')
	for room in keys[building]:
		print(room)
		curr = data[room.rstrip()]
		write_file.write(str(room[:-1])+'\n')
		write_file.write(str(curr['capacity'])+'\n')
		for i in range(48):
			write_file.write(str(curr['hour{}'.format(i+1)]['people'])+'\n')
			write_file.write(','.join(curr['hour{}'.format(i+1)]['names'])+'\n')

write_file.close()
