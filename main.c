#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <locale.h>

unsigned int metod(void);

double left_p ( double a, double b, unsigned int n );
double right_p( double a, double b, unsigned int n );
double trap   ( double a, double b, unsigned int n );
double simpson( double a, double b, unsigned int n );
double f(double x);

void resultat(double a, double b, unsigned int n, double I);

int main()
{
    setlocale(LC_ALL, "Rus");
    unsigned int num_of_method;
    unsigned int n=100;
    const double a = 0;
    const double b = 1;
    double I, I1, I2;
    double maxpoh = 0.00001;
    unsigned int N=0;

    num_of_method  =  metod();
    printf("\n\nВедiть кiлькiсть промiжкiв:");
    scanf("%u",&n);
    printf("\n\nНатиснiть будь яку клавiшу щоб продовжити\n");
    getch();

    //----------------------------------------------------------//
    if (num_of_method == 1 )
    {
       I = left_p(a, b, n);
       N = 0;
       do
        {
           N = N + 2;
           I1 = left_p(a, b, N);
           I2 = left_p(a, b, N+2);
        }
        while(fabs(I2-I1) > maxpoh);

        resultat(a, b, n, I );
        printf("\n\nкiлькiсть розбитiв для допустимоi похибки:\n\nN=%u,  Integral(N)=%.8lf\n\n\n\n", N, I1);

    }//----------------------------------------------------------//
       else if( num_of_method == 2 )
    {
       I=right_p(a, b, n);
       do
       {
           N = N + 2;
           I1 = right_p(a, b, N);
           I2 = right_p(a, b, N+2);
       }
       while(  fabs(I2-I1) > maxpoh );

        resultat(a, b, n, I);
        printf("\n\nкiлькiсть розбитiв для допустимоi похибки:\n\nN=%u,  Integral(N)=%.8lf\n\n\n\n", N, I1);
    }//--------------------------------------------------------------//
   else if( num_of_method == 3 )
   {
        I=trap(a, b, n);
       do{
           N = N + 2;
           I1 = trap(a, b, N);
           I2 = trap(a, b, N+2);
        }
        while(  fabs(I2-I1) > maxpoh);

        resultat(a, b, n, I);
        printf("\n\nкiлькiсть розбитiв для допустимоi похибки:\n\nN=%u,  Integral(N)=%.8lf\n\n\n\n", N, I1);

    }//------------------------------------------------------------//
  else if( num_of_method == 4 )
   {
       I=simpson(a, b, n);
       do
        {
           N = N + 2;
           I1 = simpson(a, b, N);
           I2 = simpson(a, b, N+2);
        }
       while(  fabs(I2-I1) > maxpoh);

        resultat(a, b, n, I);
        printf("\n\nкiлькiсть розбитiв для допустимоi похибки:\n\nN=%u,  Integral(N)=%.6lf\n\n\n\n", N, I1);
   }
    return 0;
}
//---------------------------------------------------------------------
unsigned int metod(void)
{
    unsigned int m;
    printf("\n\n Оберiть метод:\n1 - лiвих прямокутникiв \n2 - правих прямокутникiв \n3 - трапецii \n4 - сiмпсона\n>");
    scanf("%u", &m);

    while(  m < 1  ||   m > 4 )
    {
        printf("\n!!!Ведене не вiрне число!!!(1,2,3,4?) ");
        scanf("%u", &m);
    }
    switch(m){
      case 1:
             printf("\nВи обрали метод --лiвих прямокутникiв--");
             break;
      case 2:
             printf("\nВи обрали метод --правих прямокутникiв--");
             break;
      case 3:
             printf("\nВи обрали метод --трапецiй--");
             break;
      case 4:
             printf("\nВи обрали метод --Сiмпсона--");
             break;
    }


    return m;
}

//-------------------------------------------------------------------

double f( double x )
{
    double funk;
    funk = (1/(4+pow(x,2)));
    return funk;
}
//---------------------------------------------------------------------

double left_p(double a, double b, unsigned int n)
{
    double integral;
    double h;
    double x;
    double sum = 0;
    unsigned int k;

    h = ( b - a ) / n;
    x = a;

    for (k = 0;  k <= n-1;  k++ )
    {
      sum = sum + f(x);
      x = x + h;
    }
    integral = sum * h;
    return integral;
}//------------------------------------------------------
double right_p(double a, double b, unsigned int n)
{
    double integral;
    double h;
    unsigned int k;
    double x;
    double sum = 0;

    h = ( b - a ) / n;
    x = a;

    for (k = 1;  k <= n;  k++ )
    {
      sum = sum + f(x);
      x = x + h;
    }

    integral = sum * h;
    return integral;
}//--------------------------------------------------------
double trap(double a, double b, unsigned int n)
{
    double integral;
    double h;
    unsigned int k;
    double x;
    double sum = 0;
    sum = f(a)+f(b);
    h = ( b - a )/n;
    x = a;

    for (k = 1;  k <= n-1;  k++ ){
      sum = (sum + f(x));
      x = x + h;
    }

    integral = sum * h;
    return integral;
}//-------------------------------------------------------
double simpson(double a, double b, unsigned int n)
{
    double integral;
    double h;
    unsigned int k;
    double x;
    double sum1 = 0;
    double sum2 = 0;

    h=(b - a)/n;
    x = a;

    for (k = 0;  k <= n;  k++ ){
      if(k%2 != 0)
       {
        sum1=sum1+f(a+h*k);
       }
        if(k%2 == 0)
       {
        sum2=sum2+f(a+h*k);
       }
    }

    integral = ((b-a)/(n*3))*(f(a)+4*sum1+2*sum2+f(b));
    return integral;
}
//-------------------------------------------------------------------

void resultat(double a, double b, unsigned int n, double I)
{
    system("cls");
    printf("\n\na=%.2lf  b=%.2lf   n=%u    Integral = %.6lf   \n ", a, b, n, I);
}
