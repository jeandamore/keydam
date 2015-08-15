import csv
import sys

if len(sys.argv) == 2:
	filename = sys.argv[1]
else:
	print "Incorrect number of arguments. Usage : python ./extract_key_dynamics.py <csv_filepath>"
	sys.exit()

csvfile = open(filename,"rb")
keypresslist = []
reader = csv.reader(csvfile)
for row in reader:
	keypresslist.append(row)

keydynamics=[]
keydynamics.append(["key_code","keypress_duration","key_interval"])
listlen = len(keypresslist)

for i in range(listlen-1):
	action, key, timestamp = keypresslist[i]
	if action == "10":
		for j in range(i+1,listlen):
			if keypresslist[j][0] == "11":
				presstime = int(keypresslist[j][2]) - int(timestamp)
				break
		for j in range(i+1,listlen):
			if keypresslist[j][0] == "10":
				nexttime = int(keypresslist[j][2]) - int(timestamp)
				break
		keydynamics.append( [ key, presstime, nexttime ] )


with open("keystoke_dynamics.csv", "wb") as outputcsv:
    writer = csv.writer(outputcsv)
    writer.writerows(keydynamics)

print "%i rows written to keystoke_dynamics.csv" % len(keydynamics)