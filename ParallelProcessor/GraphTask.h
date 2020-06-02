#pragma once
#include <iostream>
#include <vector>
#include "FileToFileTask.h"
using namespace std;



class GraphTask : public FileToFileTask{
private:
	int N = 0;
	int destination_adress = 0;
	vector<vector<int>> sv;
public:
	GraphTask(ifstream&& a, ofstream&& b) : FileToFileTask(move(a), move(b)){ 
	}
	virtual void complete() override{
		fileout_ << "This is completed GraphTask" << endl;
		djta(N, sv);
	}
	virtual ~GraphTask(){
	}
private:
	void readData(){
		filein_.seekg(0);
		char symbol;
		while ((symbol = filein_.get()) != '\n'); // Пропускаем первую строку
		filein_ >> destination_adress >> N;
		if (N != 0){
			sv.resize(N);
			for (size_t i = 0; i < N; ++i)
				sv[i].resize(N);
			for (size_t i = 0; i < N; ++i)
				for (size_t j = 0; j < N; ++j)
					filein_ >> sv[i][j];
		}
	}
	void djta(int N, vector<vector<int>> sv) {
		vector<int> dist(N);
		vector<int> visited(N);
		int temp, minindex, min;
		int begin_index = 0;
		for (int i = 0; i < N; i++) {
			dist[i] = 10000;
			visited[i] = 1;
		}
		dist[begin_index] = 0;
		do {
			minindex = 10000;
			min = 10000;
			for (int i = 0; i < N; i++) {
				if ((visited[i] == 1) && (dist[i] < min)) {
					min = dist[i];
					minindex = i;
				}
			}
			if (minindex != 10000) {
				for (int i = 0; i < N; i++) {
					if (sv[minindex][i] > 0) {
						temp = min + sv[minindex][i];
						if (temp < dist[i]) {
							dist[i] = temp;
						}
					}
				}
				visited[minindex] = 0;
			}
		} while (minindex < 10000);
		cout << "\nКратчайшие расстояния до вершин: ";
		for (int i = 0; i < N; i++)
			cout << dist[i];
		vector<int> ver(N);
		int end = 4;
		ver[0] = end + 1;
		int k = 1;
		int weight = dist[end];
		while (end != begin_index) {
			for (int i = 0; i < N; i++)
				if (sv[i][end] != 0) {
					int temp = weight - sv[i][end];
					if (temp == dist[i]) {
						weight = temp;
						end = i;
						ver[k] = i + 1;
						k++;
					}
				}
		}
		printf("\nВывод кратчайшего пути\n");
		for (int i = k - 1; i >= 0; i--)
			fileout_ << ver[i];
	}
};

