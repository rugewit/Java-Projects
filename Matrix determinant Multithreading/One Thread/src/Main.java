import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.io.File;
import java.util.Scanner;


public class Main {
    public static void main(String[] args) {
        Matrix matrix = new Matrix();
        matrix.readData();
        long timeStart = System.currentTimeMillis();
        System.out.println("Default is " + Matrix.calcDeterminant(matrix));
        long timeEnd = System.currentTimeMillis();
        double elapsedTime = (double) (timeEnd - timeStart) / 1000;
        System.out.println("time is " + elapsedTime + "s");
    }


}
