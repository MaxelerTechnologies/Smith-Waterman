# Smith Waterman Demo

<img src="http://appgallery.maxeler.com/v0.1/app/Smith%20Waterman%20Demo/icon" alt="Smith Waterman Demo">

## Description

This App is a standard textbook algorithm for local gene sequence alignment. While it is impractical for production use, it demonstrates DFE usage for Genomics.

## Content

The repo root directory contains the following items:

- APP
- DOCS
- LICENCE.txt

### APP

Directory containing project sources.

### DOCS

Documentation of the project.
  
### LICENSE.txt

License of the project.

## Information to compile

Ensure the environment variables below are correctly set:
  * `MAXELEROSDIR`
  * `MAXCOMPILERDIR`
  * `JAVA_HOME`

To compile the application, run:

    make RUNRULE="<ProfileName>"

If would like to remove the distributed maxfiles before recompiling the application run the following command before compilation:

    make RUNRULE="<ProfileName>" distclean

## Makefile targets

### build  

Compiles the application

### clean  

Removes results of compilation from build directories  

### distclean  

Removes all results of comakempilation from build directories, including all maxfiles

Smith Waterman Demo on [AppGallery](http://appgallery.maxeler.com/)   

