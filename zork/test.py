#! /usr/bin/env python

import os
import sys


tmp_output = "tmp.output"
executable = "a.out"

def print_header(test_case):

	print("************************ " + test_case + " *********************************")

def _test_exe(test_case):
	xml_file_path = "samples/" + test_case + "sample.xml"
	input_file_path = "samples/" + test_case + "sample.txt"
	output_file_path = "samples/" + test_case + "sample.out"

	print_header("Test " + test_case)

	exe_command = "./" + executable + " " + xml_file_path + " < " + input_file_path + " > " + tmp_output
	os.system(exe_command)

	diff_comand = "diff -y " + tmp_output + " " + output_file_path
	os.system(diff_comand)

	print("\n")

def test_all():
	
	test_list = ["room", "item", "container"]

	for test_case in test_list:
		_test_(test_case)

def test_room():
	_test_exe("room")


def test_item():
	_test_exe("item")


def test_container():
	_test_exe("container")

def _test_(test_case):
	
	if test_case == "item":
		test_item()
	elif test_case == "room":
		test_room()
	elif test_case == "container": 
		test_container()
	else:
		print("Test Case not recgonized")




if __name__ == "__main__":

	if os.path.isfile(executable):
		os.remove(executable)
	
	compile_command = "g++ -g main.cpp base.cpp room.cpp trigger.cpp turnon.cpp item.cpp creature.cpp container.cpp border.cpp condition.cpp attack.cpp"
	os.system(compile_command)
	
	if not os.path.isfile(executable):
		print("Compile failed")
		sys.exit()


	if len(sys.argv) < 2:
		test_all()
		sys.exit()

	if sys.argv[1] == "all":
		test_all()
		sys.exit()

	for ct in range(1,len(sys.argv)):
		_test_(sys.argv[ct])


