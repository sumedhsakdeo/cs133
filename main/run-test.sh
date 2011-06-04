#!/bin/bash
make clean
make run-test DATA_SIZE=10
make clean
make run-test DATA_SIZE=100
make clean
make run-test DATA_SIZE=1000
make clean
make run-test DATA_SIZE=10000
