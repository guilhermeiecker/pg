#! /usr/bin/tclsh
# vim: autoindent shiftwidth=2 softtabstop=2 tabstop=2 :

set MAXRUNS 3;

set VAL_ALGOS {1}
set VAL_NODES {4 8 16 32 64}
set VAL_LINKS {4 8 16 32}

puts stderr "uhulll" 
foreach ALGO $VAL_ALGOS {
	#exec cat > /homesim/guilherme/resultado-$ALGO.txt
	foreach NODE $VAL_NODES {
		foreach LINK $VAL_LINKS {
			set RUN 1
			while {$RUN <= $MAXRUNS} {
				puts stdout "merging file /homesim/guilherme/resultado-$ALGO-$NODE-$LINK-$RUN.txt"
				exec cat /homesim/guilherme/resultado-$ALGO-$NODE-$LINK-$RUN.txt >> /homesim/guilherme/resultado-$ALGO.txt
				exec echo "\t" >> /homesim/guilherme/resultado-$ALGO.txt
				incr RUN
			}
			exec echo "\n" >> /homesim/guilherme/resultado-$ALGO.txt
		}
	}
}      
