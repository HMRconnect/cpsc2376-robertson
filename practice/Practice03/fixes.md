1. Fixed off-by-one-error in sumRange by changing < to <= in the for loop.
2. Fixed for loop in containsNegative by changing the loop variable to loop until < numbers.size(), not <=.
3. Fixed if in containsNegative by changing > 0 to < 0.
4. Fixed findMax response for when an empty vector is provided by throwing exception if vector is empty
5. Fixed for loop in findMax by changing the loop variable to = 0 and loop until < numbers.size(), not <=, 
   to make sure it loops through the correct range.
6. Fixed comparison in if in findMax by changing >= to > maxVal, so it only changes when the number is greater.