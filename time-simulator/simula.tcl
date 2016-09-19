#! /usr/bin/tclsh
# vim: autoindent shiftwidth=2 softtabstop=2 tabstop=2 :

set MAXRUNS 30;
set MAXLINKS 64;

set VAL_NODES {128}

foreach NODE $VAL_NODES {
	set LINK 4
	while {$LINK <= $MAXLINKS} {
		exec printf "$LINK\t" >> results/result-iterative-$NODE.txt
		exec printf "$LINK\t" >> results/result-recursive-$NODE.txt
		set RUN 0
		while {$RUN <= $MAXRUNS} {
		  puts stderr "running iterative for n=$NODE m=$LINK r=$RUN"
			exec ./iterative $NODE $LINK $RUN n$NODE.txt >> results/result-iterative-$NODE.txt
			puts stderr "running recursive for n=$NODE m=$LINK r=$RUN"
			exec ./recursive $NODE $LINK $RUN n$NODE.txt >> results/result-recursive-$NODE.txt
			exec printf "\t" >> results/result-iterative-$NODE.txt
			exec printf "\t" >> results/result-recursive-$NODE.txt
			incr RUN
		}
		exec printf "\n" >> results/result-iterative-$NODE.txt
		exec printf "\n" >> results/result-recursive-$NODE.txt
		incr LINK
	}
}
