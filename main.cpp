#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>

void EnemyAttackGOBOLT(int &playerHP) {
    srand(time(0));
    int attackType;
    attackType = rand() % 2;

    switch (attackType) {
        case 0:
            playerHP -= 10;
        case 1:
            playerHP -= 15;
    }
    cout << "\nafter enemy attack you have: " << playerHP << "HP" << endl;
}

void playerAttackEnemy(int &playerHP, int &playerMP, int &enemyHP, string &enemyName ) {
    int attack;
    cout << endl << "****************" << endl;

    cout << "enemy type " << enemyName <<" has HP: " << enemyHP<< endl;

do {
    cout << endl << "--------- Player HP: " << playerHP << " Player MP: " <<playerMP<<" --------" << endl;
    cout << "Choose your attack: ";
        cin >> attack;

if (attack == 1){
    enemyHP -= 10;
}
else if (attack == 2 && playerMP >= 30){
   enemyHP -= 20;
   playerMP -= 30;
}
else if (attack == 3) {
   enemyHP -= 30;
   playerHP -=30;
}
else { cout << "you made a mistake" << endl;}

if (enemyHP > 0) {
    cout << "Enemy HP: " << enemyHP << endl;
        if (enemyName == "gobolt") {
            EnemyAttackGOBOLT(playerHP);
        }
}
else {
    cout << "Enemy is dead"<< endl;
}

} while (playerHP > 0 && enemyHP > 0);


    cout << endl << "****************" << endl;

    return;
}


int main() {
    int playerHP, playerMP, select, enemyHP;
    int characterClass;
    string enemyName;
    do {
        cout << "1) Mercenary / HP = 100 MP = 60 \n2) Marshal-artist / HP = 120 MP =  40 \nSelect class: ";
        cin >> characterClass;

        switch (characterClass) {
            case 1:
                cout << "\nMercenary:\n HP = 100 \n MP = 60 \n";
                cout << "attacks: \n 1st [MP cost = 00 / HP cost = 00 / DMG = 10] \n 2nd [PM cost = 10 / HP cost = 00 / DMG = 20] \n 3th [PM cost = 00 / HP cost = 10 / DMG = 30]\n";
                cout << "Press [1] to confirm: ";
                    cin >> select;
                playerHP = 100;
                playerMP = 80;
                break;
            case 2:
                cout << "\nMarshal-artist:\n HP = 120 \n MP = 40 \n";
                cout << "attacks: \n 1st  [MP cost = 00 / HP cost = 00 / DMG = 15] \n 2nd [PM cost = 10 / HP cost = 00 / DMG = 20] \n 3th [PM cost = 00 / HP cost = 05 / DMG = 30]\n";
                cout <<"Press [1] to confirm: ";
                    cin >> select;
                playerHP = 120;
                playerMP = 40;
                break;
            default:
                cout << "Invalid class!" << endl;
        }
    } while (select != 1);

    cout << "Player HP: " << playerHP << " / Player MP: " << playerMP << endl;

        enemyName = "gobolt";
        enemyHP = 30;
        playerAttackEnemy(playerHP, playerMP, enemyHP, enemyName);


    cout << "Player HP after attack: " << playerHP << " / Payer MP after attack: " << playerMP << endl;

    return 0;
}
