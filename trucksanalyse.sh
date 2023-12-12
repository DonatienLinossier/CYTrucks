#!/bin/bash

printHelp() {
        cat printSH/printHelp.txt | sed "s#\\*#$0#g"
        exitTime $1
}

startTime() {
        start_time=`date +%s`
}

exitTime() {
        end_time=`date +%s`
        echo execution time was `expr $end_time - $start_time` s.
        exit $1
}



settingsVar=(0 0 0 0 0 0)
linkFolderReset=("temp/" "images/")
linkExeMain="progC/main.exe"
linkCMain="progC/main.c"




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

startTime 

if [ "${settingsVar[0]}" -eq 1 ]; then
    printHelp 0
fi












