#ifndef __Helpers_H__
#define __Helpers_H__

double helpers_Time();

// seed rand()
//int RandomNumber() { return rand(); };

//float RandomNumberInRange(float min, float max) { return ((rand()) / (RAND_MAX / (max - min)) + min); };

int helpers_GetUniqueID();

// #define MyColor vec4
class MyColor
{
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

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

#endif //__Helpers_H__