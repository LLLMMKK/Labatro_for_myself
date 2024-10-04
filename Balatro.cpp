#include<bits/stdc++.h>
using namespace std;
struct card{
	int number,color;
	friend bool operator<(const card &x,const card &y){
		int tmp1=x.number,tmp2=y.number;
		if(tmp1<3) tmp1+=13;
		if(tmp2<3) tmp2+=13;
		return tmp1^tmp2?tmp1<tmp2:x.color<y.color;
	}
	
	int spec;
};

struct joker{
	int type;
};

struct Deck{
	card c[105];
	int cnt;
	
	void shufle(){
		for(int i=1;i<=cnt;i++)
			swap(c[i],c[rand()%i+1]);
	}
	
	void show(){
		for(int i=1;i<=cnt;i++){
			cout<<c[i].color<<' '<<c[i].number<<'\n';
		}
	}
	
	void sort(){
		std::sort(c+1,c+1+cnt);
	}
	
	
	int head=1;
	bool empty(){
		return head>cnt;
	}
	void rewind(){
		head=1;
	}
	card GetHead(){
		return c[head++];
	}
	
	void insert(card x){
		c[++cnt]=x;
	}
	
}deck,hand,calc;

struct player{
	int money;
	card c[105];
	int ccnt;
	
	joker j[6];
}p1;

int HandMax=7;

int Target[105];

void Replenish(){
	while(hand.cnt<=HandMax&&!deck.empty()){
		hand.insert(deck.GetHead());
	}
	cout<<"now you have\n";
	hand.sort();
	hand.show();
} 

int calculate(){
	int chips=0,mults=0;
	
	calc.sort();
	
	return 0;
}


signed main(){
	srand(time(0)); 
	
	p1.money=0;
	p1.ccnt=52;
	for(int i=1;i<=4;i++) 
		for(int j=1;j<=13;j++)
			p1.c[(i-1)*13+j]=(card){j,i,0};


	while(true){
		
		int target=600,sum=0,BasicMoney=4;
		
		cout<<"This stage target is "<<target<<'\n';
		
		deck.cnt=p1.ccnt;
		for(int i=1;i<=deck.cnt;i++)
			deck.c[i]=p1.c[i];
		deck.shufle();
		hand.cnt=0;
		
		
		int hands=4,discards=4;
		
		
		for(hands=4;hands;hands--){
			
			cout<<"第 "<<5-hands<<"次出牌\n";
			
			Replenish();
			
			
			cout<<"choose 1 for 出牌, 2 for 弃牌\n";
			
			int opt; cin >> opt;
			
			while(opt==2&&discards){
				
				discards--;
				
				cout<<"输出你需要弃牌的数量和若干张需要弃的牌的序号\n";
				
				int q[15],qn=0;
				cin>>qn;
				for(int i=1;i<=qn;i++)
					cin>>q[i]; 
				
				sort(q+1,q+1+qn);
				
				for(int i=qn;i>=1;i--){
					for(int j=q[i]+1;j<=hand.cnt;j++)
						hand.c[j-1]=hand.c[j];
					hand.cnt--;
				}
				
				
				Replenish();
				
				cout<<"choose 1 for 出牌, 2 for 弃牌\n";
				
				cin>>opt;
				
			}
			
			while(opt!=1){
				cout<<"不能再弃牌了\n"; 
				cout<<"choose 1 for 出牌, 2 for 弃牌\n";
				cin>>opt;
			}
			
			if(opt==1){
				cout<<"输出你需要出牌的数量和若干张需要出的牌的序号\n";
				
				int q[15],qn=0;
				cin>>qn;
				for(int i=1;i<=qn;i++)
					cin>>q[i]; 
				
				sort(q+1,q+1+qn);
				
				calc.cnt=0;
				
				for(int i=qn;i>=1;i--){
					
					calc.c[++calc.cnt]=hand.c[q[i]];
					
					for(int j=q[i]+1;j<=hand.cnt;j++)
						hand.c[j-1]=hand.c[j];
					hand.cnt--;
				}
				
				int ans=calculate();
				
				cout<<"You get "<<ans<<"points\n";
				
				sum+=ans;
			}
			
			if(sum>=target) break;
			
		}
		
		if(sum>=target){
			cout<<"你过关！\n";
			
			int GetMoney=BasicMoney+hands+min(5,p1.money/5);
			cout<<"You get "<<GetMoney<<" coins\n";
			p1.money+=GetMoney;
			
			cout<<"THE SHOP\n";
			
			
			
		}else{
			cout<<"你不过关！\n";
			break;
		}	
	}
	
	
		
	
	return 0;
}
