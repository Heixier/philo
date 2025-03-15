# Cats

## Solution

NOTE: We will be using the odd/even solution, which isn't the best due to poor optimisation i.e. some philosophers getting blocked less than others, but it should be good enough for <= 200 philosophers

## Threads needed

- Each cat will be represented by a thread

### Cat thread

- Cats can only eat if they have two **forks**
  - Cat threads "eat" by sleeping for the specified eating duration
- Cats will die if they do not eat for too long
- Cats will **stop running** if any cat dies
  - They cannot print any more messages, but can still sleep before exiting
- After eating, cats will sleep for a certain amount of time
- Upon waking up, cats will immediately keep trying to eat again
  - The cat starts by immediately trying to grab the forks
- While waiting for the forks to be released, they will keep grooming themselves
- To prevent cats grabbing the same fork:
  - Even-numbered cats grab the left fork first, then the right fork
  - Odd-numbered cats grab the right fork first, then the left fork
    - Odd-numbered cats will also start ~1ms later to compensate for lag and clock drift

### Monitoring thread

    Because cat threads are frozen and cannot move while they are grooming, we need something to monitor their states.

    This is where the monitoring thread comes in. The monitoring thread checks and updates the status of every cat.

    This monitoring thread is also in charge of killing the cats when they starve to death. The simulations ends immediately when any cat dies.

- Constantly update the hunger levels of all cats
- Kill a cat when it runs out of hunger, setting it to dead
- Display a message when a cat dies
- **Stop running** after a cat dies

## Mutexes needed

> Ensure that mutexes are locked for as short as possible; avoid nested mutexes as much as possible

### Forks

- Every fork will be represented by a mutex
- There will be one fork for every cat, arranged in an array
- Each cat can grab the fork in front of them, or the fork one index above them

  - This represents our left and right fork, the decision to grab the fork one index above or one index below is arbitrary, because the forks share the same index numbers and are not actually physically placed left and right of the cats.
  - Think of each fork as being placed in front of each cat and the cats having to stretch awkwardly to grab the second nearest fork from their neighbour after grabbing the fork in front of them.
  - This decision does not affect the odd/even solution

Example:

```c
  pthread_mutex_lock(left_fork);
  pthread_mutex_lock(right_fork);
```

### Print

    As we only have one output, only one thread should be allowed to "speak" at a time. This is what the print mutex is for.

Analogies:

- Sound Ball Game: Threads can only speak when they have the ball
- One microphone: Each thread has to take turns speaking into the microphone

## Timestamps

When first run, the program gets the current unix time and stores it in the main data struct. Then, right before every print statement, it checks the current time against the program's original start time to check what the current timestamp is. Then, it locks the print mutex, prints the message with the timestamp, and unlocks the mutex.

## Printing

1. Get the current time
2. Substract the current time from the program's start time to get the timestamp
3. Lock the print mutex
4. Print the message with the timestamp
5. Unlock the print mutex

> There may be a slight delay from the moment the time is acquired to the moment the print starts due to the print requiring a mutex, meaning that the time displayed may be slightly behind the actual time, but this difference should not be noticeable

### Cat thread

- Prints a message whenever it changes status e.g eat, sleep, think or takes a fork, formatted as:

```
timestamp_in_ms X has taken a fork

timestamp_in_ms X is eating
```

### Monitoring Thread

- Prints a message when a cat dies

```
timestamp_in_ms X has died
```

## Cleanup

Free everything as usual, but remember to also destroy all mutexes
