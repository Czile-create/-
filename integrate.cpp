#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void read(int argc, char* argv[]) {
    ofstream fout("integrate_temp.cpp", ios::out);
    double a, b, r, s;
    bool flag = false;
    for (int i=1; i<argc; i++) 
        flag = flag || argv[i][0] == '-' && argv[i][1] == 'g';
    if (flag){
        cout<<"请输入积分下限、积分上限、精确度和最高迭代次数（若无限制，则输入0）：";
        cin>>a>>b>>r>>s;
    }
    else {
        cout<<"请输入积分下限、积分上限：";
        cin>>a>>b;
        r = 1e-6;
        s = 500;
    }
    cout<<"请用C++语法描述被积函数：\n";
    for (int i=1;i<argc;i++) 
        if (argv[i][0] != '-') {
            cout<<"#include <"<<argv[i]<<">\n";
            fout<<"#include <"<<argv[i]<<">\n";
        }
    fout<<"#include <iostream>\n#include <vector>\n#include <math.h>\nusing namespace std;\n";
    cout<<"double func(double x) {\n";
    fout<<"double func(double x) {";
    int i=1;
    while (i!=0) {
        char ch;
        ch = cin.get();
        fout<<ch;
        if (ch == '{')
            i++;
        else if (ch == '}')
            i--;
    }
    fout<<"\ndouble S(double(* func)(double), double a, double b, double r=1e-6, int s=0) {\n\
        double h = b - a;\n\
        double T_0 = h * (func(a) + func(b)) /2;\n\
        int k=0, ex_2=1, ex_4=1;\n\
        double T_1;\n\
        vector<double> T_re;\n\
        T_re.push_back(T_0);\n\
        do {\n\
            k++, ex_2*=2, ex_4=4;\n\
            double tmp = 0;\n\
            for (int i=0; i<ex_2/2; i++)\n\
                tmp += func(a + (b-a)*(2*i + 1)/ex_2);\n\
            \n\
            T_1 = T_re[0]/2 + tmp *h /ex_2;\n\
            for (int i=0; i<k; i++) {\n\
                tmp = T_1;\n\
                T_1 = ( ex_4 * T_1 - T_re[i] )/(ex_4 - 1);\n\
                ex_4 *= 4;\n\
                T_re[i] = tmp;\n\
            }\n\
            T_re.push_back(T_1);\n\
            if (s && T_re.size() > s) {\n\
                throw \"给定函数不可积分、或函数不连续、或函数不光滑、或函数并非初等函数\\\n若您确信函数可积分，可尝试添加参数-g再次尝试。\";\n\
                continue;\n\
            }\n\
        } while ((fabs(T_1-T_0)>=r) && (T_0=T_1));\n\
        return T_1;\n\
    }\n\
    \n\
    int main() {"<<"\n\tdouble a = "<<a<<", b = "<<b<<", r = "<<r<<", s = "<<s<<";\n\
        try {\n\
            cout<<S(func, a, b, r, s)<<endl;\n\
        } catch (char const* e) {\n\
            cout<<e<<endl;\n\
        }\n\
        return 0;\n\
    }";
    fout.close();
    system("g++ integrate_temp.cpp -o integrate_temp");
    system("./integrate_temp");
    system("rm integrate_temp.cpp");
    system("rm integrate_temp");
}

int main(int argc, char* argv[]) {
    bool flag = false;
    for (int i=1; i<argc; i++) 
        flag = flag || argv[i][0] == '-' && argv[i][1] == 'h';
    if (flag) {
        cout<<"# 积分\n\t在命令行输入‘./integrate’，并且按照提示输入积分下限，积分上限，以及被积函数即可。\n\t例如：./integrate\n\
            请输入积分下限、积分上限：1e-6 1\n\
            请用C++语法描述被积函数：\n\
            double func(double x) {\n\
                    return sin(x)/x;\n\
            }\n";
        cout<<"# 带库文件的积分\n\t在命令行输入‘./integrate 库1， 库2...’，并且按照提示输入积分下限，积分上限，以及被积函数即可。\n\t例如./integrate cmath\n\
        请输入积分下限、积分上限：1e-23 1\n\
        请用C++语法描述被积函数：\n\
        #include <cmath>\n\
        double func(double x) {\n\
                return sin(1/x);\n\
        }\n";
        cout<<"# 高级模式\n\t带上参数-g运行\n";
        exit(0);
    }
    cout<<"INTEGRATE V2.0 (C) Czile.\nAdd '-h' to get help.\n";
    read(argc, argv);
    return 0;
}
