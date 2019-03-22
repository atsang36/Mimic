# Mimic
A mimic program that creates a model of some sample text. 

# What does it do?
Given a text file and a non-negative integer, it creates a model of some sample text and then produces random text according to that model.  

If the integer input is 0, it would produce m lines to the standard output (using cout), where m is the number of different words in book. The rth line of output (for 0 ≤ r ≤ m − 1) is the rth new word in book (we say the word has rank r) followed by a list of all the words that immediately follow this word in the text (we call these the word’s followers), in the order of which they occur, with duplicates.  

If the integer is not zero, it would produce a sequence of n words from the text file where the probability of producing the word w1 equals the number of occurrences of w1 in book divided by the total number of words in book. Generate the next word wi+1 from the current word wi by choosing wi+1 at random from the multi-set of words that immediately follow wi in book. Thus, the probability of producing wi+1 equals the number of occurrences of wi wi+1 in book divided by the number of followers (with duplicates) of wi.
