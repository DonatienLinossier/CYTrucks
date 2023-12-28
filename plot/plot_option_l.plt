set term pngcairo enhanced size 1200,1000
set output 'output/output_option_l.png'
set encoding utf8

set margins 10, 10, 7, 5
set yrange [0:3000]
set ytics 500

set style data histogram
set style fill transparent solid 0.25
set boxwidth 0.8

set grid ytics


set title "Option -l : Distance = f(Route)" font ",20"
set ylabel "DISTANCE (Km)" font ",15"
set xlabel "ROUTE ID" font ",15" offset 0,-1


set datafile separator ";"
plot 'data/data_l.dat' using 2:xtic(1) lc "#00ffff" notitle with boxes

set output