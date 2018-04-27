#!/usr/bin/env python3
import json

FILE = "schedule.json"
BUILDINGS_PATH = "/afs/nd.edu/user24/scattana/Public/"
BUILDINGS = ["cushing.txt", "fitzpatrick.txt", "duncan.txt", "stinson.txt"]
data = json.load(open(FILE))
keys = []
for building in BUILDINGS:
	odd = True;
	for room in open(BUILDINGS_PATH+building):
		if odd:
			keys.append(room)
		odd = not odd
