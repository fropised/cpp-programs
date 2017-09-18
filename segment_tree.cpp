/*
	Name: Segment_Tree
	Copyright: 2017
	Author: Fropised
	Date: 18/09/17 19:47
	Description: The program of segment tree
*/
#include<iostream> //the headfile to input and output
#include<algorithm> //the headfile to use max
#define MaxN 1000000 //the maximum number of n
#define INF 0xffffffff //INF is a very large number nearly INT_MAX
using namespace std;

int a[MaxN + 1],f[MaxN * 4 + 10],tag[MaxN * 4 + 10];
//array a is used to save the beginning numbers
//array f is the array of the segment tree,it should be four times as large as the maximum number of n
//array tag is used to save the tag of the segment tree

void downtag(int x) //downtag means to give the segment tree tag to the son of this node
{
	if (tag[x] == 0) return ; //if the node doesn't have tag left,exit the function
	tag[x << 1] += tag[x]; //the tag of its left son should plus the node's tag
	tag[(x << 1) + 1] += tag[x]; //the tag of its right son should plus the node's tag
	f[x << 1] += tag[x]; //the left son of this node should plus the node's tag
	f[(x << 1) + 1] += tag[x]; //the right son of this node should plus the node's tag
	tag[x] = 0; //to avoid to calculate the tag again,to clear the tag of the node
}

void build(int x,int l,int r) //to build the segment tree,x is the present node,l and r are the node's range
{
	if (l == r) f[x] = a[l]; //if it is the leave node,it would be the value of the array a
	else
	{
		int mid = (l + r) >> 1; //mid is the middle of the range
		build(x << 1,l,mid); //to build the node's left son's segment tree
		build((x << 1) + 1,mid + 1,r); //to build the node's right son's segment tree  
		f[x] = max(f[x << 1],f[(x << 1) + 1]); //the node's value should be the maximum of its sons
	}
}

void modify(int x,int l,int r,int ll,int rr,int d) //to change the value of some node
{
	if (l >= ll && r <= rr) 
	//if the range which should be changed is included by present range,the present range should be changed
	{ 
		f[x] += d; tag[x] += d; //to add the value of the node,also the value of the tag
	}
	else
	{
		downtag(x); //to provide the value of the tag to its sons
		int mid = (l + r) >> 1;  //mid is the middle of the range
		if (ll <= mid) modify(x << 1,l,mid,ll,rr,d); 
		//if the left son of this node is included by the range which should be changed,modify it
		if (rr >= mid + 1) modify((x << 1) + 1,mid + 1,r,ll,rr,d);
		//if the right son of this node is included by the range which should be changed,modify it
		f[x] = max(f[x << 1],f[(x << 1) + 1]); //the node's value should be the maximum of its sons
	}
}

int query(int x,int l,int r,int ql,int qr) //to ask of some node's value
{
	if (l >= ql && r <= qr) return f[x]; //if the asking range is included by present range,return its value
	else
	{
		downtag(x); //to provide the value of its tag to its sons
		int mid = (l + r) >> 1; //mid is the middle of the range
		int s = -INF; //to give x a very large number,so each value would be large than it
		if (ql <= mid) s = max(s,query(x << 1,l,mid,ql,qr));
		//if the left son of this node is included by the range which should be changed,ask it
		if (qr >= mid + 1) s = max(s,query((x << 1) + 1,mid + 1,r,ql,qr));
		//if the right son of this node is included by the range which should be changed,ask it
		return s; //to return the answer
	}
}

int main()
{
	int n,q; 
	cin >> n >> q; //n is the number of the numbers,q is the number of the requests
	for (int i = 1;i <= n;++i) cin >> a[i]; //to get the value of the array
	build(1,1,n); //to build the segment tree
	for (int i = 1;i <= q;++i)  
	{
		int operation;
		cin >> operation;
		//operation is what to do,one means to modify the value of some node,two means to ask for some node's value
		if (operation == 1) //the first situation
		{
			int l,r,t;
			cin >> l >> r >> t; //to read the range of the node which should be changed and what to add
			modify(1,1,n,l,r,t); //to modify the range [l,r]
		}
		else
		{
			int l,r;
			cin >> l >> r; //to read the range of the node which should be asked
			cout << query(1,1,n,l,r) << endl; //to output the answer
		}
	}
	return 0;
}
