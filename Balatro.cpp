#include<bits/stdc++.h>
using namespace std;

struct joker{
	int purchasePrice;
	int salePrice;
	string type,edition,time;
	int add;
	
	friend bool operator==(const joker &x,const joker &y){
		return x.type==y.type&&x.edition==y.edition;
	}
	
	void resetEdition(){
		int t=rand()%1000;
		if(t<3) edition="Negative";
		else if(t<6) edition="Polychrome";
		else if(t<20) edition="Holographic";
		else if(t<40) edition="Foil";
		else edition="Base";
	}
}jokers[11];
void jokerInit(){
	jokers[1]=(joker){2,1,"Joker","Base","end",4};
	//mult+4 独立 

	jokers[2]=(joker){5,2,"Half Joker","Base","end",20};
	//cnt<=3 mult+20 独立 
	
	jokers[3]=(joker){5,2,"Mime","Base","end",0};
	//重新触发手牌 手牌 
	
	jokers[4]=(joker){5,2,"Banner","Base","final end",30};
	//每个剩余弃牌chip+30 独立 
	
	jokers[5]=(joker){5,2,"8 Ball","Base","middle",0};
	//每张 8 点有 1/4 概率计分时得到一张塔罗牌  独立 
	
	jokers[6]=(joker){8,4,"Fibonacci","Base","middle",8};
	// A,2,3,5,8 得分时 mult+8 独立
	
	jokers[7]=(joker){6,3,"Hack","Base","middle",0};
	// 2,3,4,5 得分时重新触发 计分 
	
	jokers[8]=(joker){7,3,"Shortcut","Base","passive",0};
	//让顺子可以相隔一个点数组成 被动
	
	jokers[9]=(joker){4,2,"Juggler","Base","passive",0};
	// 手牌上限 +1 被动 
	
	jokers[10]=(joker){6,3,"Bull","Base","end",0};
	// 每有 $1 chip+2 独立
}


int Juggler,Shortcut;

string suitToString[6]={"Stone","Diamond","Club","Heart","Spade","Wild"};
string numberToString[14]={"Stone","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
struct card{
	int number,suit;
	string enhance,seal;	
	int getRank(){
		return enhance=="Stone"?100:number==1?14:number;
	}
	int getNumber(){
		return enhance=="Stone"?0:number;
		return number;
	}
	int getSuit(){
		if(enhance=="Stone") return 0;
		if(enhance=="Wild") return 5;
		return suit;
	}	
	
	friend bool operator<(const card &x,const card &y){
		int tmp1=x.enhance=="Stone"?100:x.number==1?14:x.number;
		int tmp2=y.enhance=="Stone"?100:y.number==1?14:y.number;
		return tmp1^tmp2?tmp1<tmp2:x.suit<y.suit;
	}
	friend bool operator==(const card &x,const card &y){
		return x.number==y.number&&x.suit==y.suit&&x.enhance==y.enhance&&x.seal==y.seal;
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
			cout<<"("<<i<<")  "<<numberToString[c[i].getNumber()]<<' '<<suitToString[c[i].getSuit()]<<' '<<(c[i].enhance==""?"":(c[i].enhance+"(enhance)"))<<' '<<(c[i].seal==""?"":(c[i].seal+"(seal)"))<<'\n';
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
		bool isSameSuit=1,isStraight=1;
		if(cnt<5) isSameSuit=isStraight=0;
		else{
			int Suitlast=1;
			while(c[Suitlast].getSuit()==5&&Suitlast<=cnt) ++Suitlast;
			if(Suitlast<cnt){
				for(int i=Suitlast+1;i<=cnt;i++)
					if(c[i].getSuit()!=5&&c[i].getSuit()!=c[Suitlast].getSuit()) isSameSuit=0;
			}
			for(int i=2;i<=5;i++){
				if(Shortcut&&c[i].getRank()!=c[i-1].getRank()+1&&c[i].getRank()!=c[i-1].getRank()+2) isStraight=0;
				if(!Shortcut&&c[i].getRank()!=c[i-1].getRank()+1) isStraight=0;
			}
		}
		int tmp[6],qn=0;
		memset(tmp,0,sizeof(tmp));
		for(int i=1;i<=cnt;i++){
			if(i==1||c[i].getNumber()!=c[i-1].getNumber()) ++qn;
			++tmp[qn];
		}		
		if(tmp[1]==5&&isSameSuit) return 1;
		if(cnt==5&&qn==2&&(tmp[1]==3||tmp[2]==3)&&isSameSuit) return 2;
		if(tmp[1]==5) return 3;
		if(isSameSuit&&isStraight) return 4;
		if(tmp[1]==4||tmp[2]==4) return 5;
		if(cnt==5&&qn==2&&(tmp[1]==3||tmp[2]==3)) return 6;
		if(isSameSuit) return 7;
		if(isStraight) return 8;
		if(tmp[1]==3||tmp[2]==3||tmp[3]==3) return 9;
		if((tmp[1]==2&&(tmp[2]==2||tmp[3]==2))||(tmp[2]==2&&tmp[3]==2)) return 10;
		if(tmp[1]==2||tmp[2]==2||tmp[3]==2||tmp[4]==2) return 11;
		return 12;
	}
	
}deck,hand,calc;

struct consumables{
	string type;
	string name;
	string description;
	consumables(){};
	consumables(string Type,string Name,string Des){type=Type,name=Name,description=Des;}
	friend bool operator==(const consumables &x,const consumables &y){
		return x.type==y.type&&x.name==y.name;
	}
	friend bool operator<(const consumables &x,const consumables &y){
		return x.type<y.type||(x.type==y.type&&x.name<y.name);
	}
}spectrals[10],tarots[15],planets[13];

struct player{
	int money;
	
	card c[105];
	int ccnt;
	void addCard(card t){
		c[++ccnt]=t;
	}
	void remCard(card t){
		for(int i=1;i<=ccnt;i++)
			if(c[i]==t){
				for(int j=i+1;j<=ccnt;j++)
					c[j-1]=c[j];
				--ccnt;
				break;
			}
	}
	void enhance(const card &t,string type){
		for(int i=1;i<=ccnt;i++)
			if(c[i]==t){
				c[i].enhance=type;
				break;
			}
	}
	void seal(const card &t,string type){
		for(int i=1;i<=ccnt;i++)
			if(c[i]==t){
				c[i].seal=type;
				break;
			}
	}
	void resetSuit(const card &t,int suit){
		for(int i=1;i<=ccnt;i++)
			if(c[i]==t){
				c[i].suit=suit;
				break;
			}
	}
	
	joker j[105];
	int jcnt=0,JcntMax=5;
	void addJoker(joker tmp){
		if(tmp.edition=="Negative") ++JcntMax;
		if(jcnt<JcntMax){
			j[++jcnt]=tmp;
			if(tmp.type=="Juggler") Juggler++;
			if(tmp.type=="Shortcut") Shortcut++;
		}
	}
	void remJoker(joker tmp){
		for(int i=1;i<=jcnt;i++)
			if(j[i]==tmp){
				if(tmp.edition=="Negative") --JcntMax;
				if(tmp.type=="Juggler") Juggler--;
				if(tmp.type=="Shortcut") Shortcut--;
				for(int l=i+1;l<=jcnt;l++)
					j[l-1]=j[l];
				--jcnt;
				break;
			}
		
	}
	
	consumables co[5];
	int cocnt,cocntMax=2;
	
	void addConsumable(consumables tmp){
		if(cocnt<cocntMax)
			co[++cocnt]=tmp;
	}
	void remConsumable(consumables tmp){
		for(int i=1;i<=cocnt;i++)
			if(co[i]==tmp){
				for(int j=i+1;j<=cocnt;j++)
					co[j-1]=co[j];
				--cocnt;
				break;
			}		
	}
	void showConsumable(){
		for(int i=1;i<=cocnt;i++)
			cout<<"("<<i<<")  "<<co[i].type<<' '<<co[i].name<<' '<<co[i].description<<'\n';
	}
	
}p1;


map<consumables,int> PlanettoInt;
void planetInit(){
	planets[1]=(consumables){"planet","Eris","Level up \"Flush Five\""};
	planets[2]=(consumables){"planet","Ceres","Level up \"Flush House\""};
	planets[3]=(consumables){"planet","Planet X","Level up \"Five of a Kind\""};
	planets[4]=(consumables){"planet","Neptune","Level up \"Straight Flush\""};
	planets[5]=(consumables){"planet","Mars","Level up \"Four of a King\""};
	planets[6]=(consumables){"planet","Earth","Level up \"Full House\""};
	planets[7]=(consumables){"planet","Jupiter","Level up \"Flush\""};
	planets[8]=(consumables){"planet","Saturn","Level up \"Straight\""};
	planets[9]=(consumables){"planet","Venus","Level up \"Three of a King\""};
	planets[10]=(consumables){"planet","Uranus","Level up \"Two Pair\""};
	planets[11]=(consumables){"planet","Mercury","Level up \"Pair\""};
	planets[12]=(consumables){"planet","Pluto","Level up \"High Card\""};
	for(int i=1;i<=12;i++) PlanettoInt[planets[i]]=i;
}

void tarotInit(){
	tarots[1]=(consumables){"tarot","The Magician(1)","Enhances 2 selected cards to Lucky Cards"};

	tarots[2]=(consumables){"tarot","The Empress(3)","Enhances 2 selected cards to Mult Cards"};

	tarots[3]=(consumables){"tarot","The Hierophant(5)","Enhances 2 selected cards to Bonus Cards"};

	tarots[4]=(consumables){"tarot","The Lovers(6)","Enhances 1 selected card into a Wild Card"};

	tarots[5]=(consumables){"tarot","The Chariot(7)","Enhances 1 selected card into a Steel Card"};

	tarots[6]=(consumables){"tarot","Justice(8)","Enhances 1 selected card into a Glass Card"};

	tarots[7]=(consumables){"tarot","The Hermit(9)","Doubles money(Max of $20)"};

	tarots[8]=(consumables){"tarot","The Wheel of Fortune(10)","1 in 4 chance to add Foil, Holographic, or Polychrome edition to a random Joker"};

	tarots[9]=(consumables){"tarot","The Devil(15)","Enhances 1 selected card into a Gold Card"};

	tarots[10]=(consumables){"tarot","The Tower(16)","Enhances 1 selected card into a Stone Card"};

	tarots[11]=(consumables){"tarot","The Star(17)","Converts up to 3 selected cards to Diamonds"};

	tarots[12]=(consumables){"tarot","The Moon(18)","Converts up to 3 selected cards to Clubs"};

	tarots[13]=(consumables){"tarot","The Sun(19)","Converts up to 3 selected cards to Hearts"};

	tarots[14]=(consumables){"tarot","The World(21)","Converts up to 3 selected cards to Spades"};
}

void spectralInit(){
	spectrals[1]=(consumables){"spectral","Incantation","Destroy 1 random card in your hand, but add 4 random Enhanced numbered cards instead."};
	
	spectrals[2]=(consumables){"spectral","Wraith","Creates a random Rare Joker (must have room), but sets money to $0."};
	
	spectrals[3]=(consumables){"spectral","Sigil","Converts every card in your hand to a single, random Suit."};
	
	spectrals[4]=(consumables){"spectral","Talisman","Adds a Gold Seal to 1 selected card."};
	
	spectrals[5]=(consumables){"spectral","Deja Vu","Adds a Red Seal to 1 selected card."}; 
	
	spectrals[6]=(consumables){"spectral","Trance","Adds a Blue Seal to 1 selected card."};
	
	spectrals[7]=(consumables){"spectral","Medium","Adds a Purple Seal to 1 selected card."};
	
	spectrals[8]=(consumables){"spectral","Black Hole","Upgrades every poker hand (including secret hands not yet discovered) by one level."};//0.3% 出现
}

void getTarot(int type){
	p1.addConsumable(tarots[type]);
}
void getPlanet(int type){
	p1.addConsumable(planets[type]);
}
void getSpectral(int type){
	p1.addConsumable(spectrals[type]);
}
void getRandomJoker(){
	int t=rand()%10+1;
	joker tmp=jokers[t];
	tmp.resetEdition();
	p1.addJoker(tmp);
}
void getRandomTarot(){
	getTarot(rand()%14+1);
}
void getRandomPlanet(){
	getPlanet(rand()%12+1);
}
void getRandomSpectral(){
	if(rand()%1000<3)
		getSpectral(8);
	else getSpectral(rand()%7+1);
}

struct SHOP{
	
	
	
};




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
	
	string PHname[13]={"","Flush Five","Flush House","Five of a Kind","Straight Flush","Four of a King","Full House","Flush","Straight","Three of a King","Two Pair","Pair","High Card"};
	
	int PHchip[13]={0,160,140,120,100,60,40,35,30,30,20,10,5};
	int PHmult[13]={0,16,14,12,8,7,4,4,4,3,2,2,1};
	int PHchipAdd[13]={0,50,40,35,40,30,25,15,30,20,20,15,10};
	int PHmultAdd[13]={0,3,4,3,4,3,2,2,3,2,1,1,1};
	int PHlevel[13]={0,1,1,1,1,1,1,1,1,1,1,1,1};
	int PokerHands,numcnt[15];
	
	void PHupgrade(int tmp){
		PHlevel[tmp]++;
		PHchip[tmp]+=PHchipAdd[tmp];
		PHmult[tmp]+=PHmultAdd[tmp];
	}
	void usePlanet(const consumables &tmp){	
		PHupgrade(PlanettoInt[tmp]);
		p1.remConsumable(tmp);	
	}
	void SelecttoEnhance(int num,string type){
		Replenish();
		cout<<"now input the rank of "<<num<<" cards to be enhanced\n";
		for(int i=1;i<=num;i++){
			int x; cin>>x;
			p1.enhance(hand.c[x],type);
			hand.c[x].enhance=type;
		}
	}
	void SelecttoSuit(int num,int suit){
		Replenish();
		cout<<"now input the rank of "<<num<<" cards to be converted\n";
		for(int i=1;i<=num;i++){
			int x; cin>>x;
			p1.resetSuit(hand.c[x],suit);
			hand.c[x].suit=suit;
		}
	}
	void useTarot(const consumables &tmp){
		
		if(tmp.name=="The Magician(1)") SelecttoEnhance(2,"Lucky");
		if(tmp.name=="The Empress(3)") SelecttoEnhance(2,"Mult");
		if(tmp.name=="The Hierophant(5)") SelecttoEnhance(2,"Bonus");
		if(tmp.name=="The Lovers(6)") SelecttoEnhance(1,"Wild");
		if(tmp.name=="The Chariot(7)") SelecttoEnhance(1,"Steel");
		if(tmp.name=="Justice(8)") SelecttoEnhance(1,"Glass");
		if(tmp.name=="The Devil(15)") SelecttoEnhance(1,"Gold");
		if(tmp.name=="The Tower(16)") SelecttoEnhance(1,"Stone");
		
		if(tmp.name=="The Hermit(9)") p1.money+=min(p1.money,20);
		if(tmp.name=="The Wheel of Fortune(10)"&&rand()%4==0&&p1.jcnt){
			int t=rand()%3;
			p1.j[rand()%p1.jcnt+1].edition=(t==0?"Polychrome":t==1?"Holographic":"Foil");
		}
		
		if(tmp.name=="The Star(17)") SelecttoSuit(3,1);
		if(tmp.name=="The Moon(18)") SelecttoSuit(3,2);
		if(tmp.name=="The Sun(19)") SelecttoSuit(3,3);
		if(tmp.name=="The World(21)") SelecttoSuit(3,4);
		
		p1.remConsumable(tmp);
	}
	void SelecttoSeal(int num,string type){
		Replenish();
		cout<<"now input the rank of "<<num<<" cards to be sealed\n";
		for(int i=1;i<=num;i++){
			int x; cin>>x;
			card tmp=hand.c[x];
			p1.seal(tmp,type);
			hand.c[x].seal=type;
		}
	}	
	card randomEnhancedNumberCard(){
		return (card){rand()%10+1,rand()%4+1,enhanceName[rand()%8+1],""};
	}
	void useSpectral(const consumables &tmp){
		if(tmp.name=="Incantation"){
			int t=rand()%hand.cnt+1;
			p1.remCard(hand.c[t]);
			hand.c[t]=randomEnhancedNumberCard();
			p1.addCard(hand.c[t]);
			
			for(int i=1;i<=3;i++)
				p1.addCard(randomEnhancedNumberCard());
		}
		if(tmp.name=="Incantation"){
			getRandomJoker();
			p1.money=0;
		}
		if(tmp.name=="Sigil"){
			int suit=rand()%4+1;
				for(int i=1;i<=hand.cnt;i++){
					p1.resetSuit(hand.c[i],suit);
					hand.c[i].suit=suit;
				}
		} 
		
		if(tmp.name=="Talisman") SelecttoSeal(1,"Gold");
		if(tmp.name=="Deja Vu") SelecttoSeal(1,"Red");
		if(tmp.name=="Trance") SelecttoSeal(1,"Blue");
		if(tmp.name=="Meidum") SelecttoSeal(1,"Purple");
		
		if(tmp.name=="Black Hole") for(int i=1;i<=12;i++) PHupgrade(i);
	}

	void useConsumables(const consumables &tmp){
		//在 hand 中选取，在 p1 中加减，不对 deck 修改 
		if(tmp.type=="planet") usePlanet(tmp);
		else if(tmp.type=="tarot") useTarot(tmp);
		else if(tmp.type=="spectral") useSpectral(tmp);		
	}
	
	double chips,mults;
	void reTrigger(card tmp){
		chips+=tmp.getNumber()==1?11:tmp.getNumber()>10?10:tmp.getNumber();
		if(tmp.seal=="Gold") p1.money+=3;
		if(tmp.enhance=="Bonus") chips+=30;
		if(tmp.enhance=="Mult") mults+=4;
		if(tmp.enhance=="Glass"){
			mults*=2;
			if(rand()%4==0) p1.remCard(tmp);
		}
		if(tmp.enhance=="Lucky"){
			if(rand()%5==0) mults+=20;
			if(rand()%15==0) p1.money+=20;
		}
		
		for(int i=1;i<=p1.jcnt;i++){
			if(p1.j[i].type=="8 Ball"&&tmp.getNumber()==8&&rand()%4==0)
				getRandomTarot();
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
		
		if(PokerHands==5||PokerHands==9||PokerHands==10||PokerHands==11){
			for(int i=1;i<=calc.cnt;i++){
				if(numcnt[calc.c[i].getNumber()]>1){
					trigger(calc.c[i]);
				}else if(calc.c[i].enhance=="Stone") chips+=50;
			}
		}else if(PokerHands==12){
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
		
		int q[15],qn=0;	
		cout<<"input the amount of the cards you need to Discard\n";
		
		cin>>qn;
		
		cout<<"input the rank of the cards\n";

		for(int i=1;i<=qn;i++)
			cin>>q[i]; 
		
		sort(q+1,q+1+qn);
		
		for(int i=qn;i>=1;i--){
			if(hand.c[q[i]].seal=="Purple") getRandomTarot();	
			
			for(int j=q[i]+1;j<=hand.cnt;j++)
				hand.c[j-1]=hand.c[j];
			hand.cnt--;
		}
				
	}
	void waitForChooseWay(){
		Replenish();
		
		cout<<"input 1 for Play Hand, 2 for Discard, 3 for Spectral/Planet/Tarot\n";
		
		cin>>opt;
	}
	void playCard(){
		int q[15],qn=0;	
		cout<<"input the amount of the cards you need to Play Hand\n";
		
		cin>>qn;
		
		cout<<"input the rank of the cards\n";

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
		cout<<"You get "<<chips<<" * "<<mults<<" = "<<ans<<" points\nAdd up to "<<sum<<" points\n";		
	}
	bool settle(){
		if(sum>=target){
			
			for(int i=1;i<=hand.cnt;i++)
				if(hand.c[i].seal=="Blue") getPlanet(PokerHands);
			
			cout<<"YOU WIN！\n";
			
			int GetMoney=BasicMoney+hands+min(5,p1.money/5);
			cout<<"You get "<<GetMoney<<" coins\n";
			p1.money+=GetMoney;
		
			
			cout<<"THE SHOP\n";
			
			return true;
			
		}else{
			cout<<"YOU LOSE!\n";
			return false;
		}	
	}
	
	void Start(){
		bool Continue=1;
		while(Continue){
			reset();
			cout<<"you have "<<discards<<"times Discards\n";
			for(hands=4;hands;hands--){
				cout<<"now you have "<<hands<<"times Play Hands\n";
				waitForChooseWay();
				
				
				while(opt!=1){
					if(opt==2){
						if(discards){
							playDiscard();	
							waitForChooseWay();	
						}else{
							cout<<"You can't discard\n";
							waitForChooseWay();	
						}
					}else if(opt==3){
						if(p1.cocnt){
							p1.showConsumable();
									
							cout<<"input the rank of the consumable card you want to use or 0 to go back\n";				
							int x; cin>>x;
							if(x==0) waitForChooseWay();
							else useConsumables(p1.co[x]);
							
						}else{
							cout<<"You have no consumable card\n";
							waitForChooseWay();	
						}
					}else{
						cout<<"?\ninput again\n";
						waitForChooseWay();
					}	
				}
				playCard();
				
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
	jokerInit();
	
	playCard.Start();	
	
	return 0;
}
