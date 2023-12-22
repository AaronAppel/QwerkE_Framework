#pragma once

double helpers_Time();

// seed rand()
//int RandomNumber() { return rand(); };

//float RandomNumberInRange(float min, float max) { return ((rand()) / (RAND_MAX / (max - min)) + min); };

int helpers_GetUniqueID();

// #define MyColor vec4
class MyColor
{
public:
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;

    MyColor()
    {
    }
    MyColor(unsigned char nr, unsigned char ng, unsigned char nb, unsigned char na)
    {
        r = nr;
        g = ng;
        b = nb;
        a = na;
    }
};

void helpers_Toggle(bool* value);

int CharToInt(char num);

/* If Else helpers*/
// void IfElse(comparisonValue, condition, trueValue, falseValue);
// void ElseIf(comparisonValue, condition1, true1, false1, condition2, true2, false2...); // Variable arguments
// void IfElseIf(comparisonValue, trioData[]);

void* VoidCheck(void* check);
