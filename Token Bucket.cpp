/*@raghavkapoor-prog

Token Bucket Algorithm Implementaion By My own 

Requests are coming let us suppose 100 req per 1min 

100/1 = 100 

Server is potato server meaning it doesn't or can't handle too many requests 
we need to limit the services and request, services can't stop becoz of the exisiting customer and Bussiness Demand 

Algo: Make 1 datastructure named Bucket 
     The Bucket stores tokens, for each token 1 request is handled 
     
     
     Bucket conatins 60 tokens 
     100 requests come , only 60 will get process 
     
     1token = 1 request 
     
Paramters and Arguements 
1. Requests 
2. Bucket lets keep push front and pop back so let's have a queue 
3. Tokens a varchar variable or char or basically a string for simplicity we are keeping Int  */

#include <iostream>
#include <queue>
using namespace std;

class TokenBucket {
private:
    int capacity; 
    int tokens;   
    int refillRate; 
    queue<int> requestQueue;

    int lastRefillTime;
    int currentTime;
public:
    TokenBucket(int capacity, int refillRate) :
     capacity(capacity), tokens(capacity), refillRate(refillRate), lastRefillTime(0), currentTime(0) {}

    void refill() {
        int timeElapsed = currentTime - lastRefillTime;
        tokens += timeElapsed * refillRate;
        if (tokens > capacity) {
            tokens = capacity;
        }
        lastRefillTime = currentTime;
    }

    bool request(int requestId) {
        currentTime++;
        refill();
        if (tokens > 0) {
            tokens--;
            requestQueue.push(requestId);
            return true; // Request is processed
        } else {
            return false; // Request is denied
        }
    }

    void processRequests() {
        while (!requestQueue.empty()) {
            cout << "Processing request: " << requestQueue.front() << endl;
            requestQueue.pop();
        }
    }
};

  int main() {
    TokenBucket bucket(60, 1); // 60 tokens, 1 token per second

    for (int i = 0; i < 100; i++) {
        if (bucket.request(i)) {
            cout << "Request " << i << " processed." << endl;
        } else {
            cout << "Request " << i << " denied." << endl;
        }
    }

    bucket.processRequests();

    return 0;
}