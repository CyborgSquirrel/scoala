import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random r = new Random();
        int n = 100000000;

        int[] a = new int[n];
        int[] b = new int[n];
        int[] c = new int[n];

        for (int i = 0; i < n; ++i) {
            a[i] = r.nextInt(100);
            b[i] = r.nextInt(100);
            c[i] = 0;
        }

        long start_t = System.currentTimeMillis();

        int p = 1;
        Thread[] threads = new Thread[p];

        int start = 0;
        int end = 0;

        for (int i = 0; i < p; ++i) {
            int len = n/p;
            if (i < n%p) {
                len += 1;
            }

            end += len;

            threads[i] = new MyThreadSeq(i, start, end, a, b, c);
//            threads[i] = new MyThreadJump(i, p, n, a, b, c);
            threads[i].start();

            start += len;
        }
        for (int i = 0; i < p; ++i) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        System.out.println("Parallel time: " + (System.currentTimeMillis() - start_t)); // Single: 44

//        for (int i = 0; i < n; ++i) {
//            System.out.println(c[i] + " = " + a[i] + " + " + b[i]);
//        }
    }

    public static class MyThreadSeq extends Thread {
        int id;
        int start;
        int end;
        int[] a;
        int[] b;
        int[] c;
        public MyThreadSeq(int id, int start, int end, int[] a, int[] b, int[] c) {
            this.id = id;
            this.start = start;
            this.end = end;
            this.a = a;
            this.b = b;
            this.c = c;
        }
        public void run() {
            for (int i = this.start; i < this.end; ++i) {
                this.c[i] = this.a[i] + this.b[i];
            }
        }
    }

    public static class MyThreadJump extends Thread {
        int id;
        int p;
        int n;
        int[] a;
        int[] b;
        int[] c;
        public MyThreadJump(int id, int p, int n, int[] a, int[] b, int[] c) {
            this.id = id;
            this.p = p;
            this.n = n;
            this.a = a;
            this.b = b;
            this.c = c;
        }
        public void run() {
            for (int i = this.id; i < this.n; i += this.p) {
                this.c[i] = this.a[i] + this.b[i];
            }
        }
    }
}