#include "Ranking.h"
extern int PuzzleGame();
void main()
{
    loadRanking("ranking.txt");
    int rank = PuzzleGame();
    printRanking();
    storeRanking("ranking.txt");
}
