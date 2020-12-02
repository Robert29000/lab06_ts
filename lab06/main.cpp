//
//  main.cpp
//  lab06
//
//  Created by Роберт Артур Меликян on 02/12/2020.
//  Copyright © 2020 Роберт Артур Меликян. All rights reserved.
//

#include <iostream>
#include <vector>
#include "TextTable.h"

const int INF = 100;
const size_t v = 8;
std::vector<std::vector<int>> mat_d = {
    {0, 3, 3, INF, INF, INF, INF, INF},
    {INF, 0, INF, 5, INF, INF, INF, INF},
    {INF, INF, 0, 1, INF, 3, INF, INF},
    {INF, INF, INF, 0, 2, INF, INF, 4},
    {INF, INF, INF, INF, 0, INF, INF, 4},
    {INF, INF, INF, 3, INF, 0, 2, 100},
    {INF, INF, INF, INF, INF, INF, 0, 5},
    {INF, INF, INF, INF, INF, INF, INF, 0}
                                };

std::vector<std::vector<int>> mat_c; // матрица путей

void print_table(const std::vector<std::vector<int>>& matrix, TextTable& t){
    t.add(" ");
    for (auto i = 0; i < v; i++){
        t.add(std::to_string(i));
    }
    t.endOfRow();
    for (auto i = 0; i < v; i++){
        t.add(std::to_string(i));
        for (auto j = 0; j < v; j++){
            t.add(std::to_string(matrix[i][j]));
        }
        t.endOfRow();
    }
    std::cout << t << std::endl;
}

void print_path(int from, int to){
    if (mat_d[from][to] >= INF){
        std::cout << "There is no path" << std::endl;
        return;
    }
    auto k = from;
    while (k != to){
        std::cout << k << " -> ";
        k = mat_c[k][to];
    }
    std::cout << " -> " << k << std::endl;
}

int main(int argc, const char * argv[]) {
    TextTable t_dos('-', '|', '+');
    TextTable t_dis('-', '|', '+');
    mat_c.resize(v);
    for (auto i = 0; i < v; i++){
        mat_c[i].resize(v);
    }
    std::cout << "Матрица достижимости:" << std::endl;
    print_table(mat_d, t_dos);
    for (auto i = 0; i < v; i++){
        for (auto j = 0; j < v; j++){
            mat_c[i][j] = j;
        }
    }
    
    for (auto k = 0; k < v; k++){
        for (auto i = 0; i < v; i++){
            for (auto j = 0; j < v; j++){
                if (mat_d[i][j] > mat_d[i][k] + mat_d[k][j]){
                    mat_d[i][j] = mat_d[i][k] + mat_d[k][j];
                    mat_c[i][j] = mat_c[i][k];
                }
            }
        }
    }
    
    std::cout << "Матрица расстояний" << std::endl;
    print_table(mat_d, t_dis);
    std::cout << "Кратчайший путь из вершины 0 в вершину 7" << std::endl;
    print_path(0, 7);
    std::cout << "Длина кратчайшего пути" << std::endl;
    std::cout << mat_d[0][7] << std::endl;
    return 0;
}
