NUM_THR=1
CHUNK=10

for i in 1 2 3 4 
do
  export OMP_NUM_THREADS=$NUM_THR
  CHUNK=10
  for j in 1 2 3
  do
    echo "Static, Chunk: $CHUNK, Num of threads: $NUM_THR" >> stats.txt
    ./ask2 $CHUNK static $NUM_THR >> stats.txt 
    CHUNK=$((10*CHUNK))
  done
  NUM_THR=$((2*NUM_THR))
done

NUM_THR=1

for i in 1 2 3 4
do
  export OMP_NUM_THREADS=$NUM_THR
  CHUNK=10
  for j in 1 2 3
  do
    echo "Dynamic, Chunk: $CHUNK, Num of threads: $NUM_THR" >> stats.txt
    ./ask2 $CHUNK dynamic $NUM_THR >> stats.txt
    CHUNK=$((10*CHUNK))
  done
  NUM_THR=$((2*NUM_THR))
done

