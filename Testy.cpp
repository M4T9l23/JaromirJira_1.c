#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

void EnemyAttack(float &playerHP, vector<float> &enemyHP, float enemyMul) {
    int aliveEnemies = 0;
    for (float hp : enemyHP) {
        if (hp > 0) aliveEnemies++;
    }

    if (aliveEnemies == 0) {
        cout << "All enemies are dead lol" << endl;
        return;
    }

    for (int i = 0; i < enemyHP.size(); i++) {
        if (enemyHP[i] > 0) {
            srand(time(0) + i);
            int attackType = rand() % 2;

            switch (attackType) {
                case 0:
                    playerHP -= 10 * enemyMul;
                    cout << "Enemy " << (i+1) << " did 10 dmg" << endl;
                    break;
                case 1:
                    playerHP -= 15 * enemyMul;
                    cout << "Enemy " << (i+1) << " did 15 dmg" << endl;
                    break;
            }
        }
    }

    cout << "\nAfter enemies' attack you have: " << playerHP << " HP" << endl;
}

void playerAttackEnemy(float &playerHP, float &playerMP, vector<float> enemyHP, string enemyName, int attackPHP, float enemyMul, vector<int> P_dmg, vector<int> P_mp_cost) {
    int attack, chooseEn;

    do {
        cout << "\n--------- Player HP: " << playerHP << " Player MP: " << playerMP << " --------" << endl;
        cout << "Choose which enemy to attack (1-" << enemyHP.size() << "): ";
        cin >> chooseEn;

        if (chooseEn >= 1 && chooseEn <= enemyHP.size() && enemyHP[chooseEn - 1] > 0) {
            cout << "Enemy " << enemyName << chooseEn << " has HP: " << enemyHP[chooseEn - 1] << endl;
            cout << "Choose your attack (1-3): ";
            cin >> attack;

            if (attack >= 1 && attack <= 3) {
                int at1 = attack - 1;
                if (attack == 3 && playerHP <= attackPHP) {
                    cout << "Not enough HP!" << endl;
                } else if (playerMP >= P_mp_cost[at1]) {
                    enemyHP[chooseEn - 1] -= P_dmg[at1];
                    playerMP -= P_mp_cost[at1];
                    if (attack == 3) {
                        playerHP -= attackPHP;
                    }
                } else {
                    cout << "Not enough MP!" << endl;
                }
            } else {
                cout << "Invalid attack." << endl;
            }

        } else {
            cout << "Wrong enemy number or enemy already defeated!" << endl;
        }

        bool allDead = true;
        for (float hp : enemyHP) {
            if (hp > 0) {
                allDead = false;
                break;
            }
        }

        if (!allDead) {
            EnemyAttack(playerHP, enemyHP, enemyMul);
        } else {
            cout << "All enemies defeated!" << endl;
            cout << "----------------------------------" << endl;
            break;
        }

    } while (playerHP > 0);
}


int main() {
    vector<int> P_dmg;
    vector<int> P_mp_cost;
    float playerHP = 0, playerMP = 0;
    int attackPHP = 0;
    int select = 0, characterClass = 0;
    string enemyName = "MonsterName";
    float enemyMul;
    vector<float> enemyHP;
    int tempProgres = 0, progres = 0;

    cout << "You are in a room with a few colorful stones above which there is text:" << endl;
    cout << "{Press 1} ";
    cin >> tempProgres;
    progres += tempProgres;

    do {
        cout << "1) Mercenary / HP = 100 MP = 80\n2) Marshal-artist / HP = 120 MP = 40\nSelect class: ";
        cin >> characterClass;

        switch (characterClass) {
            case 1:
                cout << "\nMercenary:\n HP = 100 \n MP = 80 \n";
                cout << "Attacks:\n 1st [DMG=10 | MP=0 | HP=0]\n 2nd [DMG=20 | MP=10 | HP=0]\n 3rd [DMG=30 | MP=0 | HP=10]\n";
                cout << "Press [1] to confirm: ";
                cin >> select;
                if (select == 1) {
                    playerHP = 100;
                    playerMP = 80;
                    attackPHP = 10;

                    P_dmg = {10, 20, 30};
                    P_mp_cost = {0, 10, 0};
                }
                break;
            case 2:
                cout << "\nMarshal-artist:\n HP = 120 \n MP = 40 \n";
                cout << "Attacks:\n 1st [DMG=15 | MP=0 | HP=0]\n 2nd [DMG=20 | MP=10 | HP=0]\n 3rd [DMG=30 | MP=0 | HP=5]\n";
                cout << "Press [1] to confirm: ";
                cin >> select;
                if (select == 1) {
                    playerHP = 120;
                    playerMP = 40;
                    attackPHP = 5;

                    P_dmg = {15, 20, 30};
                    P_mp_cost = {0, 10, 0};
                }
                break;
            default:
                cout << "Invalid class!" << endl;
        }
    } while (select != 1);

    cout << "After you picked up the stone a secret door opened. So you walk through and there is your first monster" << endl;
    cout << "{Press 1} ";
    cin >> tempProgres;
    progres += tempProgres;

    enemyName = "Gob";
    enemyHP.push_back(20);
    enemyMul = 1;
    playerAttackEnemy(playerHP, playerMP, enemyHP, enemyName, attackPHP, enemyMul, P_dmg, P_mp_cost);

    enemyHP.clear();
    cout << "\nPlayer HP after battle: " << playerHP << " / Player MP after battle: " << playerMP << endl;
    cout << "----------------------------------" << endl << endl;

    cout << "\nPART TWO\n";
    enemyName = "Lol";
    enemyHP.push_back(10);
    enemyHP.push_back(15);
    enemyMul = 1;
    cout << enemyHP.size() << " enemies.\n";
    playerAttackEnemy(playerHP, playerMP, enemyHP, enemyName, attackPHP, enemyMul, P_dmg, P_mp_cost);

    return 0;
}
