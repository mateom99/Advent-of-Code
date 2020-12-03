# Advent of Code 2020 - Day 3

This was definitely a fun quick puzzle! I was a little worried reading through as it seemed that we might be doing some matrix with BFS/DFS or something, but it turned out to be much simpler. I got lucky that I wrote my part 1 code perfectly modular to do part 2 in seconds. I love of AoC has taught me to always write my code thinking into how it might be used in the future! After storing the map line by line into a vector I simply had to increment by the slope and check positions for trees. The only obstacle was the repeating horizontal portion but that was quite simple. We just loop back around by changing the x coordinate - subtracting the length of the line from it. Overall, I enjoyed this fun little puzzle and am excited for the next!  

  -Mateo  