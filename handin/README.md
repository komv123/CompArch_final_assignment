# Group 42 Final assignment
- Adam Kalocsai - s215236
- Lovro Antic - s235263
- Weihao Mo - s235284
  
## Usage
### Compile
To compile the simulator run:
```bash
make
```
or
```bash
gcc gr42_riscv_sim.c -o gr42
```

### Run tests
To run a single test, run:
```bash
./gr42 <test_file>.bin
```
The Makefile can run the provided tests and compare the results in the following bundles:
```bash
make test_all
```
- ```test_all``` runs all tests provided in task1-4 and compares the reults with the tests
- ```task1``` runs all tests in task1 and compares the reults with the tests
- ```task2``` runs all tests in task2 and compares the reults with the tests
- ```task3``` runs all tests in task3 and compares the reults with the tests
- ```task4``` runs all tests in task4 and compares the reults with the tests
- ```clean``` deletes the compiled simulator