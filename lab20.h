#ifndef LAB20_H
#define LAB20_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


class Equipment {
private:
    int hpmax;
    int atk;
    int def;

public:
    Equipment(int h, int a, int d) {
        hpmax = h;
        atk   = a;
        def   = d;
    }

    vector<int> getStat() {
        return {hpmax, atk, def};
    }
};

/* =======================
   Class Unit
   ======================= */
class Unit {
private:
    const char* type;
    const char* name;

    int hp;
    int hpmax;
    int atk;
    int def;

    bool guard_on;
    bool dodge_on;

    Equipment* equipped;

public:
    Unit(const char* t, const char* n) {
        type = t;
        name = n;

        hpmax = 123;
        hp    = 123;
        atk   = 15;
        def   = 9;

        guard_on = false;
        dodge_on = false;
        equipped = nullptr;
    }

    /* ===== Turn ===== */
    void newTurn() {
        guard_on = false;
        dodge_on = false;
    }

    /* ===== Action ===== */
    void guard() {
        guard_on = true;
    }

    void dodge() {
        dodge_on = true;
    }

    /* ===== Heal ===== */
    void heal() {
        int recover = rand() % 21 + 10; // 10–30
        hp += recover;
        if (hp > hpmax) hp = hpmax;
    }

    /* ===== Equip ===== */
    void equip(Equipment* eq) {
        // ถอดของเก่า
        if (equipped != nullptr) {
            vector<int> old = equipped->getStat();
            hpmax -= old[0];
            atk   -= old[1];
            def   -= old[2];
        }

        // ใส่ของใหม่
        equipped = eq;
        vector<int> s = eq->getStat();
        hpmax += s[0];
        atk   += s[1];
        def   += s[2];

        // hp ห้ามเกิน hpmax
        if (hp > hpmax) hp = hpmax;
    }

    /* ===== Damage Logic ===== */
    int beAttacked(int enemy_atk) {
        int dmg = enemy_atk - def;
        if (dmg < 0) dmg = 0;

        if (dodge_on) {
            if (rand() % 2 == 0) {
                dmg = 0;            // dodge สำเร็จ
            } else {
                dmg *= 2;           // dodge พลาด
            }
        }
        else if (guard_on) {
            dmg /= 3;
        }

        hp -= dmg;
        if (hp < 0) hp = 0;

        return dmg;
    }

    /* ===== Attack ===== */
    int attack(Unit& target) {
        return target.beAttacked(atk);
    }

    /* ===== Ultimate ===== */
    int ultimateAttack(Unit& target) {
        return target.beAttacked(atk * 2);
    }

    /* ===== Status ===== */
    void showStatus() {
        cout << "---------------------------------------\n";
        cout << name << "\n";
        cout << "HP: " << hp << "/" << hpmax
             << "\tATK: " << atk
             << "\t\tDEF: " << def << "\n";
        cout << "---------------------------------------\n";
    }
};

#endif
