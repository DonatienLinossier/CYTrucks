#!/bin/bash
temp=temp/

processD1() {
    echo Process D1 on file $1
    now=`date +%s`
    
    tail +2 $1 | awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) print count[driver], driver}' | sort -k1nr | head -10 > temp/D1.txt

    nowB=`date +%s`
    cat < temp/D1.txt
    echo "Process lasted $((nowB - now)) seconds."
}

processD2() {
    echo Process D2 on file $1
    now=`date +%s`
    
    tail +2 $1 | awk -F';' '{sum[$6]+=$5} END {for (driver in sum) print sum[driver], driver}' | sort -k1nr | head -10 > temp/D2.txt

    nowB=`date +%s`

    cat < temp/D2.txt
    echo "Process lasted $((nowB - now)) seconds."
}

processL() {
    echo Process L on file $1
    now=`date +%s`
    
    tail +2 $1 | awk -F';' '{sum[$1]+=$5} END {for (driver in sum) print sum[driver], driver}' | sort -k1nr | head -10 > temp/D3.txt

    nowB=`date +%s`

    cat < temp/D3.txt
 
    echo "Process lasted $((nowB - now)) seconds."
}

#D2 $filename
#D1 awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) print count[driver], driver}' data.csv | sort -k1,1nr > driver_routes_sorted.txt
#D2 awk -F';' '{sum[$6]+=$5} END {for (driver in sum) print sum[driver], driver}' data.csv | sort -k1,1nr > driver_distance_sorted.txt