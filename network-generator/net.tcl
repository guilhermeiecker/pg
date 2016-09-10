#! /usr/bin/tclsh
# vim: autoindent shiftwidth=2 softtabstop=2 tabstop=2 :

set S 6210;

while {$S < 35010} {
  puts stderr "./network 128 $S"
  exec ./network 128 $S >> net128.txt
  exec printf "\t" >> net128.txt
  set S [expr {$S + 10}]
}
