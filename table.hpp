#include "context.hpp"

using namespace std;

class Table
{
public:
    Table();
    vector<vector<char>> get();
    bool isFull();
    void set(pair<int, int>, char);

private:
    vector<vector<char>> table;
};

Table::Table()
{
    table = vector<vector<char>>(8, vector<char>(8, EMPTY));
    table[3][3] = WHITE;
    table[4][4] = WHITE;
    table[3][4] = BLACK;
    table[4][3] = BLACK;
}

vector<vector<char>> Table::get()
{
    return table;
}

bool Table::isFull()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (table[i][j] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

void Table::set(pair<int, int> move, char color)
{
    auto [row, column] = move;

    if (row == -1 && column == -1)
        return;

    table[row][column] = color;

    for (auto [dr, dc] : DIRECTIONS)
    {
        int r = row + dr;
        int c = column + dc;
        if (r >= 0 && r < 8 && c >= 0 && c < 8 && table[r][c] != EMPTY && table[r][c] != color)
        {
            while (r >= 0 && r < 8 && c >= 0 && c < 8 && table[r][c] != EMPTY)
            {
                if (table[r][c] == color)
                {
                    while (r != row || c != column)
                    {
                        r -= dr;
                        c -= dc;
                        table[r][c] = color;
                    }
                    break;
                }
                r += dr;
                c += dc;
            }
        }
    }
}