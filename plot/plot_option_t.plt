set term pngcairo enhanced size 1200,1000
set output 'output/output_option_t.png'
set encoding utf8

set margins 10, 10, 7, 5
set yrange [-10:6000]
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
plot 'data/data_t.dat' using 2:xtic(1) lc "#00ffff" t "Total routes" , '' using 3 lc "#00bfff" t "First town" 

set output