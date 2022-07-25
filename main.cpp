#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

// A Huffman tree node
struct MinHeapNode {

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)
    {

        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// For comparison of
// two heap nodes (needed in min heap)
struct compare {

    bool operator()(MinHeapNode* l, MinHeapNode* r)

    {
        return (l->freq > r->freq);
    }
};

// Prints huffman codes from
// the root of Huffman Tree.
void printCodes(struct MinHeapNode* root, const string& str)
{

    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

unordered_map<char, string> codePrefixs(struct MinHeapNode* root) {
    unordered_map<char, string> map;
    queue<pair<string, MinHeapNode*>> queue;
    queue.push(pair<string, MinHeapNode*>("", root));
    struct MinHeapNode *left, *right, *temp;
    string tempStr;
    while (!queue.empty()) {
        temp = queue.front().second;
        tempStr = queue.front().first;
        queue.pop();
        // in root
        if ((temp->data) != '$') {
            map[temp->data] = tempStr;
            continue;
        }
        if (temp->left) {
            queue.push(pair<string , MinHeapNode *>(tempStr + "0", temp->left));
        }
        if (temp->right) {
            queue.push(pair<string , MinHeapNode *>(tempStr + "1", temp->right));
        }

    }
    return map;
}

template<typename K, typename V>
void print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}
typedef pair<char, unsigned long long> tuplet;

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(unordered_map<char, unsigned long long> v)
{
    struct MinHeapNode *left, *right, *top;
    size_t size = v.size();
    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (auto& i: v)
        minHeap.push(new MinHeapNode(i.first, i.second));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {

        // Extract the two minimum
        // freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with
        // frequency equal to the sum of the
        // two nodes frequencies. Make the
        // two extracted node as left and right children
        // of this new node. Add this node
        // to the min heap '$' is a special value
        // for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print Huffman codes using
    // the Huffman tree built above
    print_map(codePrefixs(minHeap.top()));

    printCodes(minHeap.top(), "");
}


unordered_map<char, unsigned long long int> read_file() {
    return unordered_map<char, unsigned long long int>();
}

// Driver Code
int main()
{
    string filepath;
    cin >> filepath;
    unordered_map<char, unsigned long long> freqs = read_file();

//    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
//    int freq[] = { 5, 9, 12, 13, 16, 45 };

//    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(freqs);

    return 0;
}

//#include <iostream>
//#include <unordered_map>
//#include <queue>
//
//using namespace std;
//
//struct MyHistogram {
//
//    MyHistogram() {}
//    MyHistogram(MyHistogram const &pHistogram): count(pHistogram.count), data(pHistogram.data) {}
//    MyHistogram& operator=(const MyHistogram& other) {
//        if (this == &other) {
//            return *this;
//        }
//        delete left;
//        delete right;
//        left = new MyHistogram{*other.left};
//        right = new MyHistogram{*other.right};
//        return *this;
//    }
//
//private:
//    unsigned long long count;
//    char data;
//public:
//    MyHistogram *left, *right;
//    MyHistogram(char data, unsigned long long count = 0)
//    : count(count), data(data), left(nullptr), right(nullptr) {
//    }
//
//    ~MyHistogram() {
//        if (left != nullptr) delete left;
//        if (right != nullptr) delete right;
//    }
//
//    void print() const {
//        cout << "data: " << data << " count: " << count << "\n";
//    }
//
//
//    [[nodiscard]] unsigned long long getCount() const {
//        return count;
//    };
//
//    [[nodiscard]] char getData() const {
//        return data;
//    }
//
//
//};
//class myComparator {
//public:
//    bool operator() (const MyHistogram& h1, const MyHistogram& h2) {
//        return h1.getCount() > h2.getCount();
//    }
//};
//
//void printCodes(class MyHistogram* root, string str) {
//    if (!root) return;
//    if (root->getData() != '$') cout << root->getData() << ": " << str << "\n";
//    printCodes(root->left, str + "0");
//    printCodes(root->right, str + "1");
//}
//
//class HuffmanEncoder {
//    unsigned size;
//
//    priority_queue <MyHistogram, vector<MyHistogram>, myComparator> priorityQueue;
//public:
//    unordered_map<string, string> prefixTable;
//    HuffmanEncoder( vector<pair<unsigned long long, char>>& frequecies) {
//        size = frequecies.size();
//        for (auto i : frequecies) {
//            cout << i.second << ":" << i.first;
//            priorityQueue.push({i.second, i.first});
//        }
//        priorityQueue.top();
//        while (priorityQueue.size() != 1) {
//            auto left = priorityQueue.top();
//            priorityQueue.pop();
//            auto right = priorityQueue.top();
//            priorityQueue.pop();
//
//            auto top = new MyHistogram('$', left.getCount() + right.getCount());
//            top->left = &left;
//            top->right = &right;
//            priorityQueue.push(*top);
//        }
//        auto end = priorityQueue.top();
//        printCodes(&end, "");
//    }
//
//};
//# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))
//int main() {
//    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
//    int freq[] = { 5, 9, 12, 13, 16, 45 };
//    vector<pair<unsigned long long int, char>> pairs;
//    for (int i = 0; i < my_sizeof(arr)/my_sizeof(arr[0]); ++i) {
//        pairs.emplace_back(freq[i], arr[i]);
//    }
//    HuffmanEncoder h = *new HuffmanEncoder(pairs);
////    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}
