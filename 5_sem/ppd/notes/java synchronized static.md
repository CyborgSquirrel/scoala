`synchronized` `static` și ne-`static` nu se afectează unul pe celălalt. Adică poți da lock la ambele simultan.

Cred că asta este pentru că și clasa în sine este un obiect, și atunci când ai `synchronized` `static`, face lock efectiv pe obiectul acela, la fel cum atunci când ai `synchronized` ar face lock pe o obiectul reprezentând o instanță a clasei.

Așadar, dacă vrei să modifici variabile statice într-o manieră [[thread safe code|thread safe]], trebuie neapărat sa faci `synchronized` pe clasă.

```java
// run {"compiler": "java"}

class Main {  
    static class MyObject {  
        static int vStatic = 0;  
        int v = 0;  
  
        synchronized static void staticOp() {  
            System.out.println("staticOp enter");  
            vStatic += 5;  
            try {  
                Thread.sleep(500);  
            } catch (InterruptedException e) {  
                throw new RuntimeException(e);  
            }  
            System.out.println("staticOp exit");  
        }  
  
        synchronized void op() {  
            System.out.println("op enter");  
            v += 5;  
            try {  
                Thread.sleep(500);  
            } catch (InterruptedException e) {  
                throw new RuntimeException(e);  
            }  
            System.out.println("op exit");  
        }  
    }  
  
    public static void main(String[] args) throws Exception {  
        MyObject obj = new MyObject();  
        Thread t1 = new Thread(() -> {  
            MyObject.staticOp();  
        });  
        Thread t2 = new Thread(() -> {  
            obj.op();  
        });  
  
        t1.start();  
        t2.start();  
  
        t1.join();  
        t2.join();  
  
        System.out.println("vStatic = " + MyObject.vStatic);  
        System.out.println("v = " + obj.v);  
    }  
}
```
