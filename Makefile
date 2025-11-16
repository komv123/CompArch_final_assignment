.SILENT:

srcs = simsource/main.c
name = main

all: compile

compile: 
	gcc $(srcs) -o $(name)
	echo "Output file can be found at ./$(name)"

task1:
	echo "\nTask 1"
	echo "Test 1: addlarge"
	./$(name) ./tests/task1/addlarge.bin
	echo "\nTest 2: addneg"
	./$(name) ./tests/task1/addneg.bin
	echo "\nTest 3: addpos"
	./$(name) ./tests/task1/addpos.bin
	echo "\nTest 4: bool"
	./$(name) ./tests/task1/bool.bin
	echo "\nTest 5: set"
	./$(name) ./tests/task1/set.bin
	echo "\nTest 6: shift"
	./$(name) ./tests/task1/shift.bin
	echo "\nTest 7: shift2"
	./$(name) ./tests/task1/shift2.bin

task2:
	echo "\nTask 2"
	echo "Test 1: branchcnt"
	./$(name) ./tests/task2/branchcnt.bin
	echo "\nTest 2: branchmany"
	./$(name) ./tests/task2/branchmany.bin
	echo "\nTest 3: branchtrap"
	./$(name) ./tests/task2/branchtrap.bin

task3:
	echo "\nTask 3"
	echo "Test 1: loop"
	./$(name) ./tests/task3/loop.bin
	echo "\nTest 2: recursive"
	./$(name) ./tests/task3/recursive.bin
	echo "\nTest 3: string"
	./$(name) ./tests/task3/string.bin
	echo "\nTest 4: width"
	./$(name) ./tests/task3/width.bin

task4:
	echo "\nTask 4"
	echo "Test 1: t1"
	./$(name) ./tests/task4/t1.bin
	echo "\nTest 2: t2"
	./$(name) ./tests/task4/t2.bin
	echo "\nTest 3: t3"
	./$(name) ./tests/task4/t3.bin
	echo "\nTest 4: t4"
	./$(name) ./tests/task4/t4.bin
	echo "\nTest 5: t5"
	./$(name) ./tests/task4/t5.bin
	echo "\nTest 6: t6"
	./$(name) ./tests/task4/t6.bin
	echo "\nTest 7: t7"
	./$(name) ./tests/task4/t7.bin
	echo "\nTest 8: t8"
	./$(name) ./tests/task4/t8.bin
	echo "\nTest 9: t9"
	./$(name) ./tests/task4/t9.bin

test_all:
	echo "Running all tests"
	$(MAKE) task1
	$(MAKE) task2
	$(MAKE) task3
	$(MAKE) task4

clean:
	rm ./$(name)

.PHONY : clean compile task1 task2 task3 task4 test_all