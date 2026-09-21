*This project has been created as part of the 42 curriculum by lavverat.*

# Codexion

## Description

Codexion is a concurrent simulation inspired by the Dining Philosophers problem. Several coder threads repeatedly compile, debug, and refactor. To compile, a coder must acquire two shared dongles. The simulation models contention for those dongles, scheduling policies, cooldown periods, burnout detection, and synchronized status logging.

The project goal is to practice POSIX threads, mutexes, condition variables, shared-state protection, and deadlock-aware resource allocation in C.

Supported dongle scheduling policies are:

- `fifo`: first-in, first-out queue order.
- `edf`: earliest-deadline-first order, based on the coder's remaining time before burnout.

## Instructions

### Requirements

- A C compiler such as `cc` or `clang`.
- GNU Make.
- POSIX threads support.

### Compilation

From the repository root:

```sh
make
```

To remove object files:

```sh
make clean
```

To remove object files and the executable:

```sh
make fclean
```

### Execution

The executable expects eight arguments:

```text
./codexion CODERS TIME_TO_BURNOUT TIME_TO_COMPILE TIME_TO_DEBUG TIME_TO_REFACTOR COMPILES_REQUIRED DONGLE_COOLDOWN SCHEDULER
```

All time values are expressed in milliseconds. The scheduler must be either `fifo` or `edf`.

Example:

```sh
./codexion 5 1000 100 100 100 3 500 fifo
```

The repository also provides a convenience target using the same kind of scenario:

```sh
make run
```

The program prints timestamped coder events to standard output and exits when every coder has completed the required number of compilations or when a coder burns out.

## Blocking cases handled

### Deadlock prevention

Each coder needs two dongles, which creates the classic circular-wait risk. The last coder reverses the order in which its two dongles are requested. This breaks the circular-wait condition from the Coffman deadlock conditions, so the system does not form a cycle where every coder holds one dongle and waits for the next one.

The dongle queues also serialize access to each dongle. A coder waits until it is at the head of the queue before proceeding, then releases the dongle and wakes other waiters.

### Waiter cleanup and shutdown

A coder that is interrupted while waiting removes its own pointer from the dongle queue before unlocking the mutex. This prevents stale waiters from blocking the queue or consuming capacity after their thread has stopped participating.

When the monitor stops the simulation, it broadcasts on every dongle condition variable. Waiting coders wake up, observe the shared `running` flag, clean up their queue entries, and exit. The main thread joins all workers before destroying shared state.

### Starvation prevention

The FIFO policy preserves arrival order. The EDF policy prioritizes the coder with the least remaining time before burnout. Both policies use the same protected per-dongle queue, so a coder cannot bypass the queue or acquire a dongle concurrently with its owner.

EDF is intended to reduce the chance that a coder close to burnout remains behind less urgent work. Scheduling does not guarantee equal waiting time under every workload.

### Cooldown handling

Each dongle records its last release time. A coder waits for the remaining cooldown before attempting to proceed. The cooldown is applied while holding the dongle's mutex so the queue and the dongle timestamp are observed consistently.

### Precise burnout detection

The monitor regularly compares the current monotonic millisecond timestamp with each coder's `last_compilation` timestamp. If the elapsed time exceeds `TIME_TO_BURNOUT`, the monitor logs the burnout and stops the simulation.

### Log serialization

All status output is protected by the simulation's print mutex. This prevents multiple coder threads from interleaving output and keeps each event line intact.

## Thread synchronization mechanisms

### `pthread_mutex_t`

The implementation uses mutexes for three kinds of shared state:

- Each dongle mutex protects its queue, cooldown timestamp, and ownership transition.
- Each coder mutex protects coder state read by the monitor, including `last_compilation` and `compilation_count`.
- The simulation state mutex protects the shared `running` flag.
- The print mutex serializes status output.

For example, a coder locks a dongle mutex before appending itself to the queue and keeps that mutex while checking whether it is the queue head. The monitor locks a coder mutex before reading burnout-related state, while the worker locks the same mutex when updating it.

### `pthread_cond_t`

Each dongle has a condition variable associated with its queue. A coder that is not currently first in the queue waits with `pthread_cond_wait()`. Releasing a dongle removes the current head, broadcasts to the condition variable, and unlocks the mutex. The awakened coders recheck the queue predicate while holding the mutex, which protects against spurious wakeups and race conditions.

The monitor also broadcasts on all dongle condition variables when it changes `running` to false. This gives blocked workers a thread-safe shutdown signal.

### Custom event implementation

This project does not define a separate custom event structure or event library. Condition variables provide the event-like notification mechanism: queue changes and simulation shutdown are signaled with `pthread_cond_broadcast()`, while the protected predicates are the queue-head test and the shared `running` flag.

### Communication between coders and the monitor

Coders publish progress by updating their protected state after a successful compilation. The monitor reads that state under the coder mutexes and changes the protected simulation flag when a burnout or completion condition is detected. Workers periodically check the flag and also check it after condition-variable wakeups, allowing the monitor to stop the group without unsynchronized access to shared memory.

## Project structure

- `src/`: simulation, worker, scheduler, parser, and utility implementations.
- `includes/`: public structures and function declarations.
- `docs/en.subject.pdf`: project subject and requirements.
- `Makefile`: build, cleanup, and execution targets.

## Resources

- `man pthread_create`: POSIX thread creation and thread arguments.
- `man pthread_join`: waiting for worker termination before cleanup.
- `man pthread_mutex_lock`: mutual exclusion and protected shared state.
- `man pthread_cond_wait`: condition-variable waiting and signaling.
- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/): practical pthreads reference.
- [The Open Group pthread condition variable specification](https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_wait.html): condition-variable semantics.
- [Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem): background on shared-resource deadlocks.
- [Coffman conditions](https://en.wikipedia.org/wiki/Deadlock): the four necessary conditions for deadlock.

### AI usage

AI assistance was used as a programming support tool during development. It helped explain pthread behavior, review mutex and condition-variable control flow, identify shutdown and stale-waiter risks, suggest heap queue operations, and improve Norminette compliance. It also assisted with drafting and organizing this README. The implementation, integration decisions, debugging, and validation were performed against this repository's source code and build commands.
