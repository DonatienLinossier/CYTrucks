#!/bin/bash
temp=temp/
plot=plot/
images=images/



EXECUTABLE="/progc/bin/main"


#test
startTime() {
    start_time=$(date +%s.%N)
}

exitTime() {
    end_time=$(date +%s.%N)

    if [ -z "$start_time" ]; then
        return 1
    fi

    elapsed_time=$(echo "$end_time - $start_time" | bc)
    if (( $(echo "$elapsed_time < 1" | bc -l) )); then
        echo "Execution time was $elapsed_time s"
    else
        echo "Execution time was $elapsed_time s"
    fi

    if [ "$1" -eq 1 ]; then
        exit 1
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

    tail +2 $1 | awk -F';' '!seen[$1,$6]++ {count[$6]++} END {for (driver in count) printf "%d;%s\n", count[driver], driver}' | sort  -t ";" -k1nr | head -10 > $temp$D1plot
    
    exitTime 0
  
    gnuplot -e "filename='$temp$D1plot'" -e "out='$images$d1PlotOutput'" "$plot$plot_option_d1"

    mogrify -rotate 90 "$images$d1PlotOutput"

    if [ ! -f "$temp$D1plot" ]; then
        echo "Error: couldn't generate $temp$D1plot."
        return 1
    fi
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

    exitTime 0

    gnuplot -e "filename='$temp$D2plot'" -e "out='$images$d2PlotOutput'" "$plot$plot_option_d2"
    
    mogrify -rotate 90 'images/d2PlotOutput.png'

    if [ ! -f "$temp$D2plot" ]; then
        echo "Error: couldn't generate $temp$D2plot."
        return 1
    fi
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
        echo "Error: generation failed for: $temp$lplot."
        return 1
    fi

    exitTime 0

    gnuplot -e "filename='$temp$lplot'" -e "out='$images$lPlotOutput'" $plot$plot_option_l

    if [ ! -f "$images$lPlotOutput" ]; then
        echo "Error: couldn't generate $images$lPlotOutput."
        return 1
    fi
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

    ./progc/bin/main $1 0 > $temp$splot


    exitTime 0

    gnuplot -e "filename='$temp$splot'" -e "out='$images$sPlotOutput'" "$plot$plot_option_s"
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

    #Preprocess of treatment T
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

   ./progc/bin/main $temp$TtempC 1 > $temp$Tplot


    exitTime 0

    gnuplot -e "filename='$temp$Tplot'" -e "out='$images$tPlotOutput'" "$plot$plot_option_t"
}
