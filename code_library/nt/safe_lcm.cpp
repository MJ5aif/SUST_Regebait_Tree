__int128 safe_lcm(__int128 a, __int128 b, __int128 lim) {
    __int128 t = ((a) / gcd(a, b));
    if(t > (lim / b)) return lim+1;
    else return t * b;
}