#!/bin/bash

printHelp() {
cat <<E0L
Usage: $0 [OPTIONS]...

Description:
  This script performs a specific task.

Options:
  -h, --help     Display this help message and exit.
  -d1            Enable option 1 : .
  -d2            Enable option 2.
  -l             Enable option L.
  -t             Enable option T.
  -s             Enable option S.

Examples:
  $0 -d1 -l      # Run the script with options 1 and L.
  $0 -t -s       # Run the script with options T and S.

Options can be combined. For example:
  $0 -d1 -t -s

E0L
}









settingsVar=(0 0 0 0 0 0)


for arg in "$@"; do
    case $arg in
        "-h")
                settingsVar[0]=1
        ;;
        "-d1")
                settingsVar[1]=1
        ;;
        "-d2")
                settingsVar[2]=1
        ;;
        "-l")
                settingsVar[3]=1
        ;;
        "-t")
                settingsVar[4]=1
        ;;
        "-s")
                settingsVar[5]=1
        ;;    
    esac
done


for i in "${settingsVar[@]}"; do
    echo "$i"
done


if [ "${settingsVar[0]}" -eq 1 ]; then
    printHelp
fi




start_time=`date +%s`








end_time=`date +%s`
echo execution time was `expr $end_time - $start_time` s.