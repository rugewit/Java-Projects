import random

MATRIX_SIZE = 11
MAX_MATRIX_VALUE = 10

f = open("C:/Users/rugiv/IdeaProjects/untitled1/src/input.txt", "w")

for i in range(MATRIX_SIZE):
    for j in range(MATRIX_SIZE):
        #print(random.randint(MAX_MATRIX_VALUE),end=' ')
        f.write(str(random.randint(0,MAX_MATRIX_VALUE)) + ' ')
    #print()
    f.write('\n')


f.close()
