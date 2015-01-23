#!/bin/bash
suppressions=""
for i in $(ls ../src/valgrind/*.supp)
do
  suppressions="$suppressions --suppressions=$i"
done

echo $suppressions

valgrind $suppressions \
         --show-leak-kinds=all \
         --leak-check=full \
         --gen-suppressions=all \
         --log-file=valgrind.log \
         ./bin/friesian
