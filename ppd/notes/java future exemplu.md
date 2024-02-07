```java
// run {"compiler": "java"}
  
import java.util.ArrayList; 
import java.util.concurrent.Callable; 
import java.util.concurrent.ExecutorService; 
import java.util.concurrent.Executors; 
import java.util.concurrent.Future; 
  
class Main {  
    static final int threadsThresh = 4; 
    static final int threadsNo = 20; 
  
    public static class MyCallable implements Callable<Long> { 
        public MyCallable() {
        }
  
        @Override  
        public Long call() throws Exception {  
            long sum = 0;  
            for (int i = 0; i < 100; ++i) {  
                sum += i;  
            }  
            return sum;  
        }  
    }  
  
    public static void main(String[] args) throws Exception {  
        ExecutorService executor = Executors.newFixedThreadPool(threadsThresh);  
        ArrayList<Future<Long>> tasks = new ArrayList<>();  
        for (int i = 0; i < threadsNo; ++i) {  
            tasks.add(executor.submit(new MyCallable()));  
        }  
        executor.shutdown();  
        for (Future<Long> task : tasks) {  
            System.out.println(task.get());  
        }  
    }  
}
```