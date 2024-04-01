[source](https://www.cl.cam.ac.uk/teaching/1516/ConcDisSys/2015a-ConcurrentSystems-1B-L3-handout.pdf)

- Imagine two threads, **T1** and **T2**
	- **T1** enters the monitor and calls `wait(C)` – this suspends **T1**, places it on the queue for C, and unlocks the monitor
	- Next **T2** enters the monitor, and invokes `signal(C)`
	- Now **T1** is unblocked (i.e. capable of running again)…
	- … but can only have one thread active inside a monitor!
- If we let **T2** continue (**signal-and-continue**), **T1** must queue for re-entry to the monitor
	- And no guarantee it will be next to enter
- Otherwise **T2** must be suspended (**signal-and-wait**), allowing **T1** to continue…