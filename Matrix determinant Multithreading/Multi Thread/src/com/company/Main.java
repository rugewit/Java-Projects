package com.company;

import com.company.Matrix;

import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.io.File;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        GlobalMatrix.threadSize = 11;
        GlobalMatrix.matrix = new Matrix();

        GlobalMatrix.matrix.readData();

        long timeStart = System.currentTimeMillis();
        System.out.println("Parallel is " + ParallelThreadsCreator.calcDeterminant(GlobalMatrix.matrix));
        long timeEnd = System.currentTimeMillis();
        double elapsedTime = (double) (timeEnd - timeStart) / 1000;
        System.out.println("time is " + elapsedTime + "s");
    }
}
