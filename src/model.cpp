#include <iostream>
#include <vector>

class Map
{
  public:
    std::vector<std::vector<int> > grid{
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0}
    };

    int mapWidth = grid[0].size();
    int mapHeight = grid.size();
};


class Planner
{
  public:
    std::vector<int> start{0, 0};
    std::vector<int> goal{4, 5};
    int cost = 1;
    std::vector<std::vector<int> > movement{
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1}
    };
    
    std::vector<char> movement_arrows{'^', '<', 'v', '>'};
};

int main()
{
    std::cout << "Modeling the problem";
    return 0;
}