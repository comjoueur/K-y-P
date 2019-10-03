#include<bits/stdc++.h>
using namespace std;
int arr[10000];
int find(int a){
    if(a==arr[a]) return a;
    return arr[a]=find(arr[a]);
}
void uni(int a,int b){
    int _a=find(a);
    int _b=find(b);
    arr[a]=b;
}
int main(){
    int a,b;
    cin>>a>>b;
    for(int i=0;i<a;++i){
        arr[i]=i;
    }
    vector<vector<pair<int,int> > >T(a);
    map<int,vector<pair<int,int> > >vec;
    for(int i=0;i<b;++i){
        int g,h,k;
        cin>>g>>h>>k;
        T[g].push_back(make_pair(h,k));
        vec[k].push_back(make_pair(h,g));
        vec[k].push_back(make_pair(g,h));
    }
    int n=0;
    vector<pair<int,int> >rsp;
    while(n<a-1 && !vec.empty()){
        vector<pair<int,int> >&v=vec.begin()->second;
        if(!v.empty()){
            int f=v[v.size()-1].first;
            int s=v[v.size()-1].second;
            if(find(f)!=find(s)){
                rsp.push_back(make_pair(f,s));
                uni(f,s);
                n++;
                cout<<f<<" "<<s<<" "<<vec.begin()->first<<endl;
            }
            v.pop_back();
        }
        else{
            vec.erase(vec.begin());
        }
    }
    if(n!=a-1){
        cout<<"Sin arbol de expansion minima"<<endl;
    }
    ofstream fin("kruskal.txt");
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