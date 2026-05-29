#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <cctype>

using namespace std;

// zodis - kiek kartu pasikartojo
unordered_map<string, int> words;
// zodis - eiluciu numeriai
unordered_map<string, set<int>> lines;
// url galunes is failo
set<string> endings;
// rasti url adresai
set<string> urls;

// pavercia string i mazasias raides
string toLow(string s) 
{
    for (char& c : s) {
        c = tolower((unsigned char)c);
    }

    return s;
}

// nuima taskus, kablelius ir t.t.
string cleanW(string w) {

    string newW = "";

    for (char c : w) {
        // tikrinam ar simbolis yra raide arba skaicius
        if (isalnum((unsigned char)c)) {
            newW += tolower((unsigned char)c);
        }
    }

    return newW;
}

// nuima skyrybos zenklus nuo url pradzios ir galo
string cleanUrlW(string w) {

    while (!w.empty() && ispunct((unsigned char)w.front())) {

        w.erase(w.begin());
    }

    while (!w.empty() &&
           ispunct((unsigned char)w.back()) && w.back() != '/') {

        w.pop_back();
    }

    return w;
}

// tikrinam ar zodis yra url
bool isUrl(string w) {
    w = toLow(cleanUrlW(w));

    for (string e : endings) {
        string ending = "." + e;

        if (w.find(ending) != string::npos) {
            return true;
        }
    }

    return false;
}

// apdorojam viena eilute
void procLine(string line, int lnNum) {

    stringstream ss(line);
    string w;

    while (ss >> w) {
        // tikrinam ar tai url
        string maybeUrl = cleanUrlW(w);
        if (isUrl(maybeUrl)) {
            urls.insert(maybeUrl);
        }
        string fixed = cleanW(w);
        if (fixed != "") {
            // padidinam zodzio kieki
            words[fixed]++;
            // issaugom eilutes numeri
            lines[fixed].insert(lnNum);
        }
    }
}

// skaitom teksta
void readTxt(string fileN) {
    ifstream fd(fileN);
    if (!fd) {
        cout << "Nepavyko atidaryti failo\n";
        return;
    }
    string line;
    int lnNum = 1;
    while (getline(fd, line)) {
        procLine(line, lnNum);
        lnNum++;
    }

    fd.close();
}

// skaitom url galunes
void readUrls(string fileN) {
    ifstream fd(fileN);
    if (!fd) {
        cout << "Nepavyko atidaryti url failo\n";
        return;
    }
    string e;
    while (fd >> e) {
        // pavercia i mazasias
        endings.insert(toLow(e));
    }

    fd.close();
}

// isvedam zodziu kiekius
void outWords(string fileN) {
    ofstream fr(fileN);
    if (!fr) {
        cout << "Nepavyko sukurti failo\n";
        return;
    }
    fr << "Pasikartojantys zodziai:\n\n";
    for (auto x : words) {

        // isvedam tik tuos kurie pasikartojo daugiau nei 1 karta
        if (x.second > 1) {
            fr << x.first << " : " << x.second << endl;
        }
    }

    fr.close();
}

// isvedam cross-reference lentele
void outLines(string fileN) 
{
    ofstream fr(fileN);
    if (!fr) {
        cout << "Nepavyko sukurti failo\n";
        return;
    }
    fr << "Cross-reference:\n\n";
    for (auto x : lines) {
        string w = x.first;
        if (words[w] > 1) {
            fr << w << " : ";
            for (int nr : x.second) {
                fr << nr << " ";
            }
            fr << endl;
        }
    }

    fr.close();
}

// isvedam rastus url adresus
void outUrls(string fileN) 
{
    ofstream fr(fileN);
    if (!fr) {
        cout << "Nepavyko sukurti failo\n";
        return;
    }
    fr << "URL adresai:\n\n";
    for (string u : urls) {
        fr << u << endl;
    }

    fr.close();
}

int main() {

    string txtFile = "input.txt";
    string urlFile = "urls.txt";

    string out1 = "word_count.txt";
    string out2 = "cross_reference.txt";
    string out3 = "found_urls.txt";

    // pirma nuskaitom url galunes
    readUrls(urlFile);
    // tada teksta
    readTxt(txtFile);
    outWords(out1);
    outLines(out2);
    outUrls(out3);
    cout << "Programa baige darba\n";

    return 0;
}