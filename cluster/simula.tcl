#! /usr/bin/tclsh
# vim: autoindent shiftwidth=2 softtabstop=2 tabstop=2 :

set MAXRUNS 30;

set VAL_ALGOS {1 2 3 4 5 6}
set VAL_NODES {4 8 16 64}
set VAL_LINKS {4 8 16 64}

foreach ALGO $VAL_ALGOS {
	foreach NODE $VAL_NODES {
		foreach LINK $VAL_LINKS {
			set RUN 1
			while {$RUN <= $MAXRUNS} {
				puts stderr "./scheduling $ALGO $NODE $LINK $RUN"
				#exec qsub -e /dev/null -o /homesim/guilherme/resultado-$ALGO-$NODE-$LINK-$RUN.txt -V -b y -cwd -shell n ./scheduling$ALGO $NODE $LINK
				
				if {$RUN == 1} {
					exec printf "$ALGO\t$NODE\t$LINK\t" >> results/resultado-$ALGO.txt
				}
				
				exec ./scheduling$ALGO $NODE $LINK >> results/resultado-$ALGO.txt
				exec printf "\t" >> results/resultado-$ALGO.txt
				
				incr RUN
			}
			exec printf "\n" >> results/resultado-$ALGO.txt		
		}
	}
}      
