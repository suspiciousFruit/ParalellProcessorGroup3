#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "FileToFileTask.h"



class GraphTask : public FileToFileTask
{
public:
	GraphTask(std::ifstream&& a, std::ofstream&& b) : FileToFileTask(std::move(a), std::move(b))
	{ }

	virtual void complete() override
	{
		pars
		fileout_ << "This is completed GraphTask" << std::endl;
	}

	virtual ~GraphTask()
	{ }
};

void pars() {
	for (int i = 0; i < SIZE; i++)
	{
		sv[i][i] = 0;
		for (int j = i + 1; j < SIZE; j++) {
			printf(i + 1, j + 1);
			scanf("%d", &temp);
			a[i][j] = temp;
			a[j][i] = temp;
		}
	}
}

void djta(int SIZE, int sv[SIZE][SIZE]){
	int dist[SIZE]; 
	int visited[SIZE]; 
	int temp, minindex, min;
	int begin_index = 0;
	for (int i = 0; i < SIZE; i++){
		dist[i] = 10000;
		visited[i] = 1;
	}
	dist[begin_index] = 0;
	do {
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < SIZE; i++){ 
			if ((visited[i] == 1) && (dist[i] < min)){
				min = dist[i];
				minindex = i;
			}
		}
		if (minindex != 10000){
			for (int i = 0; i < SIZE; i++){
				if (sv[minindex][i] > 0){
					temp = min + sv[minindex][i];
					if (temp < dist[i]){
						dist[i] = temp;
					}
				}
			}
			visited[minindex] = 0;
		}
	} while (minindex < 10000);
	printf("\nКратчайшие расстояния до вершин: \n");
	for (int i = 0; i < SIZE; i++)
		printf("%5d ", dist[i]);
	int ver[SIZE];
	int end = 4;
	ver[0] = end + 1;
	int k = 1;
	int weight = dist[end];
	while (end != begin_index){
		for (int i = 0; i < SIZE; i++)
			if (sv[i][end] != 0){
				int temp = weight - sv[i][end];
				if (temp == dist[i]){
					weight = temp;
					end = i; 
					ver[k] = i + 1; 
					k++;
				}
			}
	}
	printf("\nВывод кратчайшего пути\n");
	for (int i = k - 1; i >= 0; i--)
		printf("%3d ", ver[i]);
	getchar(); getchar();
}


