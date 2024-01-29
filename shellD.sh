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
    
    #LC_NUMERIC=C sets the awk to use a period . as the decimal separator.
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

processT() {
    echo Process T on file $1
    now=`date +%s`
    

    #Pre traitement temp : 
    #Output : 'nbOfTrajectTotal(nbvilleB + nbvillaA if stepID==1) nbStartOfTraject(nbVilleA if stepId==1) ville'


    
    #PB : marseille peut apparaitre pls fois dans un meme trajet. (DOnc vérifier que chaque n'a jamais été vu ) !seen[$1,$3]


    #tail +2 $1 | awk -F';' '{if ($2==1) nbdb[$3]++;} {!seen[$1,$4]++ sum[$4]++} END {for (driver in sum) printf "%d;%d;%s\n", sum[driver]+nbdb[driver], 0+nbdb[driver], driver}' > temp/TtempC.txt
    #Il reste à enlever le cas ou la ville de départ du trajet est une ville par laquelle on repasse par la suite
    #Le cas on ou passe 2 fois par une ville dans le trajet(hors ville de départ est géré)




    #Proposition de solution, A TESTER !!

    #Si stepID == 1 (donc premiere etape d'un trajet) {
    #   +1 au nombre fois que la villeA est ville départ
    #   +1 au nombre de fois que la villeA est traversée
    #   ajout du duo [cityA($3), ROUTEID]
    #}
    #
    #Si duo [cityB($4), ROUTEID] jamais vu {
    #   +1 au nombre de fois que la villeB est traversée
    #   ajout du duo [cityB($3), ROUTEID]
    #}
    #Une fois le traitement fini
    #For chaque ville
    #   printf "%d;%d;%s", nbOfTraject[city], 0+nbdb[city], city
    tail +2 $1 | awk -F';'
    '{
        if($2==1)
        {
            nbdb[$3]++;
            nbOfTraject[$3]++;
            seen[$3;$1]++;
        }

        if(!seen[$4;$1])
        {
            nbOfTraject[$4]++;
            seen[$4;$1]++;
        }
        END 
        {
            for (city in nbOfTraject)
            {
                printf "%d:%d;%s", nbOfTraject[city], 0+nbdb[city], city
            }
        }
    }' > temp/TtempC.txt

    #Lancer le vrai traitement ici


    nowB=`date +%s`
    echo "Process lasted $((nowB - now)) seconds."

}
#For process T  
#Output : 'nbOfTrajectTotal(nbvilleB + nbvillaA if stepID==1) nbStartOfTraject(nbVilleA if stepId==1) ville'


#tail +2 ../data/data.csv | awk -F';' '{if ($2==1) nbdb[$3]++; sum[$4]++} END {for (driver in sum) print sum[driver]+nbdb[driver], 0+nbdb[driver], driver}
#' | sort -k1nr > ../temp/testS.txt

#D2 $filename
#D1 awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) print count[driver], driver}' data.csv | sort -k1,1nr > driver_routes_sorted.txt
#D2 awk -F';' '{sum[$6]+=$5} END {for (driver in sum) print sum[driver], driver}' data.csv | sort -k1,1nr > driver_distance_sorted.txt