#1/bin/bash

case $1 in
	compile)
		g++ pong.cpp -std=c++11 -o pong.out
		;;
	run)
		./pong.out
		;;
	clean)
		rm pong.out
		;;
	*)
		echo command invalid or missing
		;;
esac