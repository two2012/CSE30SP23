/**
 * Assignment: life
 * Name :Wen Guo
 * PID: A17630856
 * Class: UCSD CSE30-SP21
 *
 */
#include "cse30life.h"
#include "board.h"

/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t *createBoard(char *initFileName)
{
  // TODO:
  FILE *fp;
  // malloc a boards structure
  boards_t *board = malloc(sizeof(boards_t));
  // set the generation to 0
  board->gen = 0;
  // open file
  if ((fp = fopen(initFileName, "r")) == NULL)
  {
    fclose(fp);
    free(board);
    return NULL;
  }
  // read the first two lines which are the number of rows and cols
  if (fscanf(fp, "%zd", &board->numRows) != 1)
  {
    fclose(fp);
    free(board);
    return NULL;
  }
  if (fscanf(fp, "%zd", &board->numCols) != 1)
  {
    fclose(fp);
    free(board);
    return NULL;
  }
  // malloc bufferA and bufferB
  board->bufferA = calloc(board->numRows * board->numCols, sizeof(belem));
  board->bufferB = calloc(board->numRows * board->numCols, sizeof(belem));
  if (!board->bufferA || !board->bufferB)
  {
    fclose(fp);
    free(board->bufferA);
    free(board->bufferB);
    free(board);
    return NULL;
  }
  // set currentBuffer and nextBuffer
  board->currentBuffer = board->bufferA;
  board->nextBuffer = board->bufferB;
  // clear both board buffers
  clearBoards(board);
  // read the file until done and set the cell in the current buffer
  int row, col;
  while (fscanf(fp, "%d %d", &row, &col) == 2)
  {
    board->currentBuffer[(row * board->numCols) + col] = 1;
    board->nextBuffer[(row * board->numCols) + col] = 1;
  }

  fclose(fp);
  return board;
}

/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr)
{
  // TODO:
  // free the memory associated with the board
  free((*bptrPtr)->bufferA);
  free((*bptrPtr)->bufferB);
  free(*bptrPtr);
  *bptrPtr = NULL;
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self)
{
  // TODO:
  // set all values in bufferA and bufferB to 0
  memset(self->bufferA, 0, self->numRows * self->numCols * sizeof(belem));
  memset(self->bufferB, 0, self->numRows * self->numCols * sizeof(belem));
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self)
{
  // TODO:
  // swap the current and next buffers
  belem *temp = self->currentBuffer;
  self->currentBuffer = self->nextBuffer;
  self->nextBuffer = temp;
}

/**
 * get a cell index
 */
size_t getIndex(size_t numCols, size_t row, size_t col)
{
  // TODO:
  return row * numCols + col;
}
