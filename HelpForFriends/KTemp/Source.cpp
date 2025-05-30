#include <iterator>
#include <algorithm>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <chrono>

const int MAXROW = 10, MAXCON = 155;
int offset[MAXROW / 2 + 1];
std::string SCREEN[MAXROW];

void init_offset()
{
    offset[0] = MAXCON / 2;
    for (int i = 1; i <= MAXROW / 2; ++i) {
        offset[i] = (offset[i - 1] >> i);
    }
}

void screen_init()
{
    for (int i = 0; i < MAXROW; ++i)
        SCREEN[i] = std::string(MAXCON, '.');
}

void screen_refresh() {
    for (int i = 0; i < MAXROW; ++i)
    {
        std::cout << SCREEN[i] << std::endl;
    }
}

void screen_clear() { screen_init(); }

using namespace std;

const int lim = 1000;


struct Node {
    int key;
    Node* left, * right;
    int b;
    vector<int> serials;
    bool next;
    Node(int k, Node* l = nullptr, Node* r = nullptr) : key(k), b(0), left(l), right(r), next(false) {}
    ~Node() { delete left; delete right; }
    void display(int, int, int);
    Node(const Node&) = delete;
};

int setval(string& s, int pos, int val) {
    string t(to_string(val));
    if (pos + t.size() - 1 <= MAXCON)
        for (auto p : t) s[pos++] = p;
    return t.size();
}

void Node::display(int row, int col, int depth) {
    if ((row >= MAXROW) || (col < 0) || (col >= MAXCON))
    {
        SCREEN[MAXROW - 1][col] = '+';
        return;
    }
    int ofl = offset[depth + 1];
    setval(SCREEN[row], col, key);
    if (b == 1) { row--; ofl = 2; b = 0; }
    if (left) left->display(row + 2, col - ofl + 1, depth + 1);
    if (right)
        if (!next) { right->display(row + 2, col + offset[depth + 1] - 1, depth + 1); }
        else {
            right->b = 1;
            right->display(row + 1, col + 1, depth);
        }
}

using MyStack = stack<pair<Node*, int>>;
struct myiter : public std::iterator<std::forward_iterator_tag, int>
{
    Node* Ptr;
    MyStack St;
    myiter(Node* p = nullptr) : Ptr(p) {}
    myiter(Node* p, const MyStack&& St) : Ptr(p), St(move(St)) {}
    bool operator == (const myiter& Other) const { return Ptr == Other.Ptr; }
    bool operator != (const myiter& Other) const { return !(*this == Other); }
    myiter& operator++();
    myiter operator++(int) { myiter temp(*this); ++*this; return temp; }
    pointer operator->() { return &Ptr->key; }
    reference operator*() { return Ptr->key; }
};


template <typename Container, typename Iter = myiter>
class outiter : public std::iterator<std::output_iterator_tag, typename Container::value_type>
{
protected:
    Container& container;
    Iter iter;
public:
    outiter(Container& c, Iter it) : container(c), iter(it) {}
    const outiter<Container>&
        operator = (const typename Container::value_type& value) {
        iter = container.insert(value, iter).first;
        return *this;
    }
    const outiter<Container>&
        operator = (const outiter<Container>&) { return *this; }
    outiter<Container>& operator* () { return *this; }
    outiter<Container>& operator++ () { return *this; }
    outiter<Container>& operator++ (int) { return *this; }
};


template <typename Container, typename Iter>
inline outiter<Container, Iter> inserter(Container& c, Iter it)
{
    return outiter<Container, Iter>(c, it);
}

class MyTree {
    const char name;
    Node* root;
    size_t height, count;
    int subCount;
public:
    using key_type = int;
    using value_type = int;
    using key_compare = less<int>;
    void swap(MyTree& rgt)
    {
        std::swap(root, rgt.root);
        std::swap(count, rgt.count);
        std::swap(height, rgt.height);
        std::swap(subCount, rgt.subCount);
    };

    int power() { return subCount; }
    void display();
    void showSet();
    vector<int> getSub();
    void showSub();
    myiter begin()const;
    myiter end()const { return myiter(nullptr); }
    pair<myiter, bool> insert(int, myiter = myiter(nullptr));
    void CONCAT(MyTree&);
    void SUBST(MyTree&, int);
    void CHANGE(MyTree&, int);

    void upSerials(int k) {
        myiter x = begin();
        while (x.Ptr != nullptr)
        {
            for (int i = 0; i < x.Ptr->serials.size(); i++)
                if (x.Ptr->serials[i] > k)
                    x.Ptr->serials[i]--;
            x++;
        }
    }
    pair<myiter, bool> erase(int k) {
        stack <pair<Node*, int>> St;
        pair<myiter, bool> answer;
        Node* p(nullptr),
            * q(root),
            * r(nullptr);
        int a = 0;
        bool cont = (q != nullptr);
        while (cont && (k != q->key))
        {
            St.push(make_pair(p, a));
            p = q;
            a = k > q->key;
            q = a == 1 ? q->right : q->left;
            if (q == nullptr)
                cont = false;
        }
        if (cont) {
            int c = q->serials.back();

            q->serials.pop_back();

            if (q->serials.empty()) {
                --count;
                if (r = q->right) {
                    if (r->left) {
                        St.push(make_pair(p, a));
                        p = q;
                        a = 1;
                        do {
                            St.push(make_pair(p, a));
                            p = r;
                            a = 0;
                            r = a == 1 ? r->right : r->left;
                        } while (r->left);
                        q->key = r->key;
                        p->left = r->right;
                        q = r;
                    }
                    else {
                        r->left = q->left;
                        if (p)
                            if (a == 1)
                                p->right = r;
                            else
                                p->left = r;
                        else
                            root = r;
                        St.pop();
                        p = r;
                        a = 1;
                    }
                }
                else {
                    if (p)
                        if (a == 1)
                            p->right = q->left;
                        else
                            p->left = q->left;
                    else
                        root = q->left;
                }
            }
            if (p->next && p->right == q)
                p->next == false;
            if (q)
                q->left = q->right = nullptr;
            subCount--;
        }
        if (cont && q->serials.empty())
            delete q;
        answer = make_pair(myiter(q), cont);
        return answer;
    };
    MyTree() : name('R'), root(nullptr), height(0), count(0) {}
    int size() { return count; }
    template<typename MyIt>
    MyTree(MyIt, MyIt);
    MyTree(int pow, char c = 'R') : name(c) {
        for (int i = 0; i < pow; ++i)
            insert(rand() % lim);
    }
    MyTree(vector<int> init, const char c = ' ') : name(c), subCount(0)
    {
        for (auto x : init)
            insert(x);
    };
    ~MyTree() { delete root; }
    myiter find(int k) const
    {
        Node* temp{ root };
        while (temp)
        {
            if (temp->key == k)
                return myiter(temp);
            else
                temp = (temp->key > k) ? temp->left : temp->right;
        }
        return myiter(nullptr);
    };
    MyTree(const MyTree& rgt) : MyTree()
    {
        vector<int> Sub;
        subCount = 0;
        Sub.resize(rgt.subCount);
        for (myiter x = rgt.begin(); x != nullptr; x++)
            for (auto i : x.Ptr->serials)
                Sub[i] = x.Ptr->key;
        for (auto i : Sub)
            insert(i);
    }
    MyTree(MyTree&& rgt) : MyTree() { swap(rgt); }

    MyTree& operator = (MyTree&& rgt) { swap(rgt); return *this; }
    MyTree& operator |= (const MyTree&);
    MyTree operator | (const MyTree& rgt) const { MyTree result(*this); return (result |= rgt); }
    MyTree& operator &= (const MyTree&);
    MyTree operator & (const MyTree& rgt) const { MyTree result(*this); return (result &= rgt); }
    MyTree& operator -= (const MyTree&);
    MyTree operator - (const MyTree& rgt) const { MyTree result(*this); return (result -= rgt); }
    MyTree& operator ^= (const MyTree&);
    MyTree operator ^ (const MyTree& rgt) const
    {
        MyTree result(*this); return (result ^= rgt);
    }
};

MyTree& MyTree::operator |= (const MyTree& rgt) {
    MyTree temp;
    set_union(begin(), end(), rgt.begin(), rgt.end(), inserter(temp, myiter(nullptr)));
    swap(temp);
    return *this;
}

MyTree& MyTree::operator &= (const MyTree& rgt) {
    MyTree temp;
    set_intersection(begin(), end(), rgt.begin(), rgt.end(), inserter(temp, myiter(nullptr)));
    swap(temp);
    return *this;
}

MyTree& MyTree::operator -= (const MyTree& rgt) {
    MyTree temp;
    set_difference(begin(), end(), rgt.begin(), rgt.end(), inserter(temp, myiter(nullptr)));
    swap(temp);
    return *this;
}

MyTree& MyTree::operator ^= (const MyTree& rgt) {
    MyTree temp;
    set_symmetric_difference(begin(), end(), rgt.begin(), rgt.end(), inserter(temp, myiter(nullptr)));
    swap(temp);
    return *this;
}

void MyTree::display() {
    std::cout << "Tree " << name << " (n=" << count << " h=" << height << ")\n";
    screen_init();
    root->display(0, offset[0], 0);
    screen_refresh();
}


pair<myiter, bool> MyTree::insert(int k, myiter where)
{
    Node* t{ root };
    bool cont = true, up = false;
    stack<pair<Node*, int>> St;
    if (!where.Ptr) {

        if (t == nullptr) {
            root = new Node(k);
            count = height = 1;
            St.push(make_pair(root, 1));
            root->serials.push_back(subCount);
            subCount++;
            return make_pair(myiter(root, move(St)), true);
        }
        else St.push(make_pair(root, 1));

    }
    else {
        t = where.Ptr;
        St = move(where.St);
    }
    while (cont) {
        if (k == t->key)
        {
            t->serials.push_back(subCount);
            subCount++;
            return make_pair(myiter(t, move(St)), false);
        }
        if (k < t->key) {
            if (t->left) {
                St.push(make_pair(t, 2));
                t = t->left;
            }
            else {
                t->left = new Node(k, nullptr, t->left);
                t->left->serials.push_back(subCount);
                subCount++;
                cont = false;
            }
        }
        else if (!t->right) {
            t->right = new Node(k);
            t->right->serials.push_back(subCount);
            subCount++;
            t->next = true;
            cont = false;
        }
        else if (t->next) {
            if (k == t->right->key) {
                t->right->serials.push_back(subCount);
                subCount++;
                return make_pair(myiter(t->right, move(St)), false);
            }
            else if (k < t->right->key) {
                if (t->right->left) {
                    St.push(make_pair(t, 3));
                    t = t->right->left;
                }
                else {
                    t->right->left = new Node(k, nullptr, t->right->left);
                    t->right->left->serials.push_back(subCount);
                    subCount++;
                    cont = false;
                }
            }
            else {
                if (t->right->right) {
                    St.push(make_pair(t, 4));
                    t = t->right->right;
                }
                else {
                    t->right->right = new Node(k);
                    t->right->right->serials.push_back(subCount);
                    subCount++;
                    up = t->right->next = true;
                    cont = false;
                }
            }
        }
        else if (t->right) {
            St.push(make_pair(t, 3));
            t = t->right;
        }
        else {
            t->right = new Node(k);
            t->right->serials.push_back(subCount);
            subCount++;
            t->next = true;
            cont = false;
        }
        while (up) {
            std::swap(t->key, t->right->key);
            std::swap(t->serials, t->right->serials);
            Node* t1{ t->right };
            t->next = t1->next = false;
            t->right = t->right->right;
            t1->right = t1->left;
            t1->left = t->left;
            t->left = t1;
            t1 = t;
            t = St.top().first;
            switch (St.top().second) {
            case 1:
                ++height;
                up = false;
                break;
            case 2:
                std::swap(t->key, t1->key);
                std::swap(t->serials, t1->serials);
                t->left = t1->left;
                t1->left = t1->right;
                t1->right = t->right;
                t->right = t1;
                up = t1->next = t->next;
                break;
            case 3:
                if (t->next) {
                    t->right->left = t1->right;
                    t1->right = t->right;
                    t->right = t1;
                    t1->next = true;
                }
                else {
                    t->next = true;
                    up = t1->next = false;
                    St.pop();
                }
                break;
            case 4:
                t->right->next = true;
                t1->next = false;
            }
            if (up) St.pop();
        }
    }
    ++count;
    return make_pair(myiter(t, move(St)), true);
};

myiter MyTree::begin() const {
    MyStack St;
    Node* p(root);
    if (p)
        while (p->left) {
            St.push(make_pair(p, 0));
            p = p->left;
        }
    return myiter(p, move(St));
}

void MyTree::CHANGE(MyTree& rgt, int pos) {
    vector<int> sub1, sub2, stemp;
    sub1 = getSub();
    sub2 = rgt.getSub();
    if (pos > sub1.size())
        sub1.insert(sub1.end(), sub2.begin(), sub2.end());
    else {
        stemp.insert(stemp.end(), sub1.begin(), sub1.begin() + pos);
        stemp.insert(stemp.end(), sub2.begin(), sub2.end());
        if (pos + sub2.size() < sub1.size())
            stemp.insert(stemp.end(), sub1.begin() + pos + sub2.size(), sub1.end());
        sub1 = stemp;
        stemp.clear();
    }
    MyTree temp(sub1);
    swap(temp);
}

void MyTree::SUBST(MyTree& rgt, int pos) {
    vector<int> sub1, sub2;
    sub1 = getSub();
    sub2 = rgt.getSub();
    if (pos > sub1.size())
        sub1.insert(sub1.end(), sub2.begin(), sub2.end());
    else sub1.insert(sub1.begin() + pos, sub2.begin(), sub2.end());
    MyTree temp(sub1);
    swap(temp);
}

void MyTree::CONCAT(MyTree& rgt) {
    vector<int> sub1, sub2;
    sub1 = getSub();
    sub2 = rgt.getSub();
    sub1.insert(sub1.end(), sub2.begin(), sub2.end());
    MyTree temp(sub1);
    swap(temp);
}

void MyTree::showSet() {
    MyTree temp(*this);
    cout << name << " Set: {";
    for (auto x : temp) std::cout << x << " ";
    std::cout << "}\n";
}

vector<int> MyTree::getSub() {
    vector<int> Sub;
    Sub.resize(subCount);
    for (myiter x = begin(); x != nullptr; x++)
    {
        for (auto i : x.Ptr->serials)
            Sub[i] = x.Ptr->key;
    }
    return Sub;
}

void MyTree::showSub() {
    vector <int> a = getSub();
    std::cout << name << " Subsequence: (";
    for (auto x : a)  std::cout << x << " ";
    std::cout << ")\n";
}


myiter& myiter::operator++()
{
    if (!Ptr) {
        return *this;
    }
    if (Ptr->right) {
        St.push(make_pair(Ptr, 1));
        Ptr = Ptr->right;
        while (Ptr->left) {
            St.push(make_pair(Ptr, 0));
            Ptr = Ptr->left;
        }
    }
    else {
        pair<Node*, int> pp(Ptr, 1);
        while (!St.empty() && pp.second) { pp = St.top(); St.pop(); }
        if (pp.second)
        {
            Ptr = nullptr;
        }
        else Ptr = pp.first;
    }
    return (*this);
}

void prepareIntersection(MyTree& first, MyTree& second, int quantity) {
    for (int i = 0; i < quantity; i++)
    {
        int x = rand() % lim;
        first.insert(x);
        second.insert(x);
    }
}

void showMyTree(MyTree& t) {
    t.showSet(); t.showSub();
}

int ownRand(int d)
{
    return std::rand() % d;
}


int main() {
    srand((unsigned int)8);
    bool debug = false;
    const int MaxMul = 5;
    int middle_power = 0, set_count = 0;
    using namespace std::chrono;

    ofstream fout("in.txt");

    auto Used = [&](MyTree& t) {
        middle_power += t.power();
        ++set_count;
        };

    auto DebOut = [debug](MyTree& t) {
        if (debug) t.display();
        };

    auto rand = [](int d) { return std::rand() % d; };

    for (int p = 5; p <= 205; p += 2) {
        middle_power = 0;
        set_count = 0;
        init_offset();

        MyTree A(p, 'A'), B(p, 'B'), C(p, 'C'), D(p, 'D'), E(p, 'E'),
            F(p, 'F'), G(p, 'G'), H(p, 'H'), I(p, 'I');

        auto t1 = high_resolution_clock::now();

        A |= B;
        DebOut(A); Used(A);
        A ^= C;
        DebOut(A); Used(A);
        int q1 = rand(MaxMul) + 1;
        prepareIntersection(A, D, q1);
        A -= D;
        DebOut(A); Used(A); Used(D);
        int q2 = rand(MaxMul) + 1;
        prepareIntersection(A, E, q2);
        A -= E;
        DebOut(A); Used(A); Used(E);
        int g = ownRand(F.power() + 1);
        F.SUBST(G, g);
        DebOut(F); Used(F); Used(G);
        int h = ownRand(F.power() + 1);
        F.CHANGE(H, h);
        DebOut(F); Used(F); Used(H);
        F.CONCAT(I);
        DebOut(F); Used(F); Used(I);

        auto t2 = high_resolution_clock::now();
        auto dt = duration_cast<duration<double>>(t2 - t1);
        if (set_count > 0) middle_power /= set_count;

        fout << middle_power << " " << (double)(dt.count()) << endl;
        cout << "\n " << p << " : " << set_count << " * "
            << middle_power << " DT = " << (dt.count()) << " sec";


    }

    return 0;
}
