#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<time.h>
#include<math.h>

#define   size_x  320  // declare the size of X axis
#define   size_y  384  // declare the size of Y axis


#define   smooth  3   // define the size of mask as 3


typedef struct
{
	int imagesize_x, imagesize_y; // "imagesize_x" & "imagesize_y" is
	                              // a user-defined data type, which
	                              // is equivalent to type int.
	int **pixel; // This declaration tells the compiler that "pixel"
	             // is a pointer to a pointer of type int. A pointer to
	             // a pointer is a form of multiple indirection, or a
	             // chain of pointers. The first pointer contains the
	             // address  of the second pointer, which point to the
	             // location that contains the desired value.
}image_t; // "image_t" is a user-defined data type

/* The following declaration is a user defined function prototype
   which data type is "image_t". It has two arguments which receives
   the value of X and Y axeses */

image_t allocate_image(const int imagesize_x, const int imagesize_y);

/* The following declaration checks the boundary value*/
int mod(int z, int l);

/* main function starts */
int main()
{
  image_t   image_noise,image_filtered; // This declaration defines
                                        // "image_noise" & "image_filter"
                                        // as structure variables of
                                        // type "image_t"

  int m,n,k,l,x,y,sum1,temp,csx,csy;

  /* FILE is a special built-in structure type that establishes the
     buffer area and is defined within a system "include" file ,
     typically "stdio.h". "*file_in" is a file input pointer variable
	 that indicates the beginning of the buffer area & "*file_out" is
     a file output variable that indicates the beginning of the buffer area */
  FILE *file_in,*file_out;
  char dummy[50]="";

  file_in=fopen("i9.pgm", "r+");

  file_out=fopen("avg_smooth_image.pgm", "w");

  fgets(dummy,50,file_in); // read 49 characters from "noise_image.pgm"
                           // and store in dummy
  do
  {
      fgets(dummy,50,file_in);
  }while(dummy[0]=='#');

  fgets(dummy,50,file_in);




  fprintf(file_out,"P2\n%d %d\n255\n",size_x,size_y);

  image_noise = allocate_image(size_x,size_y);
  image_filtered = allocate_image(size_x,size_y);

  for (n = 0; n < size_y; n++)
  {
    for (m = 0; m <size_x; m++)
     {
		fscanf(file_in,"%d",&image_noise.pixel[m][n]);

     }
  }



csx=smooth/2;
csy=smooth/2;

 for (n = 0; n < size_y; n++)
 {
   for (m = 0; m < size_x; m++)
   {
     sum1=0;
     for(k=0;k<smooth;k++)
	 {
       for(l=0;l<smooth;l++)
	   {

			x=m+k-csx; y=n+l-csy;

			sum1+=image_noise.pixel[mod(x,size_x)][mod(y,size_y)];

       }
     }
       image_filtered.pixel[m][n]=sum1/(smooth*smooth);

    }
   }


   /*   Writing image (pgm) file  */

   for (n = 0; n < size_y; n++)
   {
     for (m = 0; m < size_x; m++)
	 {

		fprintf(file_out,"%d ",image_filtered.pixel[m][n]);
     }
   }

 fclose(file_out);

}



//Sub routine

/* periodic extension (outside of the  image frame) */
  int mod(int z, int l)
  {
     if( z >= 0 && z < l )
		 return z;
     else if( z < 0)
		 return (z+l);
     else if( z > (l-1))
		 return (z-l);
  }




image_t allocate_image(const int imagesize_x, const int imagesize_y)
{
  image_t result;
  int x =  0, y = 0;

  result.imagesize_x = imagesize_x;
  result.imagesize_y = imagesize_y;

  result.pixel =(int **) calloc(imagesize_x, sizeof(int*));

  for(x = 0; x < imagesize_x; x++)
  {
    result.pixel[x] =(int*) calloc(imagesize_y, sizeof(int));

    for(y = 0; y < imagesize_y; y++)
    {
      result.pixel[x][y] = 0;
    }
  }

  return result;
}


