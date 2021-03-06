#!/bin/bash
# $Id: rmDesc.sh,v 1.2 2009/07/16 15:41:03 loizides Exp $

hf=$1

if test -z "`echo $hf | grep TAM/`"; then
    sf=`dirname $hf`/`basename $hf .h`.cc
    sf=`echo $sf | replace interface src`
else
    sf=`dirname $hf`/`basename $hf .h`.cxx
    sf=`echo $sf | replace interface src`
fi

if ! test -e $sf; then
    exit 123;
fi

if test -e ${sf}.keep; then
    mv ${sf}.keep ${sf}
fi

if test -e ${hf}.keep; then
    mv ${hf}.keep ${hf}
fi
