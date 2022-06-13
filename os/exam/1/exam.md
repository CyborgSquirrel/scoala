### 1
```
grep '\b[A-Z][A-Za-z]*\b' a.txt
```

### 2
```
sed -E 's/([0-9])([0-9])/\2\1/g' a.txt
```

### 3
```
awk '{ print $1+$2 }' a.txt
```

### 4
```
cat a.txt | sort | uniq -u
```

### 5
```
ls | grep '\.txt$' | while read file; do
	if grep -q '\bcat\b' "$file"; then
		echo "$file"
	fi
done
```

### 6
PC
xx
xx
 x
--
x 
x 
--
xx

### 7
3

### 8
- if execl succeeds:
A
- if execl fails:
A
B

### 9
- if no one is writing to the pipe, then it will return 0, signifying end-of-file
- if someone is writing to the pipe, and O_NONBLOCK is set, it will return -1, and set errno to EAGAIN
- if someone is writing to the pipe, and O_NONBLOCK is clear, it will wait until some data is written

### 10
It waits for the other end of the FIFO to be opened.

### 11
Threads are lighter than processes, therefore you can create more of them, they take up fewer system resources, etc..

### 12
Most likely n=2, but there is a chance that n=1.

Because each thread locks and unlocks its own mutex, so the mutexes don't actually protect n.

### 13
A/5/9
C/1/10
B/7/13

### 14
Advantage: it helps separate data and code
Disadvantage: it doesn't address memory fragmentation

### 15
Ideally only load a page when the program tries to access it, and also load a few nearby pages at the same time.

### 16
It happens when the process tries to execute an io operation, or to lock a mutex (entering the WAIT state), and the operation is finished.

If the os' scheduler decides that the process has executed for a sufficient amount of time, it sets its state to READY.

### 17

