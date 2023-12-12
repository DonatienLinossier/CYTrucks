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

D1() {
    echo lancement du traitement D1 without c...
    now=`date +%s`
    
    awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) print count[driver], driver}' data.csv | sort -k1nr | head -10 > D1.txt

    nowB=`date +%s`
    echo $((nowB - now))
    cat < D1.txt
}

D2() {
    echo lancement du traitement D2 without c...
    now=`date +%s`
    
    awk -F';' '{sum[$6]+=$5} END {for (driver in sum) print sum[driver], driver}' data.csv | sort -k1nr | head -10 > D2.txt

    nowB=`date +%s`

    cat < D2.txt
    echo $((nowB - now))
}

D2Bis() {
    # Echo a message indicating the start of the processing
    echo "lancement du traitement D2 without c..."

    # Record the current timestamp
    now=`date +%s`

    # Use cut to extract columns 6 and 5 from data.csv and save the result in ff.txt
    cut -d ';' -f 6,5 data.csv > ff.txt

    # Record the current timestamp again
    nowB=`date +%s`

    # Display the contents of a file named D2.txt (This should be ff.txt instead based on your script)
    cat < D2.txt

    # Calculate and echo the time taken for processing
    echo $((nowB - now))
}

D2Bis
#D1 awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) print count[driver], driver}' data.csv | sort -k1,1nr > driver_routes_sorted.txt
#D2 awk -F';' '{sum[$6]+=$5} END {for (driver in sum) print sum[driver], driver}' data.csv | sort -k1,1nr > driver_distance_sorted.txt