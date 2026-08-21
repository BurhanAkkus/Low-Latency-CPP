#include "../common/logging.h"

using namespace Common;
int main(){
    Logger logger{"../logs/log_example.txt"};
    std::string cppString = "This is a C++ String";
    const char* cString = "this is a C String"; 
    logger.log("This is my first(%.) log statement\n",1);
    logger.log("% \n%\nthis is my percentage sign:%%\n",cppString,cString);
    char percentage_sign = '%';
    logger.log("I'm logging a percentage sign here%\n",percentage_sign);
    int i = 3;
    unsigned int ui = 7;
    float f{3.14159342123456789};
    double d{1.618531234567890123};
    logger.log("this is my int % and my unsigned int %\nMy float % and my double %\n",i,ui,f,d);
}