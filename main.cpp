#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

void EnemyAttack(float &playerHP, vector<float> &enemieHP, float enemyMul) {
    int aliveEnemies = 0;
    for (float hp : enemieHP) {
        if (hp > 0) aliveEnemies++;
    }

    if (aliveEnemies == 0) {
        cout << "All enemies are dead lol" << endl;
        return;
    }

    for (int i = 0; i < enemieHP.size(); i++) {
        if (enemieHP[i] > 0) { // Only alive enemies attack
            srand(time(0) + i);
            int attackType = rand() % 2;

            switch (attackType) {
                case 0:
                    playerHP -= 10 * enemyMul;
                    cout << "enemy " << (i+1) << " did 10 dmg" << endl;
                    break;
                case 1:
                    playerHP -= 15 * enemyMul;
                    cout << "enemy " << (i+1) << " did 15 dmg" << endl;
                    break;
            }
        }
    }

    cout << "\nAfter enemies' attack you have: " << playerHP << " HP" << endl;
}

void playerAttackEnemy(float &playerHP, float &playerMP,vector<float>  enemyHP, string enemyName,
                       int attackHP1, int attackMP1, int attackHP2, int attackMP2,
                       int attackHP3, int attackPHP3, float enemyMul) {
    int attack, chooseEn;

    do {
        cout << "\n--------- Player HP: " << playerHP << " Player MP: " << playerMP << " --------" << endl;

        cout << "Choose which enemy to attack (1-" << enemyHP.size() << "): ";
        cin >> chooseEn;

        if (chooseEn >= 1 && chooseEn <= enemyHP.size() && enemyHP[chooseEn - 1] > 0) {
            cout << "Enemy " << enemyName << chooseEn << " has HP: " <<enemyHP[chooseEn - 1] << endl;
            cout << "Choose your attack (1-3): ";
            cin >> attack;

            switch (attack) {
                case 1:
                   enemyHP[chooseEn - 1] -= attackHP1;
                    playerMP -= attackMP1;
                    break;
                case 2:
                    if (playerMP >= attackMP2) {
                       enemyHP[chooseEn - 1] -= attackHP2;
                        playerMP -= attackMP2;
                    } else {
                        cout << "Not enough MP!" << endl;
                    }
                    break;
                case 3:
                    if (playerHP > attackPHP3) {
                       enemyHP[chooseEn - 1] -= attackHP3;
                        playerHP -= attackPHP3;
                    } else {
                        cout << "Not enough HP!" << endl;
                    }
                    break;
                default:
                    cout << "Invalid attack." << endl;
            }
        } else {
            cout << "Wrong enemy number or enemy already defeated!" << endl;
        }

        bool allDead = true;
        for (float hp :enemyHP) {
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
    float playerHP = 0, playerMP = 0;
    int attackHP1 = 0, attackMP1 = 0, attackHP2 = 0, attackMP2 = 0, attackHP3 = 0, attackPHP3 = 0;
    int select, characterClass;
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
                    attackHP1 = 10;
                    attackMP1 = 0;
                    attackHP2 = 20;
                    attackMP2 = 10;
                    attackHP3 = 30;
                    attackPHP3 = 10;
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
                    attackHP1 = 15;
                    attackMP1 = 0;
                    attackHP2 = 20;
                    attackMP2 = 10;
                    attackHP3 = 30;
                    attackPHP3 = 5;
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
   // playerAttackEnemy(playerHP, playerMP, enemyHP, enemyName, attackHP1, attackMP1, attackHP2, attackMP2, attackHP3, attackPHP3, enemyNUM, enemyMul);

    enemyHP.clear();
    cout << "\nPlayer HP after battle: " << playerHP << " / Player MP after battle: " << playerMP << endl;
    cout << "----------------------------------" << endl << endl;

    cout << "\nPART TOW\n";
    enemyName = "lol";
    enemyHP.push_back(10);
    enemyHP.push_back( 15);
    enemyMul = 1;
    cout << enemyHP.size();
    playerAttackEnemy(playerHP, playerMP, enemyHP, enemyName, attackHP1, attackMP1, attackHP2, attackMP2, attackHP3, attackPHP3, enemyMul);

    return 0;
}