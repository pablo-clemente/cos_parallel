/*
 cos.c code for cosine function
 Copyright (C) <2020>  Pablo Clemente Moreno (clemnte@comunidad.unam.mx)

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.



 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <mpi.h>
#include "Timming.h"

int main(int nargs, char **argv){
  int miproc;
  int numproc;
  
  float a = 0.0;
  float b = 0.0;
  float dx = 0.1;
  float x = 0.0;
  int n=0;
  float dN =0;
  float a0;
  float b0;
  float y;

  double utime0, stime0, wtime0,
         utime1, stime1, wtime1,
         utime2, stime2, wtime2;
  
  MPI_Init (&nargs, &argv); /* Inicializar MPI*/
  MPI_Comm_rank(MPI_COMM_WORLD,&miproc); /*Determinar el rango del proceso invocado*/
  MPI_Comm_size(MPI_COMM_WORLD,&numproc); /*Determinar el numero de procesos*/
  MPI_Barrier (MPI_COMM_WORLD);

  if (miproc==0){
    printf("I'am 0 process.\n");
    uswtime(&utime0, &stime0, &wtime0); //toma el tiempo

  }
    /*for (int i=0;i<nargs;i++){
        printf("%s\n", argv[i]);
    }*/
    if (nargs != 4){
        printf("Number of arguments wrong. You need 2 arguments.\n");
        return 0;
    }
    sscanf(argv[1],"%f",&a);
    sscanf(argv[2],"%f",&b);
    sscanf(argv[3],"%f",&dx);
    dN = (b-a)/numproc;
    a0 = a+miproc*dN;
    b0 = a+(miproc+1)*dN;
      
    n = (b0-a0)/dx + 1;
    printf("n=%i\n",n);
    x=a0;
    for (int i=1;i<=n;i++){
      y= f(x);
      //printf("%f\t%f\n",x,f(x));
      //x = x+dx;
      // nunca sumar 0.1
      x = a0+ i*dx;
    }

    MPI_Barrier (MPI_COMM_WORLD);
    if (miproc==0){
    //printf("I'am 0 process.\n")
    uswtime(&utime1, &stime1, &wtime1); //toma el tiempo
    printf("\nBenchmarks (sec):\n");
    printf("real %.3f\n", wtime1 - wtime0);
    printf("user %.3f\n", utime1 - utime0);
    printf("sys %.3f\n", stime1 - stime0);
    printf("\n");
    printf("CPU/Wall %.3f %% \n", 100.0 * (utime1 - utime0 * stime1 - stime0)/(wtime1 - wtime0));
    printf("\n");

  }
  MPI_Finalize();
  return 0;
}
