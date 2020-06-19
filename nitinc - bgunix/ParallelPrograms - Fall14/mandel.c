/*uthor: Melaku Muluneh..........06/26/00
 *! Mandelbrot set generation......Parallel version.
 *! The following is a parallel program that generates 
 *! a matrix of size ARRAYSIZE containing the 
 *! iteration values for each point in a complex plane.
 *! The number of iterations required to decide whether a 
 *! point is in the set is defined to be 'max'.
 *! This can be changed to get the resolution required. 
 *! These data values are used to draw the 'Mandelbrot diagarm'. 
 *! The number of nodes-1 should divide ARRAYSIZE evenly. 
 *! This ensures process balance.   
****************************************************************************/
  
  
  
  
  #include "mpi.h"
  #include <math.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include "mpi.h"
  #define ARRAYSIZE 1000000
  #define MASTER  0
  #define max 25600
  
  struct complex{
      int real;
      int imaginary;
  };
  
  int main(int argc, char *argv[]){

    
  
   int index, index1, index2, index3, i, j=0, keeper = 0, 
   numtasks=0, numworkers, taskid, dest, source, chunksize,
        ierr=0,countdummy, num;
   
  MPI_Status status;
  double lengthsq=0, value1=-2, value2=-1,imaginarypart2, 
  realpart2,temp, starttime, endtime;
  
  struct complex comppoint[ARRAYSIZE], z[ARRAYSIZE];
  int iterationcount[ARRAYSIZE];
  
   
  //! This call initializes the mpi environment. 'ierr' is either zero (success) or 
  //! an arbitrary number (depends on the implementation of mpi) signifying an error.
  ierr = MPI_Init(&argc, &argv);
  
  //! This finds the ID of a node. This ID is used in allocating processes to each node. 
  //! Again, 'ierr' contains error code.
  //! MPI_COMM_WORLD is the communicator universe. It can be defind to include only a certain number of nodes. 
  //! In this case, all nodes are included (default mode). 
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  
  //! The following command finds the number of nodes we have in the cluster. 'ierr' contains error code.
  //! The number of nodes is usually used in data distribution.
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  
  //! These lines are used for array distribution among the nodes. The master is left to control 
  //! the distribution and the assembly of the final (processed) data. 
  numworkers = numtasks - 1;
  chunksize = (ARRAYSIZE / numworkers);
  
  if ((numworkers * chunksize) != ARRAYSIZE){ 
    if(taskid == MASTER) {
      printf("Data will not be distributed evenly. This might leave some points unprocessed.:"); 
      printf("Please increase or decrease the number of nodes if you want all points to be included."); 
      printf("This run will continue neverthless.");
    }
  }

 //The following loop assigns the values of a rank one matrix of complex numbers. These values represent 
 //points near the origin. 
 starttime = MPI_WTIME();
 
 if(taskid == MASTER) {
 for(i=1;i<1000;i++){
     for (j = keeper*1000 +1; j< keeper*1000 + 1000; j++) {
       comppoint[index2].real =value1; 
       comppoint[index2].imaginary = value2;
       value2 = value2 + 0.0065;
     }
      value1 = value1 + 0.0065;
      keeper = keeper + 1;
      value2 = -1.5;
  }
   ierr = MPI_Type_Contiguous(2,MPI_REAL,MPI_COMPLEX);
   //! This sends the chunks of data to each process (node).  
   index = 1;
   for (dest = 1; dest < numworkers; dest++){
      ierr = MPI_Send(index, 1, MPI_INTEGER, dest, 0, MPI_COMM_WORLD);
           //! index is an integer, locating the starting position of the data in the matrix.
     //! 1 is the number of items to be sent (i.e. the number of indices)
     //! MPI_INTEGER is the data type
     //! dest is the id of the node the data is being sent to.
     //! 0 is the tag of the data. 
     //! MPI_COMM_WORLD is the communicator
     //! ierr is the error code storage place
      ierr = MPI_Send(comppoint[index], chunksize,MPI_COMPLEX, dest, 0, MPI_COMM_WORLD)
          // ! commppoint(index) specifies the starting point of the data.
    // ! chunksize is the extent or size of the data to be sent to the node
     //! MPI_COMPLEX is the data type 
    // ! dest is the id of the node the data is being sent to.
     //! 0 is the tag of the data...this is used to identify which data should be accepted by which computer. 
     //! MPI_COMM_WORLD is the comunicator universe.
     //! ierr stores the erro code. 
     //! here, we are not making use of this error code
      
      printf("data sent to node %d with index %d", dest, index);
      printf("-------------------------------------------");
      index = index + chunksize;
  
   for(i=1; i<numworkers; i++){
     source = i;
     
     //! data collection from slave nodes
     
     ierr = MPI_Recv(index, 1, MPI_INTEGER, source, 1, MPI_COMM_WORLD, status);
          
  //  ! index is the starting adress of the array portion.
   // ! 1 is the number of data items.
  //  ! MPI_INTEGER is data  type.
  //  ! source is the id of the source node.
  //  ! 1 is the tag of the message being transfered.
   // ! status contains information about the source, data size and tag.
   // ! ierr stores error code.
    
     ierr = MPI_Recv(iterationcount(index), chunksize, MPI_INTEGER, source, 1, MPI_COMM_WORLD, status);
         // ! all the variables have been defined earlier.
    
     printf("--------------------------------------------");
     printf("Receiving processed data from node %d",source);
   }
   
   outfile = fopen(mandelbrot.dat, "w");
   for(i=1;i<1000; i++){
     for (j=i*1000; j<i*1000+1000; j++){
       fprintf(outfile,"%d",iterationcount(j));
     }
       fprintf(outfile,"\n");
    }
 //open(UNIT=1, file='mandelbrotu.dat', status='replace', form='unformatted')
 //write (UNIT=1) iterationcount  

 //! open(unit=1, file='mandelbrot.dat',status='new')
 //! write(1,100) (iterationcount(i), i =1,1000000)
 //! 100 format (100I6)
 
 endtime = MPI_WTIME();
  printf("Total time: ",endtime - starttime);
 
 }
  
 //! the following is executed only by the slave nodes
 
 if(taskid > MASTER) {
   
   ierr = MPI_Recv(index, 1, MPI_INTEGER, MASTER, 0, MPI_COMM_WORLD, status);
   
   //  ! data being received from the master node. All variables have been discussed before. 
     
   ierr = MPI_Recv(comppoint[index], chunksize,COMPLEX, MASTER, 0, MPI_COMM_WORLD, status);
   
   for(i=0; i<1000000; i++){
    z(i).real = 0;
    z(i).imaginary = 0;
   }
    
    //! This loop finds the iteration values to get out of the mandelbrot set until some maximum value is reached.
    //! All points staying in the set upto this maximum iteration value are assumed to belong to the set.
    for(index3 = index; index3<index+chunksize; index3++){
     countdummy = 0;
     lengthsq = 0;
       while (lengthsq < 4.0 && countdummy < max){
         temp =z[index3].real^2 - z[index3].imaginary^2 + comppoint[index3].real;
         imaginarypart2 = 2 *z[index3].real *z[index3].imaginary +comppoint[index3].imaginary;
         realpart2 = temp;
   z[index3].real =realpart2;
   z[index3].imaginary = imaginarypart2;
         lengthsq = z[index3].real^2 + z[index3].imaginary^2;
   countdummy = countdummy + 1;
   iterationcount[index3] = countdummy;
       }
    }
 
 // ! send back data to the master node. 
 ierr = MPI_Send(index, 1, MPI_INTEGER, MASTER, 1, MPI_COMM_WORLD);
 ierr = MPI_Send(iterationcount[index], chunksize, MPI_INTEGER, MASTER, 1, MPI_COMM_WORLD); 
 
 }
 ierr = MPI_Finalize();
}