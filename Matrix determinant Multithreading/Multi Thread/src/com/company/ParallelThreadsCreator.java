package com.company;

import java.util.ArrayList;
import java.util.List;

public class ParallelThreadsCreator {


    public static long calcDeterminant(Matrix matrix) {
        List<Thread> threads = new ArrayList<>();
        List<CofactorWorker> tasks = new ArrayList<>();

        List<Integer> linesForThreading = null;

        try {
            linesForThreading = Matrix.splitLinesForThreading(matrix.size,GlobalMatrix.threadSize);
        } catch (Exception e) {
            e.printStackTrace();
        }

        int curLine = 0;

        for (int i = 0; i < GlobalMatrix.threadSize; i++) {
            int linesCount = linesForThreading.get(i);
            int[] row = new int [linesCount];
            int[] col = new int [linesCount];

            for(int j = 0;j < linesCount; j++){
                row[j] = curLine;
                col[j] = 0;
                curLine++;
            }
            CofactorWorker task = new CofactorWorker(linesForThreading.get(i), row, col);
            tasks.add(task);
            Thread thread = new Thread(task);
            thread.start();
            threads.add(thread);
        }

        for (Thread element : threads) {
            try {
                element.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        long result = 0;

        for(int i = 0;i < GlobalMatrix.threadSize; i++){
            result += tasks.get(i).result;
        }

        return result;
    }

    /*
    private static void waitForThreads(List<Thread> threads) {
        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        threads.clear();
    }
    */

}
