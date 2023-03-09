#!/bin/sh

for file in $(echo *.cpp *.h);
do 
	cat ${file} |
	iconv -f cp1251 -tutf8 > ${file}.utf8.cpp;
	rm ${file};
	mv -v ${file}.utf8.cpp ${file}
done
