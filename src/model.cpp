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

    int mapWidth = grid.size();
    int mapHeight = grid[0].size();

};

int main()
{
    std::cout << "Modeling the problem";
    return 0;
}