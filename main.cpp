#include <vector>
#include <stack>
#include <iostream>
#include <map>

using namespace std;

std::map<std::string, int> matched_map;

struct Node
{
    Node(int a)
    {
        value = a;
    }

    int value = 0;
    Node* left = nullptr;
    Node* right= nullptr;
};


void Createchildren(Node* node, vector<int>& arr, int index, int len)
{
    if(index < len)
    {
        node->left= new Node(arr[index]);
        Createchildren(node->left, arr, index+1, len);

        node->right= new Node(-arr[index]);
        Createchildren(node->right, arr, index+1, len);
    }
}

void Dump(Node* node)
{
    std::cout<<node->value;

    if(node->left)
    {
        std::cout<<"\n\t";
        Dump(node->left);

    }

    if(node->right)
    {
        std::cout<<"\n\t";
        Dump(node->right);
    }
}

void Travers(Node* node,
            int sum,
            std::string operations_str,
            int minus_count)
{

    sum += node->value;

    if(node->left)
    {
        Travers(node->left, sum,(operations_str + "+"),minus_count);
    }
    else
    {
        if(sum == 0)
        {
            matched_map.insert(make_pair(operations_str, minus_count));
        }
    }


    if(node->right)
    {
        minus_count++;
        Travers(node->right, sum,(operations_str + "-"),minus_count);
    }
    else
    {
        if(sum == 0)
        {
            matched_map.insert(make_pair(operations_str, minus_count));
        }
    }
}

void split(int number,vector<int>& arr )
{
    while (number > 0)
    {
        int digit = number%10;
        number /= 10;

        arr.insert(arr.begin(),digit);
    }
}
int main()
{
    vector<int> arr;

    int a = gets(stdin);
    split(a,arr);

    Node* root = new Node(arr[0]);

    Createchildren(root, arr, 1, arr.size());

    Travers(root, 0, "", 0);

    int big = -1;
    std::string result= "not possible";
    for(auto itr : matched_map)
    {
        if(itr.second > big)
        {
            big = itr.second;
            result = itr.first;
        }
    }

    std::cout << result<<std::endl;

    return 0;
}
