package com.company;

public class CofactorWorker implements Runnable{

    private int length;
    private int[] row;
    private int[] col;
    public long result = 0;

    public CofactorWorker(int length, int[] row, int[] col) {
        this.length = length;
        this.row = row;
        this.col = col;
    }

    @Override
    public void run() {
        for(int i = 0;i < length; i++){
            Matrix minor = Matrix.getMinor(GlobalMatrix.matrix,row[i],col[i]);
            long calc = (GlobalMatrix.matrix.data[row[i]][0]) * Matrix.calcDeterminant(minor);
            if (row[i] % 2 == 1){
                calc *= -1;
            }
            result += calc;
        }
    }
}
