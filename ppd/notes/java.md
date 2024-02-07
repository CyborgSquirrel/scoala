Lock și variabilă condițională explicite.
```java
Lock lock = new ReentrantLock();
Condition cond = lock.newCondition();

lock.lock();
cond.await();
cond.signal();
```