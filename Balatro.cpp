#include<bits/stdc++.h>
using namespace std;


void help(){
	
	cout<<"----------------------------HELP---------------------------------\n";
	cout<<"JOKER\n";
	cout<<"EDITIONS\n";
	cout<<"Base :    No extra effects\n";
	cout<<"Foil :    +50 Chip\n";
	cout<<"Holographic :    +10 Mult\n";
	cout<<"Polychrome :    *1.5 Mult\n";
	cout<<"Negative :    +1 Joker slot\n";
	
	cout<<"\n";
	
	cout<<"PLAYING CARDS\n";
	cout<<"ENHANCEMENTS\n";
	cout<<"Bonus Card:    +30 Chip\n";
	cout<<"Mult Card:    +4 Mult\n";
	cout<<"Wild Card:    Is considered to be every suit simultaneously\n";
	cout<<"Glass Card:    *2 Mult  ,  1 in 4 chance to destroy card after all scoring is finished\n";
	cout<<"Steel Card:    x1.5 Mult while this card stays in hand\n";
	cout<<"Stone Card:    +50 Chips  ,  No rank or suit  ,  Card always scores\n";
	cout<<"Gold Card:    $3 if this card is held in hand at end of round\n";
	cout<<"Lucky Card:    1 in 5 chance for +20 Mult  ,  1 in 15 chance to win $20(Both can trigger on the same turn)\n";
	
	cout<<"\n";
	
	cout<<"SEALS\n";
	cout<<"Gold Seal:    Earn $3 when this card is played and scores\n";
	cout<<"Red Seal:    Retrigger this card 1 time. As well as when being scored in a poker hand, this also includes in-hand effects\n";
	cout<<"Blue Seal:    If this card is held at end of round, it creates the Planet card matching the final poker hand played, if you have room\n";
	cout<<"Purple Seal:    Creates a Tarot card when discarded, if you have room\n";
	
	cout<<"\n";
	cout<<"POKER HANDS\n";
	cout<<"Straight Flush:    Five cards in consecutive order, all from a single suit.\n";
	cout<<"Four of a King:    Four cards with a matching rank. Suits may differ.\n";
	cout<<"Full House:    Three cards with a matching rank, and two cards with any other matching rank, with cards from two or more suits.\n";
	cout<<"Flush:    Five cards of any rank, all from a single suit.\n";
	cout<<"Straight:    Five cards in consecutive order which are not all from the same suit. Aces can be counted high or low, but not both at once.\n";
	cout<<"Three of a King:    Three cards with a matching rank. Suits may differ.\n";
	cout<<"Two Pair:    Two cards with a matching rank, and two cards with any other matching rank. Suits may differ.\n";
	cout<<"Pair:    Two cards with a matching rank. Suits may differ.\n";
	cout<<"High Card:    When no other hand is possible, the one highest card in your hand. Aces are counted high for this hand.\n";
	
	cout<<"-----------------------------------------------------------------\n";
	cout<<"\n";
}

struct joker{
	int purchasePrice;
	int salePrice;
	string type,edition,time;
	int add;
	string description;
	string rarity;
	friend bool operator==(const joker &x,const joker &y){
		return x.type==y.type;
	}
	
	void resetEdition(){
		int t=rand()%1000;
		if(t<3) edition="Negative";
		else if(t<6) edition="Polychrome";
		else if(t<20) edition="Holographic";
		else if(t<40) edition="Foil";
		else edition="Base";
	}
	
	void show(){
		cout<<'['<<rarity<<"Joker"<<']'<<type<<'('<<edition<<")   :"<<description<<'\n';
	}
}jokers[11];
void jokerInit(){
	jokers[1]=(joker){2,1,"Joker","Base","end",4,"+4 Mult(2 coins)","Common"};

	jokers[2]=(joker){5,2,"Half Joker","Base","end",20,"+20 Mult if played hand contains 3 or fewer cards.(5 coins)","Common"};
	
	jokers[3]=(joker){5,2,"Mime","Base","end",0,"Retrigger all card held in hand abilities(5 coins)","Uncommon"};
	
	jokers[4]=(joker){5,2,"Banner","Base","final end",30,"+30 Chips for each remaining discard(5 coins)","Common"};
	
	jokers[5]=(joker){5,2,"8 Ball","Base","middle",0,"1 in 4 chance for each played 8 to create a Tarot card when scored(Must have room)(5 coins)","Common"}; 
	
	jokers[6]=(joker){8,4,"Fibonacci","Base","middle",8,"Each played Ace, 2, 3, 5, or 8 gives +8 Mult when scored(8 coins)","Uncommon"};
	
	jokers[7]=(joker){6,3,"Hack","Base","middle",0,"Retrigger each played 2, 3, 4, or 5(6 coins)","Uncommon"};
	
	jokers[8]=(joker){7,3,"Shortcut","Base","passive",0,"Allows Straights to be made with gaps of 1 rank(ex: 10 8 6 5 3)(7 coins)","Uncommon"};
	
	jokers[9]=(joker){4,2,"Juggler","Base","passive",0,"+1 hand size(4 coins)","Common"};
	
	jokers[10]=(joker){6,3,"Bull","Base","end",0,"+2 Chips for each $1 you have(6 coins)","Uncommon"};
}


int Juggler,Shortcut;

string suitToString[6]={"Stone","Diamond","Club","Heart","Spade","Wild"};
string numberToString[14]={"Stone","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
string enhanceName[9]={"","Bonus","Mult","Wild","Glass","Steel","Stone","Gold","Lucky"};
string sealName[5]={"","Gold","Red","Blue","Purple"};	
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

	void resetEnhance(){
		int t=rand()%100+1;
		if((t-1)/3+1<=8) enhance=enhanceName[(t-1)/3+1];
		else enhance="";
	}
	
	void resetSeal(){
		int t=rand()%100+1;
		if((t-1)/3+1<=4) seal=sealName[(t-1)/3+1];
		else seal="";
	}
	
	void show(){
		cout<<numberToString[getNumber()]<<' '<<suitToString[getSuit()]<<' '<<(enhance==""?"":(enhance+"(enhance)"))<<' '<<(seal==""?"":(seal+"(seal)"))<<'\n';
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
			cout<<"("<<i<<")  ";
			c[i].show();
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
	
	void remove(card x){
		for(int i=1;i<=cnt;i++)
			if(c[i]==x){
				for(int j=i+1;j<=cnt;j++)
					c[j-1]=c[j];
				--cnt;
				break;
			}
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
	int price;
	consumables(){};
	consumables(string Type,string Name,string Des,int Price){type=Type,name=Name,description=Des,price=Price;}
	friend bool operator==(const consumables &x,const consumables &y){
		return x.type==y.type&&x.name==y.name;
	}
	friend bool operator<(const consumables &x,const consumables &y){
		return x.type<y.type||(x.type==y.type&&x.name<y.name);
	}
	void show(){
		cout<<type<<' '<<name<<"   :"<<description<<'\n';
	}
}spectrals[10],tarots[15],planets[13];

struct player{
	int money;
	
	card c[105];
	int ccnt;
	void addCard(card t){
		c[++ccnt]=t;
		cout<<"Successfully added card ";
		t.show();
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
				cout<<"Successfully enhanced card ";
				c[i].show();				
				break;
			}

	}
	void seal(const card &t,string type){
		for(int i=1;i<=ccnt;i++)
			if(c[i]==t){
				c[i].seal=type;
				cout<<"Successfully sealed card ";
				c[i].show();
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
		if(tmp.edition=="Negative"){
			++JcntMax;
			cout<<"Negative Edition! +1 Joker Slot\n";
		}
		if(jcnt<JcntMax){
			
			j[++jcnt]=tmp;
			cout<<"Successfully added Joker card ";
			tmp.show();
			if(tmp.type=="Juggler"){
				Juggler++;
				cout<<"Juggler! +1 hand size\n";
			}
			if(tmp.type=="Shortcut"){
				Shortcut++;
				cout<<"Shortcut! Allows Straights to be made with gaps of 1 rank\n";
			}
		}else{
			cout<<"Sorry,but there is no room for this Joker\n";
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
		if(cocnt<cocntMax){
			co[++cocnt]=tmp;
			cout<<"Successfully added consumable card ";
			tmp.show();
		}else{
			cout<<"Sorry,but there is no room for this comsumable card\n";
		}
			
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
			cout<<"("<<i<<")    ",co[i].show();
	}
	
}p1;


map<consumables,int> PlanettoInt;
void planetInit(){
	planets[1]=(consumables){"planet","Eris","Level up \"Flush Five\" (3 coins)",3};
	planets[2]=(consumables){"planet","Ceres","Level up \"Flush House\" (3 coins)",3};
	planets[3]=(consumables){"planet","Planet X","Level up \"Five of a Kind\" (3 coins)",3};
	planets[4]=(consumables){"planet","Neptune","Level up \"Straight Flush\" (3 coins)",3};
	planets[5]=(consumables){"planet","Mars","Level up \"Four of a King\" (3 coins)",3};
	planets[6]=(consumables){"planet","Earth","Level up \"Full House\" (3 coins)",3};
	planets[7]=(consumables){"planet","Jupiter","Level up \"Flush\" (3 coins)",3};
	planets[8]=(consumables){"planet","Saturn","Level up \"Straight\" (3 coins)",3};
	planets[9]=(consumables){"planet","Venus","Level up \"Three of a King\" (3 coins)",3};
	planets[10]=(consumables){"planet","Uranus","Level up \"Two Pair\" (3 coins)",3};
	planets[11]=(consumables){"planet","Mercury","Level up \"Pair\" (3 coins)",3};
	planets[12]=(consumables){"planet","Pluto","Level up \"High Card\" (3 coins)",3};
	for(int i=1;i<=12;i++) PlanettoInt[planets[i]]=i;
}

void tarotInit(){
	tarots[1]=(consumables){"tarot","The Magician[I]","Enhances 2 selected cards to Lucky Cards (3 coins)",3};

	tarots[2]=(consumables){"tarot","The Empress[III]","Enhances 2 selected cards to Mult Cards (3 coins)",3};

	tarots[3]=(consumables){"tarot","The Hierophant[V]","Enhances 2 selected cards to Bonus Cards (3 coins)",3};

	tarots[4]=(consumables){"tarot","The Lovers[VI]","Enhances 1 selected card into a Wild Card (3 coins)",3};

	tarots[5]=(consumables){"tarot","The Chariot[VII]","Enhances 1 selected card into a Steel Card (3 coins)",3};

	tarots[6]=(consumables){"tarot","Justice[VIII]","Enhances 1 selected card into a Glass Card (3 coins)",3};

	tarots[7]=(consumables){"tarot","The Hermit[IX]","Doubles money(Max of $20) (3 coins)",3};

	tarots[8]=(consumables){"tarot","The Wheel of Fortune[X]","1 in 4 chance to add Foil, Holographic, or Polychrome edition to a random Joker (3 coins)",3};

	tarots[9]=(consumables){"tarot","The Devil[XV]","Enhances 1 selected card into a Gold Card (3 coins)",3};

	tarots[10]=(consumables){"tarot","The Tower[XVI]","Enhances 1 selected card into a Stone Card (3 coins)",3};

	tarots[11]=(consumables){"tarot","The Star[XVII]","Converts up to 3 selected cards to Diamonds (3 coins)",3};

	tarots[12]=(consumables){"tarot","The Moon[XVIII]","Converts up to 3 selected cards to Clubs (3 coins)",3};

	tarots[13]=(consumables){"tarot","The Sun[XIX]","Converts up to 3 selected cards to Hearts (3 coins)",3};

	tarots[14]=(consumables){"tarot","The World[XXI]","Converts up to 3 selected cards to Spades (3 coins)",3};
}

void spectralInit(){
	spectrals[1]=(consumables){"spectral","Incantation","Destroy 1 random card in your hand, but add 4 random Enhanced numbered cards instead. (4 coins)",4};
	
	spectrals[2]=(consumables){"spectral","Wraith","Creates a random Rare Joker (must have room), but sets money to $0. (4 coins)",4};
	
	spectrals[3]=(consumables){"spectral","Sigil","Converts every card in your hand to a single, random Suit. (4 coins)",4};
	
	spectrals[4]=(consumables){"spectral","Talisman","Adds a Gold Seal to 1 selected card. (4 coins)",4};
	
	spectrals[5]=(consumables){"spectral","Deja Vu","Adds a Red Seal to 1 selected card. (4 coins)",4}; 
	
	spectrals[6]=(consumables){"spectral","Trance","Adds a Blue Seal to 1 selected card. (4 coins)",4};
	
	spectrals[7]=(consumables){"spectral","Medium","Adds a Purple Seal to 1 selected card. (4 coins)",4};
	
	spectrals[8]=(consumables){"spectral","Black Hole","Upgrades every poker hand (including secret hands not yet discovered) by one level. (4 coins)",4};//0.3% 出现
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

string PHname[13]={"","Flush Five","Flush House","Five of a Kind","Straight Flush","Four of a King","Full House","Flush","Straight","Three of a King","Two Pair","Pair","High Card"};
int PHchip[13]={0,160,140,120,100,60,40,35,30,30,20,10,5};
int PHmult[13]={0,16,14,12,8,7,4,4,4,3,2,2,1};
int PHchipAdd[13]={0,50,40,35,40,30,25,15,30,20,20,15,10};
int PHmultAdd[13]={0,3,4,3,4,3,2,2,3,2,1,1,1};
int PHlevel[13]={0,1,1,1,1,1,1,1,1,1,1,1,1};
void PHupgrade(int tmp){
	PHlevel[tmp]++;
	PHchip[tmp]+=PHchipAdd[tmp];
	PHmult[tmp]+=PHmultAdd[tmp];
}
void usePlanet(const consumables &tmp){	
	PHupgrade(PlanettoInt[tmp]);
	cout<<"Planet Card Successfully used!\n";
}
void consumablesReplenish(){
	deck.cnt=p1.ccnt;
	for(int i=1;i<=deck.cnt;i++)
		deck.c[i]=p1.c[i];
	deck.shufle();
	hand.cnt=0;
	while(hand.cnt<8&&!deck.empty()){
		hand.insert(deck.GetHead());
	}
	cout<<"now you have in hand\n";
	hand.sort();
	hand.show();
}
void SelecttoEnhance(int num,string type){
	consumablesReplenish();
	cout<<"now INPUT the rank of "<<num<<" cards to be enhanced\n";
	for(int i=1;i<=num;i++){
		int x; cin>>x;
		p1.enhance(hand.c[x],type);
		hand.c[x].enhance=type;
	}
}
void SelecttoSuit(int num,int suit){
	consumablesReplenish();
	cout<<"now INPUT the rank of "<<num<<" cards to be converted\n";
	for(int i=1;i<=num;i++){
		int x; cin>>x;
		p1.resetSuit(hand.c[x],suit);
		hand.c[x].suit=suit;
	}
}
void useTarot(const consumables &tmp){
	
	if(tmp.name=="The Magician[I]") SelecttoEnhance(2,"Lucky");
	if(tmp.name=="The Empress[III]") SelecttoEnhance(2,"Mult");
	if(tmp.name=="The Hierophant[V]") SelecttoEnhance(2,"Bonus");
	if(tmp.name=="The Lovers[VI]") SelecttoEnhance(1,"Wild");
	if(tmp.name=="The Chariot[VII]") SelecttoEnhance(1,"Steel");
	if(tmp.name=="Justice[VIII]") SelecttoEnhance(1,"Glass");
	if(tmp.name=="The Devil[XV]") SelecttoEnhance(1,"Gold");
	if(tmp.name=="The Tower[XVI]") SelecttoEnhance(1,"Stone");
	
	if(tmp.name=="The Hermit[IX]") p1.money+=min(p1.money,20);
	if(tmp.name=="The Wheel of Fortune[X]"){
		if(rand()%4==0&&p1.jcnt){
			int t=rand()%3;
			p1.j[rand()%p1.jcnt+1].edition=(t==0?"Polychrome":t==1?"Holographic":"Foil");
		}else{
			cout<<"Sorry,Tarot Card Failed used :(\n";
			return ; 
		}	
	}

	
	if(tmp.name=="The Star[XVII]") SelecttoSuit(3,1);
	if(tmp.name=="The Moon[XVIII]") SelecttoSuit(3,2);
	if(tmp.name=="The Sun[XIX]") SelecttoSuit(3,3);
	if(tmp.name=="The World[XXI]") SelecttoSuit(3,4);
	
	cout<<"Tarot Card Successfully used!\n";

}
void SelecttoSeal(int num,string type){
	consumablesReplenish();
	cout<<"now INPUT the rank of "<<num<<" cards to be sealed\n";
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
	
	cout<<"Spectral Card Successfully used!\n";
}

void useConsumables(const consumables &tmp){
	//在 hand 中选取，在 p1 中加减，不对 deck 修改 
	if(tmp.type=="planet") usePlanet(tmp);
	else if(tmp.type=="tarot") useTarot(tmp);
	else if(tmp.type=="spectral") useSpectral(tmp);
	p1.remConsumable(tmp);	
}
struct SHOP{
	
	struct pack{
		string name,type;
		int price,total,result;
		string description;
		
		void show(){
			cout<<name<<"("<<type<<")   :"<<description<<'\n';
		}
	}packs[16];
	
	void packInit(){
		packs[1]=(pack){"Standard Pack","NORMAL",4,3,1,"Choose 1 of up to 3 Playing cards to add to your deck (4 coins)"};
		packs[2]=(pack){"Standard Pack","JUMBO",6,5,1,"Choose 1 of up to 5 Playing cards to add to your deck (6 coins)"};
		packs[3]=(pack){"Standard Pack","MEGA",8,5,2,"Choose 2 of up to 5 Playing cards to add to your deck (8 coins)"};//Poker 
		
		packs[4]=(pack){"Arcana Pack","NORMAL",4,3,1,"Choose 1 of up to 3 Tarot cards to be used immediately (4 coins)"};
		packs[5]=(pack){"Arcana Pack","JUMBO",6,5,1,"Choose 1 of up to 5 Tarot cards to be used immediately (6 coins)"};
		packs[6]=(pack){"Arcana Pack","MEGA",8,5,2,"Choose 2 of up to 5 Tarot cards to be used immediately (8 coins)"};//Tarot

		packs[7]=(pack){"Celestial Pack","NORMAL",4,3,1,"Choose 1 of up to 3 Planet cards to be used immediately (4 coins)"};
		packs[8]=(pack){"Celestial Pack","JUMBO",6,5,1,"Choose 1 of up to 5 Planet cards to be used immediately (6 coins)"};
		packs[9]=(pack){"Celestial Pack","MEGA",8,5,2,"Choose 2 of up to 5 Planet cards to be used immediately (8 coins)"};//Planet
		
		packs[10]=(pack){"Buffoon Pack","NORMAL",4,2,1,"Choose 1 of up to 2 Joker cards (4 coins)"};
		packs[11]=(pack){"Buffoon Pack","JUMBO",6,4,1,"Choose 1 of up to 4 Joker cards (6 coins)"};
		packs[12]=(pack){"Buffoon Pack","MEGA",8,4,2,"Choose 2 of up to 4 Joker cards (8 coins)"};//Joker

		packs[13]=(pack){"Spectral Pack","NORMAL",4,2,1,"Choose 1 of up to 2 Spectral cards to be used immediately (4 coins)"};
		packs[14]=(pack){"Spectral Pack","JUMBO",6,4,1,"Choose 1 of up to 4 Spectral cards to be used immediately (6 coins)"};
		packs[15]=(pack){"Spectral Pack","MEGA",8,4,2,"Choose 2 of up to 4 Spectral cards to be used immediately (8 coins)"};//Spectral
	}
	
	int randomPack(){
		int t=rand()%942+1;
		if(t<=400){
			t=rand()%3;
			if(t==0) return 1;
			else if(t==1) return 4;
			else if(t==2) return 7;
		}else if(t<=600){
			t=rand()%3;
			if(t==0) return 2;
			else if(t==1) return 5;
			else if(t==2) return 8;
		}else if(t<=650){
			t=rand()%3;
			if(t==0) return 3;
			else if(t==1) return 6;
			else if(t==2) return 9;
		}else if(t<=770){
			return 10;
		}else if(t<=830){
			return 11;
		}else if(t<=845){
			return 12;
		}else if(t<=905){
			return 13;
		}else if(t<=935){
			return 14;
		}else if(t<=942){
			return 15;
		}
		return 0;
	}
	
	struct CardtobeSold{
		int type;
		joker j;
		consumables co;
	};
	
	CardtobeSold randomCardToBeSold(){
		CardtobeSold tmp;
		int t=rand()%28+1;
		if(t<=20){
			tmp.type=1;
			t=rand()%10+1;
			tmp.j=jokers[t];
			tmp.j.resetEdition();
		}else if(t<=24){
			tmp.type=2;
			tmp.co=tarots[rand()%14+1];
		}else if(t<=28){
			tmp.type=3;
			tmp.co=planets[rand()%12+1];
		}
		return tmp;
	}
	
	bool c1buy,c2buy,p1buy,p2buy;
	CardtobeSold c1,c2;
	pack pack1,pack2;
	void Show(){
		cout<<"(1) ";
		if(c1buy) cout<<"Sold\n";
		else if(c1.type==1) c1.j.show();
		else c1.co.show();
		cout<<"(2) ";
		if(c2buy) cout<<"Sold\n";
		else if(c2.type==1) c2.j.show();
		else c2.co.show();
		cout<<"(3) ";
		if(p1buy) cout<<"Sold\n";
		else pack1.show();
		cout<<"(4) ";
		if(p2buy) cout<<"Sold\n";
		pack2.show();
	}
	void rerollC(){
		
		c1buy=c2buy=0;
		bool tmp=0;
		while(!tmp){
			tmp=1;
			c1=randomCardToBeSold();
			for(int i=1;i<=p1.jcnt;i++)
				if(c1.type==1&&c1.j==p1.j[i]) tmp=0;			
		}
		tmp=0;
		while(!tmp){
			tmp=1;
			c2=randomCardToBeSold();
			for(int i=1;i<=p1.jcnt;i++)
				if(c2.type==1&&c2.j==p1.j[i]) tmp=0;
			if(c2.type==1&&c1.type==1&&c2.j==c1.j) tmp=0;
		}
			
	}
	
	int opt;
	void WaitForOperation(){
		
		cout<<"You have "<<p1.money<<" coins now.\n";
		cout<<"INPUT 1 for Buy, 2 for Reroll the Cards(5 coins), 3 for Spectral/Planet/Tarot,\n4 for Check Jokers/Consumable Cards, 5 for Check Poker Hands Levels, 6 for help, 7 for next Round\n";
		
		cin>>opt;
	}
	
	void buyCard(const CardtobeSold &tmp,int num){
		if(tmp.type==1){
			if(p1.money<tmp.j.purchasePrice){
				cout<<"your coins are not enough\n";
				WaitForOperation();	
			}else{
				cout<<"Congratulation!\nYou just bought "<<tmp.j.type<<'\n';
				p1.money-=tmp.j.purchasePrice;
				p1.addJoker(tmp.j);
				if(num==1) c1buy=1;
				if(num==2) c2buy=1;
				Show();
				WaitForOperation();
			}
		}else{
			if(p1.money<tmp.co.price){
				cout<<"your coins are not enough\n";
				WaitForOperation();	
			}else{
				cout<<"Congratulation!\nYou just bought "<<tmp.co.name<<'\n';
				p1.money-=tmp.co.price;
				p1.addConsumable(tmp.co);
				if(num==1) c1buy=1;
				if(num==2) c2buy=1;
				Show();
				WaitForOperation();
			}
		}	
	}
	
	void openStandardPack(pack tmp){
		card tmpcard;
		hand.cnt=0;
		for(int i=1;i<=tmp.total;i++){
			tmpcard=(card){rand()%13+1,rand()%4+1,"",""};
			tmpcard.resetEnhance();
			tmpcard.resetSeal();
			hand.insert(tmpcard);
		}
		hand.sort();
		hand.show();
		cout<<"INPUT "<<tmp.result<<" ranks of the cards you want\n";
		for(int i=1;i<=tmp.result;i++){
			int x; cin>>x;
			p1.addCard(hand.c[x]);
		}
	}
	
	void openBuffoonPack(pack tmp){
		joker tmpjokers[5];
		for(int i=1;i<=10-p1.JcntMax;i++){
			bool ttmp=0;
			while(!ttmp){
				ttmp=1;
				tmpjokers[i]=jokers[rand()%10+1];
				for(int l=1;l<=p1.jcnt;l++)
					if(tmpjokers[i]==p1.j[l]) ttmp=0;
			}		
			tmpjokers[i].resetEdition();
			cout<<"("<<i<<")  ";
			tmpjokers[i].show();
		}
		if(p1.JcntMax+tmp.total>10) cout<<"Sorry there are no more Jokers\n";
		
		cout<<"INPUT "<<tmp.result<<" ranks of the jokers you want\n";
		for(int i=1;i<=tmp.result;i++){
			int x; cin>>x;
			p1.addJoker(tmpjokers[x]);
		}
	}
	
	void openCelestialPack(pack tmp){
		consumables tmpco[5];
		for(int i=1;i<=tmp.total;i++){
			tmpco[i]=planets[rand()%12+1];
			cout<<"("<<i<<")  ";
			tmpco[i].show();
		}
		cout<<"INPUT "<<tmp.result<<" ranks of the planet cards you want to use\n";
		for(int i=1;i<=tmp.result;i++){
			int x; cin>>x;
			usePlanet(tmpco[x]);
		}
	}
	
	void openArcanaPack(pack tmp){
		consumables tmpco[5];
		for(int i=1;i<=tmp.total;i++){
			tmpco[i]=tarots[rand()%14+1];
			cout<<"("<<i<<")  ";
			tmpco[i].show();
		}
		cout<<"INPUT "<<tmp.result<<" ranks of the tarot cards you want to use\n";
		for(int i=1;i<=tmp.result;i++){
			int x; cin>>x;
			useTarot(tmpco[x]);
		}
	}
	
	void openSpectralPack(pack tmp){
		consumables tmpco[5];
		for(int i=1;i<=tmp.total;i++){
			if(rand()%1000<3)
				tmpco[i]=spectrals[8];
			else tmpco[i]=spectrals[rand()%7+1];
			cout<<"("<<i<<")  ";
			tmpco[i].show();
		}
		cout<<"INPUT "<<tmp.result<<" ranks of the spectral cards you want to use\n";
		for(int i=1;i<=tmp.result;i++){
			int x; cin>>x;
			useSpectral(tmpco[x]);
		}
	}
	
	void buyPack(pack tmp,int num){
		if(p1.money<tmp.price){
			cout<<"your coins are not enough\n";
			WaitForOperation();
		}else{
			cout<<"Congratulation!\nYou just bought "<<tmp.name<<"("<<tmp.type<<")"<<'\n';
			p1.money-=tmp.price;
			
			
			if(tmp.name=="Standard Pack"){openStandardPack(tmp);}
			else if(tmp.name=="Buffoon Pack"){openBuffoonPack(tmp);}
			else if(tmp.name=="Celestial Pack"){openCelestialPack(tmp);}
			else if(tmp.name=="Arcana Pack"){openArcanaPack(tmp);}
			else if(tmp.name=="Spectral Pack"){openSpectralPack(tmp);}
			
			if(num==1) p1buy=1;
			if(num==2) p2buy=1;
			Show();
			WaitForOperation();
		}
	}
	
	void Start(){
		p1buy=p2buy=0;
		cout<<"                   THE SHOP\n";
		rerollC();
		pack1=packs[randomPack()],pack2=packs[randomPack()];
		
		cout<<"You have "<<p1.money<<" coins now.\n";
		cout<<"Improve your run!\n";
		
		Show();
		
		WaitForOperation();
		
		while(opt!=7){

			if(opt==1){
				cout<<"INPUT only ONE rank of which you want to buy\n";
				int x; cin>>x;
				if((x==1&&c1buy)||(x==2&&c2buy)||(x==3&&p1buy)||(x==4&&p2buy)){
					cout<<"it had been sold out\n";
					WaitForOperation();
				}
				else if(x==1){buyCard(c1,1);}
				else if(x==2){buyCard(c2,2);}
				else if(x==3){buyPack(pack1,1);}
				else if(x==4){buyPack(pack2,2);}
				else{
					cout<<"?\nINPUT again\n";
					WaitForOperation();
				}
			}else if(opt==2){
				if(p1.money<5){
					cout<<"your coins are not enough\n";
					WaitForOperation();
				}else{
					p1.money-=5;
					rerollC();
					cout<<"now we have\n";
					Show();
					WaitForOperation();	
				}
			}else if(opt==3){
				if(p1.cocnt){
					p1.showConsumable();		
					cout<<"INPUT the rank of the consumable card you want to use or 0 to go back\n";				
					int x; cin>>x;
					if(x==0) WaitForOperation();
					else{
						useConsumables(p1.co[x]);
						WaitForOperation();	
					}
				}else{
					cout<<"You have no consumable card\n";
					WaitForOperation();	
				}				
			}else if(opt==4){
				cout<<"your Jokers and Consumable Cards are as follow\n";
				for(int i=1;i<=p1.jcnt;i++)
					p1.j[i].show();
				for(int i=1;i<=p1.cocnt;i++)
					p1.co[i].show();
				WaitForOperation();
			}else if(opt==5){
				cout<<"your Poker Hands Levels are as follow\n";
				for(int i=4;i<=12;i++)
					cout<<PHname[i]<<"          (level="<<PHlevel[i]<<") chip="<<PHchip[i]<<" mult="<<PHmult[i]<<'\n';
				WaitForOperation();	
			}else if(opt==6){
				help();
				WaitForOperation();	
			}else if(opt==7){
				
			}else{
				cout<<"?\nINPUT again\n";
				WaitForOperation();
			}
		}
	}
	
}shop;




struct challenge{
	int T=0;
	int targets[16]={0,300,450,600,450,675,900,600,900,1200,1200,1800,2400,1800,2700,5000};
	int target,sum,BasicMoney,hands,discards,opt;
	
	void reset(){
		T++;
		
		target=targets[T],sum=0,BasicMoney=4,hands=4,discards=4;
		deck.cnt=p1.ccnt;
		for(int i=1;i<=deck.cnt;i++)
			deck.c[i]=p1.c[i];
		deck.shufle();
		deck.rewind();
		hand.cnt=0;			
		cout<<"This round target is "<<target<<'\n';
	}

	int PokerHands,numcnt[15];
	
	double chips,mults;
	
	void showChipandMult(){
		cout<<"Chip = "<<chips<<" *  Mult = "<<mults<<'\n';
	}
	void showMoney(){
		cout<<"You have "<<p1.money<<" coins now\n";
	}
	void reTrigger(card tmp){
		
		tmp.show();
		chips+=tmp.getNumber()==1?11:tmp.getNumber()>10?10:tmp.getNumber();
		cout<<"+"<<(tmp.getNumber()==1?11:tmp.getNumber()>10?10:tmp.getNumber())<<" Chip\n";
		showChipandMult();
		
		if(tmp.seal=="Gold"){
			p1.money+=3;
			cout<<"Gold Seal! +3 coins\n";
			showMoney();
		}
		if(tmp.enhance=="Bonus"){
			chips+=30;
			cout<<"Bonus Card! +30 Chip\n";
			showChipandMult();
		}
		if(tmp.enhance=="Mult"){
			mults+=4;
			cout<<"Mult Card! +4 Mult\n";
			showChipandMult();
		}
		if(tmp.enhance=="Glass"){
			mults*=2;
			cout<<"Glass Card! *2 Mult\n";
			showChipandMult();
			if(rand()%4==0){
				p1.remCard(tmp);
				cout<<"Glass Card:( this card has been destroyed\n";
			}
		}
		if(tmp.enhance=="Lucky"){
			if(rand()%5==0){
				mults+=20;
				cout<<"Lucky Card! +20 Mult\n";
				showChipandMult(); 
			}
			if(rand()%15==0){
				p1.money+=20;
				cout<<"Lucky Card! +20 coins\n";
				showMoney();
			}
		}
		
		for(int i=1;i<=p1.jcnt;i++){
			if(p1.j[i].type=="8 Ball"&&tmp.getNumber()==8&&rand()%4==0){
				cout<<"8 Ball! get random tarot\n";
				getRandomTarot();
			}
				
			if(p1.j[i].type=="Fibonacci"&&(tmp.getNumber()==1||tmp.getNumber()==2||tmp.getNumber()==3||tmp.getNumber()==5||tmp.getNumber()==8)){
				mults+=8;
				cout<<"Fibonacci! +8 Mult\n";
				showChipandMult();
			}
				
		}
	}
	void trigger(card tmp){
		reTrigger(tmp);
		if(tmp.seal=="Red"){
			cout<<"Red Seal! Retrigger this card\n";
			reTrigger(tmp);
		}
		for(int i=1;i<=p1.jcnt;i++)
			if(p1.j[i].type=="Hack"&&(tmp.getNumber()==2||tmp.getNumber()==3||tmp.getNumber()==4||tmp.getNumber()==5)){
				cout<<"Hack! Retrigger this card\n";
				reTrigger(tmp);
				break;
			}		
	}
	
	int calculate(){
		
		PokerHands=calc.GetType();
		cout<<"It`s "<<PHname[PokerHands]<<"!\n";
		
		chips=PHchip[PokerHands],mults=PHmult[PokerHands];
		showChipandMult();
		
		for(int i=1;i<=calc.cnt;i++)
			numcnt[calc.c[i].getNumber()]++;
		
		card tmp;
		
		if(PokerHands==5||PokerHands==9||PokerHands==10||PokerHands==11){
			for(int i=1;i<=calc.cnt;i++){
				if(numcnt[calc.c[i].getNumber()]>1){
					trigger(calc.c[i]);
				}else if(calc.c[i].enhance=="Stone"){
					calc.c[i].show();
					chips+=50;	
					cout<<"Stone Card! +50 Chip\n";
					showChipandMult();
				}
			}
		}else if(PokerHands==12){
			trigger(calc.c[calc.cnt]);
			for(int i=1;i<calc.cnt;i++)
				if(calc.c[i].enhance=="Stone"){
					calc.c[i].show();
					chips+=50;
					cout<<"Stone Card! +50 Chip\n";
					showChipandMult();
				} 
		}else{
			for(int i=1;i<=calc.cnt;i++)
				trigger(calc.c[i]);
		}
		
		for(int i=1;i<=calc.cnt;i++)
			numcnt[calc.c[i].getNumber()]--;
			
			
		for(int i=1;i<=hand.cnt;i++){
			if(hand.c[i].enhance=="Steel"){
				hand.c[i].show();
				mults*=1.5;
				cout<<"Steel Card! *1.5 Mult\n";
				showChipandMult();
			}
		}
		
		for(int i=1;i<=p1.jcnt;i++){
			if(p1.j[i].type=="Joker"){
				mults+=4;
				cout<<"Joker! +4 Mult\n";
				showChipandMult();
			}
			if(p1.j[i].type=="Half Joker"&&calc.cnt<=3){
				mults+=20;
				cout<<"Half Joker! +20 Mult\n";
				showChipandMult();
			} 
			if(p1.j[i].type=="Mime"){
				cout<<"Mime! retrigger cards in hand\n";
				for(int l=1;l<=hand.cnt;l++){
					if(hand.c[l].enhance=="Steel"){
						hand.c[l].show();
						mults*=1.5;
						cout<<"Steel Card! *1.5 Mult\n";
						showChipandMult();
					}
				}
			}
			if(p1.j[i].type=="Banner"){
				chips+=30*discards;
				cout<<"Banner! +30*discard="<<30*discards<<" Chip\n";
				showChipandMult();
			}
			if(p1.j[i].type=="Bull"){
				chips+=p1.money*2;
				cout<<"Bull! +2*coins="<<p1.money*2<<" Chip\n";
				showChipandMult();
			}
			
			if(p1.j[i].edition=="Foil"){
				chips+=50;
				cout<<"Foil Edition! +50 Chip\n";
				showChipandMult();
			}
			if(p1.j[i].edition=="Holographic"){
				mults+=10;
				cout<<"Holographic Edition! +10 Mult\n";
				showChipandMult();
			}
			if(p1.j[i].edition=="Polychrome"){
				mults*=1.5;
				cout<<"Polychrome Edition! *1.5 Mult\n";
				showChipandMult();
			}
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
		
		
		int q[15],qn=0;	
		cout<<"INPUT the amount of the cards you need to Discard\n";
		
		cin>>qn;
		
		cout<<"INPUT the rank of the cards\n";

		for(int i=1;i<=qn;i++)
			cin>>q[i]; 
		
		sort(q+1,q+1+qn);
		
		for(int i=2;i<=qn;i++){
			if(q[i]==q[i-1]){
				cout<<"Invalid INPUT!\n";
				return ;
			}
		}
		for(int i=1;i<=qn;i++){
			if(q[i]<1||q[i]>hand.cnt){
				cout<<"Invalid INPUT!\n";
				return ;
			}
		}
		
		
		
		for(int i=qn;i>=1;i--){
			if(hand.c[q[i]].seal=="Purple"){
				hand.c[q[i]].show();
				cout<<"Purple Seal! get random tarot\n";
				getRandomTarot();	
			}
			
			for(int j=q[i]+1;j<=hand.cnt;j++)
				hand.c[j-1]=hand.c[j];
			hand.cnt--;
		}
		discards--;		
	}
	void waitForOperation(){
		Replenish();
		cout<<"you have "<<discards<<" times Discards\n";
		cout<<"INPUT 1 for Play Hand, 2 for Discard, 3 for Spectral/Planet/Tarot,\n4 for Check Jokers/Consumable Cards, 5 for Check Poker Hands Levels, 6 for help\n";
		
		cin>>opt;
	}
	bool playCard(){
		int q[15],qn=0;	
		cout<<"INPUT the amount of the cards you need to Play Hand\n";
		
		cin>>qn;
		
		if(qn>5){
			cout<<"Invalid INPUT!\n";
			return false;
		}
		
		cout<<"INPUT the rank of the cards\n";

		for(int i=1;i<=qn;i++)
			cin>>q[i]; 
		
		sort(q+1,q+1+qn);
		
		for(int i=2;i<=qn;i++){
			if(q[i]==q[i-1]){
				cout<<"Invalid INPUT!\n";
				return false;
			}
		}
		for(int i=1;i<=qn;i++){
			if(q[i]<1||q[i]>hand.cnt){
				cout<<"Invalid INPUT!\n";
				return false;
			}
		}
		
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
		return true;	
	}
	bool settle(){
		if(sum>=target){
			
			for(int i=1;i<=hand.cnt;i++){
				if(hand.c[i].seal=="Blue"){
					hand.c[i].show();
					cout<<"Blue Seal! get planet\n";
					getPlanet(PokerHands);
				}
				if(hand.c[i].enhance=="Gold"){
					p1.money+=3;
					hand.c[i].show();
					cout<<"Gold Card! +3 coins\n";
					showMoney();
				}				
			}
						
			cout<<"YOU WIN！\n";
			
			int GetMoney=BasicMoney+hands+min(5,p1.money/5);
			cout<<"You get BasicMoney+hands+interest="<<GetMoney<<" coins\n";
			p1.money+=GetMoney;
		
			shop.Start();
						
			return true;
			
		}else{
			cout<<"YOU LOSE!\n";
			cout<<"Let's see who's the real joker lol (";
			return false;
		}	
	}
	
	void Start(){
		bool Continue=1;
		while(Continue){
			reset();
			
			for(hands=4;hands;hands--){
				cout<<"now you have "<<hands<<" times Play Hands\n";
				waitForOperation();
				
				
				while(opt!=1){
					if(opt==2){
						if(discards){
							playDiscard();	
							waitForOperation();	
						}else{
							cout<<"You can't discard\n";
							waitForOperation();	
						}
					}else if(opt==3){
						if(p1.cocnt){
							p1.showConsumable();
									
							cout<<"INPUT the rank of the consumable card you want to use or 0 to go back\n";				
							int x; cin>>x;
							if(x==0) waitForOperation();
							else{
								useConsumables(p1.co[x]);
								waitForOperation();	
							}
							
						}else{
							cout<<"You have no consumable card\n";
							waitForOperation();	
						}
					}else if(opt==4){
						cout<<"your Jokers and Consumable Cards are as follow\n";
						for(int i=1;i<=p1.jcnt;i++)
							p1.j[i].show();
						for(int i=1;i<=p1.cocnt;i++)
							p1.co[i].show();
						waitForOperation();
					}else if(opt==5){
						cout<<"your Poker Hands Levels are as follow\n";
						for(int i=4;i<=12;i++)
							cout<<PHname[i]<<"          (level="<<PHlevel[i]<<") chip="<<PHchip[i]<<" mult="<<PHmult[i]<<'\n';
						waitForOperation();	
					}else if(opt==6){
						help();
						waitForOperation();	
					}else{
						cout<<"?\nINPUT again\n";
						waitForOperation();
					}	
				}
				
				bool ttmp=playCard();
				while(!ttmp) ttmp=playCard();
				
				if(sum>=target) break;
			}			
			Continue=settle();
			if(T==15) break;
		}		
		
		cout<<"Congratulation!\n\nI'm the real joker :(\nChange the data and try more :)";
		
	}
	
	
	
	void tutorial(){
		cout<<"This is tutorial and if you are experienced you can input 0 to skip.\n";
		cout<<"Otherwise input any number except 0 to continue\n";
		
		int ttmp; cin>>ttmp;
		
		if(ttmp==0){
			cout<<"Have a nice game!\n";
			return ;
		}
		
		cout<<"Welcome to Labatro.()\n";
		
		cout<<"So what you should do here is Discard,Discard,Discard,and then Play Hand.\n";
		
		cout<<"It's ok not knowing any Poker Hands,you can ask for help anytime.\n";
		
		cout<<"Let's take a look at a situation.\n";
		
		cout<<"Now you have\n";
		
		cout<<"(1) 2 Spade\n";
		cout<<"(2) 5 Diamond\n";
		cout<<"(3) 6 Spade\n";
		cout<<"(4) 7 Club\n";
		cout<<"(5) 9 Club\n";
		cout<<"(6) J Spade\n";
		cout<<"(7) Q Heart\n";
		cout<<"(8) Q Spade\n";
		
		cout<<"You can Play Hand with no more than 5 Playing Cards, like (7) Q Heart and (8) Q Spade for a \"Pair\".\n";
		cout<<"Or you can choose to discards any amount of cards you like, hoping for a better Poker Hand.\n";
		cout<<"And you Discards (2) 5 Diamond, (4) 7 Club and (5) 9 Club,now you have\n";
		
		cout<<"(1) 2 Club\n";
		cout<<"(2) 2 Spade\n";
		cout<<"(3) 5 Heart\n";
		cout<<"(4) 6 Spade\n";
		cout<<"(5) J Spade\n";
		cout<<"(6) Q Heart\n";
		cout<<"(7) Q Spade\n";
		cout<<"(8) A Spade\n";		
		
		cout<<"Now you can Play (2),(4),(5),(7),(8) cause these cards are from the same suit,so you played a \"Flush\".";
		cout<<"Then you get (Chip = 35 + 2 + 6 + 10 + 10 + 11 = 74) * (Mult = 4) = 296 Points\n";
		
		cout<<"The Poker Hands give the basis(35 and 4), and every card that make up this Poker Hands give additions, while Joker Cards and Consumable Cards give more.\n";
		cout<<"Initially, You have 4 chances for Playing Cards and 4 chances for Discards.\n";
		cout<<"Your goal is to maximize the Points and buy the Cards and Packs in the Shop to improve your run.\n";
		
		cout<<"That's almost the basic rule. Go and explore this game and find the pleasure.\n";
		cout<<"Have a nice game!\n";
		
		cout<<"Read them all and input any number to continue\n";
		cin>>ttmp;
	}
	
	
	
}playCard;

void init(){
	p1.money=0;
	p1.ccnt=52;
	for(int i=1;i<=4;i++) 
		for(int j=1;j<=13;j++)
			p1.c[(i-1)*13+j]=(card){j,i,"",""};
	p1.jcnt=0;
	jokerInit();
	planetInit();
	tarotInit();
	spectralInit();
	shop.packInit();
}

signed main(){
	srand(time(0)); 
	init();
	playCard.tutorial();
	playCard.Start();
	return 0;
}
