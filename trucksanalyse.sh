#!/bin/bash
source shellD.sh
source constant.sh

printHelp() {
        cat printSH/printHelp.txt | sed "s#\\*#$0#g"
        exitTime $1
}



#If we don't have the right number of argument, (1) we print the usage
if [ "$#" -eq 0 ]; then
    echo "You didn't use the right number of argument. At least one argument is expected."
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$dataFolder/$1"
if [ -f "$filename" ]; then
    if [ "$DEBUG" -eq 1 ]; then 
        echo "File $filename exists."
    fi
else
    echo "File $filename does not exist."
    exit 1
fi 


settingsVar=(0 0 0 0 0 0)


if [ "$DEBUG" -eq 0 ]; then 
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
fi


#Recupérer les arguments
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



#Choice
if [ "${settingsVar[0]}" -eq 1 ]; then
    printHelp 0
else 
    if [ "${settingsVar[1]}" -eq 1 ]; then
        processD1 $filename
    fi

    if [ "${settingsVar[2]}" -eq 1 ]; then
        processD2 $filename
    fi

    if [ "${settingsVar[3]}" -eq 1 ]; then
        processL $filename
    fi

    if [ "${settingsVar[4]}" -eq 1 ]; then
        processT $filename
    fi

    if [ "${settingsVar[5]}" -eq 1 ]; then
        processS $filename
    fi
fi













