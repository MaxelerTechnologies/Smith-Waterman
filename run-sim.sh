#!/bin/bash

control=tmp/control
feedback=tmp/feedback
path=sequences
maxcard=MAX3424A

N=1

args=("$@")

if [[ "$#" > 0 ]]; then
  let 'N=args[0]'
fi

mkdir -p tmp

if ! [[ -p $control ]]; then
  rm -f $control
  mkfifo $control
fi


if ! [[ -p $feedback ]]; then
  rm -f $feedback
  mkfifo $feedback
fi

$MAXCOMPILERDIR/bin/maxcompilersim -n SmithWaterman -c MAX3424A -d 1 restart
trap "$MAXCOMPILERDIR/bin/maxcompilersim -n SmithWaterman stop; exit 1" SIGTERM SIGINT
export MAXELEROSDIR=$MAXCOMPILERDIR/lib/maxeleros-sim
export LD_PRELOAD=$MAXELEROSDIR/lib/libmaxeleros.so:$LD_PRELOAD
export SLIC_CONF="use_simulation=SmithWaterman"

java -jar bin/SmithWaterman.jar $control $feedback $path &

LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH bin/max_ssearch -c $control -f $feedback -i 0 -n $N -s -e "*"


sleep 1

$MAXCOMPILERDIR/bin/maxcompilersim -n SmithWaterman stop

rm -rf tmp


