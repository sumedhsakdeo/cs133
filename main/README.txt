-------------------------------------------------------------------
CS133 Project
-------------------------------------------------------------------
Team: 
Aditya Bhiday
Sudeep Pradhan
Sumedh Sakdeo 
Shashwat Purushottam

-------------------------------------------------------------------

Directory Structure of the tarball

${ROOT_FOLDER}/inc/*:      All the header files
${ROOT_FOLDER}/src/*:      All the source files
${ROOT_FOLDER}/test/*:     All the test files
${ROOT_FOLDER}/obj/*:      All the source and test binaries
${ROOT_FOLDER}/Makefile

-------------------------------------------------------------------

Compilation Instructions

Requirements

Softwares installed g++, pthreads.


1. Compile Source!

Run 'make' command inside ${ROOT_FOLDER}. Make command will generate all the
source in ${ROOT_FOLDER}/obj folder.

2. Compile Source & Tests!

Run 'make test' command inside ${ROOT_FOLDER}. Make test command will generate
all the source and test binaries in ${ROOT_FOLDER}/obj and also run python scripts
to generate input files for testing.

3. Run All Tests!

Run 'make run-test' command inside ${ROOT_FOLDER}. Make run test command will
do everything as in option 2 plus will run all the test cases for serial and 
parallel versions of arithmetic and bitwise. 
Example output:
   MULT =>
   Serial:
   49735925 (time taken in micro seconds)

   Parallel:
   7725922 (time taken in micro seconds)

4. Run Individual Tests!

Run 'make run-*' command works like option 3, with a difference that it runs
specified operation.
Example usage:
   make run-add, make run-sub, make run-mult, make run-div, 
   make run-and, make run-or, make run-xor, make run-not, make run-eq,
   make run-lshift, make run-rshift

-------------------------------------------------------------------
