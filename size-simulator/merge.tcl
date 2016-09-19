#! /usr/bin/tclsh
# vim: autoindent shiftwidth=2 softtabstop=2 tabstop=2 :

set VAL_ALGOS {1 2 3 4 5 6}
set MAXRUNS 30
set RUN 1

exec printf "algorithm\tn\tm" >> resultado.txt

while {$RUN <= $MAXRUNS} {
	exec printf "\tr$RUN" >> resultado.txt
	incr RUN
}

exec printf "\n" >> resultado.txt
 
foreach ALGO $VAL_ALGOS {
	puts stdout "merging file resultado-$ALGO.txt"
	exec cat resultado-$ALGO.txt >> resultado.txt
	exec printf "\n" >> resultado-$ALGO.txt
}
