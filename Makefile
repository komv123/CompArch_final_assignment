MAKEFLAGS += --no-print-directory
.SILENT:

srcs = simsource/main.c
name = main
compare = test_final_proj/02155_check_output.sh

all: compile

compile: 
	gcc $(srcs) -o $(name)
	echo "Output file can be found at ./$(name)"

task1:
	echo "\nTask 1"
	echo "Test 1: addlarge"
	./$(name) ./tests/task1/addlarge.bin
	./$(compare) tests/task1/addlarge.res results/addlarge.res
	echo "Test 2: addneg"
	./$(name) ./tests/task1/addneg.bin
	./$(compare) tests/task1/addneg.res results/addneg.res
	echo "Test 3: addpos"
	./$(name) ./tests/task1/addpos.bin
	./$(compare) tests/task1/addpos.res results/addpos.res
	echo "Test 4: bool"
	./$(name) ./tests/task1/bool.bin
	./$(compare) tests/task1/bool.res results/bool.res
	echo "Test 5: set"
	./$(name) ./tests/task1/set.bin
	./$(compare) tests/task1/set.res results/set.res
	echo "Test 6: shift"
	./$(name) ./tests/task1/shift.bin
	./$(compare) tests/task1/shift.res results/shift.res
	echo "Test 7: shift2"
	./$(name) ./tests/task1/shift2.bin
	./$(compare) tests/task1/shift2.res results/shift2.res

task2:
	echo "\nTask 2"
	echo "Test 1: branchcnt"
	./$(name) ./tests/task2/branchcnt.bin
	./$(compare) tests/task2/branchcnt.res results/branchcnt.res
	echo "Test 2: branchmany"
	./$(name) ./tests/task2/branchmany.bin
	./$(compare) tests/task2/branchmany.res results/branchmany.res
	echo "Test 3: branchtrap"
	./$(name) ./tests/task2/branchtrap.bin
	./$(compare) tests/task2/branchtrap.res results/branchtrap.res

task3:
	echo "\nTask 3"
	echo "Test 1: loop"
	./$(name) ./tests/task3/loop.bin
	./$(compare) tests/task3/loop.res results/loop.res
	echo "Test 2: recursive"
	./$(name) ./tests/task3/recursive.bin
	./$(compare) tests/task3/recursive.res results/recursive.res
	echo "Test 3: string"
	./$(name) ./tests/task3/string.bin
	./$(compare) tests/task3/string.res results/string.res
	echo "Test 4: width"
	./$(name) ./tests/task3/width.bin
	./$(compare) tests/task3/width.res results/width.res

task4:
	echo "\nTask 4"
	echo "Test 1: t1"
	./$(name) ./tests/task4/t1.bin
	./$(compare) tests/task4/t1.res results/t1.res
	echo "Test 2: t2"
	./$(name) ./tests/task4/t2.bin
	./$(compare) tests/task4/t2.res results/t2.res
	echo "Test 3: t3"
	./$(name) ./tests/task4/t3.bin
	./$(compare) tests/task4/t3.res results/t3.res
	echo "Test 4: t4"
	./$(name) ./tests/task4/t4.bin
	./$(compare) tests/task4/t4.res results/t4.res
	echo "Test 5: t5"
	./$(name) ./tests/task4/t5.bin
	./$(compare) tests/task4/t5.res results/t5.res
	echo "Test 6: t6"
	./$(name) ./tests/task4/t6.bin
	./$(compare) tests/task4/t6.res results/t6.res
	echo "Test 7: t7"
	./$(name) ./tests/task4/t7.bin
	./$(compare) tests/task4/t7.res results/t7.res
	echo "Test 8: t8"
	./$(name) ./tests/task4/t8.bin
	./$(compare) tests/task4/t8.res results/t8.res
	echo "Test 9: t9"
	./$(name) ./tests/task4/t9.bin
	./$(compare) tests/task4/t9.res results/t9.res

test_all:
	echo "Running all tests"
	$(MAKE) task1
	$(MAKE) task2
	$(MAKE) task3
	$(MAKE) task4

clean:
	rm ./$(name)

.PHONY : clean compile task1 task2 task3 task4 test_all