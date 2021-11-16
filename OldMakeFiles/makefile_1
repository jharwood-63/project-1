#makefile for lab 1 pass off cases
NUM:=1
buckets:=70 90 100
numbers_70:=1 3 4 5 6 7 noway
numbers_90:=1 2 3
numbers_100:=1 2
tests:=Lab$(NUM)PassOffCases

.SILENT: all $(buckets)

all: $(buckets)
	@rm $(tests)/out.txt

$(buckets):
	echo "Bucket $@"; \
	for number in ${numbers_$@} ; \
	do \
		echo "Running input $$number" ; \
		./lab$(NUM) $(tests)/$(NUM)-$@/input$$number.txt > $(tests)/out.txt ; \
		diff $(tests)/$(NUM)-$@/answer$$number.txt $(tests)/out.txt || (echo "diff failed on test $$number \n") ; \
	done \

compile:
	g++ -Wall -Werror -std=c++17 -g *.cpp -o lab$(NUM)
