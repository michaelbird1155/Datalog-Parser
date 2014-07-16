#!/bin/bash

reset

name=${PWD##*/}

for file in `ls *.hpp`; do cp "$file" "tests/${file/.hpp/.h}"; done
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
    if valgrind -q --leak-check=full ./$name "$file" "${file/in/myout}"; then
        echo "Valgrind passed on $file"
    fi
done

#for file in `ls out*.txt`; do diff -y --suppress-common-lines "${file/out/myout}" "$file"; done

for file in `ls out*.txt`; do 
    if diff -q "$file" "${file/out/myout}"; then
        echo "Expected output for file $file"
    else
        (gvim -d "$file" "${file/out/myout}" &> /dev/null &)
        break
    fi
done

zip -q $name.zip *.cpp *.h

rm $name
rm *.h
rm *.cpp
