import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.io.File;
import java.util.Scanner;


public class Main {
    public static void main(String[] args) {
        final int MATRIX_SIZE = 11;

        Matrix matrix = new Matrix(MATRIX_SIZE);
        matrix.readData();
        long timeStart = System.currentTimeMillis();
        System.out.println("Det is " + Matrix.calcDeterminant(matrix));
        long timeEnd = System.currentTimeMillis();
        double elapsedTime = (double) (timeEnd - timeStart) / 1000;
        System.out.println("Time is " + elapsedTime + "s");
    }


}
