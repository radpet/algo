#include<iostream>
#include<string.h>
#include<ctime>

using namespace std;

class TabData {
private:
    char *url;
    long timestamp;

    long genTimestamp() {
        time(&timestamp);
        return timestamp;
    }

    void copyUrlInternal(const char *_url) {
        url = new char[strlen(_url)];
        url = strcpy(url, _url);
    }

public:
    TabData() : url(nullptr) {
        copyUrlInternal("about:blank");
        timestamp = genTimestamp();
    }

    TabData(const char *_url) {
        timestamp = genTimestamp();
        copyUrlInternal(_url);
    }

    TabData(const TabData &other) {
        *this = other;
    }

    TabData &operator=(const TabData &other) {
        if (this != &other) {
            delete url;
            copyUrlInternal(other.url);
            timestamp = other.timestamp;
        }
    }

    ~TabData() {
        delete url;
    }

    void updateTimestamp() {
        timestamp = genTimestamp();
    }

    void setUrl(const char *_url) {
        copyUrlInternal(_url);
    }

    long getTimestamp() const {
        return timestamp;
    }

    const char *getUrl() const {
        return url;
    }

};

ostream &operator<<(ostream &out, const TabData &data) {
    out << data.getUrl() << " " << data.getTimestamp();
}

class Tab {
private:
    Tab *next;
    Tab *prev;
    TabData data;
public:
    Tab() : next(nullptr), prev(nullptr) {

    }

    Tab *getNext() const {
        return next;
    }

    Tab *getPrev() const {
        return prev;
    }

    bool hasNext() const {
        return getNext() != nullptr;
    }

    bool hasPrev() const {
        return getPrev() != nullptr;
    }

    void setNext(Tab *_next) {
        next = _next;
    }

    void setPrev(Tab *_prev) {
        prev = _prev;
    }

    void setUrl(const char *_url) {
        data.setUrl(_url);
    }

    void updateTimestamp() {
        data.updateTimestamp();
    }

    TabData &getTabData() {
        return data;
    }
};

class Browser {

    Tab *root;
    Tab *current;
public:

    Browser() {
        root = new Tab();
        current = root;
    }

    void go(const char *_url) {
        current->setUrl(_url);
        current->updateTimestamp();
    }

    void insert(const char *_url) {
        Tab *newTab = new Tab();
        newTab->setUrl(_url);
        newTab->updateTimestamp();
        if (current->hasNext()) {
            Tab *tmp = current->getNext();

            current->setNext(newTab);
            newTab->setPrev(current);
            tmp->setPrev(newTab);
        } else {
            current->setNext(newTab);
            newTab->setPrev(current);
        }
        current = newTab;
    }

    void back() {
        if (current->hasPrev()) {
            current = current->getPrev();
        }
    }

    void forward() {
        if (current->hasNext()) {
            current = current->getNext();
        }
    }

    void remove() {
        if (current->hasNext()) {
            Tab *next = current->getNext();
            Tab *prev = current->getPrev();

            prev->setNext(next);
            next->setPrev(prev);

            current = next;
        } else {
            if (current == root) { // we close the first tab
                delete current;
                current = new Tab();
                root = current;
            } else {
                current = current->getPrev();
            }
        }
    }

    void print() {
        Tab *tmp = root;
        while (tmp != nullptr) {
            if (tmp == current) {
                cout << "> ";
            }
            cout << tmp->getTabData() << endl;
            tmp = tmp->getNext();
        }
    }

    ~Browser() {
        Tab *cur = root;
        while (cur->hasNext()) {
            Tab *tmp = cur;
            cur = cur->getNext();
            delete tmp;
        }
    }

};

void test1_1(Browser &browser) {
    browser.go("www.youtube.com/watch?v=dQw4w9WgXcQ");
    browser.insert("www.google.bg/search?q=google+plz+help+me+solve+my+data+structures+task");
    browser.insert("www.9gag.com/gag/aAV83g9/when-you-realise-today-is-the-homework-assignment-deadline");
    browser.insert("www.en.wikipedia.org/wiki/Data_structure ");

    // browser.print();

    browser.back();
    browser.back();
    browser.remove();
    browser.print();

}

void test1_2(Browser &browser) {
    browser.remove();
    browser.go("www.wikihow.com/Deal-With-Tons-of-Homework");
    browser.forward();
    browser.go("www.susi.uni-sofia.bg");
    browser.print();
}

void test1() {
    cout << "########## Test 1 #########" << endl;
    Browser browser;
    cout << "[Test 1.1]" << endl;
    test1_1(browser);
    cout << "[Test 1.2]" << endl;
    test1_2(browser);
    cout << endl;
}

void test2_1(Browser &browser) {
    browser.back();
    browser.remove();
    browser.go("www.random.org");
    browser.forward();
    browser.remove();
    browser.print();
}


void test2() {
    cout << "########## Test 2 #########" << endl;
    Browser browser;
    cout << "[Test 2.1]" << endl;
    test2_1(browser);

    cout << endl;
}


int main() {
    test1();
    test2();
}