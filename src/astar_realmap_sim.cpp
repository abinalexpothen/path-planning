#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

class Map
{
  public:
    const static int mapHeight = 300;
    const static int mapWidth = 150;
    std::vector<std::vector<double> > map = GetMap();
    std::vector<std::vector<int> > grid = MaptoGrid();
    std::vector<std::vector<int> > heuristic = GenerateHeuristic();

  private:
    //read file and get map
    std::vector<std::vector<double> > GetMap()
    {
        std::vector<std::vector<double> > mymap(mapHeight, std::vector<double>(mapWidth));
        std::ifstream myReadFile;
        myReadFile.open("map.txt");

        while(!myReadFile.eof())
        {
            for (int i = 0; i < mapHeight; i++)
            {
                for (int j = 0;  j < mapWidth; j++)
                {
                    myReadFile >> mymap[i][j];
                }
            }
        }
        return mymap;
    }

    std::vector<std::vector<int> > MaptoGrid()
    {
        std::vector<std::vector<int> > grid(mapHeight, std::vector<int>(mapWidth));

        for (int i = 0; i < mapHeight; i++)
        {
            for (int j = 0; j < mapWidth; j++)
            {
                if (map[i][j] >= 0.0)
                {
                    grid[i][j] = 1;
                }
                else
                {
                    grid[i][j] = 0;
                }
            }
        }
        return grid;
    }

    std::vector<std::vector<int> > GenerateHeuristic()
    {
        int goal[2] = {60, 50};
        std::vector<std::vector<int> > heuristic(mapHeight, std::vector<int>(mapWidth));

        // generate manhattan heuristic
        for(int i = 0; i < mapHeight; i++)
        {
            for (int j = 0; j < mapWidth; j++)
            {
                heuristic[i][j] = abs(goal[0] - i) + abs(goal[1] - j);
            }
        }

        return heuristic;
    }
};

//planner class
class Planner : Map
{
  public:
    int start[2] = {230, 145};
    int goal[2] = {60,50};
    int cost = 1;

    std::string movements_arrows[4] = {"^", "<", "v", ">"};

    std::vector<std::vector<int> > movements{
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1}
    };

    std::vector<std::vector<int> > path;
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

void visualization(Map map, Planner planner)
{
    //Graph Format
    plt::title("Path");
    plt::xlim(0, map.mapHeight);
    plt::ylim(0, map.mapWidth);

    std::vector<double> green_x;
    std::vector<double> green_y;
    std::vector<double> red_x;
    std::vector<double> red_y;
    std::vector<double> black_x;
    std::vector<double> black_y;

    // Draw every grid of the map:
    for (double x = 0; x < map.mapHeight; x++) {
        std::cout << "Remaining Rows= " << map.mapHeight - x << std::endl;
        for (double y = 0; y < map.mapWidth; y++) {
            if (map.map[x][y] == 0) { //Green unkown state
                green_x.push_back(x);
                green_y.push_back(y);
            }
            else if (map.map[x][y] > 0) { //Black occupied state
                black_x.push_back(x);
                black_y.push_back(y);
            }
            else { //Red free state
                red_x.push_back(x);
                red_y.push_back(y);
            }
        }
    }

    plt::plot(green_x, green_y, "g.");
    plt::plot(black_x, black_y, "k.");
    plt::plot(red_x, red_y, "r.");

    // Plot start and end states in blue colors using o and * respectively
    std::vector<double> start_x;
    std::vector<double> start_y;
    std::vector<double> end_x;
    std::vector<double> end_y;

    start_x.push_back(planner.start[0]);
    start_y.push_back(planner.start[1]);
    end_x.push_back(planner.goal[0]);
    end_y.push_back(planner.goal[1]);

    plt::plot(start_x, start_y, "bo");
    plt::plot(end_x, end_y, "b*");

    std::vector<int> path_x;
    std::vector<int> path_y;

    std::cout << "Path vector size is: " << planner.path.size() << std::endl;
    for (int i = 0; i < planner.path.size(); i++)
    {
        path_x.push_back(planner.path[i][0]);
        path_y.push_back(planner.path[i][1]);
    }
    // plot robot path
    plt::plot(path_x, path_y, "b-");

    plt::show();
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
    
    planner.path.push_back({x,y});

    while (x != planner.start[0] || y != planner.start[1])
    {
        x2 = x - planner.movements[action[x][y]][0];
        y2 = y - planner.movements[action[x][y]][1];
        
        policy[x2][y2] = planner.movements_arrows[action[x][y]];
        
        x = x2;
        y = y2;

        planner.path.push_back({x,y});
    }

    // std::cout << std::endl;
    // std::cout << "Expansion list: " << std::endl;
    // print2DVector(expansion_list);
    // std::cout << std::endl;
    // std::cout << "Policy vector: " << std::endl;
    // print2DVector(policy);

    visualization(map, planner);

}

int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    search(map, planner);

    return 0;
}
