# Blackjack
A small CLI version of Blackjack.
I chose to write this because it is my favorite card game.
This is also a good exercise for working with arrays. Some 
may look at the code and be appalled at the use of goto 
statements. I understand that they reduce readability but
I really find the direct translation to jump instructions
quite intuitive and better in this case than juggling a lot
of flags and nested loops.

# Implementation
I implemented most of the different moves that you can take
in their own functions.

---

**Shuffling**
I initialize the deck with 0-47 then I created a function to 
use a pseudo-random number that determines the position that
the card will be swapped with. I first started by just using
rand, however, I realized in testing that it would shuffle the
deck the same way each time so I corrected this by seeding the
rand function with the current time which is sufficient for
this use case.

---

**Dealing:**
In order to track the position to pull cards from, I added a deck
pointer. It starts at zero, then when the dealer gives you a card,
it is incremented. The rank is then calculated and added to your
total. The suit is also calculated to display to the user. You are
given the first 2 cards in the deck as per the Blackjack rules.

---

**Hitting:**
This function is rather similar to the dealing function. It pulls
the next card off of the deck, adds the rank to the total, then
increments the deck pointer. Any rank greater than 10 are clamped
to 10 because face cards are all worth 10.

---

**Standing:**
This function takes in your total and your bet. It compares your
total in the logical expression 18 < total <21, If you are within
that range, you win. The winnings are calculated at a ratio of 3:2
and you are congratulated. If you lose, It says that you lost your
bet.

---

**Doubling Down:**
In the main function you are asked to place a bet, doubling down
doubles your bet, hits then stands. This was rather simple to add
because it just doubles the bet, then calls the hit function above
and then the stand function I also described above.

---

**Splitting:**
This was new to me when I was researching the rules. This is allowed
when you get two cards with the same rank from the dealer. It allows
you to only use one of the cards at a time, making two separate games.
This was an interesting problem to solve. I chose to put the game into
a for loop and in the dealing function, added a splitable flag. The for
loop iterates over the game while the index is less than or equal to 
the splitable flag so one or two times. I also had to create a variable
specifically for that dynamic, if the splitable flag is 1 then it halves
the total and stores that in the second variable for use in the second 
game.

# To Do:
- Reduce the number of global variables
- Implement the behavior of Aces
