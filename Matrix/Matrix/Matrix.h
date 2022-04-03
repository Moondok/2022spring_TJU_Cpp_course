#pragma once
#define MAXSIZE 100

//在一个功能结束后获取是否返回主菜单的指令
int return_menu();

//等一个回车
void wait_for_enter();

//打印菜单
char present_menu();

//输入一个行/列值
int input_size(int flag);

//输出一个nrows行,ncols列的矩阵
void output_matrix(int* matrix, int nrows, int ncols);

//输入一个nrows行,ncols列的矩阵
void input_matrix(int* matrix, int nrows, int ncols,bool is_conv=false);

//实现矩阵加法（不包括输入输出
int* inner_plus(int* matrix1, int* matrix2, int nrows, int ncols);

//输出矩阵相加/哈达玛乘积的运算式
void output_plus_hadam(int* matrix1, int* matrix2, int* result, int nrows, int ncols, const char choice);

//实现矩阵数乘功能，被main直接调用
void nummulti();

//实现矩阵数乘，不包括输入输出
int* inner_nummulti(int* matrix1, int nrows, int ncols, int multiplier);

//输入数乘时的乘数
int input_multiplier();

//打印每个功能开始前的标题
void present_title(const char* content);

//实现哈达玛乘积（不包括输入输出）
int* inner_hadamulti(int* matrix1, int* matrix2, int nrows, int ncols);

//实现矩阵转置，被main调用
void matritrans();

//实现矩阵转置，不包括输入输出
int* inner_trans(int* matrix, int nrows, int ncols);

//实现矩阵乘法，被main调用
void matrimulti();

//实现矩阵乘法，不包括输入输出
int* inner_matrimulti(int* left_matrix, int* right_matrix, int nrows, int npivot, int ncols);

//输出矩阵乘法的算式
void output_matrix_multi(int* matrix1, int* matrix2, int* result, int nrows, int npivot, int ncols);

//实现卷积功能
void conv();

//实现对lena的卷积
void conv_application();

//实现卷积功能（不包括输入输出）
int* inner_conv(int* matrix, int* conv_kernel, int nrows, int ncols, bool is_normalize = false);

//实现OTSU算法
void OSTU_demo();
