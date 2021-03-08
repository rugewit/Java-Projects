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
        GlobalMatrix.matrixSize = 11;
        GlobalMatrix.threadSize = 11;
        GlobalMatrix.matrix = new Matrix(GlobalMatrix.matrixSize);

        GlobalMatrix.matrix.readData();

        long timeStart = System.currentTimeMillis();
        System.out.println("Det is " + ParallelThreadsCreator.calcDeterminant(GlobalMatrix.matrix));
        long timeEnd = System.currentTimeMillis();
        double elapsedTime = (double) (timeEnd - timeStart) / 1000;
        System.out.println("Time is " + elapsedTime + "s");
    }
}
