```java
// run {"compiler": "java"}
  
import java.util.ArrayList;  
import java.util.concurrent.Callable;  
import java.util.concurrent.ExecutorService;  
import java.util.concurrent.Executors;  
import java.util.concurrent.Future;  
  
class Main {  
    static final int threadsThresh = 10;  
  
    public static class MergeSort implements Callable<Void> {  
        ExecutorService executor;  
        ArrayList<Integer> list;  
        int lt;  
        int rt;  
        public MergeSort(ExecutorService executor, ArrayList<Integer> list, int lt, int rt) {  
            this.executor = executor;  
            this.list = list;  
            this.lt = lt;  
            this.rt = rt;  
        }  
  
        @Override  
        public Void call() throws Exception {  
            int len = rt - lt + 1;  
            if (len <= 1) return null;  
  
            int mid = lt + len/2;  
            Future<Void> fLt = executor.submit(new MergeSort(executor, list, lt, mid-1));  
            Future<Void> fRt = executor.submit(new MergeSort(executor, list, mid, rt));  
  
            fLt.get();  
            fRt.get();  
  
            ArrayList<Integer> tmp = new ArrayList<>();  
            tmp.ensureCapacity(len);  
            int lti = lt;  
            int rti = mid;  
            while (lti <= mid-1 || rti <= rt) {  
                if (lti > mid-1) {  
                    tmp.add(list.get(rti));  
                    rti++;  
                } else if (rti > rt) {  
                    tmp.add(list.get(lti));  
                    lti++;  
                } else {  
                    if (list.get(lti) < list.get(rti)) {  
                        tmp.add(list.get(lti));  
                        lti++;  
                    } else {  
                        tmp.add(list.get(rti));  
                        rti++;  
                    }  
                }  
            }  
  
            for (int i = 0; i < len; ++i) {  
                list.set(lt+i, tmp.get(i));  
            }  
  
            return null;  
        }  
    }  
  
    public static void main(String[] args) throws Exception {  
        ExecutorService executor = Executors.newFixedThreadPool(threadsThresh);  
        ArrayList<Integer> list = new ArrayList<>();  
        list.add(5);  
        list.add(7);  
        list.add(1);  
        list.add(3);  
        list.add(8);  
        list.add(10);  
        list.add(3);  
  
        Future<Void> f = executor.submit(new MergeSort(executor, list, 0, list.size()-1));  
        f.get();  
        executor.shutdown();  
        for (Integer integer : list) {  
            System.out.println(integer);  
        }  
    }  
}
```