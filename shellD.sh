#!/bin/bash
temp=temp/



startTime() {
        start_time=`date +%s.%N`
}

exitTime() {
        end_time=`date +%s.%N`
        x=$(echo "$end_time - $start_time" | bc)
                
        if [ "$(echo "$x<1" | bc)" -eq 1 ];then
                echo execution time was 0$x s 
        else
                echo execution time was $x s 
        fi

        if [ "$1" -eq 1 ]; then
            exit 1
        else echo
        fi
}

processD1() {
    echo Process D1 on file $1
    
    startTime

    tail +2 $1 | awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) printf "%d;%s\n", count[driver], driver}' | sort  -t ";" -k1nr | head -10 > temp/D1plot.txt
    
    exitTime 0

    gnuplot -e "filename='temp/D1plot.txt'" -e "out='images/d1PlotOutput.png'" plot/plot_option_d1.plt

    mogrify -rotate 90 'images/d1PlotOutput.png'

}

processD2() {
    echo Process D2 on file $1

    startTime
    
    tail +2 $1 | LC_NUMERIC=C awk -F';' '{sum[$6]+=$5} END {for (driver in sum) printf "%f;%s\n", sum[driver], driver}' | sort -t ";" -k1nr | head -10 > temp/D2plot.txt

    exitTime 0

    gnuplot -e "filename='temp/D2plot.txt'" -e "out='images/d2PlotOutput.png'" plot/plot_option_d2.plt
    
    mogrify -rotate 90 'images/d2PlotOutput.png'

}

processL() {
    echo Process L on file $1

    startTime
    
    tail +2 $1 | LC_NUMERIC=C awk -F';' '{sumTrajet[$1]+=$5} END {for (trajet in sumTrajet) printf "%f;%s\n", sumTrajet[trajet], trajet}' | sort -t ";" -k1nr | head -10 | sort -t ";" -k2n > temp/Lplot.txt

    exitTime 0

    gnuplot -e "filename='temp/Lplot.txt'" -e "out='images/lPlotOutput.png'" plot/plot_option_l.plt
}

processS() {


    echo Process S on file $1
    startTime


    exitTime 0
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
