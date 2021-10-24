#include <iostream>
#include <vector>

void demo_2D_vector()
{
    std::vector<std::vector<int> > vect {{1, 2, 3},{4, 5, 6},{7, 8, 9}};

    for (int i =0; i < vect.size(); i++)
    {
        for (int j=0; j<vect[i].size(); j++)
        {
            std::cout << " " << vect[i][j];
        }

        std::cout << std::endl;
    }
}

int main()
{
    std::cout << "2D vectors in C++" << std::endl;

    demo_2D_vector();
    
    return 0;
}