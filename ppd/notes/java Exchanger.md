Constructori:
- `Exchanger()`

Metode:
- `V exchange(V v)`

Așteaptă să se întâlnească două thread-uri la punctul de exchange. Apoi se întâmplă schimbul de mesaje între thread-uri, și ele pot să continue.

```java
// run {"compiler": "java"}
  
import java.util.concurrent.Exchanger;  
  
class Main {  
    public static void main(String[] args) throws Exception {  
        Exchanger<Integer> exchanger = new Exchanger<>();  
  
        Thread t1 = new Thread(() -> {  
            int send = 10;  
            int recv;  
            System.out.println("t1 exchanging; send = " + send);  
            try {  
                recv = exchanger.exchange(send);  
            } catch (InterruptedException e) {  
                throw new RuntimeException(e);  
            }  
            System.out.println("t1 recv = " + recv);  
        });  
        Thread t2 = new Thread(() -> {  
            int send = 25;  
            int recv;  
            System.out.println("t2 exchanging; send = " + send);  
            try {  
                recv = exchanger.exchange(send);  
            } catch (InterruptedException e) {  
                throw new RuntimeException(e);  
            }  
            System.out.println("t2 recv = " + recv);  
        });  
  
        t1.start();  
        t2.start();  
  
        t1.join();  
        t2.join();  
    }  
}
```
