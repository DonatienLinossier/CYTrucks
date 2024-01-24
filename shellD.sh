#!/bin/bash
temp=temp/

processD1() {
    echo Process D1 on file $1
    now=`date +%s`
    
    tail +2 $1 | awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) printf "%d;%s\n", count[driver], driver}' | sort -k1nr | head -10 > temp/D1.txt

    nowB=`date +%s`

    cat < temp/D1.txt # La anto

    echo "Process lasted $((nowB - now)) seconds."
}

processD2() {
    echo Process D2 on file $1
    now=`date +%s`
    
    #LC_NUMERIC=C sets the awk to use a period . as the decimal separator.
    tail +2 $1 | LC_NUMERIC=C awk -F';' '{sum[$6]+=$5} END {for (driver in sum) printf "%f;%s\n", sum[driver], driver}' | sort -k1nr | head -10 > temp/D2.txt

    nowB=`date +%s`

    cat < temp/D2.txt # La anto
    echo "Process lasted $((nowB - now)) seconds."
}

processL() {
    echo Process L on file $1
    now=`date +%s`
    
    tail +2 $1 | LC_NUMERIC=C awk -F';' '{sumTrajet[$1]+=$5} END {for (trajet in sumTrajet) print "%f;%s\n", sumTrajet[trajet], trajet}' | sort -k1nr | head -10 | sort -k2n > temp/D3.txt

    nowB=`date +%s`

    cat < temp/D3.txt # La anto
 
    echo "Process lasted $((nowB - now)) seconds."
}

#For process T  
#Output : 'nbOfTrajectTotal(nbvilleB + nbvillaA if stepID==1) nbStartOfTraject(nbVilleA if stepId==1) ville'


#tail +2 ../data/data.csv | awk -F';' '{if ($2==1) nbdb[$3]++; sum[$4]++} END {for (driver in sum) print sum[driver]+nbdb[driver], 0+nbdb[driver], driver}
#' | sort -k1nr > ../temp/testS.txt

#D2 $filename
#D1 awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) print count[driver], driver}' data.csv | sort -k1,1nr > driver_routes_sorted.txt
#D2 awk -F';' '{sum[$6]+=$5} END {for (driver in sum) print sum[driver], driver}' data.csv | sort -k1,1nr > driver_distance_sorted.txt