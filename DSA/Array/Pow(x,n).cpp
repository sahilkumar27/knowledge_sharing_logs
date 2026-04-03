double myPow(double x, long long n) {
    
    // If exponent is negative, convert:
    // x^(-n) = (1/x)^n
    if (n < 0) {
        x = 1.0 / x;
        n = -n;
    }

    // Call recursive helper to compute power
    return helper(x, n);
}

double helper(double num, long long n) {
    
    // Base case: anything power 0 = 1
    if (n == 0) {
        return 1;
    }

    // Recursively calculate half power
    double half = helper(num, n / 2);

    // If n is even: x^n = (x^(n/2))^2
    if (n % 2 == 0) {
        return half * half;
    } 
    
    // If n is odd: x^n = (x^(n/2))^2 * x
    else {
        return half * half * num;
    }
}