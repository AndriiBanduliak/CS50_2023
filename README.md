# Bulbs
The Basics
The simplest base is base-1, or unary; to write a number, N, in base-1, we would simply write N consecutive 1s. So the number 4 in base-1 would be written as 1111, and the number 12 as 111111111111. Think of it like counting on your fingers or tallying up a score with marks on a board.

You might see why base-1 isn’t used much nowadays. (The numbers get rather long!) Instead, a common convention is base-10, or decimal. In base-10, each digit is multiplied by some power of 10, in order to represent larger numbers. For instance, 
 is short for 
.

Changing base is as simple as changing the 
 above to a different number. For instance, if you wrote 123 in base-4, the number you’d really be writing is 
, which is equal to the decimal number 
.

Computers, though, use base-2, or binary. In binary, writing 123 would be a mistake, since binary numbers can only have 0s and 1s. But the process of figuring out exactly what decimal number a binary number stands for is exactly the same. For instance, the number 10101 in base-2 represents 
, which is equal to the decimal number 
.

Encoding a Message
Light bulbs can only be on or off. In other words, light bulbs represent two possible states; either the bulb is on, or the bulb is off, just as binary numbers are either 1 or 0. We’ll have to find a way to encode text as a sequence of binary numbers.

Let’s write a program called bulbs that takes a message and converts it to a set of bulbs that we could show to an unsuspecting audience. We’ll do it in two steps:

The first step consists of turning the text into decimal numbers. Let’s say we want to encode the message HI!. Luckily, we already have a convention in place for how to do this, ASCII. Notice that H is represented by the decimal number 72, I is represented by 73, and ! is represented by 33.
The next step involves taking our decimal numbers (like 72, 73, and 33) and converting them into equivalent binary numbers, which only use 0s and 1s. For the sake of having a consistent number of bits in each of our binary numbers, assume that each decimal is represented with 8 bits. 72 is 01001000, 73 is 01001001, and 33 is 00100001.
Lastly, we’ll interpret these binary numbers as instructions for the light bulbs on stage; 0 is off, 1 is on. (You’ll find that bulbs.c includes a print_bulb function that’s been implemented for you, which takes in a 0 or 1 and outputs emoji representing light bulbs.)

Here’s an example of how the completed program might work. Unlike the Sanders stage, we’ll print one byte per line for clarity.

# Caesar
Supposedly, Caesar (yes, that Caesar) used to “encrypt” (i.e., conceal in a reversible way) confidential messages by shifting each letter therein by some number of places. For instance, he might write A as B, B as C, C as D, …, and, wrapping around alphabetically, Z as A. And so, to say HELLO to someone, Caesar might write IFMMP instead. Upon receiving such messages from Caesar, recipients would have to “decrypt” them by shifting letters in the opposite direction by the same number of places.
The secrecy of this “cryptosystem” relied on only Caesar and the recipients knowing a secret, the number of places by which Caesar had shifted his letters (e.g., 1). Not particularly secure by modern standards, but, hey, if you’re perhaps the first in the world to do it, pretty secure!
Unencrypted text is generally called plaintext. Encrypted text is generally called ciphertext. And the secret used is called a key.
To be clear, then, here’s how encrypting HELLO with a key of 1 yields IFMMP:
plaintext
H
E
L
L
O
+ key	1	1	1	1	1
= ciphertext	I	F	M	M	P
More formally, Caesar’s algorithm (i.e., cipher) encrypts messages by “rotating” each letter by k positions. More formally, if p is some plaintext (i.e., an unencrypted message), pi is the ith character in p, and k is a secret key (i.e., a non-negative integer), then each letter, ci, in the ciphertext, c, is computed as
ci=(pi+k)%26
wherein %26 here means “remainder when dividing by 26.” This formula perhaps makes the cipher seem more complicated than it is, but it’s really just a concise way of expressing the algorithm precisely. Indeed, for the sake of discussion, think of A (or a) as 0, B (or b) as 1, …, H (or h) as 7, I (or i) as 8, …, and Z (or z) as 25. Suppose that Caesar just wants to say Hi to someone confidentially using, this time, a key, k, of 3. And so his plaintext, p, is Hi, in which case his plaintext’s first character, p0, is H (aka 7), and his plaintext’s second character, p1, is i (aka 8). His ciphertext’s first character, c0, is thus K, and his ciphertext’s second character, c1, is thus L. Make sense?
Let’s write a program called caesar that enables you to encrypt messages using Caesar’s cipher. At the time the user executes the program, they should decide, by providing a command-line argument, what the key should be in the secret message they’ll provide at runtime. We shouldn’t necessarily assume that the user’s key is going to be a number; though you may assume that, if it is a number, it will be a positive integer.

# Substitution
In a substitution cipher, we “encrypt” (i.e., conceal in a reversible way) a message by replacing every letter with another letter. To do so, we use a key: in this case, a mapping of each of the letters of the alphabet to the letter it should correspond to when we encrypt it. To “decrypt” the message, the receiver of the message would need to know the key, so that they can reverse the process: translating the encrypt text (generally called ciphertext) back into the original message (generally called plaintext).
A key, for example, might be the string NQXPOMAFTRHLZGECYJIUWSKDVB. This 26-character key means that A (the first letter of the alphabet) should be converted into N (the first character of the key), B (the second letter of the alphabet) should be converted into Q (the second character of the key), and so forth.
A message like HELLO, then, would be encrypted as FOLLE, replacing each of the letters according to the mapping determined by the key.
Let’s write a program called substitution that enables you to encrypt messages using a substitution cipher. At the time the user executes the program, they should decide, by providing a command-line argument, on what the key should be in the secret message they’ll provide at runtime.
Here are a few examples of how the program might work. For example, if the user inputs a key of YTNSHKVEFXRBAUQZCLWDMIPGJO and a plaintext of HELLO:
$ ./substitution YTNSHKVEFXRBAUQZCLWDMIPGJO
plaintext:  HELLO
ciphertext: EHBBQ
Here’s how the program might work if the user provides a key of VCHPRZGJNTLSKFBDQWAXEUYMOI and a plaintext of hello, world:
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext:  hello, world
ciphertext: jrssb, ybwsp
Notice that neither the comma nor the space were substituted by the cipher. Only substitute alphabetical characters! Notice, too, that the case of the original message has been preserved. Lowercase letters remain lowercase, and uppercase letters remain uppercase.
Whether the characters in the key itself are uppercase or lowercase doesn’t matter. A key of VCHPRZGJNTLSKFBDQWAXEUYMOI is functionally identical to a key of vchprzgjntlskfbdqwaxeuymoi (as is, for that matter, VcHpRzGjNtLsKfBdQwAxEuYmOi).
And what if a user doesn’t provide a valid key? The program should explain with an error message:
$ ./substitution ABC
Key must contain 26 characters.
Or really doesn’t cooperate, providing no command-line argument at all? The program should remind the user how to use the program:
$ ./substitution
Usage: ./substitution key
Or really, really doesn’t cooperate, providing too many command-line arguments? The program should also remind the user how to use the program:
$ ./substitution 1 2 3
Usage: ./substitution key
