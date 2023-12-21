#include <bits/stdc++.h>
#define fast std::cin.tie(0);std::ios_base::sync_with_stdio(0);
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const ll RBN = 1e9+7;
const ll RSN = -(1e9+7);
const double PI = 3.141592653589793;
//mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); ll gen(){return rnd()%100;}

struct Node {
    ll number;
    ll base;
    ll pow;
};

struct MinHeap {
    //non-increasing
    vector<Node> heap;

    void sift_up(ll index) {
        while (index > 0 && heap[(index-1)/2].number > heap[index].number) {
            ll parent = (index-1)/2;
            swap(heap[index],heap[parent]);
            index = parent;
        }
    }
    void sift_down(ll index) {
        while (2*index+1 < heap.size()) {
            ll left = 2 * index + 1;
            ll right = 2 * index + 2;
            ll j = left;
            if ((right < heap.size()) && (heap[right].number < heap[left].number)) {
                j = right;
            }
            if (heap[index].number <= heap[j].number) {
                break;
            }
            swap(heap[index], heap[j]);
            index = j;
        }
    }

    void insert(Node value) {
        heap.push_back(value);
        sift_up(heap.size()-1);

    }
    Node extract_min() {
        Node value = heap[0];
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        sift_down(0);
        sift_up(heap.size()-1);
        return value;
    }
};

signed main() {
    fast;
    ll n;
    cin >> n;
    //через решето ищем одд намберс кидаем в бин кучу
    MinHeap heap_odd_numbers;
    ll* sieve = new ll[5000001];
    for (ll i = 0; i <= 5000000; i++) {
        sieve[i] = i;
    }

    for (ll i = 2; i*i <= 5000000; i++) {
        if (sieve[i]) {
            for (ll j = i * i; j <= 5000000; j += i) {
                sieve[j] = 0;
            }
        }
    }

    for (ll i = 2; i < 5000000; i++) {
        if (sieve[i]) {
            Node number;
            number.number = sieve[i];
            number.base = sieve[i];
            number.pow = 1;
            heap_odd_numbers.insert(number); //думаем
        }
    }
    ll count = 0;
    vector<Node> saved_numbers;
    while (count < n) {
        Node saved;
        Node new_saved;
        new_saved = heap_odd_numbers.extract_min();
        saved = new_saved;
        new_saved.number *= new_saved.number;
        new_saved.pow *= 2;
        count+=1;
        saved_numbers.push_back(saved);
        heap_odd_numbers.insert(new_saved);
    }
    for (ll i = 0; i < saved_numbers.size(); i++) {
        heap_odd_numbers.insert(saved_numbers[i]);
    }
    saved_numbers.clear();

    ll count_of_pows = 0;
    for (ll i = 0; i < n; i++) {
        count_of_pows += heap_odd_numbers.heap[0].pow;
        saved_numbers.push_back(heap_odd_numbers.extract_min());
    }
    cout << count_of_pows << '\n';
    vector<ll> a;
    for (ll i = 0; i<saved_numbers.size(); i++) {
        for (ll j = 0; j < saved_numbers[i].pow; j++) {
            a.push_back(saved_numbers[i].base);
        }
    }
    sort(a.begin(), a.end());
    for (ll i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    return 0;
}
