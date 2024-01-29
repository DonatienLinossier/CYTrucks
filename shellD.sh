#!/bin/bash
temp=temp/

processD1() {
    echo Process D1 on file $1
    now=`date +%s`
    
    tail +2 $1 | awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) printf "%d;%s\n", count[driver], driver}' | sort  -t ";" -k1nr | head -10 > temp/D1plot.txt

    nowB=`date +%s`

    cat < temp/D1plot.txt # La anto

    echo "Process lasted $((nowB - now)) seconds."
}

processD2() {
    echo Process D2 on file $1
    now=`date +%s`
    
    tail +2 $1 | LC_NUMERIC=C awk -F';' '{sum[$6]+=$5} END {for (driver in sum) printf "%f;%s\n", sum[driver], driver}' | sort -t ";" -k1nr | head -10 > temp/D2plot.txt

    nowB=`date +%s`

    cat < temp/D2plot.txt # La anto
    echo "Process lasted $((nowB - now)) seconds."
}

processL() {
    echo Process L on file $1
    now=`date +%s`
    
    tail +2 $1 | LC_NUMERIC=C awk -F';' '{sumTrajet[$1]+=$5} END {for (trajet in sumTrajet) printf "%f;%s\n", sumTrajet[trajet], trajet}' | sort -t ";" -k1nr | head -10 | sort -t ";" -k2n > temp/Lplot.txt

    nowB=`date +%s`

    cat < temp/Lplot.txt # La anto
 
    echo "Process lasted $((nowB - now)) seconds."
}

processS() {


    echo Process S on file $1
    now=`date +%s`

    echo 'not done yet'

    nowB=`date +%s`
    echo "Process lasted $((nowB - now)) seconds."
}

processT() {


    echo Process T on file $1
    now=`date +%s`


    #PreTreatement
    #if stepID == 1 (is city first step?) {
    #   +1 au nombre fois que la villeA est ville départ
    #   Si duo [cityA($3), ROUTEID] jamais vu {
    #       +1 au nombre de fois que la villeA est traversée
    #       ajout du duo [cityA($3), ROUTEID]
    #   }
    #}
    #
    #Si duo [cityB($4), ROUTEID] jamais vu {
    #   +1 au nombre de fois que la villeB est traversée
    #   ajout du duo [cityB($3), ROUTEID]
    #}
    #Une fois le traitement fini
    #For chaque ville
    #   printf "%d;%d;%s", nbOfTraject[city], 0+nbdb[city], city
    tail +2 $1 | awk -F';' '{
        if ($2 == 1) {
            nbdb[$3]++;
            if(!seen[$3,$1]) {
                nbOfTraject[$3]++;
                seen[$3,$1]++;
            }
        }
        if (!seen[$4,$1]) {
            nbOfTraject[$4]++;
            seen[$4,$1]++;
        }
    }
    END {
        for (city in nbOfTraject) {
            printf "%d:%d;%s\n", nbOfTraject[city], 0+nbdb[city], city;
        }
    }' > temp/TtempC.txt

    nowB=`date +%s`
    echo "Process lasted $((nowB - now)) seconds."
}