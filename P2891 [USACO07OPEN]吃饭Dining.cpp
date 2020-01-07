#include<bits/stdc++.h>
#define LL long long
#define LD long double
#define DD double
#define inf 1000000000
#define maxn 400
using namespace std;

int n, f, d, s, t, head[maxn + 2], len = 0;
int dep[maxn + 2];

struct node{
	int v, w, next;
}e[maxn * maxn + 2 * maxn + 1];

void read(int &x){
	char ch;
	bool ok;
	for(ok = 0, ch = getchar(); !isdigit(ch); ch = getchar()) if(ch == '-') ok = 1;
	for(x = 0; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	if(ok) x = -x;
}

void add(int u, int v, int w){
	e[len] = (node){v, w, head[u]};
	head[u] = len++;
}

bool bfs(){
	memset(dep, 0, sizeof dep);
	queue<int> q;
	q.push(s);
	dep[s] = 1;
	while(q.size()){
		int u = q.front(); q.pop();
		for(int i = head[u]; ~i; i = e[i].next){
			int v = e[i].v, w = e[i].w;
			if(!w || dep[v]) continue;
			dep[v] = dep[u] + 1;
			if(v == t) return 1;
			q.push(v);
		}
	}
	return 0;
}

int dfs(int u, int flow){
	if(u == t || !flow) return flow;
	int ansi = 0;
	for(int i = head[u]; ~i; i = e[i].next){
		int v = e[i].v, w = e[i].w;
		if(dep[u] + 1 != dep[v] || !w) continue;
		int tem = dfs(v, min(flow, w));
		flow -= tem; ansi += tem;
		e[i].w -= tem; e[i ^ 1].w += tem;
		if(!flow) break; 
	}
	return ansi;
}

int din(){
	int ansi = 0;
	while(bfs()) ansi += dfs(s, inf);
	return ansi;
}

int main(){
	memset(head, -1, sizeof head);
	read(n); read(f); read(d); s = 0; t = f + 2 * n + d + 1;
	for(int i = 1; i <= f; ++i) add(0, i, 1), add(i, 0, 0);
	for(int i = 1; i <= n; ++i) add(f + i, f + n + i, 1), add(f + n + i, f + i, 0);
	for(int i = 1; i <= d; ++i) add(f + 2 * n + i, t, 1), add(t, f + 2 * n + i, 0);
	for(int i = 1; i <= n; ++i){
		int x, y; read(x); read(y);
		while(x--){
			int z; read(z);
			add(z, f + i, 1); add(f + i, z, 0);
		}
		while(y--){
			int z; read(z);
			add(f + n + i, f + 2 * n + z, 1); add(f + 2 * n + z, f + n + i, 0);
		}
	}
	printf("%d\n", din());
	return 0;
}


