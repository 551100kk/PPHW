#!/bin/sh

for i in {1..8};
do
    sed -e "s/pcount/$i/g" ~/run.sh > run.sh
    qsub run.sh
done
