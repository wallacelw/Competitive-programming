## Seg 2d

```cpp
int t[MAXN<<2][MAXN<<2];
char forest[MAXN][MAXN];
int n,q;
 
 
void buildy(int vx,int tlx,int trx,int vy=1,int tly=0,int tr=n-1){
 
    if(tly==tr){
        if(tlx==trx){
            t[vx][vy]=(forest[tlx][tly]=='*');
        }else{
            t[vx][vy]= t[vx<<1][vy]+t[vx<<1|1][vy];
        }
        return;
    }
    int tmy = (tly+tr)/2;
    buildy(vx,tlx,trx,vy<<1,tly,tmy);
    buildy(vx,tlx,trx,vy<<1|1,tmy+1,tr);
    t[vx][vy]= t[vx][vy<<1]+t[vx][vy<<1|1];
}
 
void buildx(int vx=1,int tlx=0,int trx=n-1){
    
    if(tlx!=trx){
        int tmx = (tlx+trx)/2;
        buildx(vx<<1,tlx,tmx);
        buildx(vx<<1|1,tmx+1,trx);
    }
 
    buildy(vx,tlx,trx,1,0,n-1);
}
 
int sum_y(int vx,int vy,int tly,int tr,int ly,int ry){
    if(tr<ly || tly>ry){
        return 0;
    }
 
    if(tly==ly && tr ==ry){
        return t[vx][vy];
    }
 
    int tmy = (tly+tr)/2;
    return sum_y(vx,vy<<1,tly,tmy,ly,min(tmy,ry))+sum_y(vx,vy<<1|1,tmy+1,tr,max(tmy+1,ly),ry);
}
 
 
int sum_x(int vx,int tlx,int trx,int lx,int rx,int ly,int ry){
 
    if(trx<lx || tlx>rx){
        return 0;
    }
 
    if(tlx==lx && trx ==rx){
        return sum_y(vx,1,0,n-1,ly,ry);
    }
 
    int tmx = (tlx+trx)/2;
    return sum_x(vx<<1,tlx,tmx,lx,min(tmx,rx),ly,ry)+sum_x(vx<<1|1,tmx+1,trx,max(lx,tmx+1),rx,ly,ry);
}
 
 
void updatey(int vx,int vy,int y,int tly,int tr,int tlx,int trx){
    if(tly==tr){
        if(tlx==trx){
            t[vx][vy]=(t[vx][vy]^=1);
        }else{
            t[vx][vy]= t[vx<<1][vy]+t[vx<<1|1][vy];
        }
        return;
    }
    int tmy = (tly+tr)/2;
 
    if(y<=tmy){
        updatey(vx,vy<<1,y,tly,tmy,tlx,trx);
    }else{
        updatey(vx,vy<<1|1,y,tmy+1,tr,tlx,trx);
    }
 
    t[vx][vy]=t[vx][vy<<1]+ t[vx][vy<<1|1];
}
 
void updatex(int vx,int tlx,int trx,int y,int x){
    if(tlx!=trx){
 
        int tmx = (tlx+trx)/2;
 
        if(x<=tmx){
            updatex(vx<<1,tlx,tmx,y,x);
        }else{
            updatex(vx<<1|1,tmx+1,trx,y,x);
        }   
    }
 
    updatey(vx,1,y,0,n-1,tlx,trx);
}
 
int main(){
    sws
    cin>>n>>q;
 
    rep(i,0,n*n)cin>>forest[i%n][i/n];
 
    buildx();
    
    while(q--){
        int op;cin>>op;
        if(op==1){
            int y,x;
            cin>>y>>x;
            y--;x--;
            updatex(1,0,n-1,y,x);
        }else{
            int y1,x1,y2,x2;
            cin>>y1>>x1>>y2>>x2;
            y1--;y2--;x1--;x2--;
            cout<<sum_x(1,0,n-1,x1,x2,y1,y2)<<endl;
        }
 
    }
}
```