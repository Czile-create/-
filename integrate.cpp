#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

double func(double a) {
    return 1/(1+a*a);
}

// integrete（积分函数， 初始点， 终止点， 精确度， 迭代次数）
double integrate(double(* func)(double), double a, double b, double r=1e-6, int s=0) {
    double h = b - a;
    double T_0 = h * (func(a) + func(b)) /2;
    int k=0, ex_2=1, ex_4=1;
    double T_1;
    vector<double> T_re;
    T_re.push_back(T_0);
    do {
        k++, ex_2*=2, ex_4=4;
        double tmp = 0;
        for (int i=0; i<ex_2/2; i++)
            tmp += func(a + (b-a)*(2*i + 1)/ex_2);
        
        T_1 = T_re[0]/2 + tmp *h /ex_2;
        for (int i=0; i<k; i++) {
            tmp = T_1;
            T_1 = ( ex_4 * T_1 - T_re[i] )/(ex_4 - 1);
            ex_4 *= 4;
            T_re[i] = tmp;
        }
        T_re.push_back(T_1);
        if (s && T_re.size() > s) {
            throw "给定函数不可积分、或函数不连续、或函数不光滑、或函数并非初等函数\n若您确信函数可积分，可尝试降低精确度要求（参数r）或取消迭代次数保护（参数s）\n";
            continue;
        }
    } while ((fabs(T_1-T_0)>=r) && (T_0=T_1));
    return T_1;
}

int main() {
    try {
        cout<<integrate(func, 0, 1, 1e-9, 15)<<endl;
    } catch (char const* e) {
        cout<<e<<endl;
    }
    return 0;
}
