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
    std::vector<std::vector<int> > movements{
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1}
    };
    
    std::vector<char> movements_arrows{'^', '<', 'v', '>'};
};

template<class T>
void print2DVector(std::vector<std::vector<T> > vect)
{
    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect[i].size(); j++)
        {
            std::cout << vect[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::cout << "Modeling the problem" << std::endl;
    
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Print classes variables
    std::cout << "Map:" << std::endl;
    print2DVector(map.grid);
    std::cout << "Start: " << planner.start[0] << " , " << planner.start[1] << std::endl;
    std::cout << "Goal: " << planner.goal[0] << " , " << planner.goal[1] << std::endl;
    std::cout << "Cost: " << planner.cost << std::endl;
    std::cout << "Robot Movements: " << planner.movements_arrows[0] << " , " << planner.movements_arrows[1] << " , " << planner.movements_arrows[2] << " , " << planner.movements_arrows[3] << std::endl;
    std::cout << "Delta:" << std::endl;
    print2DVector(planner.movements);

    return 0;
}