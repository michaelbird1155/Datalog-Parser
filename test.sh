#!/bin/bash

reset

name=${PWD##*/}

for file in `ls *.h`; do cp "$file" "tests/$file"; done
cp *.cpp tests/

cd tests

if g++ -g -Wall -std=c++11 *.cpp -o $name; then 
    echo "Compilation Succeeded"
else
    echo "Compilation Failed"
    exit 1
fi

maxcomplex=`pmccabe *.cpp *.h | grep -o '^[1234567890]*' | sort -r | head -n1`

if (($maxcomplex > 8)); then
    echo "Complexity limit fails with max complexity of $maxcomplex"
else
    echo "Complexity limit passed"
fi

for file in `ls in*.txt`; do 
    if ./$name "$file" "${file/in/myout}"; then
        echo "Valgrind passed on $file"
    fi
done

for file in `ls out*.txt`; do diff -y --suppress-common-lines "${file/out/output}" "$file"; done

#for file in `ls out*.txt`; do
#    if diff -q "$file" "${file/out/output}"; then
#        echo "Expected output for file $file"
#    else
#        (gvim -d "$file" "${file/out/output}" &> /dev/null &)
#        break
#    fi
#done

zip -q $name.zip *.cpp *.h

rm $name
rm *.h
rm *.cpp
