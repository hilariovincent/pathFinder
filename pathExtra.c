/*********************************************
 *This file will be where the maze gets solved
 *
 *@author: Vincent Hilario
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/*this function reads in the maze file and puts it 
  inside an array */
int readInFile()
{
  int c,i,j,n = 0;
  int *maze;
  int *path;

  for(c = getc(stdin); c != '\n'; c = getc(stdin))
  {
    n++;
  }
  rewind(stdin);

  maze = (int*) malloc((n*n)*sizeof(int));
  path = (int*) calloc((n*n),sizeof(int));
  path[0] = 1;
  path[(n*n) - 1] = 1;

  c = getc(stdin);
  i = 0;
  
  while (c != EOF)
  {
    if (c != '\n')
    {
      maze[i] = c;
      i++;
    }

    c = getc(stdin);
  }

  /*call recursive function*/
  if(!solveMaze(path, maze, n, 0))
  {
    printf("no path found.\n");
  }

  else
  {
    printf("PATH FOUND!\n");
    for (i = 0; i < n; i++)
    {
      for(j = 0; j < n; j++)
      {
	printf("%d" , path[i*n + j]);
      }
      printf("\n");
    }
  }

  free(path);
  free(maze);
  
  return 0;
}

/*recursive function that finds the path*/
int solveMaze(int *path, int *maze, int n, int i)
{
  int end = n * n - 1;

  /*change viewed spaces to 0 so recursion doesn't go through it again*/
  maze[i] = 0;
  path[i] = 1;

  /*base case*/
  if (i == end)
  {
    path[i] = 1;
    return 1;
  }

  /*go to the right first*/     
  if ((i + 1) % n != 0)
  {
    if (maze[i + 1] == '1')
    {
      if(solveMaze(path, maze, n, i+1))
      {
	return 1;
      }
      
    }
   
  }

  /*go down if no path of the right*/
  if ((i + n) <= (end))
  {
    if (maze[i + n] == '1')
    { 
      if(solveMaze(path, maze, n, i + n))
      {
	return 1;
      }
    }
  }

  path[i] = 0;
  return 0;
}

