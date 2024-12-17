#include <stdio.h>
#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)

// global vars
int lane = 4;
int green[] = {15, 35, 25, 25};
int red[] = {0, 0, 0, 0};
int cunt[] = {0, 0, 0, 0};
int traffic_rate = 2.0;
int chance[] = {0, 0, 0, 0};
int max_threshold = 50;
int base_increment = 5;
int maxCount = 0;
bool won = false;



//Show Array
void showArr(int arr[], int size, int front)
{
    for (int i = front; i < front + size; i++) {
        printf("%d ", arr[i % size]);
    }
    cout << "\n";
}

//Calculate Red Time
void calc_red()
{
    FOR(x, lane) {
        int temp = 0;
        FORE(y, x, x + lane - 1)
        temp += green[(y + 1) % lane];
        red[x] = temp;
    }
}

//Reset Chance
void reset_chance()
{
    won = false;
    FOR(x, lane)
    chance[x] = -1;
}

//Get Values from File
void get_count()
{
    ifstream fin;
    fin.open("count.txt", ios::in);
    int temp;
    int x = 0;
    while(fin >> temp) {
        cunt[x] = temp;
        cout << cunt[x] << " ";
    }
}
