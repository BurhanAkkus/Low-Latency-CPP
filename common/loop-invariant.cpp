#include <cstdlib>

using namespace std;

int main(){
    auto invariantValueGenerator = [](double x) noexcept {return x * x;};
    int a[100],b=rand();

    // without Loop-Invariant Code Motion(LICM)
    for(auto i = 0; i < 100; i++){
        a[i] = invariantValueGenerator(15) * 3 + b / 2;
    }

    // with LICM
    auto invariant = invariantValueGenerator(15) * 3 + b / 2;
    for(auto i = 0; i < 100; i++){
        a[i] = invariant;
    }
}