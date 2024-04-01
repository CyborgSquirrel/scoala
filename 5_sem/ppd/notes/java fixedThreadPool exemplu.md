Acest exemplu va întoarce mereu `a=13; b=13`, pentru că `fixedThreadPool` nu pornește un thread nou, până nu apare un loc liber pentru acesta.

```java
// run {"compiler": "java"}
  
import java.util.concurrent.ExecutorService;  
import java.util.concurrent.Executors;  
import java.util.concurrent.TimeUnit;  
  
public class Main {  
    static Object l1 = new Object();  
    static Object l2 = new Object();  
    static int a = 4;  
    static int b = 4;  
  
    public static void main(String args[]) throws Exception {  
        T1 r1 = new T1();  
        T2 r2 = new T2();  
        Runnable r3 = new T1(); Runnable r4 = new T2();  
        ExecutorService pool = Executors.newFixedThreadPool( 1 );  
        pool.execute( r1 );  
        pool.execute( r2 );  
        pool.execute( r3 );  
        pool.execute( r4 );  
  
        pool.shutdown();  
        while (!pool.awaitTermination(60, TimeUnit.SECONDS)) { }  
  
        System.out.println("a=" + a + "; b=" + b);  
    }  
  
    private static class T1 extends Thread {  
        public void run() {  
            synchronized (l1) {  
                synchronized (l2) {  
                    int temp = a;  
                    a += b;  
                    b += temp;  
                }  
            }  
        }  
    }  
  
    private static class T2 extends Thread {  
        public void run() {  
            synchronized (l2) {  
                synchronized (l1) {  
                    a--;  
                    b--;  
                }  
            }  
        }  
    }  
}
```
