#include<stdio.h>
#include<iostream>
#include<cmath>
//PI
#include<bits/stdc++.h>

struct quaternion{
  double real;
  double imaginary[3];
};

double vector_dot(const quaternion *q1 , const quaternion * q2){
  double cross = ( q1->imaginary[0] * q2->imaginary[0] ) + ( q1->imaginary[1] * q2->imaginary[1] ) + ( q1->imaginary[2] * q2->imaginary[2] );
  return cross;
}

void vector_cross(const quaternion *q1 , const quaternion *q2 , quaternion *ans){
  //https://mathwords.net/gaiseki
  ans->imaginary[0] += ( q1->imaginary[1] * q2->imaginary[2] ) - ( q1->imaginary[2] * q2->imaginary[1] );
  ans->imaginary[1] += ( q1->imaginary[2] * q2->imaginary[0] ) - ( q1->imaginary[0] * q2->imaginary[2] );
  ans->imaginary[2] += ( q1->imaginary[0] * q2->imaginary[1] ) - ( q1->imaginary[1] * q2->imaginary[0] );
}


void quaternion_times(const quaternion *q1 , const quaternion *q2 , quaternion *ans){
  ans->real = (q1->real * q2->real) - (vector_dot(q1 , q2) ) ;
  //imaginary
  ans->imaginary[0] = (q1->real * q2->imaginary[0]) + (q2->real * q1->imaginary[0]);
  ans->imaginary[1] = (q1->real * q2->imaginary[1]) + (q2->real * q1->imaginary[1]);
  ans->imaginary[2] = (q1->real * q2->imaginary[2]) + (q2->real * q1->imaginary[2]);
  //cross
  vector_cross(q1 , q2 , ans);
  
}

void quaternion_disp( quaternion *q1 ){
  std::cout << "real:" << q1->real  << "," <<  "xyz:" << q1->imaginary[0] << "," <<  q1->imaginary[1] << "," << q1->imaginary[2] << std::endl;
}

int main(void){

  //回転させたい角度
  int rotate_deg = 90;
  double rotate_rad = (double)rotate_deg * (M_PI/180.0);
  //回転軸
  double x_axis = 1.0;
  double y_axis = 0.0;
  double z_axis = 0.0;
  //回転元
  quaternion p = { 0 , 1 , 2 , 0 };
  //クォータニオンと共役クォータニオン
  quaternion q = { std::cos(rotate_rad/2) , x_axis * std::sin(rotate_rad/2) , y_axis * std::sin(rotate_rad/2) , z_axis * std::sin(rotate_rad/2) };
  quaternion r = { std::cos(rotate_rad/2) , -1.0 * x_axis * std::sin(rotate_rad/2) , -1.0 * y_axis * std::sin(rotate_rad/2) , -1.0 * z_axis * std::sin(rotate_rad/2) };
  //演算結果
  //rpq = (0 ; ans)
  quaternion rp = {0 , 0 , 0 , 0 };
  quaternion rpq = {0 , 0 , 0 , 0 };

  quaternion_times( &r , &p , &rp);
  quaternion_times( &rp , &q , &rpq);
  quaternion_disp(&rpq);


  quaternion_times( &q , &p , &rp);
  quaternion_times( &rp , &r , &rpq);
  quaternion_disp(&rpq);

}
