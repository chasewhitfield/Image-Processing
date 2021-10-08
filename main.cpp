#include <iostream>
#include <iomanip>
#include<fstream>
#include<sstream>
#include <vector>
#include "Header.h"
using namespace std;

Header taskOne()
{
    Header a = Header("input/layer1.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    Header b = Header("input/pattern1.tga");
    b.ReadData(b.filePath, b.blue, b.green, b.red);
    a.Multiply("output/part1.tga", b);
    a.WriteData(a.filePath, a.blue, a.green, a.red);
    return a;
}

Header taskTwo()
{
    Header a = Header("input/car.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    Header b = Header("input/layer2.tga");
    b.ReadData(b.filePath, b.blue, b.green, b.red);
    a.Subtract("output/part2.tga", b);
    a.WriteData(a.filePath, a.blue, a.green, a.red);
    return a;
}

Header taskThree()
{
    Header a = Header("input/layer1.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    Header b = Header("input/pattern2.tga");
    b.ReadData(b.filePath, b.blue, b.green, b.red);
    a.Multiply("part3.tga", b);
    Header c = Header("input/text.tga");
    c.ReadData(c.filePath, c.blue, c.green, c.red);
    a.Screen("output/part3.tga",c);
    a.WriteData(a.filePath, a.blue, a.green, a.red);
    return a;
}

Header taskFour()
{
    Header a = Header("input/circles.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    Header b = Header("input/layer2.tga");
    b.ReadData(b.filePath, b.blue, b.green, b.red);
    a.Multiply("part4.tga", b);
    Header c = Header("input/pattern2.tga");
    c.ReadData(c.filePath, c.blue, c.green, c.red);
    a.Subtract("output/part4.tga", c);
    a.WriteData(a.filePath, a.blue, a.green, a.red);
    return a;
}

Header taskFive()
{
    Header a = Header("input/layer1.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    Header b = Header("input/pattern1.tga");
    b.ReadData(b.filePath, b.blue, b.green, b.red);
    a.Overlay("output/part5.tga", b);
    a.WriteData(a.filePath, a.blue, a.green, a.red);
    return a;
}
Header taskSix()
{
    Header a = Header("input/car.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    for(unsigned int n = 0; n < a.green.size(); n++)
    {
        int hold = a.green.at(n);
        hold += 200;
        if(hold > 255)
        {
            a.green.at(n) = 255;
        }
        else
        {
            a.green.at(n) = (unsigned char)hold;
        }
    }
    a.filePath = "output/part6.tga";
    a.WriteData(a.filePath, a.blue, a.green, a.red);
    return a;
}

Header taskSeven() {
    Header a = Header("input/car.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    for (unsigned int n = 0; n < a.green.size(); n++) {
        float hold = a.blue.at(n);
        hold *= 0.0f;
        a.blue.at(n) = (unsigned char) hold;

        hold = a.red.at(n);
        hold *= 4.0f;
        if (hold > 255.0f) {
            a.red.at(n) = 255;
        } else {
            a.red.at(n) = (unsigned char) hold;
        }
    }
    a.filePath = "outpu/part7.tga";
    a.WriteData(a.filePath, a.blue, a.green, a.red);
    return a;
}

Header taskEightb()
{
    Header a = Header("input/car.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);

    a.green = a.blue;
    a.red = a.blue;
    a.WriteData("output/part8_b.tga", a.blue, a.green, a.red);
    return a;
}

Header taskEightg()
{
    Header a = Header("input/car.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);

    a.blue = a.green;
    a.red = a.green;
    a.WriteData("output/part8_g.tga", a.blue, a.green, a.red);
    return a;
}

Header taskEightr()
{
    Header a = Header("input/car.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);

    a.blue = a.red;
    a.green = a.red;
    a.WriteData("output/part8_r.tga", a.blue, a.green, a.red);
    return a;
}

Header taskNine()
{
    Header a = Header("input/layer_red.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    Header b = Header("input/layer_blue.tga");
    b.ReadData(b.filePath, b.blue, b.green, b.red);
    Header c = Header("input/layer_green.tga");
    c.ReadData(c.filePath, c.blue, c.green, c.red);
    a.blue = b.blue;
    a.green = c.green;
    a.WriteData("output/part9.tga", a.blue, a.green, a.red);
    return a;
}

Header taskTen()
{
    Header a = Header("input/text2.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    vector<unsigned char> b = a.blue;
    vector<unsigned char> g = a.green;
    vector<unsigned char> r = a.red;
    unsigned int size = a.green.size() - 1;
    for(unsigned int n = 0; n < (unsigned int)a.green.size(); n++)
    {
        a.blue.at(n) = b.at(size);
        a.green.at(n) = g.at(size);
        a.red.at(n) = r.at(size);
        size--;
    }
    a.WriteData("output/part10.tga", a.blue, a.green, a.red);
    return a;
}

void testAll()
{
    Header a = Header("examples/EXAMPLE_part1.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    Header b = taskOne();
    int count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 1...Passed." << endl;
    }
    else
    {
        cout << "Test 1...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part2.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskTwo();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 2...Passed." << endl;
    }
    else
    {
        cout << "Test 2...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part3.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskThree();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 3...Passed." << endl;
    }
    else
    {
        cout << "Test 3...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part4.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskFour();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 4...Passed." << endl;
    }
    else
    {
        cout << "Test 4...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part5.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskFive();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 5...Passed." << endl;
    }
    else
    {
        cout << "Test 5...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part6.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskSix();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 6...Passed." << endl;
    }
    else
    {
        cout << "Test 6...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part7.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskSeven();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 7...Passed." << endl;
    }
    else
    {
        cout << "Test 7...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part8_b.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskEightb();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 8b...Passed." << endl;
    }
    else
    {
        cout << "Test 8b...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part8_g.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskEightg();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 8g...Passed." << endl;
    }
    else
    {
        cout << "Test 8g...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part8_r.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskEightr();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 8r...Passed." << endl;
    }
    else
    {
        cout << "Test 8r...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part9.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskNine();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 9...Passed." << endl;
    }
    else
    {
        cout << "Test 9...Failed." << endl;
    }

    a = Header("examples/EXAMPLE_part10.tga");
    a.ReadData(a.filePath, a.blue, a.green, a.red);
    b = taskTen();
    count = 0;
    for(unsigned int n = 0; n < (a.width * a.height); n++)
    {
        if(a.blue.at(n) != b.blue.at(n) ||a.green.at(n) != b.green.at(n) || a.red.at(n) != b.red.at(n))
        {
            count++;
        }
    }
    if(count == 0)
    {
        cout << "Test 10...Passed." << endl;
    }
    else
    {
        cout << "Test 10...Failed." << endl;
    }
}

int main() {
    testAll();
    return 0;
}