#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__
#include "main.h"

// #define DEBUG
class BaseBag;
class BaseOpponent;
class BaseKnight;
class Events;
class BaseItem;
class ArmyKnights;
enum ItemType {Antidote,PhoenixdownI,PhoenixdownII,PhoenixdownIII,PhoenixdownIV};

class BaseBag {
public:
    class node{
    public:
        BaseItem* item=NULL;
        node* next=NULL;
    };
protected:
    node* head=NULL;
    int capaciy,num_of_item;
public:
    virtual bool insertFirst(BaseItem * item);
    virtual bool useAntidote();
    virtual void usePhoenixdown(BaseKnight * knight, Events* events,int i);
    virtual string toString() const;
    void dropItem();
    void delete_allItem();
};
class BagofPaladin : public BaseBag{
public:
    BagofPaladin();
};
class BagofLancelot : public BaseBag{
public:
    BagofLancelot();
};
class BagofDragon : public BaseBag{
public:
    BagofDragon();
};
class BagofNormal : public BaseBag{
public:
    BagofNormal();
};
enum OpponentType{MadBear=1,Bandit, LordLupin, Elf, Troll, Tornbery, QueenOfCards, NinaDeRings, DurianGarden, OmegaWeapon, Hades};
class BaseOpponent{
protected:
    OpponentType type;
};
class MadBearOpponent : public BaseOpponent{
public:
    MadBearOpponent(BaseKnight* knight, int i);
};
class BanditOpponent : public BaseOpponent{
public:
    BanditOpponent(BaseKnight* knight, int i);
};
class LordLupinOpponent : public BaseOpponent{
public:
    LordLupinOpponent(BaseKnight* knight, int i);
};
class ElfOpponent : public BaseOpponent{
public:
    ElfOpponent(BaseKnight * knight, int i);
};
class TrollOpponent : public BaseOpponent{
public:
    TrollOpponent(BaseKnight * knight, int i);
};
class TornberyOpponent : public BaseOpponent{
public:
    TornberyOpponent(BaseKnight * knight, int i);
};
class QueenOfCardsOpponent : public BaseOpponent{
public:
    QueenOfCardsOpponent(BaseKnight * knight, int i);
};
class NinaDeRingsOpponent : public BaseOpponent{
public:
    NinaDeRingsOpponent(BaseKnight * Knight);
};
class DurianGardenOpponent : public BaseOpponent{
public:
    DurianGardenOpponent(BaseKnight* knight);
};
class OmegaWeaponOpponent : public BaseOpponent{
public:
    OmegaWeaponOpponent(BaseKnight* knight);
};
class HadesOpponent : public BaseOpponent{
public:
    HadesOpponent(BaseKnight * Knight);
};
class UltimateOpponent : public BaseOpponent{
public:
    UltimateOpponent(BaseKnight* knight);
};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag* bag;
    KnightType knightType;
    bool Isdead=false;
    bool poisoned = false;
    int ExtraGil = 0;
    static bool lose_ultimate;
    static bool PassOmega;
    static bool PassHades;
    double KnightBaseDamage;
public:
    int gethp();
    void sethp(int hp);
    int getmaxhp();
    int getlevel();
    void setlevel(int level);
    int getgil();
    void setgil(int gil);
    int getantidote();
    void setantidote(int antidote);
    BaseBag* this_bag();
    int getExtraGil();
    void setExtraGil(int ExtraGil);
    bool isPoisoned();
    void setpoison(bool poisoned);
    bool Lose_Ultimate();
    void Lost_Ultimate(bool lose);
    bool isdead();
    void setisdead(bool dead);
    bool passOmega();
    void passedOmega();
    bool passHades();
    void passedHades();
    void resurrection();
    double getBaseDamage();
    KnightType gettype();
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};
class PaladinKnight : public BaseKnight{
public: 
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~PaladinKnight(){
        delete[] bag;
    }
};
class LancelotKnight : public BaseKnight{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~LancelotKnight(){
        delete[] bag;
    }
};
class DragonKnight : public BaseKnight{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~DragonKnight(){
        delete[] bag;
    }
};
class NormalKnight : public BaseKnight{
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~NormalKnight(){
        delete[] bag;
    }
};
class ArmyKnights {
protected:
    int number_of_knights;
    int const_knights;
    BaseKnight** knights;
    bool PaladinShield,LancelotSpear,GuinevereHair,ExcaliburSword;
public:
    ArmyKnights (const string & file_armyknights);

    void getPaladinShield();
    bool fight(BaseOpponent * opponent, Events* events, int i);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
protected:
    ItemType itemType;
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual ItemType Type() = 0;
    
};
class AntidoteItem : public BaseItem{
public:
    AntidoteItem();
    ItemType Type();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class PhoenixdownIItem : public BaseItem{
public:
    PhoenixdownIItem();
    ItemType Type();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class PhoenixdownIIItem : public BaseItem{
public:
    PhoenixdownIIItem();
    ItemType Type();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class PhoenixdownIIIItem : public BaseItem{
public:
    PhoenixdownIIIItem();
    ItemType Type();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class PhoenixdownIVItem : public BaseItem{
public:
    PhoenixdownIVItem();
    ItemType Type();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class Events {
protected:
    int number_of_events;
    int* a_event;
public:
    Events(const string & file_event);
    int count() const;
    int get(int i) const;
    bool isbattle(int num);
    void delete_Events();
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__

