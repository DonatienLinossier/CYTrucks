if (!exists("filename")) filename='data/data_d1.dat'

if (!exists("out")) out='output/output_option_d1.png'

set term pngcairo enhanced size 800,600
set output out
set encoding utf8


set margins 10, 10, 5, 5
set yrange [0:220]


set style data histogram
set style histogram cluster gap 1
set style fill transparent solid 0.25
set boxwidth 0.8

set xtics format ""
set grid ytics

unset title


set label "Option -d1 : Nb routes = f(Driver)" at screen 0.05,0.5 center rotate by 90 font ",20" 

set xlabel "DRIVER NAMES"font ",18" rotate by -180 center offset 0,1
set xtics rotate by 90 offset 0,1.5 font ",15"


set ytics mirror rotate by 90 offset 75,0 font ",15" center
set ylabel "NB ROUTES"font ",18" rotate by 90 center offset 85,0



set datafile separator ";"
plot filename using 1:xtic(2):xticlabels(2) lc "#00ffff"  notitle with boxes

set output