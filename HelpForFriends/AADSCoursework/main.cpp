#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <unordered_set>

const int MAXROW = 7, MAXCON = 155;
int offset[MAXROW / 2 + 1];
std::string SCREEN[MAXROW];
int setval(std::string& s, int pos, int val)
{
    std::string t(std::to_string(val));
    for (auto p : t)
    {
        s[pos++] = p;
    }
    return t.size();
}
void init_offset()
{
    offset[0] = MAXCON / 2;
    for (int i = 1; i < MAXROW / 2 + 1; ++i)
    {
        offset[i] = (offset[i - 1] / 2);
    }

}
void screen_init()
{
    for (int i = 0; i < MAXROW; ++i)
    {
        SCREEN[i] = std::string(MAXCON, '.');
    }
}
void screen_refresh()
{
    for (int i = 0; i < MAXROW; ++i)
    {
        std::cout << SCREEN[i] << std::endl;
    }
}
struct Node
{
    int key;
    Node* L[2];
    int N;
    int b = 0;
    std::vector<int> serials;
    Node(int k, int n = 0) : key(k), N(n)
    {
        L[0] = nullptr; L[1] = nullptr;
    }
    ~Node()
    {
        delete L[0];
        delete L[1];
    }
    Node(const Node&) = delete;
    void display(int row, int col, int depth)
    {
        std::string sb{ "-o+" };
        if ((row > MAXROW) || (col < 0) || (col > MAXCON))
        {
            return;
        }
        if (row > MAXROW)
        {
            SCREEN[row].replace(col, 3, "+++");
            return;
        }
        setval(SCREEN[row], col, key);
        SCREEN[row + 1][col + 1] = sb[b + 1];
        if (L[0])
        {
            L[0]->display(row + 1, col - offset[depth], depth + 1);
        }
        if (L[1])
        {
            L[1]->display(row + 1, col + offset[depth], depth + 1);
        }
    }
};
using MyStack = std::stack<std::pair<Node*, int>>;
struct myiter : public std::iterator<std::forward_iterator_tag, int>
{
    Node* Ptr;
    MyStack St;
    myiter(Node* p = nullptr) : Ptr(p)
    {
    }
    myiter(Node* p, MyStack&& St) : Ptr(p), St(move(St))
    {
    }
    bool operator == (const myiter& Other) const
    {
        return Ptr == Other.Ptr;
    }
    bool operator != (const myiter& Other) const
    {
        return !(*this == Other);
    }
    myiter& operator++()
    {
        if (!Ptr)
        {
            return *this;
        }
        if (Ptr->L[1])
        {
            St.push(std::make_pair(Ptr, 1));
            Ptr = Ptr->L[1];
            while (Ptr->L[0])
            {
                St.push(std::make_pair(Ptr, 0));
                Ptr = Ptr->L[0];
            }
        }
        else
        {
            std::pair<Node*, int> pp(Ptr, 1);
            while (!St.empty() && pp.second != 0)
            {
                pp = St.top();
                St.pop();
            }
            if (pp.second == 1)
            {
                Ptr = nullptr;
            }
            else
            {
                Ptr = pp.first;
            }
        }
        return (*this);
    }
    myiter operator++(int)
    {
        myiter temp(*this);
        ++*this;
        return temp;
    }
    pointer operator->()
    {
        return &Ptr->key;
    }
    reference operator*()
    {
        return Ptr->key;
    }
};
template <typename Container, typename Iter = myiter>
class outiter : public std::iterator<std::output_iterator_tag, typename Container::value_type>
{
protected:
    Container& container;
    Iter iter;
public:
    outiter(Container& c, Iter it) : container(c), iter(it)
    {
    }
    const outiter<Container>& operator=(const typename Container::value_type& value)
    {
        iter = container.insert(value, Iter(nullptr)).first;
        return *this;
    }
    const outiter<Container>& operator= (const outiter<Container>&)
    {
        return *this;
    }
    outiter<Container>& operator* ()
    {
        return *this;
    }
    outiter<Container>& operator++ ()
    {
        return *this;
    }
    outiter<Container>& operator++ (int)
    {
        return *this;
    }
};
template <typename Container, typename Iter>
inline outiter<Container, Iter> inserter(Container& c, Iter it)
{
    return outiter<Container, Iter>(c, it);
}
class Tree
{
private:
    Node* root = nullptr;
    int n = 0;
    int h = 0;
public:
    using key_type = int;
    using value_type = int;
    using key_compare = std::less<int>;
    Tree(int r = 0)
    {
        for (int i = 0; i < r; ++i)
        {
            insert(rand() % 1000);
        }
    }
    Tree(const Tree& rgt) : Tree()
    {
        for (auto x : rgt)
        {
            insert(x);
        }
    }
    Tree(Tree&& rgt) noexcept : Tree()
    {
        swap(rgt);
    }
    Tree(const std::vector<int>& v)
    {
        for (int x : v)
        {
            insert(x);
        }
    }
    ~Tree()
    {
        delete root;
    }
    Tree& operator = (const Tree& rgt)
    {
        Tree temp(sub());
        swap(temp);
        return *this;
    }
    Tree& operator = (Tree&& rgt) noexcept
    {
        swap(rgt);
        return *this;
    }
    void swap(Tree& rgt)
    {
        std::swap(root, rgt.root);
        std::swap(n, rgt.n);
        std::swap(h, rgt.h);
    }

    size_t getPower() const
    {
        return std::distance(begin(), end());
    }

    static Tree generate(int count, int universe)
    {
        std::unordered_set<int> used;
        Tree result;

        while ((int)used.size() < count) 
        {
            int val = rand() % universe;
            if (used.insert(val).second)
                result.insert(val);
        }

        return result;
    }

    void prepareIntersection(Tree& other, int common) 
    {
        std::unordered_set<int> shared;

        while ((int)shared.size() < common) 
        {
            int val = rand() % 100000;

            if (shared.insert(val).second) 
            {
                this->insert(val);
                other.insert(val);
            }
        }
    }

    void display()
    {
        screen_init();
        root->display(0, offset[0], 0);
        screen_refresh();
    }
    myiter begin() const
    {
        MyStack path;
        Node* node(root);
        if (node)
        {
            while (node->L[0])
            {
                path.push(std::make_pair(node, 0));
                node = node->L[0];
            }
        }
        return myiter(node, move(path));
    }
    myiter end() const
    {
        return myiter(nullptr);
    }
    std::pair<myiter, bool> insert(myiter where, int k)
    {
        return insert(k, where);
    }
    std::pair<myiter, bool> insert(int k, myiter where = myiter(nullptr))
    {
        int a = 0, B[] = { -1, +1 };
        bool cont = true;
        MyStack St(move(where.St));
        if (!where.Ptr)
        {
            if (!root)
            {
                root = new Node(k);
                root->serials.push_back(n);
                n = h = 1;
                return make_pair(myiter(root, move(St)), true);
            }
        }
        Node* p(where.Ptr ? where.Ptr : root), * q(nullptr);
        while (p && k != p->key)
        {
            a = k > p->key ? 1 : 0;
            St.push(std::make_pair(p, a));
            q = p->L[a];
            if (q)
            {
                p = q;
            }
            else
            {
                p->L[a] = q = new Node(k);
                q->serials.push_back(n);
                ++n;
                cont = false;
                break;
            }
        }
        if (cont)
        {
            p->serials.push_back(n++);
            return make_pair(myiter(q), true);
        }
        auto result_stack = MyStack(St);
        auto result = std::make_pair(myiter(p->L[a], std::move(result_stack)), true);
        while (!St.empty())
        {
            auto pa = St.top();
            St.pop();
            p = pa.first;
            a = pa.second;
            if (!p->b)
            {
                p->b = B[a];
                if (p == root)
                {
                    ++h;
                    break;
                }
                else
                {
                    q = p;
                    p = St.top().first;
                }
            }
            else if (p->b == -B[a])
            {
                p->b = 0;
                break;
            }
            else if (p->b == q->b)
            {
                p->L[a] = q->L[1 - a];
                q->L[1 - a] = p;
                p->b = q->b = 0;
                if (p == root)
                {
                    p = root = q;
                }
                else
                {
                    St.top().first->L[St.top().second] = p = q;
                }
                break;
            }
            else {
                Node* r(q->L[1 - a]);
                p->L[a] = r->L[1 - a];
                q->L[1 - a] = r->L[a];
                r->L[1 - a] = p;
                r->L[a] = q;
                if (r->b == B[a])
                {
                    p->b = -B[a];
                    q->b = 0;
                }
                else if (r->b == -B[a])
                {
                    p->b = 0;
                    q->b = B[a];
                }
                else
                {
                    p->b = q->b = 0;
                }
                r->b = 0;
                if (p == root)
                {
                    p = root = r;
                }
                else
                {
                    St.top().first->L[St.top().second] = p = r;
                }
                break;
            }
        }
        return result;
    }
    myiter find(int k)
    {
        Node* p = root;
        MyStack st;
        while (p && p->key != k)
        {
            st.push(std::make_pair(p, k > p->key));
            p = p->L[k > p->key];
        }
        return myiter(p, std::move(st));
    }
    std::pair<myiter, bool> erase(int k)
    {
        std::stack<std::pair<Node*, int>> St;
        Node* p(nullptr), * q(root), * r(nullptr);
        int a(0), B[] = { -1, +1 };
        bool cont = (q != nullptr);
        while (cont && (k != q->key))
        {
            St.push(std::make_pair(p, a));
            p = q;
            a = k > q->key;
            q = q->L[a];
            if (q == nullptr)
            {
                cont = false;
            }
        }
        if (cont)
        {
            n -= q->serials.size();
            if (r = q->L[1])
            {
                if (r->L[0])
                {
                    St.push(std::make_pair(p, a));
                    p = q;
                    a = 1;
                    do
                    {
                        St.push(std::make_pair(p, a));
                        p = r;
                        r = r->L[a = 0];
                    } while (r->L[0]);
                    q->key = r->key;
                    p->L[0] = r->L[1];
                    q = r;
                }
                else
                {
                    r->L[0] = q->L[0];
                    if (p)
                    {
                        p->L[a] = r;
                    }
                    else
                    {
                        root = r;
                    }
                    St.pop();
                    p = r;
                    p->b = q->b;
                    a = 1;
                }
            }
            else
            {
                if (p)
                {
                    p->L[a] = q->L[0];
                }
                else
                {
                    root = q->L[0];
                }
            }
            q->L[0] = q->L[1] = nullptr;
            delete q;
            while (cont)
            {
                cont = false;
                if (!p)
                {
                    --h;
                }
                else if (p->b)
                {
                    cont = true;
                    if (p->b == B[a])
                    {
                        p->b = 0;
                        auto pp = St.top();
                        St.pop();
                        p = pp.first;
                        a = pp.second;
                    }
                    else
                    {
                        q = r = p->L[1 - a];
                        if (r->b == -p->b)
                        {
                            r = r->L[a];
                            p->L[1 - a] = r->L[a];
                            q->L[a] = r->L[1 - a];
                            r->L[a] = p;
                            r->L[1 - a] = q;
                            if (r->b)
                            {
                                if (r->b == B[a])
                                {
                                    p->b = 0;
                                    q->b = -B[a];
                                }
                                else
                                {
                                    p->b = B[a];
                                    q->b = 0;
                                }
                                r->b = 0;
                            }
                            else
                            {
                                q->b = p->b = 0;
                            }
                        }
                        else
                        {
                            p->L[1 - a] = r->L[a];
                            r->L[a] = p;
                            if (r->b)
                            {
                                r->b = p->b = 0;
                            }
                            else
                            {
                                r->b = B[a];
                                cont = false;
                            }
                        }
                        auto pp = St.top();
                        St.pop();
                        p = pp.first;
                        a = pp.second;
                        if (p)
                        {
                            p->L[a] = r;
                        }
                        else
                        {
                            root = r;
                        }
                    }
                }
                else
                {
                    p->b = -B[a];
                }
            }
            return std::make_pair(myiter(nullptr), true);
        }
        else
        {
            return std::make_pair(myiter(nullptr), false);
        }
    }
    std::vector<int> sub() const
    {
        std::vector<int> sub;
        sub.resize(n);
        for (myiter it = begin(); it.Ptr != nullptr; it++)
        {
            for (int i : it.Ptr->serials)
            {
                sub[i] = it.Ptr->key;
            }
        }
        return sub;
    }
    void CONCAT(const Tree& tree)
    {
        std::vector<int> sub1 = sub(), sub2 = tree.sub();
        sub1.reserve(sub1.size() + sub2.size());
        sub1.insert(sub1.end(), sub2.begin(), sub2.end());
        Tree temp(sub1);
        swap(temp);
    }
    void EXCL(Tree& tree)
    {
        std::vector<int> sub1 = sub(), sub2 = tree.sub();
        auto in_sub2 = [&sub2](int n)
            {
                auto it_val = std::find(sub2.begin(), sub2.end(), n);
                return it_val != sub2.end();
            };
        sub1.erase(std::remove_if(sub1.begin(), sub1.end(), in_sub2), sub1.end());
        Tree temp(sub1);
        swap(temp);
    }
    void MUL(int n)
    {
        std::vector<int> sub1 = sub();
        std::vector<int> temp_sub(sub1);
        sub1.reserve(sub1.size() * n);
        for (int i = 0; i < n; i++)
        {
            sub1.insert(sub1.end(), temp_sub.begin(), temp_sub.end());
        }
        Tree temp(sub1);
        swap(temp);
    }

    Tree& operator |= (const Tree& rgt)
    {
        Tree temp;
        set_union(begin(), end(), rgt.begin(), rgt.end(), inserter(temp, myiter(nullptr)));
        swap(temp);
        return *this;
    }
    Tree operator | (const Tree& rgt) const
    {
        Tree result(*this);
        return (result |= rgt);
    }

    Tree& operator ^= (const Tree& rgt)
    {
        Tree temp;
        set_symmetric_difference(begin(), end(), rgt.begin(), rgt.end(), inserter(temp, myiter(nullptr)));
        swap(temp);
        return *this;
    }
    Tree operator ^(const Tree& rgt) const
    {
        Tree result(*this);
        return (result ^= rgt);
    }

    Tree& operator -=(const Tree& rgt)
    {
        Tree temp;
        set_difference(begin(), end(), rgt.begin(), rgt.end(), inserter(temp, myiter(nullptr)));
        swap(temp);
        return *this;
    }
    Tree operator -(const Tree& rgt) const
    {
        Tree result(*this);
        return (result -= rgt);
    }
};


void prepare_intersection(Tree& first_tree, Tree& second_tree, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int x = rand() % 1000;
        first_tree.insert(x);
        second_tree.insert(x);
    }
}
void print_set_and_sub(Tree& tree, std::string tree_name = "")
{
    std::cout << tree_name << '\n';
    std::cout << "Множество:          ";
    for (auto node : tree)
    {
        std::cout << node << ' ';
    }
    std::cout << "\nПодмножество: ";
    for (int x : tree.sub())
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

int main()
{

    setlocale(LC_ALL, "Rus");
    srand(time(0));

    std::ofstream out("results.txt");
    if (!out)
    {
        std::cerr << "Не удалось открыть файл для записи результатов.\n";
        return 1;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int universe_multiplier = 10;

    for (int size = 10; size <= 200; ++size)
    {
        try
        {
            int intersection = size / 3;
            int universe = size * universe_multiplier;

            auto start = std::chrono::high_resolution_clock::now();

            Tree A = Tree::generate(size, universe);
            Tree B = Tree::generate(size, universe);
            Tree C = Tree::generate(size, universe);
            Tree D = Tree::generate(size, universe);
            Tree E = Tree::generate(size, universe);
            Tree F = Tree::generate(size, universe);

            Tree G = Tree::generate(size, universe);
            A.prepareIntersection(B, intersection);
            A.prepareIntersection(C, intersection);
            A.prepareIntersection(D, intersection);
            A.prepareIntersection(G, intersection);

            A -= B;
            A -= C;
            A ^= D;
            A |= E;
            A.CONCAT(F);
            A.EXCL(G);
            A.MUL(2);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            size_t totalPower = A.getPower() + B.getPower() + C.getPower() + D.getPower() + E.getPower() + F.getPower() + G.getPower();
            int containerCount = 7;
            double avgPower = static_cast<double>(totalPower) / containerCount;

            std::cout << size << " " << duration << " " << avgPower << "\n";
            out << size << " " << duration << "\n";
        }
        catch (const std::bad_alloc&)
        {
            std::cerr << "Недостаточно памяти при size = " << size << ". Пропуск.\n";
        }
        catch (const std::exception& e)
        {
            std::cerr << "Ошибка при size = " << size << ": " << e.what() << "\n";
        }
    }

    out.close();
    return 0;
}




//int main()
//{
//    setlocale(LC_ALL, "Rus");
//    srand(time(0));
//    std::ofstream in_txt("in.txt");
//
//    for (int i = 0; i < 200; i++)
//    {
//        int intersection = rand() % 10;
//        int power = 5 * i + intersection * 4 + 1;
//        Tree A(power - 4 * intersection),
//            B(power - intersection),
//            C(power - intersection),
//            D(power - intersection),
//            E(power),
//            F(power),
//            G(power - intersection);
//        std::cout << i << '\n';
//        auto begining = std::chrono::high_resolution_clock::now();
//        prepare_intersection(A, B, intersection);
//        prepare_intersection(A, C, intersection);
//        prepare_intersection(A, D, intersection);
//        prepare_intersection(A, G, intersection);
//        A -= B;
//        A -= C;
//        A ^= D;
//        A |= E;
//        A.CONCAT(F);
//        A.EXCL(G);
//        A.MUL(2);
//        auto end = std::chrono::high_resolution_clock::now();
//        in_txt << power << ' ' << std::chrono::duration_cast<std::chrono::duration<double>>(end - begining).count() << '\n';
//        system("cls");
//    }
//
//    return 0;
//}