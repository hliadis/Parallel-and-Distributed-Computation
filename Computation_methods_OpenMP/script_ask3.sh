NUM_THR=1

for i in 1 2 3 4
do
  export OMP_NUM_THREADS=$NUM_THR
  
  for j in 1 2 3
  do
    echo "num of threads $NUM_THR" >> logfile_ask3.txt
    ./ask3 >> logfile_ask3.txt
  done
    NUM_THR=$((2*NUM_THR))
done
