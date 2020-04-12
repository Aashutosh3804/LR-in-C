#include<stdio.h>
#include<windows.h>
#include "koolplot.h"
void read(char *b,float*m);
float dot(float *a,float *err);
float  error(float *b,float*c,float *err);
void y_hat(float *a,float m,float b,float *c);
float err_sum(float *err);

int i=0;
float m=1,j=1;
int main(){

  float a[42],b[42],c[42],err[42];
  read("dates.txt",a);
  read("prices.txt",b);
  

   float grad_m,grad_j,err_su;
 
   double l[42],n[42];
   for(i=0;i<42;i++){
     
	 l[i]=(double)a[i];
   
   }
   for(i=0;i<42;i++){
     
	 n[i]=(double)b[i];
   
   }
for(int k=0;k<36000;k++){
   y_hat(a,m,j,c);
   error(b,c,err);
   err_su=err_sum(err);

   grad_m=((float)-1/42)*(dot(a,err));
   grad_j=((float)-1/42)*err_su;
   m=m-0.001*grad_m;
   j=j-0.001*grad_j;
    
   if(k%1000==0){
   printf("Error=%f\n",err_su);
 
 Plotdata z(l,41);
   Plotdata k(n,41);
   breakplot(z,k);
 Plotdata p(0, 41), y = m*p+j; 
 z<<p;
 k<<y; 
  plot(z, k);
    
   }
 }
 printf("\n");
   //for (i=0;i<42;i++)printf("%f\t",err[i]);
   printf("%f\t %f\n",m,j);
   for(i=0;i<42;i++){
     printf("days:%f\t Exact values:%f\t Predicted Values:%f\n",a[i]+1,b[i],(m*a[i]+j));
   }
   _fcloseall();
   return 0;
  
}

void read(char *b,float *m){
  FILE *fp = fopen(b, "r");
  i=0;
  float number;
  int res;
    while((res = fscanf(fp, "%f",&number)) != EOF){
        if(res == 1){
            m[i]=number;
            i++;
        }else{
          printf("error");
        }
    }


}

void y_hat(float *a,float m,float b,float *c){
  for (i=0;i<42;i++){
    c[i]=a[i]*m+b;
  }
}
float dot(float *a,float *err){
   float sum=0;
   for(i=0;i<42;i++){
     sum+=a[i]*err[i];
   }
  return sum;
}

float  error(float *b,float*c,float *err){
  for(i=0;i<42;i++){
    err[i]=(b[i]-c[i]);
  }
}

float err_sum(float *err){
  float sum=0;
  for(i=0;i<42;i++){
    sum=sum+(err[i]);
  }
  return sum;
}

