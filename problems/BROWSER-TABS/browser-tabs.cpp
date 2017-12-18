#include<iostream>
#include<string.h>


using namespace std;

class TabData {
private:
    char *url;
    long timestamp;

    long genTimestamp() {
        timestamp = clock(); //too fast for time
    }

    void copyUrlInternal(const char *_url) {
        delete[] url;
        int len = strlen(_url);
        url = new char[len + 1];
        strcpy(url, _url);
    }

public:
    TabData() {
        url = nullptr;
        copyUrlInternal("about:blank");
        genTimestamp();
    }

    TabData(const TabData &other) {
        url = nullptr;
        timestamp = genTimestamp();
        *this = other;
    }

    TabData &operator=(const TabData &other) {
        if (this != &other) {
            copyUrlInternal(other.url);
            timestamp = other.timestamp;
        }
    }

    ~TabData() {
        delete[] url;
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

    static bool cmpByTimestamp(const TabData &one, const TabData &other) {
        if (one.getTimestamp() == other.getTimestamp()) {
            return strcmp(one.getUrl(), other.getUrl()) > 0;
        }
        return one.getTimestamp() > other.getTimestamp();
    }

    static bool cmpByURL(const TabData &one, const TabData &other) {
        if (strcmp(one.getUrl(), other.getUrl()) == 0) {
            return one.getTimestamp() > other.getTimestamp();
        }

        return strcmp(one.getUrl(), other.getUrl()) > 0;
    }

    static void swap(TabData &one, TabData &other) {
        TabData tmp = one;

        one = other;
        other = tmp;
    }

};

ostream &operator<<(ostream &out, const TabData &data) {
    out << data.getUrl() << " " << data.getTimestamp();
}

class Tab {

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

    void setTabData(const TabData &tabData) {
        data = tabData;
    }

    TabData &getData() {
        return data;
    }
};

// no memory management here
class Browser {
private:
    Tab *root;
    Tab *current;

    void sort(bool (*cmp)(const TabData &, const TabData &)) {
        current = root;
        for (Tab *i = root; i != nullptr; i = i->getNext()) {
            for (Tab *j = root; j->hasNext(); j = j->getNext()) {
                if (cmp(j->getData(), j->getNext()->getData())) {
                    //swap
                    TabData::swap(j->getData(), j->getNext()->getData());
                }
            }
        }
    }

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
            cout << tmp->getData() << endl;
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

    void sort(const char *by) {
        if (strcmp(by, "URL") == 0) {
            sort(TabData::cmpByURL);
        }

        if (strcmp(by, "TIME") == 0) {
            sort(TabData::cmpByTimestamp);
        }
    }
};

void test1_1(Browser &browser) {
    browser.go("www.youtube.com/watch?v=dQw4w9WgXcQ");
    browser.insert("www.google.bg/search?q=google+plz+help+me+solve+my+data+structures+task");
    browser.insert("www.9gag.com/gag/aAV83g9/when-you-realise-today-is-the-homework-assignment-deadline");
    browser.insert("www.en.wikipedia.org/wiki/Data_structure");

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

void test3_1(Browser &browser) {
    browser.go("www.youtube.com/watch?v=dQw4w9WgXcQ");
    browser.insert("www.en.wikipedia.org/wiki/Data_structure");
    browser.insert("www.wikihow.com/Deal-With-Tons-of-Homework");
    browser.insert("www.susi.uni-sofia.bg");

    browser.sort("URL");
    browser.print();
}

void test3_2(Browser &browser) {
    browser.sort("TIME");
    browser.print();
}


void test3() {
    cout << "########## Test 3 #########" << endl;
    Browser browser;
    cout << "[Test 3.1]" << endl;
    test3_1(browser);
    cout << "[Test 3.2]" << endl;
    test3_2(browser);

    cout << endl;
}

int main() {
    test1();
    test2();

    test3();
}