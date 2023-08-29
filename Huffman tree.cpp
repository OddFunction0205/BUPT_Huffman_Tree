//因为用中文写注释要来回切换输入法，太麻烦了，所以我就用英文写注释了
#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<algorithm>
using namespace std;

struct HNode//build a node
{
    float weight;//the weight of the node(represented by frequency,so it is 'float')
    int parent;//the subscript of parent
    int LChild;//the subscript of left child
    int RChild;//the subscript of right child
};
struct CodeTableNode//build the code table
{
    char name;//the name of  the character,like'A','B','C'
    int length;
    string code;//the Huffman code
};

//the function declare
void InitializeVisitedArray();
void InitializeHuffmanTree();
void CreatHuffmanTree();
int FindMin(int i);
void DrawHuffmanTree();
void CountStep(int i,int num);
void Encode(int i,string code);
void CreatTable();
void PrintTable();
void EncodeTheTestString();

CodeTableNode CodeTable[26];
HNode HTree[26*2-1];//Huffman Tree is a triple fork tree,so at most have 2*N-1 nodes
bool visited[26*2-1];

int main()
{
    InitializeVisitedArray();
    InitializeHuffmanTree();
    CreatHuffmanTree();
    DrawHuffmanTree();
    printf("\n\n\n");
    CreatTable();
    PrintTable();
    printf("\n\n\n");
    EncodeTheTestString();
    printf("\n\n\n");
    system("pause");
}

void InitializeVisitedArray()
{
    for(int i=0;i<26*2-1;i++)
    {
        visited[i]=0;
    }
}
void InitializeHuffmanTree()
{
    //initialize the array
    float weight[26]={
        0.0819,0.0147,0.0383,0.0391,0.1225,
        0.0226,0.0171,0.0457,0.0710,0.0041,
        0.0014,0.0377,0.0334,0.0706,0.0726,
        0.0289,0.0009,0.0685,0.0636,0.0941,
        0.0258,0.0109,0.0159,0.0021,0.0158,
        0.0008
    };//the frequency from A to Z
    for(int i=0;i<26;i++)
    {
        HTree[i].weight=weight[i];
    }
    for(int i=0;i<2*26-1;i++)
    {
        HTree[i].LChild=HTree[i].RChild=HTree[i].parent=-1;
    }
}
int FindMin(int i)
{
    //find the min:
    float min=1000000;
    int pos=-1;
    
    for(int j=0;j<i;j++)
    {
        if(HTree[j].weight<min&&HTree[j].parent==-1&&visited[j]==0)
        {
            min=HTree[j].weight;
            pos=j;
        }
    }
    visited[pos]=1;
    return pos;
}
void CreatHuffmanTree()
{
    
    for(int i=26;i<26*2-1;i++)
    {
        int Min1=FindMin(i);//the smallest from 0 to i
        int Min2=FindMin(i);//the second smallest from 0 to i

        
        //Build the tree
        HTree[Min1].parent=i;
        HTree[Min2].parent=i;
        HTree[i].weight=HTree[Min1].weight+HTree[Min2].weight;
        HTree[i].LChild=Min1;
        HTree[i].RChild=Min2;
        HTree[i].parent=-1;
    }
}
void DrawHuffmanTree()
{
    printf("|-------------Huffman Tree--------------|\n");
    printf("|---------|--------|------|------|------|\n");
    printf("|Character| Weight |LChild|RChild|Parent|\n");
    printf("|---------|--------|------|------|------|\n");
    for(int i=0;i<26;i++)
    {
        printf("|    %c    | %.4f |  %02d  |  %02d  |  %02d  |\n",(char)(65+i),HTree[i].weight,HTree[i].LChild,HTree[i].RChild,HTree[i].parent);
        printf("|---------|--------|------|------|------|\n");
    }
    for(int i=26;i<26*2-1;i++)
    {
        printf("|   %02d    | %.4f |  %02d  |  %02d  |  %02d  |\n",i,HTree[i].weight,HTree[i].LChild,HTree[i].RChild,HTree[i].parent);
        printf("|---------|--------|------|------|------|\n");
    }
}
void CountStep(int i,int num)
{
    if(HTree[i].LChild==-1)
    {
        CodeTable[i].length=num;
        return;
    }
    CountStep(HTree[i].LChild,num+1);
    CountStep(HTree[i].RChild,num+1);
}
void Encode(int i,string code)
{
    if(HTree[i].LChild==-1)
    {
        CodeTable[i].code=code;
        return;
    }
    Encode(HTree[i].LChild,code+"0");
    Encode(HTree[i].RChild,code+"1");
}
void CreatTable()
{
    for(int i=0;i<26;i++)
    {
        CodeTable[i].name=(char)(65+i);
    }
    CountStep(26*2-2,0);
    Encode(26*2-2,"");
}
void PrintTable()
{
    printf("|-----------Code Table-----------|\n");
    printf("|---------|-----------|----------|\n");
    printf("|Character|Code Length|   Code   |\n");
    printf("|---------|-----------|----------|\n");
    for(int i=0;i<26;i++)
    {
        printf("|    %c    |    %02d     |%-10s|\n",CodeTable[i].name,CodeTable[i].length,CodeTable[i].code.c_str());
        printf("|---------|-----------|----------|\n");
    }
}
void EncodeTheTestString()
{
    cout<<"The Huffman Code of the string 'pneumonoultramicroscopicsilicovolcanoconiosis' is:"<<endl;
    string str("pneumonoultramicroscopicsilicovolcanoconiosis");
    int num=str.length();
    for(int i=0;i<num;i++)
    {
        cout<<CodeTable[str[i]-'a'].code;
    }
}
