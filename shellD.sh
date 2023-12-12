#!/bin/bash
temp=temp/


if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi



filename="data/$1"

if [ -f "$filename" ]; then
    echo "File $filename exists."
else
    echo "File $filename does not exist."
    exit 1
fi 



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
    
    tail +2 $1 | awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) print count[driver], driver}' | sort -k1nr | head -10 > temp/D1.txt

    nowB=`date +%s`
    echo $((nowB - now))
    cat < D1.txt
}

D2() {
    echo lancement du traitement D2 without c...
    now=`date +%s`
    
    tail +2 $1 | awk -F';' '{sum[$6]+=$5} END {for (driver in sum) print sum[driver], driver}' | sort -k1nr | head -10 > temp/D2.txt

    nowB=`date +%s`

    cat < temp/D2.txt
    echo $((nowB - now))
}


#Equivalent speed as D2Bis
D2Bis() {
    # Echo a message indicating the start of the processing
    echo "lancement du traitement D2 without c..."

    # Record the current timestamp
    now=`date +%s`

    # Use cut to extract columns 6 and 5 from data.csv and save the result in ff.txt
    tail +2 $1 | cut -d ';' -f 5,6 | awk -F ';' '{count[$2]+=$1} END {for (elt in count) print elt, count[elt]}' | sort -k3nr | head -10 > temp/D2Bis.csv

    # Record the current timestamp again
    nowB=`date +%s`

    # Display the contents of a file named D2.txt (This should be ff.txt instead based on your script)
    cat < temp/D2Bis.txt

    # Calculate and echo the time taken for processing
    echo $((nowB - now))
}

D2 $filename
#D1 awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) print count[driver], driver}' data.csv | sort -k1,1nr > driver_routes_sorted.txt
#D2 awk -F';' '{sum[$6]+=$5} END {for (driver in sum) print sum[driver], driver}' data.csv | sort -k1,1nr > driver_distance_sorted.txt