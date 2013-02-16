import os
import sys
import argparse

def parse_command_line():
	parser = argparse.ArgumentParser()
	parser.add_argument("-f", "--filename", dest="file_number", required=True)
	return parser.parse_args()

def main(argv=None):
	args = parse_command_line()
	iterations = 20
	# number to start results output from, runX
	# run1, run2, run3, etc...
	initial = int(args.file_number) 
	
	for i in range(initial, initial + iterations):
		# run the C code to actually time the filesystem
		arg = " %d" % i
		os.system(arg)
	return 0

if __name__ == '__main__':
	status = main()
	sys.exit(status)

