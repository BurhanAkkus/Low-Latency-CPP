#include <cstdlib>

using namespace std;

// can't extract *b out of the loop as loop-invariant.
// can't guarantee *b stays the same through the loop because
// can't guarantee a doesn't point to the same address as b. 
void possiblePointerAliasing(int* a, int* b, int n){
    for(auto i = 0; i < n; i++){
        a[i] += *b;
    }
}

void noPointerAliasingGuarantee(int* __restrict a, int* __restrict b, int n){
    for(auto i = 0; i < n; i++){
        a[i] += *b;
    }
}


void noPointerAliasingGuaranteeOnlyA(int* __restrict a, int* b, int n){
    for(auto i = 0; i < n; i++){
        a[i] += *b;
    }
}


void noPointerAliasingGuaranteeOnlyB(int* a, int* b, int n){
    for(auto i = 0; i < n; i++){
        a[i] += *b;
    }
}

int main(){

}