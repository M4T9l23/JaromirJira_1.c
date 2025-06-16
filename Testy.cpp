#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Attack {
    int damage;
    int mpCost;
    int hpCost;
};

struct Player {
    float hp;
    float mp;
    float maxHP;
    float maxMP;
    int gold;
    int xp;
    vector<Attack> attacks;
};

int RandomNum(int min, int max) {
    return rand() % (max - min + 1) + min;
}

struct Boss {
    float hp = 100;
    bool doubleNextDamage = false;
    bool doubleNextAttack = false;

    void takeDamage(int dmg) {
        if (doubleNextDamage) {
            dmg *= 2;
            doubleNextDamage = false;
            cout << ">>> Oddound received DOUBLE DAMAGE!\n";
        }

        hp -= dmg;
        cout << "Oddound took " << dmg << " damage. Remaining HP: " << hp << endl;

        if (dmg % 2 == 0) {
            doubleNextDamage = true;
            cout << "Oddound will take DOUBLE DAMAGE next hit!\n";
        } else {
            doubleNextAttack = true;
            cout << "Oddound's next attack will deal DOUBLE DAMAGE!\n";
        }
    }

    void attack(Player &player) {
        int a = RandomNum(1, 10);
        int b = RandomNum(1, 10);
        int dmg = 0;

        cout << "\nOddound rolls: " << a << " and " << b << endl;

        bool a_odd = a % 2 == 1;
        bool b_odd = b % 2 == 1;

        if (a_odd && b_odd) {
            dmg = (a + b) * 2;
            cout << "Both numbers are odd. Damage: (a + b) * 2 = " << dmg << endl;
        } else if (!a_odd && !b_odd) {
            dmg = abs(a - b) - 1;
            if (dmg < 0) dmg = 0;
            cout << "Both numbers are even. Damage: |a - b| - 1 = " << dmg << endl;
        } else {
            if (a_odd) {
                dmg = a + 5 - b;
            }else {
                dmg = b + 5 - a;
            }
            if (dmg < 0) dmg = 0;
            cout << "One odd, one even. Damage: odd + 5 - even = " << dmg << endl;
        }

        if (doubleNextAttack) {
            dmg *= 2;
            doubleNextAttack = false;
            cout << ">>> Oddound uses DOUBLE DAMAGE ATTACK!\n";
        }

        player.hp -= dmg;
        cout << "Oddound deals " << dmg << " damage to player! Player HP: " << player.hp << endl;
    }
};

void EnemyAttack(Player &player, vector<float> &enemyHP, float enemyMul) {
    int aliveEnemies = 0;
    for (float hp : enemyHP) {
        if (hp > 0) aliveEnemies++;
    }

    if (aliveEnemies == 0) {
        cout << "All enemies are defeated." << endl;
        return;
    }

    srand(time(0));

    for (int i = 0; i < enemyHP.size(); i++) {
        if (enemyHP[i] > 0) {
            int attackType = rand() % 2;
            int dmg = (attackType == 0) ? 10 : 15;
            player.hp -= dmg * enemyMul;
            cout << "Enemy " << (i + 1) << " did " << dmg << " dmg" << endl;
        }
    }

    cout << "\nAfter the enemies' attack, you have: " << player.hp << " HP" << endl;
}

int playerAttackEnemy(Player &player, vector<float> &enemyHP, const string &enemyName, float enemyMul) {
    int attack, chooseEn;
    cout << "Enemy " << enemyName << endl;

    do {
        cout << "\n--------- Player HP: " << player.hp << " | MP: " << player.mp << " --------" << endl;

        cout << "\nEnemy Status:\n";
        for (int i = 0; i < enemyHP.size(); ++i) {
            if (enemyHP[i] > 0) {
                cout << "Enemy " << (i + 1) << " is ALIVE with " << enemyHP[i] << " HP\n";
            } else {
                cout << "Enemy " << (i + 1) << " is DEAD\n";
            }
        }

        cout << "Choose which enemy to attack (1-" << enemyHP.size() << "): ";
        cin >> chooseEn;

        if (chooseEn >= 1 && chooseEn <= enemyHP.size() && enemyHP[chooseEn - 1] > 0) {
            cout << "Choose your attack (1-" << player.attacks.size() << "): ";
            cin >> attack;

            if (attack >= 1 && attack <= player.attacks.size()) {
                Attack chosen = player.attacks[attack - 1];

                if (player.mp < chosen.mpCost) {
                    cout << "Not enough MP!" << endl;
                    continue;
                }
                if (player.hp <= chosen.hpCost) {
                    cout << "Not enough HP!" << endl;
                    continue;
                }

                enemyHP[chooseEn - 1] -= chosen.damage;
                player.mp -= chosen.mpCost;
                player.hp -= chosen.hpCost;

            } else {
                cout << "Invalid attack." << endl;
            }
        } else {
            cout << "Invalid enemy number or enemy already defeated!" << endl;
        }

        bool allDead = true;
        for (float hp : enemyHP) {
            if (hp > 0) {
                allDead = false;
                break;
            }
        }

        if (allDead && player.hp > 0) {
            cout << "\nAll enemies defeated!" << endl;
            cout << "----------------------------------" << endl;
            cout << "Player HP after battle: " << player.hp << " | MP: " << player.mp << endl;
            cout << "----------------------------------\n" << endl;
            return 0;
        }

        if (!allDead) {
            EnemyAttack(player, enemyHP, enemyMul);

            if (player.hp <= 0) {
                cout << "You are dead. Game Over.\n";
                exit(0);
            }
        }

        } while (player.hp > 0);
    }

void shop(Player &player) {
    int shopAction;
    bool exitShop = false;

    do {
        cout << "\n--------- Shopping \n  you have: " << player.gold << " gold" << endl;

        cout << " [1] Refill HP    -- 10 gold\n"
             << " [2] Max HP + 10  -- 15 gold\n"
             << " [3] Refill MP    -- 5 gold\n"
             << " [4] Max MP + 20  -- 15 gold\n"
             << " [5] Manage XP\n"
             << " [6] Skip shop\n";
        cin >> shopAction;

        switch (shopAction) {
            case 1:
                if (player.gold >= 10) {
                    player.hp = player.maxHP;
                    player.gold -= 10;
                    cout << "your HP is " << player.hp << endl;
                } else {
                    cout << "Not enough gold!" << endl;
                }
                break;
            case 2:
                if (player.gold >= 15) {
                    player.maxHP += 10;
                    player.gold -= 15;
                    cout << "your max HP is " << player.maxHP << endl;
                } else {
                    cout << "Not enough gold!" << endl;
                }
                break;
            case 3:
                if (player.gold >= 5) {
                    player.mp = player.maxMP;
                    player.gold -= 5;
                    cout << "your MP is " << player.mp << endl;
                } else {
                    cout << "Not enough gold!" << endl;
                }
                break;
            case 4:
                if (player.gold >= 15) {
                    player.maxMP += 20;
                    player.gold -= 15;
                    cout << "your max MP is " << player.maxMP << endl;
                } else {
                    cout << "Not enough gold!" << endl;
                }
                break;
            case 5:
                cout << "You have " << player.xp << " XP available out of 100" << endl;
                if (player.xp >= 100) {
                    cout << "\nLEVEL UP!\n";
                    player.maxHP += 10;
                    player.maxMP += 10;
                    player.hp = player.maxHP;
                    player.mp = player.maxMP;
                    player.xp = 0;

                    for (Attack &atk : player.attacks) {
                        atk.damage += 5;
                    }

                    cout << "New stats: Max HP = " << player.maxHP << ", Max MP = " << player.maxMP << endl;
                    cout << "attack dmg: " << endl;
                    for (Attack &atk : player.attacks) {
                        cout << atk.damage << endl;
                    }
                }
                break;
            case 6:
                cout << "Ending shopping" << endl;
                exitShop = true;
                break;
            default:
                cout << "Invalid shop action." << endl;
        }

    } while (!exitShop);

    cout << "You have " << player.maxHP << " max HP\n";
    cout << "You have " << player.hp << " current HP\n";
    cout << "You have " << player.maxMP << " max MP\n";
    cout << "You have " << player.mp << " current MP\n";
}

int main() {
    srand(time(0));

    Player player;
    int characterClass, select = 2, tempProgres = 0, progres = 0;
    float enemyMul;
    string name;

    cout << "You are in a room with a few colorful stones with text above them:\n";
    cout << "{Press 1} ";
    cin >> tempProgres;
    progres += tempProgres;

    do {
        cout << "1) Mercenary (HP = 100, MP = 80)\n";
        cout << "2) Martial Artist (HP = 120, MP = 40)\n";
        cout << "Select class: ";
        cin >> characterClass;

        switch (characterClass) {
            case 1:
                player.maxHP = player.hp = 100;
                player.maxMP = player.mp = 80;
                player.gold = 10;
                player.xp = 0;
                player.attacks = {{10, 0, 0}, {20, 10, 0}, {30, 0, 10}};
                break;
            case 2:
                player.maxHP = player.hp = 120;
                player.maxMP = player.mp = 40;
                player.gold = 10;
                player.xp = 0;
                player.attacks = {{15, 0, 0}, {20, 10, 0}, {30, 0, 5}};
                break;
            default:
                cout << "Invalid class!" << endl;
                continue;
        }
        for (int i = 0; i < player.attacks.size(); i++) {
            cout << "Attack " << (i + 1) << " dmg: " << player.attacks[i].damage << endl;
            cout << "Attack " << (i + 1) << " MP cost: " << player.attacks[i].mpCost << endl;
            cout << "Attack " << (i + 1) << " HP cost: " << player.attacks[i].hpCost << endl << endl;
        }
        cout << "{press 1 to confirm}" << endl;
        cin >> select;
    } while (select != 1);

    cout << "\nAfter you picked up the stone, a secret door opens. You walk through and encounter your first monster.\n";
    cout << "{Press 1} ";
    cin >> tempProgres;
    progres += tempProgres;

    string enemyName = "Gob";
    vector<float> enemyHP = {20};
    enemyMul = 1.0f;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    if (RandomNum(1, 2) == 1) player.gold += 5;
    player.xp += 40;

    shop(player);

     // Second part
    cout << "\n--- PART TWO ---\n";
    enemyName = "Cob";
    enemyHP = {10, 15};
    enemyMul = 1.0f;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    for (float hp : enemyHP) {
        if (hp <= 0 && RandomNum(1, 2) == 1) {
            player.gold += RandomNum(5, 15);
        }
    }
    player.xp += 60;

    shop(player);

    cout << "\n--- PART TWO ---\n";
    enemyName = "Qob";
    enemyHP = {10, 10};
    enemyMul = 2;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    for (float hp : enemyHP) {
        if (hp <= 0 && RandomNum(1, 2) == 1) {
            player.gold += RandomNum(10, 20);
        }
    }
    player.xp += 40;

    //mini boss
    enemyName = "BoB the mini boss";
    enemyHP = {45};
    enemyMul = 3;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    player.gold += RandomNum(25, 40);
    player.xp += 60;

    shop(player);
    cout << "\n--- PART THREE ---\n";

    enemyName = "Cob";
    enemyHP = {20, 20, 15};
    enemyMul = 0.5;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    for (float hp : enemyHP) {
        if (hp <= 0 && RandomNum(1, 2) == 1) {
            player.gold += RandomNum(15, 25);
        }
    }
    player.xp += 40;

    enemyName = "Dob";
    enemyHP = {8, 12};
    enemyMul = 1.5;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    for (float hp : enemyHP) {
        if (hp <= 0 && RandomNum(1, 2) == 1) {
            player.gold += RandomNum(5, 10);
        }
    }
    player.xp += 20;

    enemyName = "Lob";
    enemyHP = {8, 12,15};
    enemyMul = 1;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    for (float hp : enemyHP) {
        if (hp <= 0 && RandomNum(1, 2) == 1) {
            player.gold += RandomNum(10, 15);
        }
    }
    player.xp += 20;

    enemyName = "Tob the mini boss";
    enemyHP = {80};
    enemyMul = 2;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    player.gold += RandomNum(30, 40);
    player.xp += 40;

    shop(player);

    cout << "\n--- PART FOUR ---\n";

    enemyName = "Rob";
    enemyHP = {10, 12,13};
    enemyMul = 1.5;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    for (float hp : enemyHP) {
        if (hp <= 0 && RandomNum(1, 2) == 1) {
            player.gold += RandomNum(10, 15);
        }
    }
    player.xp += 40;

    enemyName = "Lob";
    enemyHP = {15, 18,20};
    enemyMul = 1;
    playerAttackEnemy(player, enemyHP, enemyName, enemyMul);
    for (float hp : enemyHP) {
        if (hp <= 0 && RandomNum(1, 2) == 1) {
            player.gold += RandomNum(20, 25);
        }
    }
    player.xp += 60;

    shop(player);

    cout << "\n--- PART FIVE (boss) ---\n";
    Boss boss;
    do {
        cout << "\nYour HP: " << player.hp << " | MP: " << player.mp << "\n";
        cout << "Oddound HP: " << boss.hp << "\n";

        int attackChoice;
        cout << "Choose your attack (1-" << player.attacks.size() << "): ";
        cin >> attackChoice;

        if (attackChoice < 1 || attackChoice > player.attacks.size()) {
            cout << "Invalid attack.\n";
            continue;
        }

        Attack atk = player.attacks[attackChoice - 1];
        if (player.mp < atk.mpCost || player.hp <= atk.hpCost) {
            cout << "Not enough resources!\n";
            continue;
        }

        player.mp -= atk.mpCost;
        player.hp -= atk.hpCost;

        boss.takeDamage(atk.damage);

        if (boss.hp <= 0) {
            cout << ">>> Oddound has been defeated!\n";
            break;
        }

        boss.attack(player);

        if (player.hp <= 0) {
            cout << ">>> You were defeated by Oddound...\n";
            break;
        }

    } while (player.hp > 0 && boss.hp > 0);

    return 0;
}
