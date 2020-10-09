#1/bin/bash

case $1 in
	compile)
		g++ main.cpp -std=c++11 -o main.out
		;;
	run)
		./main.out
		;;
	clean)
		rm main.out
		;;
	*)
		echo command invalid or missing
		;;
esac