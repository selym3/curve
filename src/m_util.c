int factorial(int n)
{
    int r;

    for (r = 1; n >= 2; --n)
    {
        r *= n;
    }

    return r;
}

int nCr(int n, int r)
{
    return factorial(n) / (factorial(r) * factorial(n - r));
}

int signum(int n)
{
    return (-(n < 0)) + (n > 0);
}

double fpow(double base, int exponent)
{
    double res = 1.0;

    int n = signum(exponent);

    if (n < 0)
        exponent = -exponent;

    while (exponent > 0)
    {
        if (exponent & 1)
            res *= base;
        base *= base;
        exponent >>= 1;
    }

    if (n < 0)
        return 1.0 / res;
    else
        return res;
}

double ufpow(double base, unsigned int exponent)
{
    double res = 1;

    while (exponent > 0)
    {
        if (exponent & 1)
            res *= base;
        base *= base;
        exponent >>= 1;
    }

    return res;
}