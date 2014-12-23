#!/bin/bash
# --------------------------------------------------
#
#       Title: testsef.sh
# Description: Script Testes Projecto Compiladores IST 2013
#      Author: Ricardo Sequeira
#
#        Name: testsef
#        File: testsef
#     Created: May 10, 2013
#       Usage:	Run all tests:		./testsef.sh
#		Run ex1-while-cycle.mf	./testsef.sh ex1-while-cycle.mf
#		Compile Only		./testsef.sh -s
# --------------------------------------------------

# Directorio onde se encontram os testes da entrega intermedia
# disponiveis em https://fenix.ist.utl.pt/disciplinas/com564/2012-2013/2-semestre/projecto/desenvolvimento/pacotes-de-testes
TESTSDIR='/home/klang/Documents/mayfly-tests-daily-201305102237'

# Directorio base do projecto
PROJDIR='/home/klang/project'


##################################################################################

TEMPDIR='/tmp/logs_co13'
rm -rf $TEMPDIR
mkdir $TEMPDIR

SUCCESS=0
FAIL=0
TOTAL=0
STRRESULTS=""


exec > >(tee $TEMPDIR/tests.res) 2>&1

cd $PROJDIR
$(make clean)
make

echo ""
echo "#################### PROJECT STRUCTURE ####################"
echo ""
echo "====================     N O D E S     ===================="
echo ""
if [ -d $PROJDIR/nodes ]
  then
    cd nodes
    TOTALNODES=$(ls -l *.h | wc -l)
    cd expression
    TOTALNODES=$[TOTALNODES + $(ls -l *.h | wc -l) - 1]
    cd ..
    echo "-- Directory 'nodes' found."
    echo ""
    echo "Number of nodes: $TOTALNODES"    
  else
    echo "!! Directory 'nodes' not found."
fi

echo ""
echo "====================     SEMANTICS     ===================="
echo ""
if [ -d $PROJDIR/semantics ]
  then
    echo "-- Directory 'semantics' found."
  else
    echo "!! Directory 'semantics' not found."
fi

echo ""
echo "====================     SCANNER       ===================="
echo ""
if [ -f $PROJDIR/MFScanner.l ]
  then
    echo "-- Scanner specification found."
  else
    echo "!! Scanner specification not found."
fi

echo ""
echo "====================      PARSER       ===================="
echo ""
if [ -f $PROJDIR/MFParser.y ]
  then
    echo "-- Parser specification found."
    tail -n 2 $PROJDIR/MFParser.output
    
    rm $TEMPDIR/blank5786548.txt
    touch $TEMPDIR/blank5786548.txt
    if $(grep "never reduced" $PROJDIR/MFParser.output | diff -w -q - $TEMPDIR/blank5786548.txt);
      then
	rm $TEMPDIR/blank5786548.txt
	touch $TEMPDIR/blank5786548.txt
	if $(grep "reduce conflict" $PROJDIR/MFParser.output | diff -w -q - $TEMPDIR/blank5786548.txt)
	  then
	    echo "-- grammar has no conflics"
	  else
	    echo "!! GRAMMAR HAS CONFLICTS"
	fi
      else
	echo "!! GRAMMAR HAS CONFLICTS"
    fi
  else
    echo "!! Parser specification not found."
fi

echo ""
echo "====================     COMPILING     ===================="
echo ""
if [ -f $PROJDIR/mayfly ]
  then
    echo "-- successfully generated 'mayfly'".
  else
    echo "!! Makefile could not produce 'mayfly'."
    exit -1;
fi

if [ "$1" ==  "-s" ] # summarize
  then
    exit 0;
fi

rm $TEMPDIR/blank5786548.txt
touch $TEMPDIR/blank5786548.txt

if [ "$1" ==  "" ] # Run all tests
  then
    for file in $TESTSDIR/*.mf
    do
	filename=$(basename $file)
	filename=${filename%%.*}
	
	TOTAL=$[TOTAL+1]
	
	echo "====================$filename===================="
	$PROJDIR/mayfly $TESTSDIR/$filename.mf -o $TEMPDIR/$filename.asm
	yasm -felf $TEMPDIR/$filename.asm -o $TEMPDIR/$filename.o
	ld -o $TEMPDIR/$filename $TEMPDIR/$filename.o -lrts
	$TEMPDIR/$filename > $TEMPDIR/$filename.out
	
	
	if diff -w $TEMPDIR/$filename.out $TESTSDIR/expected/$filename.out
	  then
	    SUCCESS=$[SUCCESS+1]
	    STRRESULTS="$STRRESULTS$filename - OK\n"
	  else
	    FAIL=$[FAIL+1]
	    STRRESULTS="$STRRESULTS$filename - FAIL !!\n"
	fi
    done
  else # run specific test
    filename=$(basename $1)
    filename=${filename%%.*}

    echo "====================$filename===================="
    $PROJDIR/mayfly $TESTSDIR/$filename.mf -o $TEMPDIR/$filename.asm
    yasm -felf $TEMPDIR/$filename.asm -o $TEMPDIR/$filename.o
    ld -o $TEMPDIR/$filename $TEMPDIR/$filename.o -lrts
    $TEMPDIR/$filename > $TEMPDIR/$filename.out
    if diff -w $TEMPDIR/$filename.out $TESTSDIR/expected/$filename.out
      then
	SUCCESS=$[SUCCESS+1]
	STRRESULTS="$STRRESULTS$filename - OK\n"
      else
	  FAIL=$[FAIL+1]
	  STRRESULTS="$STRRESULTS$filename - FAIL !!\n"
    fi
fi


echo ""
echo "=====================TEST RESULTS====================="
echo -e $STRRESULTS
echo ""
echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "Generated '$TEMPDIR/tests.res'"
