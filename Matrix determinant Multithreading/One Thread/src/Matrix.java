import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Matrix {
    int[][] data;

    public int size = 0;

    public Matrix(int size) {
        this.size = size;
        data = new int[this.size][this.size];
    }

    void print(){
       for(int i = 0;i < size; i++){
           for(int j = 0;j < size; j++){
               System.out.print(data[i][j] + " ");
           }
           System.out.println();
       }
    }

    void readData(){
        String fullPath = "C:/Users/rugiv/IdeaProjects/untitled1/src/input.txt";
        File file = new File(fullPath);
        if (file.exists() && file.canRead()){
            Scanner reader = null;
            try {
                reader = new Scanner(file);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
            for(int i = 0;i < size; i++){
                for(int j = 0;j < size; j++){
                    data[i][j] = reader.nextInt();
                }
            }
        }
        else {
            System.out.println("Problem with file");
        }
    }


    static Matrix getMinor(Matrix matrix,int row,int col){
        //checkBorders(matrix,row,col);
        Matrix resMatrix = new Matrix(matrix.size-1);
        int curI = 0, curJ = 0;
        for(int i = 0;i < matrix.size; i++){
            curJ = 0;
            if (i == row){
                continue;
            }
            for(int j = 0;j < matrix.size;j++){
                if (j != col){
                    resMatrix.data[curI][curJ] = matrix.data[i][j];
                    curJ++;
                }
            }
            curI++;
        }
        return resMatrix;
    }


    static long calcDeterminant(Matrix matrix){
        if (matrix == null){
            System.out.println("Matrix is null");
        }

        if (matrix.size == 0) {
            return 0;
        }
        else if (matrix.size == 1) {
            return matrix.data[0][0];
        }
        else if (matrix.size == 2) {
            return (long) matrix.data[0][0] * matrix.data[1][1]
                    - (long) matrix.data[0][1] * matrix.data[1][0];
        }
        else {
            long res = 0;
            for(int i = 0; i < matrix.size; i++){
                Matrix minor = getMinor(matrix,i,0);
                long calc = matrix.data[i][0] * calcDeterminant(minor);
                if (i % 2 == 1){
                    calc *= -1;
                }
                res += calc;
            }
            return res;
        }
    }

}