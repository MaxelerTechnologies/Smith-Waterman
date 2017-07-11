# Smith Waterman Demo

<img src="http://appgallery.maxeler.com/v0.1/app/Smith%20Waterman%20Demo/icon" alt="Smith Waterman Demo">

## Description

This App is a standard textbook algorithm for local gene sequence alignment. While it is impractical for production use, it demonstrates DFE usage for Genomics.

## Content

The repo root directory contains the following items:

- APP
- DOCS
- sequences
- LICENCE.txt

### APP

Directory containing project sources.

### DOCS

Documentation of the project.

### SEQUENCES

This application contains amino acids sequences from the UniRef50 database and the UniProtKB/SwissProt database.

For more informations or to download the latest release, visit http://www.uniprot.org/
  
### LICENSE.txt

License of the project.

## How to compile

Ensure the environment variables below are correctly set:
  * `MAXELEROSDIR`
  * `MAXCOMPILERDIR`
  * `JAVA_HOME`

To compile the application, run:

    ./build.sh -p "<ProfileName>" -t build

Default Profile Name is `Simulation`.

If you would like to remove the distributed maxfiles, jars and binaries before recompiling the application run the following command before compilation:

    ./build.sh -p "<ProfileName>" -t distclean

## Build targets

### build  

Compiles the application

### clean  

Removes results of compilation from build directories  

### distclean  

Removes all results of compilation from build directories, including all maxfiles

## How to run 

Before running application we need to download input data. In order to do that we need to run:

    git lfs pull

In order to run application in simulation mode after compilation run:

    ./run-sim.sh

In order to run application on real DFE after compilation run:

    ./run.sh

Smith Waterman Demo on [AppGallery](http://appgallery.maxeler.com/)   

