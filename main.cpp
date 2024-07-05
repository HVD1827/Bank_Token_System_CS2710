#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

class Acct // representing details of an account
{
private:
    int acct_num, balance;
    Acct *next;
    Acct(int d)
    {
        acct_num = d;
        balance = 1000;
        next = nullptr;
    }
    friend class sll_Acct;
};

class sll_Acct // singly linked list to represent the list of accounts
{
private:
    Acct *first = nullptr;
    int len = 0;
    Acct *last = nullptr;

public:
    void addAcct(int d)
    {
        if (first == nullptr)
        {
            first = new Acct(d);
            last = first;
        }
        else
        {
            Acct *temp = first;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new Acct(d);
            last = temp->next;
        }
        len++;
    }

    void printlist()
    {
        Acct *temp = first;
        while (temp != nullptr)
        {
            cout << temp->acct_num << " " << temp->balance << endl;
            ;
            temp = temp->next;
        }
        cout << endl;
    }

    void process(int x, char c, int y)
    {
        Acct *temp = first;
        while (1)
        {
            if (temp->acct_num == x)
            {
                if (c == 'D')
                    temp->balance += y;
                else
                    temp->balance -= y;
                break;
            }
            temp = temp->next;
        }
    }

    void undoprocess(int x, char c, int y)
    {
        Acct *temp = first;
        while (true)
        {
            if (temp->acct_num == x)
            {
                if (c == 'W')
                    temp->balance += y;
                else
                    temp->balance -= y;
                break;
            }
            temp = temp->next;
        }
    }

    Acct *returnfirst() { return first; }

    int getbal(int k)
    {
        Acct *temp = first;
        for (int i = 0; i < k - 1; i++)
        {
            temp = temp->next;
        }
        return temp->balance;
    }
    int retaccno(int k)
    {
        Acct *temp = first;
        for (int i = 0; i < k - 1; i++)
        {
            temp = temp->next;
        }
        return temp->acct_num;
    }
    int retlen() { return len; }

    void retbalanceofacc(int x)
    {
        Acct *temp = first;
        while (temp != nullptr)
        {
            if (temp->acct_num == x)
            {
                cout << temp->balance << endl;
                break;
            }
            else
                temp = temp->next;
        }
    }
    void highestbal()
    {
        int max = INT_MIN;
        Acct *temp = first;
        while (temp != nullptr)
        {
            if (temp->balance > max)
                max = temp->balance;
            temp = temp->next;
        }
        temp = first;
        while (temp != nullptr)
        {
            if (temp->balance == max)
                cout << temp->acct_num << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
class transac // transaction node
{
private:
    int acct_num;
    int amt;
    char type;
    transac *next;
    transac *prev;

    transac(int x, char c, int y)
    {
        acct_num = x;
        type = c;
        amt = y;
        prev = next = nullptr;
    }

public:
    int getacct_num() { return acct_num; }
    char gettype() { return type; }
    int getamt() { return amt; }
    friend class dll_transac;
};
class dll_transac
{
private:
    transac *head;
    transac *tail;
    transac *cursor;
    int len;

public:
    dll_transac()
    {
        head = new transac(0, 0, 0);
        tail = new transac(0, 0, 0);
        head->next = tail;
        tail->prev = head;
        cursor = head;
        len = 0;
    }
    void addtrans(int x, char c, int y)
    {
        transac *temp = head;
        transac *toadd = new transac(x, c, y);
        if (head->next == tail)
        {
            head->next = toadd;
            tail->prev = toadd;
            toadd->next = tail;
            toadd->prev = head;
        }
        else
        {
            transac *t = tail->prev;
            tail->prev = toadd;
            toadd->next = tail;
            t->next = toadd;
            toadd->prev = t;
        }
        len++;
    }
    void printlist()
    {
        transac *temp = head->next;
        while (temp != tail)
        {
            cout << temp->acct_num << " " << temp->type << " " << temp->amt << endl;
            temp = temp->next;
        }
    }
    void insertafter(transac *p, int x, int y, char c)
    {
        transac *t = p->next;
        p->next = new transac(x, c, y);
        t->prev = p->next;
        p->next->prev = p;
        t->prev->next = t;
    }
    void processxtrans(int x, sll_Acct &acct)
    {
        transac *temp = cursor->next;
        while (temp != tail && x > 0)
        {
            acct.process(temp->acct_num, temp->type, temp->amt);
            x--;
            temp = temp->next;
        }
        cursor = temp->prev;
    }
    void undoytrans(int y, sll_Acct &acct)
    {
        transac *temp = cursor;
        while (y > 0 && temp != head)
        {
            acct.undoprocess(temp->acct_num, temp->type, temp->amt);
            y--;
            temp = temp->prev;
        }
        cursor = temp;
    }
    void insertnewtransacton(int k, int x, int y, char c, dll_transac &trxn, sll_Acct &acct)
    {

        if (k <= len)
        {
            int dum = 0;
            transac *temp = head;
            for (int i = 0; i < k; i++)
            {
                if (temp == cursor)
                    dum = 1;
                temp = temp->next;
            }
            // cout << dum << endl;
            if (dum == 0)
            {
                acct.process(x, c, y);
            }
            trxn.insertafter(temp, x, y, c);
            len++;
        }
    }
    void processallafterc(sll_Acct &acct)
    {
        transac *temp = cursor->next;
        while (temp != tail)
        {
            acct.process(temp->acct_num, temp->type, temp->amt);
            temp = temp->next;
        }
        cursor = tail->prev;
    }
    int printvalgr8(int x, sll_Acct &acct)
    {
        Acct *temp = acct.returnfirst();
        int cnt = 0;
        for (int i = 0; i < acct.retlen(); i++)
        {
            if (acct.getbal(i + 1) >= x)
                cnt++;
        }
        return cnt;
    }

    void printbal(int x, sll_Acct &acct) { acct.retbalanceofacc(x); }

    void transofy(int y)
    {
        transac *temp = head->next;
        while (temp != cursor->next)
        {
            if (temp->acct_num == y)
            {
                cout << temp->acct_num << " " << temp->type << " " << temp->amt << endl;
            }
            temp = temp->next;
        }
    }

    void deletetransac(int a, int m, sll_Acct &acct)
    {
        int isdone = 0;
        if (m > 0)
        {
            isdone = 1;
            transac *temp = cursor->next;
            while (m != 0 && temp != tail)
            {
                if (temp == cursor)
                {
                    temp = cursor->next;
                    isdone = 0;
                }
                if (temp->acct_num == a)
                {
                    if (isdone == 1)
                    {
                        // l.undoprocess(a, temp->type, temp->amt);
                        transac *t = temp;
                        temp->prev->next = temp->next;
                        t->next->prev = temp->prev;
                        len--;
                        m--;
                    }
                }
                temp = temp->next;
            }
        }
        else
        {
            transac *temp = cursor->prev;
            while (m != 0 && temp != head)
            {
                if (temp->acct_num == a)
                {
                    acct.undoprocess(a, temp->type, temp->amt);

                    transac *t = temp;
                    temp->prev->next = temp->next;
                    t->next->prev = temp->prev;
                    len--;
                    m++;
                }
                temp = temp->prev;
            }
        }
    }
    void printalltrans()
    {
        transac *temp = head->next;
        while (temp != tail)
        {
            cout << temp->acct_num << " " << temp->type << " " << temp->amt << endl;
        }
    }
};
int main()
{
    sll_Acct acct_list;
    dll_transac transac_list;
    int c;
    cin >> c;
    for (int i = 0; i < c; i++)
    {
        int x;
        cin >> x;
        acct_list.addAcct(x);
    }
    int n;
    cin >> n;
    int x, y;
    char type;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> type >> y;
        transac_list.addtrans(x, type, y);
    }
    string s, s1 = "END";
    cin >> s;
    while (s != s1)
    {
        if (s[0] == 'F')
        { // WORKING
            int x;
            cin >> x;
            transac_list.processxtrans(x, acct_list);
        }
        else if (s[0] == 'R')
        { // WORKING
            int y;
            cin >> y;
            transac_list.undoytrans(y, acct_list);
        }
        else if (s[0] == 'I')
        {
            int x, y;
            char c;
            cin >> x >> c >> y;
            int k;
            cin >> k;
            transac_list.insertnewtransacton(k, x, y, c, transac_list, acct_list);
        }
        else if (s[0] == 'D')
        {
            int a, m;
            cin >> a >> m;
            transac_list.deletetransac(a, m, acct_list);
        }
        else if (s[0] == 'C')
        {
            transac_list.processallafterc(acct_list);
        }
        else if (s[0] == 'S')
        {
            int y;
            cin >> y;
            transac_list.transofy(y);
        }
        else if (s[0] == 'G')
        {
            int x;
            cin >> x;
            cout << transac_list.printvalgr8(x, acct_list) << endl;
        }
        else if (s[0] == 'M')
        {
            acct_list.highestbal();
        }
        else if (s[0] == 'V')
        {
            int x;
            cin >> x;
            transac_list.printbal(x, acct_list);
        }
        cin >> s;
    }
}