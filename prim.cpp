//dot -Tpng nuevo.txt -o graf.png
#include<bits/stdc++.h>
#include <string> 
using namespace std;
int main(){
    int a,b;
    cin>>a>>b;
    vector<vector<pair<int,int> > > G(a);
    vector<vector<pair<int,int> > > T(a);
    for(int i=0;i<b;i++){
        int g,h,k;
        cin>>g>>h>>k;
        T[g].push_back(make_pair(h,k));
        G[g].push_back(make_pair(h,k));
        G[h].push_back(make_pair(g,k));
    }
    vector<pair<int,int> >rsp;
    map<int,vector<pair<int,int> > >M;
    for(int i=0;i<G[0].size();++i){
        M[G[0][i].second].push_back(make_pair(0,G[0][i].first));
    }
    bool arr[a];
    memset(arr,0,sizeof(arr));
    arr[0]=1;
    int n=1;
    //cout<<M.size()<<endl;
    while(!M.empty() && n!=a){
        vector<pair<int,int> >&v=M.begin()->second;
        int f=v[v.size()-1].first;
        int s=v[v.size()-1].second;
        cout<<f<<" "<<s<<" "<<M.begin()->first<<endl;
        if(!arr[s]){
            rsp.push_back(v[v.size()-1]);
            n++;
            arr[s]=1;
            v.pop_back();
            if(v.empty())
                M.erase(M.begin());
            for(int i=0;i<G[s].size();i++){
                if(!arr[G[s][i].first]){
                    M[G[s][i].second].push_back(make_pair(s,G[s][i].first));
                }
            }
        }
        else{
            v.pop_back();
            if(v.empty())
                M.erase(M.begin());
        }
    }
    if(n!=a){
        cout<<"no hay arbol de expansion minima"<<endl;
        return 0;
    }
    ofstream fin("nuevo.txt");
    char co=34;
    string comi;
    comi+=co;
    string p="digraph G{\n";
    for(int i=0;i<a;i++){
        p+="nodo";
        p+=to_string(i);
        p+="[label=";
        p+=to_string(i);
        p+="]\n";
    }
    for(int i=0;i<a;i++){
        for(int j=0;j<T[i].size();++j){
            p+=(("edge[color="+ comi) +"black")+comi;
            p+="]\n";
            for(int k=0;k<rsp.size();++k)
                if(min((int)i,(int)T[i][j].first)==min((int)rsp[k].first,(int)rsp[k].second) && max((int)i,(int)T[i][j].first)==max((int)rsp[k].first,(int)rsp[k].second)){
                    p+=(("edge[color="+ comi) +"red")+comi;
                    p+="]\n";
                }
            p+="nodo";
            p+=((to_string(i)+"->"+"nodo"+to_string(T[i][j].first))+"[label=")+(to_string(T[i][j].second)+" dir="+comi+"both"+comi+"]\n");
        }
    }
    p+="\n}";
    fin<<p;
}