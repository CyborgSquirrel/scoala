Ajunge la `l.lock()`, și se blochează.

```java
// run {"compiler": "java"}

import java.util.concurrent.BrokenBarrierException;  
import java.util.concurrent.CyclicBarrier;  
import java.util.concurrent.locks.Lock;  
import java.util.concurrent.locks.ReentrantLock;  
  
public class Main {  
    static int value = 0;  
    static class MyThread extends Thread {  
        Lock l;  
        CyclicBarrier b;  
        public MyThread(Lock l, CyclicBarrier b) { this.l = l; this.b = b;}  
        public void run(){  
            try {  
                l.lock();  
                value += 1; b.await();  
            }  
            catch (InterruptedException | BrokenBarrierException e) { e.printStackTrace(); }  
            finally { l.unlock();}  
        }  
    }  
  
    public static void main(String[] args) throws InterruptedException {  
        Lock l = new ReentrantLock();  
        CyclicBarrier b = new CyclicBarrier(2);  
        MyThread t1 = new MyThread( l, b );  
        MyThread t2 = new MyThread( l, b );  
        t1.start(); t2.start();  
        t1.join(); t2.join();  
        System.out.print(value);  
    }  
}
```
