#!/usr/bin/env python3
DESTINATION = "../data/schedule.json"
BUILDINGS_PATH = "../data/"
BUILDINGS = ["cushing.txt", "fitzpatrick.txt", "duncan.txt", "stinson.txt"]
wf = open(DESTINATION, "w")
rooms = []

year = input("Year: ")
month = input("Month: ")
day = input("Day: ")
hour = input("Hour: ")

for building in BUILDINGS:
	odd = True
	for room in open(BUILDINGS_PATH+building):
		if len(room) <= 1:
			break
		room = room.rstrip()
		if odd:
			rooms.append({})
			rooms[len(rooms)-1]['name'] = room
		else:
			rooms[len(rooms)-1]['capacity'] = room
		odd = not odd
first = True
wf.write("{\n")
for room in rooms:
	if first:
		first = False
	else:
		wf.write(",\n")
	wf.write("\t\""+room['name']+"\":{\n")
	wf.write("\t\t\"year\":{},\n".format(year))
	wf.write("\t\t\"month\":{},\n".format(month))
	wf.write("\t\t\"day\":{},\n".format(day))
	wf.write("\t\t\"hour\":{},\n".format(hour))
	wf.write("\t\t\"capacity\":{},\n".format(room['capacity']))
	for i in range(48):
		wf.write("\t\t\"hour"+str(i+1)+"\":{\n")
		wf.write("\t\t\t\"people\":0,\n")
		wf.write("\t\t\t\"names\":[]\n")
		wf.write("\t\t}")	
		if i != 47:
			wf.write(",\n")
	wf.write("\n\t}")
wf.write("\n}")
