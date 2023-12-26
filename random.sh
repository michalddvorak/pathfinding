#!/bin/bash
algos=(bfs dfs random astar greedy)
files=(datasets/72.txt datasets/26.txt datasets/36.txt datasets/38.txt)
while true
do
	algo=$(($RANDOM % 5))
	./cmake-build-debug/pathfinding ${files[$RANDOM % 3]} ${algos[algo]} -n rudl -s 40
	echo "Algorithm: ${algos[algo]}"
	sleep 5
done
