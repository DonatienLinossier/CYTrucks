
# CYTrucks

A CY-tech project introducing students to data analysis and data manipulation using shell, C and gnuplot.





## Installation

Install and setup with apt-get and git on debian distrib

```bash
  sudo apt-get install gnuplot
  sudo apt-get install imagemagick
  git clone https://github.com/DonatienLinossier/CYTrucks
  cd CYTrucks
  chmod 777 trucksanalyse.sh
```
    
## Usage/Examples

```bash
Usage: truckanalyse.sh [FILE] [OPTIONS]...

Description:
  This script performs a data analysis for CYTrucks.

Options:
  -h, --help     Display this help message and exit.
  -d1            Enable option D1
  -d2            Enable option D2
  -l             Enable option L
  -t             Enable option T
  -s             Enable option S

Examples:
  truckanalyse.sh -d1 -l      # Run the script with options D1 and L.
  truckanalyse.sh -t -s       # Run the script with options T and S.

Options can be combined. For example:
  truckanalyse.sh -d1 -t -s

```

Once you ran truckanalyse.sh check the images file where all the plots are generated.

## Options

There are 5 different data analysis options for this project, all creating graph images that shows this data.

D1 Process :
  Displays the names and numbers of routes of the 10 truckers with the highest number of routes.

D2 Process :
  Displays the names and total distance driven of the 10 truckers with the highest distance.

L Process :
  Displays the 10 routes longest routes.

T Process :
  Displays the name, numbers of routes going through and number of routes beginning there of the 10 cities with the highest numbers of routes going through.

S Process : 
  Displays the minimum, maximum and average distance of the steps of the 50 routes with the highest difference maximum - minimum.



## Screenshots

![App Screenshot](https://raw.githubusercontent.com/DonatienLinossier/CYTrucks/main/plot/output/output_option_d1.png)
![App Screenshot](https://raw.githubusercontent.com/DonatienLinossier/CYTrucks/main/plot/output/output_option_l.png)



## Authors

- [@DonatienLinossier](https://www.github.com/DonatienLinossier)
- [@Eliasgdr](https://www.github.com/Eliasgdr)
- [@AntoninBÔ](https://www.github.com/AntoninB0)

