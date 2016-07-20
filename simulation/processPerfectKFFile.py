
import sys
def process_file (source_name, dest_name):
	sf = open (source_name, 'r')
	df = open (dest_name, 'w')
	for line in sf:
		pr = line.split(",")
		for i in range(len(pr) - 1):
			df.write(pr[i]+",")
		df.write(pr[len(pr) - 1])
		df.write("\0")
	sf.close()
	df.close()
def main ():
	process_file('perfectKF.txt', 'dest.txt')
main()

	
