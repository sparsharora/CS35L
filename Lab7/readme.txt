For the homework, one of the major issues I faced was that my output
was wrong and my image was not right because in the for loop for
creating threads, the last argument I passed was just an address to
the counter variable that was being incremented each time. This was
wrong because a refrence to that variable would be the same everytime
and would show unwanted behavior.

To overcome this, I made an intger array holding all i values and
sent a refrence of each element of the array as the argument for my
multithreaded function. This seemed to work right.

Another problem I faced was that the argument sent to my
multi-threaded function was a void pointer which I tried to assign to
my int variable. This caused an error. I had to cast the void pointer
to an int pointer to assign to a variable that was later used to
initialize px.  

As seen by the output of make clean check, we notice that the
multithreaded performance is very good as it completes exection in
almost 1/8th of the time it takes to do it without
multithreading. Moreover, there was a trend that as the threads
increased, the performance increased too.
