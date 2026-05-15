vector<int> primes;
bool isprime[MAXN];
int spf[MAXN], phi[MAXN];
void sieve() {
  for (int i = 0; i < MAXN; ++i) {
      isprime[i] = true; spf[i] = i; phi[i] = i;
  }
  isprime[0] = isprime[1] = false;
  
  for (ll i = 2; i < MAXN; ++i) {
      if (isprime[i]) {
          primes.push_back(i); phi[i] = i - 1; 
          for (ll j = 2 * i; j < MAXN; j += i) {
              isprime[j] = false;
              if (spf[j] == j) spf[j] = i;
              phi[j] -= phi[j] / i;
          }
      }
  }
}