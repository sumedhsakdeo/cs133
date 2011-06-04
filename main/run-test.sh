#!/bin/bash
make clean
make run-test DATA_SIZE=10
make clean
make run-test POOL_CNT=100
make clean
make run-test POOL_CNT=1000
make clean
make run-test POOL_CNT=10000
