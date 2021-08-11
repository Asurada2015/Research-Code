#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <time.h>
#include <armadillo>
#include "functions.h"
using namespace std;

void print_mat_matlab(mat &D) {

    puts("[");
    for(int i = 0; i < D.n_rows; ++i) {
        printf("[");
        for(int j = 0; j < D.n_cols; ++j) {
            if(j) printf(",");
            printf("%f ", D(i, j));
        }
        puts("]");
    }
    puts("]");
    system("pause");
}

undelimiter_individual transferOperation(delimiter_individual &ind, int customer_size, mat &M, mat &original_dist, int K) {

//    puts("\nind---------old---------start");
//    print_one_dim_array(ind.sequence, ind.count);
//    printf("fitness: %f\n", ind.fitness);
//    puts("ind-----------old---------end\n");
//    ��problem�����Ž�ת���ɾ������D
    mat DL = getDisMat(customer_size, ind);
//    puts("DL:");
//    print_mat_int(DL);
//    print_mat_matlab(DL);

//    �ֽ�������õ���������f*n
//    ok
    mat FL = getMultiDimensionScaling(DL);

//    puts("FL");
//    print_mat_float(FL);
//    puts("check FL");
//    print_MDS(FL);

//    float error_fitness = calc_error(FL, DL);
//    printf("error: %f\n", error_fitness);
//    puts("M:");
//    print_mat_float(M);

//    ͨ����������ת����Ϣ
    mat FR = FL * M;

//    puts("FR:");
//    print_mat_float(FR);
//    puts("check FR:");
//    print_MDS(FR);
//    float error_fitness = calc_error(FR, DL);
//    printf("error: %f\n", error_fitness);

//    ͨ�������Լ�pairwise sorting�õ�2��Ⱦɫ��

    undelimiter_individual chromosome = kMeans(FR, K, original_dist);

//    puts("\nchr---------ans---------start");
//    print_one_dim_array(chromosome.sequence, chromosome.count);
//    puts("chr-----------ans---------end\n");

    return chromosome;
}
undelimiter_individual selfInsertOperation(delimiter_individual &ind, int customer_size, mat &original_dist, int K) {

//    puts("\nind---------old---------start");
//    print_one_dim_array(ind.sequence, ind.count);
//    puts("ind-----------old---------end\n");
//    ��problem�����Ž�ת���ɾ������D
    mat D = getDisMat(customer_size, ind);
//    D.print("D: ");
//    �ֽ�������õ���������f*n
    mat F = getMultiDimensionScaling(D);


//    ͨ�������Լ�pairwise sorting�õ�Ⱦɫ��
    undelimiter_individual chromosome = kMeans(F, K, original_dist);
//    puts("\nchr---------new---------start");
//    print_one_dim_array(chromosome.sequence, chromosome.count);
//    puts("chr-----------new---------end\n");

    return chromosome;
}
float OPT(Problem &problem, undelimiter_individual &chromesome, int current_size, string problem_n, int op) {

    delimiter_individual del_c;

    /*��Ǩ�Ƶ�childִ��split�����һ��individual */
    if(!new_split(&del_c, &chromesome, problem))
        return 0;
    return add_to_problem(del_c, problem, op);
}
