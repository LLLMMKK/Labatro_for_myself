#include<bits/stdc++.h>
using namespace std;
struct card{
	int number,color;
	friend bool operator<(const card &x,const card &y){
		int tmp1=x.number,tmp2=y.number;
		if(tmp1==1) tmp1+=13;
		if(tmp2==1) tmp2+=13;
		return tmp1^tmp2?tmp1<tmp2:x.color<y.color;
	}
	friend bool operator==(const card &x,const card &y){
		return x.number==y.number&&x.color==y.color&&x.enhance==y.enhance&&x.seal==y.seal;
	}
	string enhance,seal;
	
	int getNumber(){
		if(enhance=="Stone") return 0;
		return number;
	}
	int getColor(){
		if(enhance=="Stone") return 0;
		if(enhance=="Wild") return 5;
		return color;
	}
};

struct joker{
	int type,edition;
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
			cout<<c[i].getColor()<<' '<<c[i].getNumber()<<'\n';
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
	
	
	
	int GetType(){
		bool isSameColor=1,isStraight=1;
		if(cnt<5) isSameColor=isStraight=0;
		else{
			int Colorlast=1;
			while(c[Colorlast].getColor()==5&&Colorlast<=cnt) ++Colorlast;
			if(Colorlast<cnt){
				for(int i=Colorlast+1;i<=cnt;i++)
					if(c[i].getColor()!=5&&c[i].getColor()!=c[Colorlast].getColor()) isSameColor=0;
			}
			for(int i=2;i<=5;i++){
				if(c[i].getNumber()!=c[i-1].getNumber()+1) isStraight=0;
			}
		}
		if(isSameColor&&isStraight) return 1;
		int tmp[6],qn=0;
		memset(tmp,0,sizeof(tmp));
		for(int i=1;i<=cnt;i++){
			if(i==1||c[i].getNumber()!=c[i-1].getNumber()) ++qn;
			++tmp[qn];
		}
		if(tmp[1]==4||tmp[2]==4) return 2;
		if(cnt==5&&qn==2&&(tmp[1]==3||tmp[2]==3)) return 3;
		if(isSameColor) return 4;
		if(isStraight) return 5;
		if(tmp[1]==3||tmp[2]==3||tmp[3]==3) return 6;
		if((tmp[1]==2&&(tmp[2]==2||tmp[3]==2))||(tmp[2]==2&&tmp[3]==2)) return 7;
		if(tmp[1]==2||tmp[2]==2||tmp[3]==2||tmp[4]==2) return 8;
		return 9;
	}
	
}deck,hand,calc;

struct player{
	int money;
	
	card c[105];
	int ccnt;
	void remove(card t){
		for(int i=1;i<=ccnt;i++){
			if(c[i]==t){
				for(int j=i+1;j<=ccnt;j++)
					c[j-1]=c[j];
				--ccnt;
				break;
			}
		}
	}
	
	joker j[105];
	int jcnt,JcntMax=5,neg;
}p1;

int HandMax=7;

int Target[105];

void Replenish(){
	while(hand.cnt<HandMax&&!deck.empty()){
		hand.insert(deck.GetHead());
	}
	cout<<"now you have\n";
	hand.sort();
	hand.show();
}

string enhanceName[9]={"",
"Bonus",
"Mult",
"Wild",
"Glass",
"Steel",
"Stone",
"Gold",
"Lucky"};

string sealName[5]={"",
"Gold",
"Red",
"Blue",
"Purple"};

string PHname[10]={"",
"Straight Flush",
"Four of a King",
"Full House",
"Flush",
"Straight",
"Three of a King",
"Two Pair",
"Pair",
"High Card"};

int PHchip[10]={0,100,60,40,35,30,30,20,10,5};
int PHmult[10]={0,8,7,4,4,4,3,2,2,1};

int PokerHands,numcnt[15];

double chips,mults;

void trigger(card tmp){
	chips+=tmp.getNumber()==1?11:tmp.getNumber()>10?10:tmp.getNumber();
	if(tmp.seal=="Gold") p1.money+=3;
	if(tmp.enhance=="Bonus") chips+=30;
	if(tmp.enhance=="Mult") mults+=4;
	if(tmp.enhance=="Glass"){
		mults*=2;
		if(rand()%4==0) p1.remove(tmp);
	}
	if(tmp.enhance=="Lucky"){
		if(rand()%5==0) mults+=20;
		if(rand()%15==0) p1.money+=20;
	}
}

int calculate(){
	
	PokerHands=calc.GetType();
	cout<<"It`s "<<PHname[PokerHands]<<"!\n";
	
	chips=PHchip[PokerHands],mults=PHmult[PokerHands];
	
	for(int i=1;i<=calc.cnt;i++)
		numcnt[calc.c[i].getNumber()]++;
	
	card tmp;
	
	if(PokerHands==2||PokerHands==6||PokerHands==7||PokerHands==8){
		for(int i=1;i<=calc.cnt;i++){
			if(numcnt[calc.c[i].getNumber()]>1){
				trigger(calc.c[i]);
				if(calc.c[i].seal=="Red") trigger(calc.c[i]);
			}else if(calc.c[i].enhance=="Stone") chips+=50;
	
		}
		
	}else if(PokerHands==9){
		trigger(calc.c[calc.cnt]);
		if(calc.c[calc.cnt].seal=="Red") trigger(calc.c[calc.cnt]);
		for(int i=1;i<calc.cnt;i++)
			if(calc.c[i].enhance=="Stone") chips+=50;
	}else{
		for(int i=1;i<=calc.cnt;i++){
			trigger(calc.c[i]);
			if(calc.c[i].seal=="Red") trigger(calc.c[i]);
		}
	}
	
	for(int i=1;i<=calc.cnt;i++)
		numcnt[calc.c[i].getNumber()]--;
		
	
	for(int i=1;i<=hand.cnt;i++){
		if(hand.c[i].enhance=="Steel") mults*=1.5;
		if(hand.c[i].enhance=="Gold") p1.money+=3;
	}
	
	return chips*mults;
}


signed main(){
	srand(time(0)); 
	
	p1.money=0;
	p1.ccnt=52;
	for(int i=1;i<=4;i++) 
		for(int j=1;j<=13;j++)
			p1.c[(i-1)*13+j]=(card){j,i,"",""};


	while(true){
		
		int target=300,sum=0,BasicMoney=4;
		
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
				sum+=ans;
				cout<<"You get "<<ans<<"points\nAdd up to "<<sum<<" points\n";
				
				
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
