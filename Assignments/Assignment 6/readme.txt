README

Upon first glance of the program, I noticed that we had a large bottleneck in the
main function in which we have 4 nested for loops running calculations on every
pixel. The work done on a single pixel does not, however, affect the outcome
of the work done on another pixel. They are all in fact different. Thus there
seems to be an obvious ("embarassingly parallel") way to parallelize this
software. Instead of having one thread work on all the pixels, we can have
multiple threads work on a partition of the pixels.

Our particular method of partioning the pixels involves dividing the pixels into
nthread columns, where nthread is the number of threads we have currently. Each
thread would work on their own column, thus preventing any race conditions since
every pixel is independent of the other. So even though there are really 4
for loops, we only need to parallelize the outer most loop.

One issue was trying to figure out how precisely to parallelize the loop. The
solution I chose was to go from column X to column (X + width / nthreads). Doing
this also gave nice microptimizations with cache hits since we have more spatial
locality in our accesses (we are incrementing our counter from column X to column
(X + width/nthreads) only by one every iteration).  