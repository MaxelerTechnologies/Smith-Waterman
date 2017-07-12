#!/bin/bash

cpucode="APP/CPUCode/"
gui="APP/CPUCode/gui/"
maxssearch="APP/CPUCode/max_ssearch/"

function printUsage {
    echo "usage: ./$(basename $0)" 
}

function printHelp {
    printUsage
    echo ""
    echo "  -h                            Print help and exit"
    echo "  -p STR                        Set build Profile Name (default=Simulation)"
    echo "  -t STR                        Set Makefile target (default=build)"
}

#----- process command line args
profile="Simulation"
target="build"
while getopts "ht:p:" option ; do
    case "$option" in
    h)    printHelp
          exit 0;;
    t)    target="$OPTARG" ;;
    p)    profile="$OPTARG" ;;
    [?])  printUsage
          exit 1;;
    esac
done

name="Simulation"
case "$profile" in 
    Simulation)  name="libmaxlib_Simulation_n_lin.so" ;;
    Coria)       name="libmaxlib_Coria_n_lin.so" ;;
    Maia)        name="libmaxlib_Maia_n_lin.so" ;;
    Vectis)      name="libmaxlib_MAX3424A_n_lin.so" ;;
    *)           echo "Unknown Profile Name!"
                 exit 1;;
esac

if [[ $target == 'build' ]] ; then
    make -C $cpucode RUNRULE=$profile
    ant -f $gui/build.xml jar
    make -C $maxssearch
    mkdir -p bin
    mkdir -p lib
    cp $gui/bin/SmithWaterman.jar bin
    cp $maxssearch/bin/max_ssearch bin
    cp APP/RunRules/$profile/binaries/libmaxlib.so lib/$name
else
    make -C $cpucode RUNRULE=$profile $target
    ant -f $gui clean
    make -C $maxssearch clean
    if [[ $target == 'distclean' ]] ; then
        rm -rf bin lib
    fi
fi

