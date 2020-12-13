# Advent of Code 2020 - Day 13

This has got to be the worst code I've written during this year's Advent of Code. That said, it got the job done. I noticed that on my puzzle input (and everyone else’s I suspect), the 3rd bus comes exactly the first busses ID minutes after the first bus (Same for 2nd and 7th and some more). I just used the first fact which meant that my answer (y) will be in the form of y = (bus1*bus3)x - (bus1*bus3-bus1). So, I only needed to check the condition for multiples of 15,419 in my case. I let this run while working on a faster solution (I knew nothing about the Chinese Remainder Theorem) and eventually I got the answer, so I just stopped working. Overall, tough puzzle but I still placed decently on the leaderboard with a bruteforce solution which was good enough for me. Perhaps one day I'll revisit this puzzle and create an optimal solution.

  -Mateo  
