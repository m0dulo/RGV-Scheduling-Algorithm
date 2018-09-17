#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define Pposition 4 //共有四个位置

//！修改以下信息进行测试

#define lsl 31       //第i组左边取料时间
#define rsl 28       //第i组右边取料时间
#define clean 25     //第i组清洗时间
#define worktime 560 //第i组工作时间
#define TIME time1   //第i组移动时间矩阵

//时间矩阵
int time1[4][4] = {0, 20, 33, 46,
                   20, 0, 20, 33,
                   33, 20, 0, 20,
                   46, 32, 18, 0};

//时间矩阵
int time2[4][4] = {0, 23, 41, 59,
                   23, 0, 23, 41,
                   41, 23, 0, 23,
                   59, 41, 23, 0};

//时间矩阵
int time3[4][4] = {0, 18, 32, 46,
                   18, 0, 18, 32,
                   33, 18, 0, 18,
                   46, 32, 18, 0};

//时间矩阵

int job[4][2] = {0, 0,
                 0, 0,
                 0, 0,
                 0, 0};

//起点位置1——4
int position = 1;
//选择到达点的最小等待时间
int pk(int right, int left)
{
    return right - left <= lsl - rsl ? 1 : 0; //右边
}
//比较当前cnc时间大小
int pkk(int right, int left)
{
    return right < left ? right : left;
}

//表示当前可选择队列的列表
typedef struct
{
    int time;
    char number;
} CNC;
//上料时间表
vector<int> timetable;
//下料时间表
vector<int> overtimetable;
//排序函数
int comp(const CNC &a, const CNC &b)
{
    return a.time < b.time;
}
//判断当前状态函数
CNC check(int startpoint, int time[][4], int job[][2])
{
    //每个p1点能使能的状态有5个
    CNC templine[5];
    int j = 0;
    for (int i = 0; i < Pposition; i++) //0-3
    {
        //i是除了当前位置的其他位置值
        if (i == startpoint)
            continue;
        templine[j].number = i + 1 + '0'; //1-4
        //寻找每个点当前最小的等待时间
        if (pk(job[i][1], job[i][0])) //右侧（奇数）时间小于左侧（偶数）时间间隔大于上料时间差
        {
            //移动时间
            if (job[i][1] >= time[startpoint][i])
                templine[j].time = time[startpoint][i];
            else
                templine[j].time = time[startpoint][i];
            //右侧上料时间
            templine[j].time += rsl;
            //清洗时间
            templine[j].time += clean;
        }
        else
        {
            //移动时间
            if (job[i][0] >= time[startpoint][i])
                templine[j].time = job[i][0];
            //左侧等待时间
            else
                templine[j].time = time[startpoint][i];
            //左侧上料时间
            templine[j].time += lsl;
            //清洗时间
            templine[j].time += clean;
        }

        j++;
    }
    templine[j].number = 'L';
    //当前点左侧等待时间
    templine[j].time = job[startpoint][0];
    //当前点左侧上料时间
    templine[j].time += lsl;
    //当前点清洗时间
    templine[j].time += clean;

    templine[j + 1].number = 'R';
    //当前点右侧等待时间
    templine[j + 1].time = job[startpoint][1];
    //当前点右侧上料时间
    templine[j + 1].time += rsl;
    //当前点清洗时间
    templine[j + 1].time += clean;
    sort(templine, templine + 5, comp);
    return templine[0];
}

//修改当前时间段
void timed(int job[][2], CNC order)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            job[i][j] -= order.time;
            if (job[i][j] < 0)
            {
                job[i][j] = 0;
            }
        }
    }
}

void change(int job[][2], CNC order, int &position, int time[][4])
{
    switch (order.number)
    {
    case 'L':
    {
        //位置不变
        //执行工作（改变job表）
        timed(job, order);
        job[position - 1][0] += worktime;
        //记录上料时间
        vector<int>::iterator it = timetable.end() - 1;
        timetable.push_back(*it + order.time);
        //记录下料时间
        it = timetable.end() - 1;
        overtimetable.push_back(*it + worktime);
        break;
    }
    case 'R':
    {
        //位置不变
        //执行工作（改变job表）
        timed(job, order);
        job[position - 1][1] += worktime;
        std::vector<int>::iterator it = timetable.end() - 1;
        //记录上料时间
        timetable.push_back(*it + order.time);
        //保留开始时间点
        it = timetable.end() - 1;
        //记录下料时间
        overtimetable.push_back(*it + worktime);
        break;
    }
    case '1':
    {
        int oposition = position;
        //位置改变
        position = order.number - '0';
        //保留开始时间点
        if (time[oposition - 1][position - 1] > pkk(job[position - 1][1], job[position - 1][0]))
        {
            //路程时间更多
            vector<int>::iterator it = timetable.end() - 1;
            *it += time[oposition - 1][position - 1];
            //修改下料时间（还需要等待RGV）
            vector<int>::iterator t = timetable.end() - 8;
            *t += time[oposition - 1][position - 1];
            //记录上料时间
            timetable.push_back(*it + order.time - time[oposition - 1][position - 1]);
            //记录下料时间
            it = timetable.end() - 1;
            overtimetable.push_back(*it + worktime);
        }
        else
        {
            vector<int>::iterator it = timetable.end() - 1;
            *it += pkk(job[position - 1][1], job[position - 1][0]);
            //正常结束
            //记录上料时间
            timetable.push_back(*it + order.time - pkk(job[position - 1][1], job[position - 1][0]));
            //记录下料时间
            it = timetable.end() - 1;
            overtimetable.push_back(*it + worktime);
        }
        //执行工作（改变job表）
        timed(job, order);
        job[position - 1][pk(job[position - 1][1], job[position - 1][0])] += worktime;
        break;
    }
    case '2':
    {
        int oposition = position;
        //位置改变
        position = order.number - '0';
        //保留开始时间点
        if (time[oposition - 1][position - 1] > pkk(job[position - 1][1], job[position - 1][0]))
        {
            //路程时间更多
            vector<int>::iterator it = timetable.end() - 1;
            *it += time[oposition - 1][position - 1];
            //修改下料时间（还需要等待RGV）
            vector<int>::iterator t = timetable.end() - 8;
            *t += time[oposition - 1][position - 1];
            //记录上料时间
            timetable.push_back(*it + order.time - time[oposition - 1][position - 1]);
            //记录下料时间
            it = timetable.end() - 1;
            overtimetable.push_back(*it + worktime);
        }
        else
        {
            vector<int>::iterator it = timetable.end() - 1;
            *it += pkk(job[position - 1][1], job[position - 1][0]);
            //正常结束
            //记录上料时间
            timetable.push_back(*it + order.time - pkk(job[position - 1][1], job[position - 1][0]));
            //记录下料时间
            it = timetable.end() - 1;

            overtimetable.push_back(*it + worktime);
        }
        //执行工作（改变job表）
        timed(job, order);
        job[position - 1][pk(job[position - 1][1], job[position - 1][0])] += worktime;
        break;
    }

    case '3':
    {
        int oposition = position;
        //位置改变
        position = order.number - '0';
        //保留开始时间点
        if (time[oposition - 1][position - 1] > pkk(job[position - 1][1], job[position - 1][0]))
        {
            //路程时间更多
            vector<int>::iterator it = timetable.end() - 1;
            *it += time[oposition - 1][position - 1];
            //修改下料时间（还需要等待RGV）
            vector<int>::iterator t = timetable.end() - 8;
            *t += time[oposition - 1][position - 1];
            //记录上料时间
            timetable.push_back(*it + order.time - time[oposition - 1][position - 1]);
            //记录下料时间
            it = timetable.end() - 1;
            overtimetable.push_back(*it + worktime);
        }
        else
        {
            vector<int>::iterator it = timetable.end() - 1;
            *it += pkk(job[position - 1][1], job[position - 1][0]);
            //正常结束
            //记录上料时间
            timetable.push_back(*it + order.time - pkk(job[position - 1][1], job[position - 1][0]));
            //记录下料时间
            it = timetable.end() - 1;
            overtimetable.push_back(*it + worktime);
        }
        //执行工作（改变job表）
        timed(job, order);
        job[position - 1][pk(job[position - 1][1], job[position - 1][0])] += worktime;
        break;
    }
    case '4':
    {
        int oposition = position;
        //位置改变
        position = order.number - '0';
        //保留开始时间点
        if (time[oposition - 1][position - 1] > pkk(job[position - 1][1], job[position - 1][0]))
        {
            //路程时间更多
            vector<int>::iterator it = timetable.end() - 1;
            *it += time[oposition - 1][position - 1];
            //修改下料时间（还需要等待RGV）
            vector<int>::iterator t = timetable.end() - 8;
            *t += time[oposition - 1][position - 1];
            //记录上料时间
            timetable.push_back(*it + worktime);
        }
        else
        {
            vector<int>::iterator it = timetable.end() - 1;
            *it += pkk(job[position - 1][1], job[position - 1][0]);
            //正常结束
            //纪录上料时间
            timetable.push_back(*it + order.time - pkk(job[position - 1][1], job[position - 1][0]));
            //记录下料时间
            it = timetable.end() - 1;
            overtimetable.push_back(*it + worktime);
        }
        //执行工作（改变job表）
        timed(job, order);
        job[position - 1][pk(job[position - 1][1], job[position - 1][0])] += worktime;
        break;
    }
    };
}

int main(int argc, char const *argv[])
{
    timetable.push_back(0);
    overtimetable.push_back(0 + worktime);
    int sum = 0;
    cout << "--------------------choose:" << endl;
    for (int times = 0; times < 28800;)
    {
        CNC order = check(position - 1, TIME, job);
        //输出选择序列
        switch (order.number)
        {
        case 'L':
            cout << position * 2 << ";" << endl; //i位置左手边是i*2号机器
            break;
        case 'R':
            cout << position << ";" << endl; //1位置左手边是2号机器
            break;
        case '1':
            cout << 1 << ";" << endl; //1位置时间最短的机器
            break;
        case '2':
            cout << 3 << ";" << endl; //2位置时间最短的机器
            break;
        case '3':
            cout << 5 << ";" << endl; //3位置时间最短的机器
            break;
        case '4':
            cout << 7 << ";" << endl; //4位置时间最短的机器
            break;
        };
        int o = position;
        change(job, order, position, TIME);
        times += order.time;
        sum++;
    }

    //输出上料时间
    cout << "-------------------time of putting up" << endl;
    for (auto it = timetable.begin(); it != timetable.end(); it++)
        cout << *it << ";" << endl;
    //输出下料时间
    cout << "-------------------time of taking down" << endl;
    for (auto it = overtimetable.begin(); it != overtimetable.end(); it++)
        cout << *it << ";" << endl;
    cout << "sum::" << sum;
    system("pause");
    return 0;
}
