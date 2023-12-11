#!/bin/bash
start_time=`date +%s`

printHelp() {
cat printSH/printHelp.txt | sed "s#\\*#$0#g"
}

settingsVar=(0 0 0 0 0 0)

if [ -e "$1" ]; then
        for arg in "$@"; do
        case $arg in
                "-h")
                settingsVar[0]=1 ;;
                "-d1")
                settingsVar[1]=1 ;;
                "-d2") 
                settingsVar[2]=1 ;;
                "-l") 
                settingsVar[3]=1 ;;
                "-t") 
                settingsVar[4]=1 ;;
                "-s") 
                settingsVar[5]=1 ;;    
        esac
        done
else
        settingsVar[0]=1
fi





#for i in "${settingsVar[@]}"; do
#    echo "$i"
#done


if [ "${settingsVar[0]}" -eq 1 ]; then
    printHelp
    exit 0
fi












end_time=`date +%s`
echo execution time was `expr $end_time - $start_time` s.