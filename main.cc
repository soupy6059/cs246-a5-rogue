import <iostream>;
import <vector>;

using namespace std;

int main() { try {
    Game game;
    game.start();
}
catch(const exception &ex) {
    cerr << ex.what() << endl;
    return -1;
}}
