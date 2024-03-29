#!/bin/bash
source shellD.sh
source constant.sh

printHelp() {
        cat printSH/printHelp.txt | sed "s#\\*#$0#g" #print /printSH/printHelp.txt replacement of all the * by the file name
        exitTime $1
}



#If we don't have the right number of argument, (1) we print the usage
if [ "$#" -eq 0 ]; then
    echo "You didn't use the right number of argument. At least one argument is expected."
    echo "Usage: $0 <filename>"
    exit 1
fi

#verrification 

make createDataDir -s
if [ ! -f "$1" ]; then
    echo "File $1 does not exist."
    printHelp 1 # Put 1 as a parameter to indicate exit.
else
    cp "$1" "$dataFolder/$dataname"
fi

# Set the full path of the file in the variable filename.
filename="$dataFolder/$dataname"

# Declaration and initialization of the settingsVar array.
settingsVar=(0 0 0 0 0 0)

# Take the arguments.
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

# Choice of actions to be performed based on the passed parameters.
if [ "${settingsVar[0]}" -eq 1 ]; then
    printHelp 1
else 
    # Compilation if necessary.
    if ((${settingsVar[4]} == 1 || ${settingsVar[5]} == 1)); then # We compile for the modes that need c to be executed.
        if [ ! -f ".$EXECUTABLE" ]; then
            echo Compilation
            make cleanCompilation -s
            make createCompDir -s
            echo "  Created/Cleaned bin/ and build/"
            make -s
            echo "  Compilation done."
        fi
    fi

    make createDir -s
    make moveImagesToDemo -s
    make cleanTemp -s
    echo Created/Cleaned temp/
    echo 

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
