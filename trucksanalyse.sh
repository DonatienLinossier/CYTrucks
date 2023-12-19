#!/bin/bash

printHelp() {
        cat printSH/printHelp.txt | sed "s#\\*#$0#g"
        exitTime $1
}

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
        exit $1
}

startTime

settingsVar=(0 0 0 0 0 0)
linkFolderReset=("temp/" "images/")
linkExeMain="progc/main.exe"
linkCMain="progc/main.c"
sleep 1



if [ ! -e "$linkExeMain" ]; then
        gcc -o $linkExeMain $linkCMain 
        if [ ! $? -eq 0 ];then
                echo compilation not succesfull
                exit 1
                   
        fi
fi      

for folder in "${linkFolderReset[@]}"; do
        if [ -e "$folder" ]; then
                rm -r "$folder"
        fi
        mkdir "$folder"
done


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

 

if [ "${settingsVar[0]}" -eq 1 ]; then
    printHelp 0
fi








exitTime



