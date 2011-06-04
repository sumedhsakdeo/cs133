#!/bin/bash
make run-test POOL_CNT=1 BLOCK_SIZE=120
make run-test POOL_CNT=2 BLOCK_SIZE=120
make run-test POOL_CNT=4 BLOCK_SIZE=120
make run-test POOL_CNT=8 BLOCK_SIZE=120
