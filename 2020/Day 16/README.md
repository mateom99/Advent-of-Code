# Advent of Code 2020 - Day 16

This was quite a fun puzzle. It was immediately obvious that we would eventually need to figure out which field was which and I've got to say, it seemed hard at first. After parsing the input, every step to getting to the solution simply flowed nicely. First, I removed all tickets that simply aren't possible for part 1. Then I created a vector of unordered_sets to allow each column from the tickets to have a set of all possible fields it could be. After that was done, we simply had to find which field had only a single possibility and remove that field from all sets (removal in a set is done in constant time, which is why I chose it). We just had to keep repeating this until every set had exactly only 1 possible field which leads to our answer. Overall, I enjoyed the puzzle and liked how everything flowed fairly intuitively.  

  -Mateo  
