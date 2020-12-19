# Advent of Code 2020 - Day 18

This was a fun puzzle, that kid sure gets a ton of homework! I was able to use a double-ended queue for this puzzle which made the puzzle fairly simple with recursion. We just have to get the operands and the operator, evaluate and push that the result to the front of the queue. If we ever hit parenthesis, we can treat everything within them as its own equation and use our same function to recursively obtain the answer. Part 2 only required the change that we solve all the addition first, then go back and resolve all the multiplication Overall, I enjoyed making this simple calculator.  

  -Mateo  
