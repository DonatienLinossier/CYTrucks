if (!exists("filename")) filename='data/data_t.dat'

if (!exists("out")) out='output/output_option_t.png'

set term pngcairo enhanced size 1200,1000
set output out
set encoding utf8



set margins 10, 10, 7, 5
set yrange [-10:3500]
set ytics 1000

set style data histogram
set style histogram cluster gap 4
set style fill transparent solid 1
set boxwidth 3

set grid ytics

set xtics rotate by 45 center font ",12" right


set title "Option -t : Nb routes = f(Towns)" font ",20"
set ylabel "NB ROUTES" font ",15"
set xlabel "TOWN NAMES" font ",15" offset 0,-1



set datafile separator ";"
plot filename using 2:xtic(1) lc "#00ffff" t "Total routes" , '' using 3 lc "#000fff" t "First town" 

set output