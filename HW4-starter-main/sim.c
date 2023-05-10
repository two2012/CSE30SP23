/**
 * Assignment: life
 * Name: TODO
 * PID: A17630856
 * Class: UCSD CSE30-SP21
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, size_t, size_t, size_t);

/**
 * gets x mod N (works for negative numbers as well! Use this instead of %)
 */
size_t getModVal(int x, size_t N)
{
  size_t adj = x / N;

  return ((x + adj * N) % N);
}

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *src, size_t row, size_t rows, size_t cols)
{
  // TODO:
  // calculate the alive neighbors for each cell in the row
  for (size_t i = 0; i < cols; i++)
  {
    int alive_neighbors = 0;

    // check surrounding cells for each cell in the row
    for (size_t j = -1; j < 2; j++)
    {
      for (size_t k = -1; k < 2; k++)
      {
        if (j == 0 && k == 0)
        {
          continue;
        }
        if (src[(getModVal(row + j, rows) * cols) + k] == 1)
        {
          alive_neighbors++;
        }
      }
    }

    // update the cell state in the destination buffer
    if (src[row * cols + i] == 1)
    { // If the cell is alive
      if (alive_neighbors < 2 || alive_neighbors > 3)
      {
        dest[row * cols + i] = 0; // The cell dies
      }
      else
      {
        dest[row * cols + i] = 1; // The cell stays alive
      }
    }
    else
    { // If the cell is dead
      if (alive_neighbors == 3)
      {
        dest[row * cols + i] = 1; // The cell becomes alive
      }
      else
      {
        dest[row * cols + i] = 0; // The cell stays dead
      }
    }
  }
}

/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, unsigned int steps)
{
  // TODO:

  for (size_t i = 0; i < steps; i++)
  {
    // calculate the next board
    for (size_t j = 0; j < self->numRows; j++)
    {
      doRow(self->nextBuffer, self->currentBuffer, j, self->numRows, self->numCols);
    }
  }
  // swap current and next
  swapBuffers(self);
}