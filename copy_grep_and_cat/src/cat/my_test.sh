#!/bin/bash

COUNT_SUCCESS=0
COUNT_FAIL=0
DIFF=""
FILE="bytes.txt"
echo "" > log.txt

for flag in -b -e -n -s -t -v
do
    TEST_1="$flag $FILE"
    echo "$TEST_1"
    ./s21_cat $TEST_1 > s_21_cat.txt
    cat $TEST_1 > true_cat.txt
    DIFF="$(diff -s s_21_cat.txt true_cat.txt)"
    if  [ "$DIFF" == "Files s_21_cat.txt and true_cat.txt are identical" ]
        then
            (( COUNT_SUCCESS++ ))
        else
            echo "$TEST_1" >> log.txt
            (( COUNT_FAIL++))
    fi
    rm s_21_cat.txt true_cat.txt
done

for flag in -b -e -n -s -t -v
do
  for flag2 in -b -e -n -s -t -v
  do
        if [ $flag != $flag2 ]
        then
          TEST_1="$flag $flag2 $FILE"
          echo "$TEST_1"
          ./s21_cat $TEST_1 > s_21_cat.txt
          cat $TEST_1 > true_cat.txt
          DIFF="$(diff -s s_21_cat.txt true_cat.txt)"
          if [ "$DIFF" == "Files s_21_cat.txt and true_cat.txt are identical" ]
            then
              (( COUNT_SUCCESS++ ))
            else
              echo "$TEST_1" >> log.txt
              (( COUNT_FAIL++ ))
          fi
          rm s_21_cat.txt true_cat.txt
        fi
  done
done

for flag in -b -e -n -s -t -v
do
  for flag2 in -b -e -n -s -t -v
  do
      for flag3 in -b -e -n -s -t -v
      do
        if [ $flag != $flag2 ] && [ $flag2 != $flag3 ] && [ $flag != $flag3 ]
        then
          TEST_1="$flag $flag2 $flag3 $FILE"
          echo "$TEST_1"
          ./s21_cat $TEST_1 > s_21_cat.txt
          cat $TEST_1 > true_cat.txt
          DIFF="$(diff -s s_21_cat.txt true_cat.txt)"
          if [ "$DIFF" == "Files s_21_cat.txt and true_cat.txt are identical" ]
            then
              (( COUNT_SUCCESS++ ))
            else
              echo "$TEST_1" >> log.txt
              (( COUNT_FAIL++ ))
          fi
          rm s_21_cat.txt true_cat.txt

        fi
      done
  done
done

for flag in -b -e -n -s -t -v
do
  for flag2 in -b -e -n -s -t -v
  do
      for flag3 in -b -e -n -s -t -v 
      do
          for flag4 in -b -e -n -s -t -v
          do
            if [ $flag != $flag2 ] && [ $flag2 != $flag3 ] && [ $flag != $flag3 ] && [ $flag != $flag4 ] && [ $flag2 != $flag4 ] && [ $flag3 != $flag4 ]
            then
              TEST_1="$flag $flag2 $flag3 $flag4 $FILE"
              echo "$TEST_1"
              ./s21_cat $TEST_1 > s_21_cat.txt
              cat $TEST_1 > true_cat.txt
              DIFF="$(diff -s s_21_cat.txt true_cat.txt)"
              if [ "$DIFF" == "Files s_21_cat.txt and true_cat.txt are identical" ]
                then
                  (( COUNT_SUCCESS++ ))
                else
                  echo "$TEST_1" >> log.txt
                  (( COUNT_FAIL++ ))
              fi
              rm s_21_cat.txt true_cat.txt

            fi
          done
      done
  done
done

echo "SUCCESS: $COUNT_SUCCESS"
echo "FAIL: $COUNT_FAIL"