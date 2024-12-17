#include <bits/stdc++.h>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <windows.h>
#include <mutex>

using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)

std::mutex mu;

// global vars
int lane = 4;
int green[] = {10, 30, 20, 20};
int red[] = {0, 0, 0, 0};
int cunt[] = {0, 0, 0, 0};
float traffic_rate = 2;
int chance[] = {0, 0, 0, 0};
int max_threshold = 50;
int base_increment = 5;
int maxCount = 0;
int minCount = 0;
int greenTime = 0;
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
        x++;
    }
    fin.close();
}

//Max of array
int maxMinPos(int arr[], int mode)
{
    int m, index = 0;
    if(mode == 0) {
        m = 0;
        FOR(i, lane) {
            if(arr[i] > m) {
                m = arr[i];
                index = i;
            }
            maxCount = m;
        }
    } else {
        m = 999999;
        FOR(i, lane) {
            if(arr[i] < m) {
                m = arr[i];
                index = i;
            }
        }
        minCount = m;
    }

    return index;
}

void increment()
{
    int laneNo = maxMinPos(cunt, 0);
    float ftemp = (1.0 / traffic_rate) * maxCount + base_increment;

    //cout<<"Increment DEBUG\nlaneNo:"<<laneNo<<"   ftemp:"<<ftemp<<"\n";


    if (ftemp > max_threshold)
        ftemp = max_threshold;

    if (ftemp < base_increment)
        ftemp = base_increment;

    greenTime = (round(ftemp));
    if ((chance[laneNo] >= 1) && (won == false)) {
        printf("twice\n");
        cunt[laneNo] = -1;
        won = true;
        increment();
    }

    else {
        // update time logic should be over here

        chance[laneNo] += 1;
        printf("\n------------------\n%d needs %d time\n------------------\n", laneNo, greenTime);
        if(won == true) {
            cunt[laneNo] = -1;
            maxMinPos(chance, 1);
            if (minCount == 0) {
                reset_chance();
                mu.lock();
                get_count();
                mu.unlock();
            }
        }
    }
    showArr(chance,lane,0);
}


//MAIN
int tax()
{
    calc_red();
    reset_chance();
    get_count();
    cout << "\n";
    while(1) {
        increment();
        std::this_thread::sleep_for(std::chrono::milliseconds(1700));
    }
    return 0;
}

int xat()
{
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        mu.lock();
        //printf("\nReading New Values..\n");
        ifstream laneX;
        ofstream countFile;
        int temp;
        countFile.open("count.txt", ios::out);
        laneX.open("lane1.txt", ios::in);
        laneX >> temp;
        countFile << temp;
        countFile << "\n";
        laneX.close();
        laneX.open("lane2.txt", ios::in);
        laneX >> temp;
        countFile << temp;
        countFile << "\n";
        laneX.close();
        laneX.open("lane3.txt", ios::in);
        laneX >> temp;
        countFile << temp;
        countFile << "\n";
        laneX.close();
        laneX.open("lane4.txt", ios::in);
        laneX >> temp;
        countFile << temp;
        countFile << "\n";
        laneX.close();
        countFile.close();
        mu.unlock();
    }

}

void sax()
{
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
        srand(time(0));
        mu.lock();
        //printf("\nInserting New Values..\n");
        int temp = rand() % 60;
        ofstream laneX;
        laneX.open("lane2.txt", ios::out);
        laneX << temp;
        //printf("%d ", temp);
        laneX.close();
        temp = rand() % 60;
        laneX.open("lane3.txt", ios::out);
        laneX << temp;
        // printf("%d ", temp);
        laneX.close();
        temp = rand() % 60;
        laneX.open("lane4.txt", ios::out);
        laneX << temp;
        // printf("%d\n", temp);
        laneX.close();
        mu.unlock();
    }
}

int main(int argc, char const *argv[])
{
    thread y(xat);
    thread x(tax);
    thread z(sax);

    y.join();
    z.join();
    x.join();
    return 0;
}