#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell {
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell {
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell {
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell {
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
};
string SpellJournal::journal = "";

void counterspell(Spell *spell) {
/* Enter your code here. Read input from STDIN. Print output to STDOUT */
     if (dynamic_cast<Fireball*>(spell) != NULL) {
          dynamic_cast<Fireball*>(spell)->revealFirepower();
     } else if (dynamic_cast<Waterbolt*>(spell) != NULL) {
          dynamic_cast<Waterbolt*>(spell)->revealWaterpower();
     } else if (dynamic_cast<Thunderstorm*>(spell) != NULL) {
          dynamic_cast<Thunderstorm*>(spell)->revealThunderpower();
     } else if (dynamic_cast<Frostbite*>(spell) != NULL) {
          dynamic_cast<Frostbite*>(spell)->revealFrostpower();
     } else {
          // Longest Common Subsequence Algorithm
          // Translated from Wikipedia Pseudo Code
          const string& X = spell->revealScrollName();
          const string& Y = SpellJournal::read();
          int m = X.length() + 1;
          int n = Y.length() + 1;
          int i,j;
          vector<vector<int>> C;

          // setup size and initialize all elements to 0
          C.resize(m);
          for (i = 0; i < m; ++i) {
               C[i].resize(n);
          }

          // do the giant black magic logic of the LCS
          for(i = 1; i < m; i++) {
               for(j = 1; j < n; j++) {
                    if (X[i-1] == Y[j-1]) {
                         C[i][j] = C[i-1][j-1] + 1;
                    } else {
                         C[i][j] = C[i][j-1] >= C[i-1][j] ? C[i][j-1] : C[i-1][j];
                    }
               }
          }
          cout << C[m-1][n-1] << endl;
     }
}

class Wizard {
public:
     Spell *cast() {
          Spell *spell;
          string s; cin >> s;
          int power; cin >> power;
          if(s == "fire") {
               spell = new Fireball(power);
          }
          else if(s == "frost") {
               spell = new Frostbite(power);
          }
          else if(s == "water") {
               spell = new Waterbolt(power);
          }
          else if(s == "thunder") {
               spell = new Thunderstorm(power);
          }
          else {
               spell = new Spell(s);
               cin >> SpellJournal::journal;
          }
          return spell;
     }
};

int main() {
     int T;
     Wizard Arawn;
     cin >> T;
     while(T--) {
          Spell *spell = Arawn.cast();
          counterspell(spell);
     }
     return 0;
}
