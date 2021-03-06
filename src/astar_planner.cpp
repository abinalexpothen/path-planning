#include <algorithm>
#include <iostream>
#include <string.h>
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


// search function which generates expansions
void search(Map map,Planner planner)
{
    std::vector<std::vector<int> > closed(map.mapHeight,std::vector<int>(map.mapWidth));
    closed[planner.start[0]][planner.start[1]] = 1;

    std::vector<std::vector<int> > expansion_list(map.mapHeight, std::vector<int>(map.mapWidth, -1));

    std::vector<std::vector<int> > action(map.mapHeight, std::vector<int>(map.mapWidth, -1));
    
    // create manhattan heuristic vector
    std::vector<std::vector<int> > manhattan(map.mapHeight, std::vector<int>(map.mapWidth, -1));
    
    for (int i = 0; i < manhattan.size(); i++)
    {
        for (int j = 0; j < manhattan[0].size(); j++)
        {
            manhattan[i][j] = abs(i-planner.goal[0]) + abs(j-planner.goal[1]);
        }
    }

    // define the triplet values
    int x = planner.start[0];
    int y = planner.start[1];
    int g = 0;
    int f = manhattan[x][y] + g;

    // store the expansions
    std::vector<std::vector<int> > open;
    open.push_back({f, g, x, y});

    // flags
    bool found = false;
    bool resign = false;

    int x2;
    int y2;

    int count = 0;

    while (!found && !resign)
    {
        if (open.size() == 0)
        {
            resign = true;
            std::cout << "Failed to reach a goal" << std::endl;
        }
        else
        {
            // remove triplets from open list
            std::sort(open.begin(), open.end());
            std::reverse(open.begin(), open.end());

            std::vector<int> next;
            // store the poped value into next
            next  = open.back();
            open.pop_back();

            f = next[0];
            g = next[1];
            x = next[2];
            y = next[3];

            expansion_list[x][y] = count;
            count++;

            //check if we reached goal
            if (x == planner.goal[0] && y == planner.goal[1])
            {
                found = true;
                //  std::cout << "[" << g << ", " << x << ", " << y << "]" << std::endl;
            }
            else
            {
                for (int i=0; i < planner.movements.size(); i++)
                {
                    x2 = x + planner.movements[i][0];
                    y2 = y + planner.movements[i][1];
                    if (x2 >= 0 && x2 < map.grid.size() && y2 >= 0 && y2 < map.grid[0].size())
                    {
                        if (closed[x2][y2] == 0 && map.grid[x2][y2] == 0)
                        {
                            int g2 = g + planner.cost;
                            int f2 = manhattan[x2][y2] + g2;
                            open.push_back({f2, g2, x2, y2});
                            closed[x2][y2] = 1;
                            action[x2][y2] = i;
                        }
                    }
                }
            }
        }
    }

    std::vector<std::vector<std::string> > policy(map.mapHeight, std::vector<std::string>(map.mapWidth, "-"));

    x = planner.goal[0];
    y = planner.goal[1];
    
    policy[x][y] = "*";
    
    while (x != planner.start[0] || y != planner.start[1])
    {
        x2 = x - planner.movements[action[x][y]][0];
        y2 = y - planner.movements[action[x][y]][1];
        
        policy[x2][y2] = planner.movements_arrows[action[x][y]];
        
        x = x2;
        y = y2;
    }

    std::cout << std::endl;
    std::cout << "Expansion list: " << std::endl;
    print2DVector(expansion_list);
    std::cout << std::endl;
    std::cout << "Policy vector: " << std::endl;
    print2DVector(policy);
}

int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    search(map, planner);

    return 0;
}