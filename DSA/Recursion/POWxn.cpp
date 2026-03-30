double helper(double x,long n){
    //base case
    if(n==0){
        return 1;
    }

    double half=helper(x,n/2);
    if(n%2==0){
        return half*half;
    }
    return half*half*x;
}

double myPow(double x, int n) {
    if(n==0){
        return 1;
    }
    long pow=n;
    if(n<0){
        x=1/x;
        pow=-pow;
    }
    return helper(x,pow);
}