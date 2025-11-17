# Philosophers (Dining Philosophers) – One Page Overview

## 1. Purpose
Implements the classic Dining Philosophers concurrency problem. Multiple philosopher threads compete for forks (mutexes) to eat. Demonstrates safe synchronization, avoidance of deadlock/starvation, and detection of philosopher death (time_to_die exceeded). Optional meal quota lets the simulation end cleanly.

## 2. Program Arguments
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- number_of_philosophers: 1–200
- time_to_die / time_to_eat / time_to_sleep: milliseconds (>= 60)
- number_of_times_each_philosopher_must_eat: optional (>=1); if omitted → infinite loop until someone dies.

## 3. Build & Run
```bash
make            # build binary philo
./philo 5 800 200 200 3
./philo 1 800 200 200      # edge case: single philosopher
```
Stop with Ctrl+C if running infinite scenario.

## 4. Core Data Structures
- `t_philo` (per philosopher): `id`, `left_fork`, `right_fork`, `last_meal`, `meals_eaten`, thread handle, per‑philo mutex (`meal_mutex`).
- `t_data` (shared): counts & timings, `someone_died` flag, `start_time`, array of fork mutexes, `print_mutex`, philosophers array, monitor thread.

## 5. Life Cycle (Philosopher Thread)
1. Take forks: lock two fork mutexes in parity order (odd: right→left, even: left→right) to reduce deadlock risk.
2. Update `last_meal` (under `meal_mutex`), print "is eating", sleep `time_to_eat`, increment `meals_eaten` under same mutex.
3. Release forks (unlock both mutexes).
4. Print "is sleeping", sleep `time_to_sleep`.
5. Print "is thinking" (short pause) and repeat until death flag or meal quota satisfied.

## 6. Monitor Thread
Loops while no death flag:
- For each philosopher: lock `meal_mutex`, check if `current_time - last_meal > time_to_die`; if yes → print "died", set `someone_died`.
- If meal quota specified: verify all `meals_eaten >= num_meals`; if all done → set flag to stop.
- Small sleep (e.g., 100µs) between passes to reduce busy waiting.

## 7. Concurrency & Mutexes
| Resource / Field      | Mutex                    | Notes |
|-----------------------|--------------------------|-------|
| Each fork             | `forks[i]`               | Exclusive access to fork. |
| Printing              | `print_mutex`            | Prevent interleaved output. |
| `last_meal`, `meals_eaten` | `philo->meal_mutex`  | Use SAME mutex for both read & write. |
| `someone_died` flag   | (dedicated mutex or atomic) | Always guard accesses. |

Golden rule: The same field must always be protected by the same mutex (writer + reader).

## 8. Termination Conditions
- Death: Any philosopher’s `last_meal` exceeds `time_to_die` interval.
- Completion: If meal quota provided and all philosophers reached it.
- Otherwise run until a death occurs.

## 9. Common Pitfalls & Fix Rules
| Problem | Symptom | Fix |
|---------|---------|-----|
| Immediate death | "0ms philo X died" | Initialize `last_meal = start_time` for all philosophers. |
| Data race on `last_meal` | Helgrind warns; random deaths | Wrap all reads/writes with `meal_mutex`. |
| Deadlock | Threads freeze after taking one fork | Parity ordering or lock lower-index first. |
| Unlock of not locked | Helgrind "unlocked a not-locked lock" | Match every lock/unlock; audit early returns. |
| Stuck thread holding lock | Helgrind: exiting thread holds lock | Ensure cleanup paths unlock before return. |
| Interleaved output | Garbled text | Guard prints with `print_mutex`. |

## 10. Validation & Debugging
Helgrind (race / lock correctness):
```bash
valgrind --tool=helgrind --history-level=approx ./philo 5 800 200 200 3 2>&1 | tee helgrind.out
grep -E "race|unlocked|lock" helgrind.out
```
Memory leaks (if needed):
```bash
valgrind --leak-check=full ./philo 5 800 200 200 3
```
Runtime log:
```bash
./philo 5 800 200 200 3 | tee run.log
tail -n 50 run.log
```
GDB attach (hang analysis):
```bash
ps aux | grep philo
gdb -p <PID>
(gdb) info threads
(gdb) thread apply all bt
```

## 11. Quick Checklist Before Submit
- [ ] `last_meal` initialized to `start_time`.
- [ ] Writer & reader of `last_meal` / `meals_eaten` use same mutex.
- [ ] Every fork lock has a matching unlock on all paths.
- [ ] Death/meal completion sets termination flag exactly once.
- [ ] No Helgrind data races or unlock warnings.

## 12. Extensibility Ideas (Optional)
- Add colored output. 
- Replace busy-wait sleep loop with condition variables.
- Collect statistics (average eating intervals).

## 13. License / Attribution
Add a license section here if required (e.g., MIT).

---
Single-page end.
