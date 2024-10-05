#include<bits/stdc++.h>
using namespace std;

struct consumables{
	int type;
};

struct joker{
	int purchasePrice;
	int salePrice;
	string type,edition,time;
	int add;
	
	void resetEdition(){
		int t=rand()%1000;
		if(t<3) edition="Negtive";
		else if(t<6) edition="Polychrome";
		else if(t<20) edition="Holographic";
		else if(t<40) edition="Foil";
		else edition="Base";
	} 
}jokers[11];
void jokerInit(){
	jokers[1]=(joker){2,1,"Joker","Base","duli",4};
	//mult+4 独立 

	jokers[2]=(joker){5,2,"Half Joker","Base","duli",20};
	//cnt<=3 mult+20 独立 
	
	jokers[3]=(joker){5,2,"Mime","Base","duli",0};
	//重新触发手牌 手牌 
	
	jokers[4]=(joker){5,2,"Banner","Base","duli",30};
	//每个剩余弃牌chip+30 独立 
	
	jokers[5]=(joker){5,2,"8 Ball","Base","jifen",0};
	//每张 8 点有 1/4 概率计分时得到一张塔罗牌  独立 
	
	jokers[6]=(joker){8,4,"Fibonacci","Base","jifen",8};
	// A,2,3,5,8 得分时 mult+8 独立
	
	jokers[7]=(joker){6,3,"Hack","Base","jifen",0};
	// 2,3,4,5 得分时重新触发 计分 
	
	jokers[8]=(joker){7,3,"Shortcut","Base","beidong",0};
	//让顺子可以相隔一个点数组成 被动
	
	jokers[9]=(joker){4,2,"Juggler","Base","beidong",0};
	// 手牌上限 +1 被动 
	
	jokers[10]=(joker){6,3,"Bull","Base","duli",0};
	// 每有 $1 chip+2 独立
}


int Juggler,Shortcut;

struct card{
	int number,color;
	string enhance,seal;	
	int getRank(){
		return enhance=="Stone"?100:number==1?14:number;
	}
	int getNumber(){
		return enhance=="Stone"?0:number;
		return number;
	}
	int getColor(){
		if(enhance=="Stone") return 0;
		if(enhance=="Wild") return 5;
		return color;
	}	
	
	friend bool operator<(const card &x,const card &y){
		int tmp1=x.enhance=="Stone"?100:x.number==1?14:x.number;
		int tmp2=y.enhance=="Stone"?100:y.number==1?14:y.number;
		return tmp1^tmp2?tmp1<tmp2:x.color<y.color;
	}
	friend bool operator==(const card &x,const card &y){
		return x.number==y.number&&x.color==y.color&&x.enhance==y.enhance&&x.seal==y.seal;
	}

	

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
		
		sort();
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
				if(Shortcut&&c[i].getRank()!=c[i-1].getRank()+1&&c[i].getRank()!=c[i-1].getRank()+2) isStraight=0;
				if(!Shortcut&&c[i].getRank()!=c[i-1].getRank()+1) isStraight=0;
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
	int jcnt=0,JcntMax=5;
	
	
}p1;






struct SHOP{
	
	
	
};


void getTarot(){
	
}
void getPlanet(){
	
}
void getSpectral(){
	
}
struct challenge{
	int target,sum,BasicMoney,hands,discards,opt;
	
	
	
	void reset(){
		target=300,sum=0,BasicMoney=4,hands=4,discards=4;
		deck.cnt=p1.ccnt;
		for(int i=1;i<=deck.cnt;i++)
			deck.c[i]=p1.c[i];
		deck.shufle();
		hand.cnt=0;			
		cout<<"This stage target is "<<target<<'\n';
	}
	
	string enhanceName[9]={"","Bonus","Mult","Wild","Glass","Steel","Stone","Gold","Lucky"};
	
	string sealName[5]={"","Gold","Red","Blue","Purple"};
	
	string PHname[10]={"","Straight Flush","Four of a King","Full House","Flush","Straight","Three of a King","Two Pair","Pair","High Card"};
	
	int PHchip[10]={0,100,60,40,35,30,30,20,10,5};
	int PHmult[10]={0,8,7,4,4,4,3,2,2,1};
	
	int PokerHands,numcnt[15];
	
	double chips,mults;
	void reTrigger(card tmp){
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
		
		for(int i=1;i<=p1.jcnt;i++){
			if(p1.j[i].type=="8 Ball"&&tmp.getNumber()==8&&rand()%4==0)
				getTarot();
			if(p1.j[i].type=="Fibonacci"&&(tmp.getNumber()==1||tmp.getNumber()==2||tmp.getNumber()==3||tmp.getNumber()==5||tmp.getNumber()==8))
				mults+=8;
		}
	}
	void trigger(card tmp){
		reTrigger(tmp);
		if(tmp.seal=="Red") reTrigger(tmp);
		for(int i=1;i<=p1.jcnt;i++)
			if(p1.j[i].type=="Hack"&&(tmp.getNumber()==2||tmp.getNumber()==3||tmp.getNumber()==4||tmp.getNumber()==5))
				reTrigger(tmp);
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
				}else if(calc.c[i].enhance=="Stone") chips+=50;
			}
			
		}else if(PokerHands==9){
			trigger(calc.c[calc.cnt]);
			for(int i=1;i<calc.cnt;i++)
				if(calc.c[i].enhance=="Stone") chips+=50;
		}else{
			for(int i=1;i<=calc.cnt;i++)
				trigger(calc.c[i]);
			
		}
		
		for(int i=1;i<=calc.cnt;i++)
			numcnt[calc.c[i].getNumber()]--;
			
			
		for(int i=1;i<=hand.cnt;i++){
			if(hand.c[i].enhance=="Steel") mults*=1.5;
			if(hand.c[i].enhance=="Gold") p1.money+=3;
		}
		
		for(int i=1;i<=p1.jcnt;i++){
			if(p1.j[i].type=="Joker") mults+=4;
			if(p1.j[i].type=="Half Joker"&&calc.cnt<=3) mults+=20;
			if(p1.j[i].type=="Mime"){
				for(int i=1;i<=hand.cnt;i++){
					if(hand.c[i].enhance=="Steel") mults*=1.5;
					if(hand.c[i].enhance=="Gold") p1.money+=3;
				}			
			}
			if(p1.j[i].type=="Banner") chips+=30*discards;
			if(p1.j[i].type=="Bull") chips+=p1.money*2;
			
			if(p1.j[i].edition=="Foil") chips+=50;
			if(p1.j[i].edition=="Holographic") mults+=10;
			if(p1.j[i].edition=="Polychrome") mults*=1.5;
		}
		
		return chips*mults;
	}	
	
	
	int HandMax=8;
	void Replenish(){
		while(hand.cnt<HandMax+Juggler&&!deck.empty()){
			hand.insert(deck.GetHead());
		}
		cout<<"now you have\n";
		hand.sort();
		hand.show();
	}
	
	void playDiscard(){
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
				
	}
	void waitForChooseWay(){
		Replenish();
		
		cout<<"choose 1 for 出牌, 2 for 弃牌\n";
		
		cin>>opt;
	}
	void playCard(){
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
	bool settle(){
		if(sum>=target){
			cout<<"你过关！\n";
			
			int GetMoney=BasicMoney+hands+min(5,p1.money/5);
			cout<<"You get "<<GetMoney<<" coins\n";
			p1.money+=GetMoney;
			
			cout<<"THE SHOP\n";
			
			return true;
			
		}else{
			cout<<"你不过关！\n";
			return false;
		}	
	}
	
	void Start(){
		bool Continue=1;
		while(Continue){
			reset();
			for(hands=4;hands;hands--){
				cout<<"第 "<<5-hands<<"次出牌\n";
				waitForChooseWay();		
				while(opt==2&&discards){	
					playDiscard();	
					waitForChooseWay();
				}
				while(opt!=1){
					cout<<"不能再弃牌了\n";
					waitForChooseWay();
				}
				if(opt==1) playCard();
				if(sum>=target) break;
			}			
			Continue=settle();	
		}		
	}
	
}playCard;

signed main(){
	srand(time(0)); 
	
	p1.money=0;
	p1.ccnt=52;
	for(int i=1;i<=4;i++) 
		for(int j=1;j<=13;j++)
			p1.c[(i-1)*13+j]=(card){j,i,"",""};
	p1.jcnt=0;
	
	playCard.Start();	
	
	return 0;
}
