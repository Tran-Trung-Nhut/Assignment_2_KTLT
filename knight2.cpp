#include "knight2.h"
/* * * BEGIN implementation of class BaseBag * * */
BagofPaladin::BagofPaladin(){
    this->capaciy=100000;
    this->num_of_item=0;
}
BagofLancelot::BagofLancelot(){
    this->capaciy=16;
    this->num_of_item=0;
}
BagofDragon::BagofDragon(){
    this->capaciy=14;
    this->num_of_item=0;
}
BagofNormal::BagofNormal(){
    this->capaciy=19;
    this->num_of_item=0;
}   
bool BaseBag::insertFirst(BaseItem* item){
    if(num_of_item==capaciy) return false;
    else{
        node* tmp= new node();
        tmp->next=head;
        tmp->item=item;
        head=tmp;
        num_of_item++;
        return true;
    }
}
bool BaseBag:: useAntidote(){
    if(num_of_item==0) return false;
    node* tmp=head;
    while(tmp!=NULL){
        if(tmp->item->Type()!=Antidote){
            tmp=tmp->next;
        } else break;
    }
    if(tmp==NULL) return false;
    else if(tmp->item->Type()==Antidote){
        swap(head->item,tmp->item);
        tmp=head;
        head=head->next;
        num_of_item--;
        delete[] tmp->item;
        delete[] tmp;
    }
    return true;
}
void BaseBag::usePhoenixdown(BaseKnight * knight, Events* events,int i){
    if(num_of_item==0 || !events->isbattle(events->get(i))) return;
    node*tmp=head;
    while(tmp!=NULL){
        if(tmp->item->Type()!=Antidote){
            if(tmp->item->canUse(knight)){
                tmp->item->use(knight);
                swap(head->item,tmp->item);
                tmp=head;
                head=head->next;
                num_of_item--;
                delete[] tmp->item;
                delete[] tmp;
                break;
            }else{tmp=tmp->next;}
        }
        else tmp=tmp->next;
    }
}
string BaseBag::toString() const{
    if(num_of_item==0) return "Bag[count=0;]";
    string str="Bag[count="+to_string(num_of_item)+";";
    node* tmp=head;
    while(tmp!=NULL){
        if(tmp->item->Type()==Antidote){str+="Antidote,";}
        else if(tmp->item->Type()==PhoenixdownI){str+="PhoenixI,";}
        else if(tmp->item->Type()==PhoenixdownII){str+="PhoenixII,";}
        else if(tmp->item->Type()==PhoenixdownIII){str+="PhoenixIII,";}
        else {str+="PhoenixIV,";}
        tmp=tmp->next;
    }
    str[str.length()-1] = ']';
    return str;
}
void BaseBag::dropItem(){
    if(num_of_item==0) return;
    node* tmp=head;
    head=head->next;
    num_of_item--;
    delete[] tmp->item;
    delete[] tmp;
}

void BaseBag::delete_allItem(){
    if(num_of_item==0) return;
    node* tmp=head;
    while(tmp!=NULL){
        delete tmp->item;
        node* temp=tmp->next;
        delete tmp;
        tmp=temp;
    }
}
/* * * END implementation of class BaseBag * * */
//BaseOpponent Starts
MadBearOpponent::MadBearOpponent(BaseKnight* knight, int i){
    this->type=MadBear;
    int levelO=(i+this->type)%10+1;
    if(knight->getlevel()>=levelO || knight->gettype()==LANCELOT || knight->gettype()==PALADIN){
        knight->setgil(knight->getgil()+100);
    }else{
        knight->sethp(knight->gethp()-10*(levelO-knight->getlevel()));
    }
}
BanditOpponent::BanditOpponent(BaseKnight* knight,int i){
    this->type=Bandit;
    int levelO=(i+this->type)%10+1;
     if(knight->getlevel()>=levelO || knight->gettype()==LANCELOT || knight->gettype()==PALADIN){
        knight->setgil(knight->getgil()+150);
    }else{
        knight->sethp(knight->gethp()-15*(levelO-knight->getlevel()));
    }
}
LordLupinOpponent::LordLupinOpponent(BaseKnight* knight, int i){
    this->type=LordLupin;
    int levelO=(i+this->type)%10+1;
     if(knight->getlevel()>=levelO || knight->gettype()==LANCELOT || knight->gettype()==PALADIN){
        knight->setgil(knight->getgil()+450);
    }else{
        knight->sethp(knight->gethp()-45*(levelO-knight->getlevel()));
    }
}
ElfOpponent::ElfOpponent(BaseKnight* knight, int i){
    this->type=Elf;
    int levelO=(i+this->type)%10+1;
     if(knight->getlevel()>=levelO || knight->gettype()==LANCELOT || knight->gettype()==PALADIN){
        knight->setgil(knight->getgil()+750);
    }else{
        knight->sethp(knight->gethp()-75*(levelO-knight->getlevel()));
    }
}
TrollOpponent::TrollOpponent(BaseKnight* knight, int i){
    this->type=Troll;
    int levelO=(i+this->type)%10+1;
     if(knight->getlevel()>=levelO || knight->gettype()==LANCELOT || knight->gettype()==PALADIN){
        knight->setgil(knight->getgil()+800);
    }else{
        knight->sethp(knight->gethp()-95*(levelO-knight->getlevel()));
    }
}
TornberyOpponent::TornberyOpponent(BaseKnight* knight, int i){
    this->type=Tornbery;
    int levelO=(i+this->type)%10+1;
    if(knight->getlevel()<levelO){
        if(knight->gettype()!=DRAGON) knight->setpoison(true);
    }else{
        knight->setlevel(knight->getlevel()+1);
    }
}
QueenOfCardsOpponent::QueenOfCardsOpponent(BaseKnight* knight, int i){
    this->type=QueenOfCards;
    int levelO=(i+this->type)%10+1;
    if(knight->getlevel()<levelO){
        if(knight->gettype()!=PALADIN) knight->setgil(knight->getgil()/2);
    }else{
        knight->setgil(knight->getgil()*2);
    }
}
NinaDeRingsOpponent::NinaDeRingsOpponent(BaseKnight* knight){
    this->type=NinaDeRings;
    if(knight->gethp()<knight->getmaxhp()/3){
        if(knight->gettype()==PALADIN){
            knight->sethp(knight->gethp()+knight->getmaxhp()/5);
        }else if(knight->getgil()>=50){
            knight->sethp(knight->gethp()+knight->getmaxhp()/5);
            knight->setgil(knight->getgil()-50);
        }
    }
}
DurianGardenOpponent::DurianGardenOpponent(BaseKnight * knight){
    knight->sethp(knight->getmaxhp());
}
OmegaWeaponOpponent::OmegaWeaponOpponent(BaseKnight * knight){
    if(!knight->passOmega()){
        if((knight->getlevel()==10 && knight->gethp()==knight->getmaxhp()) || knight->gettype()==DRAGON){
            knight->setlevel(10);
            knight->setgil(999);
            knight->passedOmega();
        }else{
            knight->sethp(0);
        }
    }
}

//BaseOpponent Ends
/* * * BEGIN implementation of class BaseKnight * * */
bool BaseKnight::PassOmega=false;
bool BaseKnight::PassHades=false;
bool BaseKnight::lose_ultimate=false;
int BaseKnight::gethp(){
    return hp;
}
void BaseKnight::sethp(int hp){
    if(hp>maxhp) this->hp=maxhp;
    else this->hp=hp;
}
int BaseKnight::getmaxhp(){
    return maxhp;
}
int BaseKnight::getlevel(){
    return level;
}
void BaseKnight::setlevel(int level){
    if(level>10) this->level=10;
    else this->level=level;
}
int BaseKnight::getgil(){
    return gil;
}
void BaseKnight::setgil(int gil){
    if(gil>999){
        this->gil=999;
        ExtraGil=gil-999;
    }
    else this->gil=gil;
}
BaseBag* BaseKnight::this_bag(){
    return this->bag;
}
int BaseKnight::getantidote(){
    return antidote;
}
void BaseKnight:: setantidote(int antidote){
    this->antidote=antidote;
}
int BaseKnight::getExtraGil(){
    return ExtraGil;
}
void BaseKnight:: setExtraGil(int ExtraGil){
    this->ExtraGil=ExtraGil;
}
bool BaseKnight::isPoisoned(){
    return poisoned;
}
void BaseKnight::setpoison(bool poisoned){
    this->poisoned=poisoned;
}
KnightType BaseKnight:: gettype(){
    return knightType;
}
bool BaseKnight:: Lose_Ultimate(){
    return lose_ultimate;
}
void BaseKnight:: Lost_Ultimate(bool lose){
    this->lose_ultimate=lose;
}
bool BaseKnight::passOmega(){
    return PassOmega;
}
void BaseKnight::passedOmega(){
    PassOmega=true;
}
bool BaseKnight::passHades(){
    return PassHades;
}
void BaseKnight::passedHades(){
    PassHades=true;
}
void BaseKnight::resurrection(){
    hp=maxhp/2;
    gil-=100;
}
double BaseKnight::getBaseDamage(){
    return KnightBaseDamage;
}
BaseKnight* BaseKnight :: create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    bool isPaladin, isLancelot, isDragon;
    isLancelot=isDragon=false;
    isPaladin=true;
    if(maxhp==888) isLancelot=true;
    for(int i=2;i<sqrt(maxhp);i++){
        if(maxhp%i==0){
            isPaladin=false;
            break;
        }
    }
    if(maxhp==345 || maxhp==354 || maxhp==435 || maxhp==453 || maxhp==543 || maxhp==534) isDragon=true;
    
    if(isLancelot){return new LancelotKnight(id,maxhp,level,gil,antidote,phoenixdownI);}
    else if(isPaladin){return new PaladinKnight(id,maxhp,level,gil,antidote,phoenixdownI);}
    else if(isDragon){return new DragonKnight(id,maxhp,level,gil,antidote,phoenixdownI);}
    else{return new NormalKnight(id,maxhp,level,gil,antidote,phoenixdownI);}
}
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->knightType=PALADIN;
    this->KnightBaseDamage=0.06;
    this->bag = new BagofPaladin();
    while(phoenixdownI--){
        BaseItem* item = new PhoenixdownIItem();
        if(!this->bag->insertFirst(item)) delete[] item;
    }
    while(antidote--){
        BaseItem* item = new AntidoteItem();
        if(!this->bag->insertFirst(item)) delete[] item;
    }
}
LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->knightType=LANCELOT;
    this->KnightBaseDamage=0.05;
    this->bag = new BagofLancelot();
    while(phoenixdownI--){
        BaseItem* item = new PhoenixdownIItem();
        if(!this->bag->insertFirst(item)) delete[] item;
    }
    while(antidote--){
        BaseItem* item = new AntidoteItem();
        if(!this->bag->insertFirst(item)) delete[] item;
    }
}
DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->knightType=DRAGON;
    this->KnightBaseDamage=0.075;
    this->antidote=antidote;
    this->bag = new BagofDragon();
    while(phoenixdownI--){
        BaseItem* item = new PhoenixdownIItem();
        if(!this->bag->insertFirst(item)) delete[] item;
    }
}
NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->knightType=NORMAL;
    this->bag = new BagofNormal();
    while(phoenixdownI--){
        BaseItem* item = new PhoenixdownIItem();
        if(!this->bag->insertFirst(item)) delete[] item;
    }
    while(antidote--){
        BaseItem* item = new AntidoteItem();
        if(!this->bag->insertFirst(item)) delete[] item;
    }  
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_army){
    ifstream inp_knight(file_army);
    PaladinShield=LancelotSpear=GuinevereHair=ExcaliburSword=false;
    inp_knight>>number_of_knights;
    const_knights=number_of_knights;
    knights= new BaseKnight* [number_of_knights];
    for(int i=0;i<number_of_knights;i++){
        int ihp,ilevel,igil,iantidote,iphoenixdownI;
        inp_knight>>ihp;
        inp_knight>>ilevel;
        inp_knight>>iphoenixdownI;
        inp_knight>>igil;
        inp_knight>>iantidote;
        knights[i]=BaseKnight::create(i+1, ihp, ilevel,igil,iantidote,iphoenixdownI);
    }
}

void ArmyKnights::getPaladinShield(){
    PaladinShield=true;
}
bool ArmyKnights::adventure(Events * events){
    BaseOpponent *opponent;
    bool win=false;
    for(int i=0;i<events->count();i++){
        if(lastKnight()->gettype()==DRAGON){
            int z=number_of_knights-2;
            while(lastKnight()->getantidote()){
                BaseItem* item= new AntidoteItem();
                if(knights[z]->this_bag()->insertFirst(item)){
                    lastKnight()->setantidote(lastKnight()->getantidote()-1);
                } else{
                    delete item;
                    z++;
                }
            }
        }
        if(events->get(i)==1){opponent = new MadBearOpponent(lastKnight(),i);delete opponent;}
        else if(events->get(i)==2) {opponent = new BanditOpponent(lastKnight(),i);delete opponent;}
        else if(events->get(i)==3) {opponent = new LordLupinOpponent(lastKnight(),i);delete opponent;}
        else if(events->get(i)==4) {opponent = new ElfOpponent(lastKnight(),i);delete opponent;}
        else if(events->get(i)==5) {opponent = new TrollOpponent(lastKnight(),i);delete opponent;}
        else if(events->get(i)==6) {opponent = new TornberyOpponent(lastKnight(),i);delete opponent;}
        else if(events->get(i)==7) {opponent = new QueenOfCardsOpponent(lastKnight(),i);delete opponent;}
        else if(events->get(i)==8) {opponent = new NinaDeRingsOpponent(lastKnight());delete opponent;}
        else if(events->get(i)==9) {opponent = new DurianGardenOpponent(lastKnight());delete opponent;}
        else if(events->get(i)==10) {opponent = new OmegaWeaponOpponent(lastKnight());delete opponent;}
        else if(events->get(i)==11){
            if(!lastKnight()->passHades()){
                if(lastKnight()->getlevel()==10 || (lastKnight()->gettype()==PALADIN && lastKnight()->getlevel()>=8)){
                    if(!PaladinShield){
                        PaladinShield=true;
                        lastKnight()->passedHades();
                    }else{lastKnight()->passedHades();}
                }else{
                    lastKnight()->sethp(0);
                }
            }
        }
        else if(events->get(i)==112){
            BaseItem* item= new PhoenixdownIIItem();
            for(int j=number_of_knights-1;j>=0;j--){
                if(knights[j]->this_bag()->insertFirst(item)) break;
                if(j==0 && !knights[j]->this_bag()->insertFirst(item)) delete item;
            }
        }
        else if(events->get(i)==113){
            BaseItem* item = new PhoenixdownIIIItem();
            for(int j=number_of_knights-1;j>=0;j--){
                if(knights[j]->this_bag()->insertFirst(item)) break;
                if(j==0 && !knights[j]->this_bag()->insertFirst(item)) delete item;
            }
        }
        else if(events->get(i)==114){
            BaseItem* item = new PhoenixdownIVItem();
            for(int j=number_of_knights-1;j>=0;j--){
                if(knights[j]->this_bag()->insertFirst(item)) break;
                if(j==0 && !knights[j]->this_bag()->insertFirst(item)) delete item;
            }
        }
        else if(events->get(i)==95) PaladinShield=true;
        else if(events->get(i)==96) LancelotSpear=true;
        else if(events->get(i)==97) GuinevereHair=true;
        else if(events->get(i)==98){
            if(PaladinShield && LancelotSpear && GuinevereHair) ExcaliburSword=true;
        }
        else if(events->get(i)==99){
            if(!ExcaliburSword){
                int Ultiamte_hp=5000;
                if(PaladinShield && LancelotSpear && GuinevereHair){
                    for(int j=number_of_knights-1;j>=0;j--){
                        if(knights[j]->gettype()==PALADIN || knights[j]->gettype()==LANCELOT || knights[j]->gettype()==DRAGON){
                           int DamageofKnight=knights[j]->gethp()*knights[j]->getlevel()*knights[j]->getBaseDamage();
                           Ultiamte_hp-=DamageofKnight;
                           if(Ultiamte_hp<=0){
                                win=true;
                                break;
                           }else{
                                number_of_knights--;
                                knights[j]->this_bag()->delete_allItem();
                                delete[] knights[j];
                                knights[j]=NULL;
                           }
                        }
                    }
                    if(!win) number_of_knights=0;
                    else{
                        for(int i=const_knights-1;i>=0;i--){
                            if(knights[i]!=NULL && knights[i]!=knights[number_of_knights-1]){
                                delete knights[number_of_knights-1];
                                knights[number_of_knights-1]=knights[i];
                                knights[i]=NULL;
                                break;
                            }
                        }
                    }
                }else{
                    lastKnight()->Lost_Ultimate(true);
                }
            }else{win=true;}
        }
        while(!win && events->get(i)!=99 && lastKnight()->getExtraGil()>0){
            for(int j=number_of_knights-2;j>=0;j--){
                if(lastKnight()->getExtraGil()==0) break;
                if(knights[j]->getgil()<999){
                    if(999-knights[j]->getgil()>=lastKnight()->getExtraGil()){
                        knights[j]->setgil(knights[j]->getgil()+lastKnight()->getExtraGil());
                        lastKnight()->setExtraGil(0);
                    }
                    else{
                        lastKnight()->setExtraGil(lastKnight()->getExtraGil()-(999-knights[j]->getgil()));
                        knights[j]->setgil(999);
                    }
                }
                if(j==0) lastKnight()->setExtraGil(0);
            }
        }
        if(events->get(i)!=99)
            if(!this->fight(opponent,events,i)){
            for(int c=const_knights-1;c>=0;c--){
                if(lastKnight()==knights[c]){
                    knights[c]->this_bag()->delete_allItem();
                    delete knights[c];
                    knights[c]=NULL;
                    break;
                }
            }
            number_of_knights--;
        }
        if(number_of_knights!=0 && lastKnight()->Lose_Ultimate()) number_of_knights=0;
        this->printInfo();
    }
    for(int i=0;i<const_knights;i++){
        if(knights[i]!=NULL){
            knights[i]->this_bag()->delete_allItem();
            delete knights[i];
        }
    }
    delete knights;
    return win;
}
int ArmyKnights::count() const{
    return number_of_knights;
}

BaseKnight* ArmyKnights::lastKnight() const{
    return knights[number_of_knights-1];
}
bool ArmyKnights::fight(BaseOpponent* opponent,Events* events, int i){
    if(number_of_knights!=0 && lastKnight()->isPoisoned()){
        if(!lastKnight()->this_bag()->useAntidote()){
            lastKnight()->sethp(lastKnight()->gethp()-10);
            for(int j=1;j<=3;j++){lastKnight()->this_bag()->dropItem();}
            lastKnight()->setpoison(false);
        }else{
            BaseItem* item = new AntidoteItem();
            item->use(lastKnight());
            delete[] item;
        }
    }
    if(number_of_knights!=0 && lastKnight()->gethp()<lastKnight()->getmaxhp()) lastKnight()->this_bag()->usePhoenixdown(lastKnight(),events,i);
    if(number_of_knights!=0 && lastKnight()->gethp()<=0){
        if(lastKnight()->getgil()>=100){
            lastKnight()->resurrection();
            return true;
        } else return false;
    }else return true;
}
bool ArmyKnights::hasPaladinShield() const{
    return PaladinShield;
}
bool ArmyKnights::hasLancelotSpear() const{
    return LancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const{
    return GuinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const{
    return ExcaliburSword;
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight* lknight = lastKnight();
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */
//BaseItem Starts
AntidoteItem::AntidoteItem(){
    this->itemType=Antidote;
}
PhoenixdownIItem::PhoenixdownIItem(){
    this->itemType=PhoenixdownI;
}
PhoenixdownIIItem::PhoenixdownIIItem(){
    this->itemType=PhoenixdownII;
}
PhoenixdownIIIItem::PhoenixdownIIIItem(){
    this->itemType=PhoenixdownIII;
}
PhoenixdownIVItem::PhoenixdownIVItem(){
    this->itemType=PhoenixdownIV;
}
bool AntidoteItem:: canUse(BaseKnight * knight){
    return knight->isPoisoned();
}
void AntidoteItem::use(BaseKnight * knight){
    knight->setpoison(false);
}
bool PhoenixdownIItem:: canUse(BaseKnight * knight){
    if(knight->gethp()<=0) return true;
    else return false;
}
void PhoenixdownIItem :: use(BaseKnight * knight){
    knight->sethp(knight->getmaxhp());
}
bool PhoenixdownIIItem :: canUse(BaseKnight * knight){
    if(knight->gethp()<knight->getmaxhp()/4) return true;
    else return false;
}
void PhoenixdownIIItem :: use (BaseKnight * knight){
    knight->sethp(knight->getmaxhp());
}
bool PhoenixdownIIIItem :: canUse(BaseKnight * knight){
    if(knight->gethp()<knight->getmaxhp()/3) return true;
    else return false;
}
void PhoenixdownIIIItem :: use(BaseKnight * knight){
    if(knight->gethp()<=0){knight->sethp(knight->getmaxhp()/4);}
    else{knight->sethp(knight->gethp()+knight->getmaxhp()/4);}
}
bool PhoenixdownIVItem :: canUse(BaseKnight * knight){
    if(knight->gethp()<knight->getmaxhp()/2) return true;
    else return false;
}
void PhoenixdownIVItem :: use(BaseKnight * knight){
    if(knight->gethp()<=0){knight->sethp(knight->getmaxhp()/2);}
    else {knight->sethp(knight->gethp()+knight->getmaxhp()/5);}
}
ItemType AntidoteItem:: Type(){
    return itemType;
}
ItemType PhoenixdownIItem :: Type(){
    return itemType;
}
ItemType PhoenixdownIIItem :: Type(){
    return itemType;
}
ItemType PhoenixdownIIIItem :: Type(){
    return itemType;
}
ItemType PhoenixdownIVItem :: Type(){
    return itemType;
}
//BaseItem Ends
/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
void KnightAdventure::loadArmyKnights(const string & file_knight){
    armyKnights = new ArmyKnights(file_knight);
}
void KnightAdventure::loadEvents(const string & file_event){
    events = new Events(file_event);
}
KnightAdventure::~KnightAdventure(){
    delete[] armyKnights;
    delete[] events;
}
void KnightAdventure::run(){
    armyKnights->printResult(armyKnights->adventure(events));
}
/* * * END implementation of class KnightAdventure * * */
// Class Events Starts
    int Events::count() const{
        return number_of_events;
    }
    int Events::get(int i) const{
        return a_event[i];
    }
    Events::Events(const string & file_event){
        ifstream inp_event(file_event);
        inp_event>>number_of_events;
        a_event=new int[number_of_events];
        for(int i=0;i<number_of_events;i++){
            inp_event>>a_event[i];
        }
    }
    bool Events::isbattle(int num){
        return num == 1|| num==2||num==3||num==4||num==5||num==6||num==7||num==8||num==9||num==10||num==11;
    }
    void Events::delete_Events(){
        delete a_event;
    }
