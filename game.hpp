#include "context.hpp"
#include "table.hpp"
#include "human.hpp"

using namespace std;

class Game
{
public:
    Game();
    void start();

private:
    void gameLoop();
    pair<int, int> processEvents(vector<pair<int, int>> &);
    void update(pair<int, int>);
    void render(vector<pair<int, int>> &);
    bool isGameOver();
    bool isMoveValid(vector<pair<int, int>> &, pair<int, int>);
    vector<pair<int, int>> canSet(char color);
    char getWinner();

    Table table;
    int currentPlayer;
    vector<unique_ptr<PlayerBase>> players;
};

Game::Game()
{
    table = Table();
}

void Game::start()
{
    players.push_back((unique_ptr<PlayerBase>)make_unique<Human>(BLACK));
    players.push_back((unique_ptr<PlayerBase>)make_unique<Human>(WHITE));
    currentPlayer = 0;
    gameLoop();
}

void Game::gameLoop()
{
    while (!isGameOver())
    {
        auto canSet = this->canSet(players[currentPlayer]->getColor());
        render(canSet);
        pair<int, int> move = processEvents(canSet);
        update(move);
    }

    auto winner = getWinner();
    if (winner == BLACK)
        cout << "Black wins!" << endl;
    else if (winner == WHITE)
        cout << "White wins!" << endl;
    else
        cout << "Draw!" << endl;
}

pair<int, int> Game::processEvents(vector<pair<int, int>> &canSet)
{
    if (canSet.size() == 0)
    {
        cout << "You can't set any piece." << endl;
        return {-1, -1};
    }
    pair<int, int> move = players[currentPlayer]->makeMove();
    while (!isMoveValid(canSet, move))
    {
        cout << "Invalid move!" << endl;
        move = players[currentPlayer]->makeMove();
    }

    return move;
}

void Game::update(pair<int, int> move)
{
    table.set(move, players[currentPlayer]->getColor());
    currentPlayer = !currentPlayer;
}

void Game::render(vector<pair<int, int>> &canSet)
{
    try
    {
        system("cls");
    }
    catch (...)
    {
        system("clear");
    }

    auto table = this->table.get();
    for (auto [row, column] : canSet)
    {
        table[row][column] = CANSET;
    }

    players[currentPlayer]->lookTable(table, canSet);
}

bool Game::isGameOver()
{
    if (table.isFull())
        return true;
    
    int black = 0, white = 0;
    for (auto &row : table.get())
    {
        for (auto &column : row)
        {
            if (column == BLACK)
                black++;
            else if (column == WHITE)
                white++;
        }
    }

    if (black == 0 || white == 0)
        return true;

    return false;
}

bool Game::isMoveValid(vector<pair<int, int>> &canSet, pair<int, int> move)
{
    for (auto &i : canSet)
        if (i == move)
            return true;
    return false;
}

vector<pair<int, int>> Game::canSet(char color)
{
    vector<pair<int, int>> canSet;
    auto table = this->table.get();
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (table[i][j] != EMPTY)
                continue;

            for (auto [dr, dc] : DIRECTIONS)
            {
                int row = i + dr;
                int column = j + dc;
                if (row >= 0 && row < 8 && column >= 0 && column < 8 && table[row][column] != EMPTY && table[row][column] != color)
                {
                    while (row >= 0 && row < 8 && column >= 0 && column < 8 && table[row][column] != EMPTY)
                    {
                        if (table[row][column] == color)
                        {
                            canSet.push_back({i, j});
                            break;
                        }
                        row += dr;
                        column += dc;
                    }
                }
            }
        }

    return canSet;
}

char Game::getWinner()
{
    int black = 0, white = 0;
    for (auto &row : table.get())
    {
        for (auto &column : row)
        {
            if (column == BLACK)
                black++;
            else if (column == WHITE)
                white++;
        }
    }

    if (black > white)
        return BLACK;
    else if (black < white)
        return WHITE;
    else
        return EMPTY;
}