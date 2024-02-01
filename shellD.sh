#!/bin/bash
temp=temp/
plot=plot/
images=images/



EXECUTABLE="/progc/EXEC"


#test
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

D1plot=D1plot.txt
d1PlotOutput=d1PlotOutput.png
plot_option_d1=plot_option_d1.plt
processD1() {

    # Check if input file is provided
    if [ $# -ne 1 ]; then
        echo "Usage: -d1 <input_file>"
        return 1
    fi

    if [ ! -f "$1" ]; then
        echo "Error: Input file '$1' not found."
        return 1
    fi

    echo Process D1 on file $1
    
    startTime

    tail +2 $1 | awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) printf "%d;%s\n", count[driver], driver}' | sort  -t ";" -k1nr | head -10 > temp/D1plot.txt
    
    exitTime 0
    now=`date +%s`
    
    tail +2 $1 | awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) printf "%d;%s\n", count[driver], driver}' | sort  -t ";" -k1nr | head -10 > $temp$D1plot

    if [ ! -f "$temp$D1plot" ]; then
        echo "Error: couldn't generate $temp$D1plot."
        return 1
    fi

    nowB=`date +%s`

    gnuplot -e "filename='temp/D1plot.txt'" -e "out='images/d1PlotOutput.png'" plot/plot_option_d1.plt

    mogrify -rotate 90 "$images$d1PlotOutput"

    echo "Process lasted $((nowB - now)) seconds."
}





D2plot=D2plot.txt
d2PlotOutput=d2PlotOutput.png
plot_option_d2=plot_option_d2.plt
processD2() {

    # Check if input file is provided
    if [ $# -ne 1 ]; then
        echo "Usage: -d2 <input_file>"
        return 1
    fi

    if [ ! -f "$1" ]; then
        echo "Error: Input file '$1' not found."
        return 1
    fi


    echo Process D2 on file $1

    startTime
    
    tail +2 $1 | LC_NUMERIC=C awk -F';' '{sum[$6]+=$5} END {for (driver in sum) printf "%f;%s\n", sum[driver], driver}' | sort -t ";" -k1nr | head -10 > $temp$D2plot

    if [ ! -f "$temp$D2plot" ]; then
        echo "Error: couldn't generate $temp$D2plot."
        return 1
    fi

    exitTime 0

    gnuplot -e "filename='temp/D2plot.txt'" -e "out='images/d2PlotOutput.png'" plot/plot_option_d2.plt
    
    mogrify -rotate 90 'images/d2PlotOutput.png'

    echo "Process lasted $((nowB - now)) seconds."
}





lplot=lplot.txt
lPlotOutput=lPlotOutput.png
plot_option_l=plot_option_l.plt
processL() {

    # Check if input file is provided
    if [ $# -ne 1 ]; then
        echo "Usage: -l <input_file>"
        return 1
    fi

    if [ ! -f "$1" ]; then
        echo "Error: Input file '$1' not found."
        return 1
    fi


    echo Process L on file $1

    startTime
    
    tail +2 $1 | LC_NUMERIC=C awk -F';' '{sumTrajet[$1]+=$5} END {for (trajet in sumTrajet) printf "%f;%s\n", sumTrajet[trajet], trajet}' | sort -t ";" -k1nr | head -10 | sort -t ";" -k2n > $temp$lplot

    if [ ! -f "$temp$lplot" ]; then
        echo "Error: couldn't generate $temp$lplot."
        return 1
    fi

    exitTime 0

    if [ ! -f "$images$lPlotOutput" ]; then
        echo "Error: couldn't generate $images$lPlotOutput."
        return 1
    fi

    gnuplot -e "filename='$temp$lplot'" -e "out='$images$lPlotOutput'" $plot$plot_option_l



    echo "Process lasted $((nowB - now)) seconds."
}



splot=splot.txt
sPlotOutput=sPlotOutput.png
plot_option_s=plot_option_s.plt
processS() {

    # Check if input file is provided
    if [ $# -ne 1 ]; then
        echo "Usage: -s <input_file>"
        return 1
    fi

    if [ ! -f "$1" ]; then
        echo "Error: Input file '$1' not found."
        return 1
    fi


    echo Process S on file $1
    startTime

    if [ ! -f "$EXECUTABLE" ]; then
        gcc -o ./progc/EXEC ./progc/main.c ./progc/processes.c ./progc/inputFile.c  ./progc/avlT.c ./progc/avlS.c ./progc/processes.h ./progc/inputFile.h ./progc/avlT.h ./progc/avlS.h ./progc/processes.h -lm
    fi


    ./progc/EXEC $1 0 > temp/Splot.txt


    exitTime 0

    gnuplot -e "filename='temp/Splot.txt'" -e "out='images/sPlotOutput.png'" plot/plot_option_s.plt
}

TtempC=TtempC.txt
Tplot="Tplot.txt"
tPlotOutput="tPlotOutput.png"
plot_option_t="plot_option_t.plt"

processT() {

    # Check if input file is provided
    if [ $# -ne 1 ]; then
        echo "Usage: -t <input_file>"
        return 1
    fi

    if [ ! -f "$1" ]; then
        echo "Error: Input file '$1' not found."
        return 1
    fi

    echo Process T on file $1
    startTime


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
            printf "%d;%d;%s\n", nbOfTraject[city], 0+nbdb[city], city;
        }
    }' > $temp$TtempC

   ./progc/EXEC $temp$TtempC 1 > $temp$Tplot


    exitTime 0

    gnuplot -e "filename='$temp$Tplot'" -e "out='$images$tPlotOutput'" "$plot$plot_option_t"
}
