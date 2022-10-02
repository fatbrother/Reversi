#include "context.hpp"
#include "playerBase.hpp"

using namespace std;

class Human : public PlayerBase
{
public:
    Human(char color);
    void lookTable(vector<vector<char>> table, vector<pair<int, int>>) override;
    pair<int, int> makeMove() override;
};

Human::Human(char color) : PlayerBase(color)
{
}

void Human::lookTable(vector<vector<char>> table, vector<pair<int, int>> canSet)
{
    for (auto [row, col] : canSet)
        table[row][col] = CANSET;

    cout << "Now is " << color << " turn." << endl;
    cout << "  1 2 3 4 5 6 7 8 col" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; j++)
        {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
    cout << "row" << endl;
}

pair<int, int> Human::makeMove()
{
    int row, column;
    cout << "Enter column: ";
    cin >> column;
    cout << "Enter row: ";
    cin >> row;

    return {row - 1, column - 1};
}