if (!exists("filename")) filename='data/data_s.dat'

if (!exists("out")) out='output/output_option_s.png'

set term pngcairo enhanced size 1600,1200
set output out
set encoding utf8


set margins 7, 5, 5, 5
set style data lines
set title font ",15"
set style fill transparent solid 0.25

set title "Option -s : Distance = f(Route)" 

set xrange [ 1 : * ]
set xtics rotate by 45 center font ",12" offset -1,-1 

 

set yrange [ -1 : 1000 ]
set ytics 100


set datafile separator ";"
plot filename using 1:3:5 with filledcurves lc "#00ffff" t "Distances Max/Min (Km)", \
	'' using 1:4 linecolor -1 t "Distances average (Km)" ,\
	'' using 1:2:xticlabels(2) notitle 

