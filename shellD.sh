#!/bin/bash


traitement_D1() {
    echo lancement du traitement D1...
    awk -F';' '{printf "%s;%d\n", $6, $1}' sample.csv | tail -n +2 > temp/tmpD1.csv
    ./progc/main
}



traitement_D2() {
    echo lancement du traitement D2...
    awk -F ';' 'BEGIN{OFS=";"; LC_NUMERIC="C"} {printf "%s;%.3f\n", $6, $5}' sample.csv | tail -n +2 > temp/tmpD2.csv
}

traitement_D2

#D1 awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) print count[driver], driver}' data.csv | sort -k1,1nr > driver_routes_sorted.txt
#D2 awk -F';' '{sum[$6]+=$5} END {for (driver in sum) print sum[driver], driver}' data.csv | sort -k1,1nr > driver_distance_sorted.txt