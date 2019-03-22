#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int coord[16][2];
int n;
void read();
void perm();
void swap();
double get_distance(int x, int y, int x1, int y1);
double mindist = 10000;
int answer[16][2];

int main() {
	read();

	perm(0);
	printf("최단 거리: %f ", mindist);
	printf("[ ");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if ((answer[i][0] == coord[j][0]) && (answer[i][1] == coord[j][1])) printf("%d ", j);
	}
	printf("]\n");
	return 0;
}

void read() {
	FILE *fp;

	if ((fp = (fopen("input4.txt", "r"))) == NULL) {
		printf("File open failed!");
		exit(1);
	}
	fscanf(fp, "%d", &n);

	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d %d", &coord[i][0], &coord[i][1]);
	}
}

void perm(int k) {
	double dist;
	double totdist = 0;
	if (k == n) {
		for (int i = 0; i < n; i++) {
			dist = get_distance(coord[i][0], coord[i][1], coord[i + 1][0], coord[i + 1][1]);
			if (i + 1 == n)
				dist = get_distance(coord[i][0], coord[i][1], coord[0][0], coord[0][1]);
			totdist += dist;
			if (mindist < totdist) {
				break;
			}
		}

		if (mindist > totdist) {
			mindist = totdist;
			for (int i = 0; i < n; i++) {
				answer[i][0] = coord[i][0];
				answer[i][1] = coord[i][1];
			}
		}
		return;
	}

	for (int i = k; i < n; i++) {
		swap(coord, k, i);
		perm(k + 1);
		swap(coord, k, i);
	}
}

double get_distance(int x, int y, int x1, int y1) {
	return (double)sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1));
}

void swap(int data[][2], int a, int b) {
	int tmp = data[a][0];
	data[a][0] = data[b][0];
	data[b][0] = tmp;

	tmp = data[a][1];
	data[a][1] = data[b][1];
	data[b][1] = tmp;
}