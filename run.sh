#!/bin/bash

control=tmp/control
feedback=tmp/feedback
path=sequences

function printUsage {
    echo "usage: $(basename $0)"
}

function printHelp {
    printUsage
    echo ""
    echo "  -h                            Print help and exit"
    echo "  -r STR                        Either IP address of remote node or 'local' (default=local)"
}

N=8

mkdir -p tmp

if ! [[ -p $control ]]; then
  rm -f $control
  mkfifo $control
fi


if ! [[ -p $feedback ]]; then
  rm -f $feedback
  mkfifo $feedback
fi

#----- process command line args
node="local"
while getopts "hr:" option ; do
    case "$option" in
    h)    printHelp
          exit 0;;
    r)    node="$OPTARG" ;;
    [?])  printUsage
          exit 1;;
    esac
done


if [[ $node == 'local' ]] ; then
    top=$($MAXELEROSDIR/utils/maxtop)
else
    top=$($MAXELEROSDIR/utils/maxtop -r $node)
    if [ -z "$SLIC_CONF" ] ; then
        export SLIC_CONF="default_engine_resource=$node"
    else
        export SLIC_CONF="default_engine_resource=$node;$SLIC_CONF"
		N=`echo $top | sed -e 's/.*Found \([0-9][0-9]*\).*/\1/'`
    fi
fi

# Only specify the card in the remote case
case "$top" in
    *Vectis*) card='Vectis' ;;
    *Maia*)   card='Maia'   ;;
    *Coria*)  card='Coria'  ;;
    *)        ;;
esac
if [[ $card == 'none' ]] ; then
    echo "No Vectis, Maia or Coria cards found on this system; check that daemon is running."
    exit 1
fi
echo "Using $card..."
card_arg="-d $card"

java -jar bin/SmithWaterman.jar $control $feedback $path &

LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH bin/max_ssearch -c $control -f $feedback -i 0 -n $N -e "*" $card_arg


sleep 1

rm -rf tmp


