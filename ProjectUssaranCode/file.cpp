//
//  main.cpp
//  ProjectUssaranCode
//
//  Created by Jessica Rodrigues on 14/05/25.
//

#include <iostream>
#include <stdio.h>

#include <cmath>
using namespace std;

class Letter {
public:
    std::string key;
    std::string value;

    Letter() {}
    Letter(const std::string& k, const std::string& v) : key(k), value(v) {}

    bool operator==(const Letter& other) const {
        return key == other.key && value == other.value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Letter& l) {
        os << l.key << ": " << l.value;
        return os;
    }
};


template<typename T>
class Node {
  private:
  T item;

  public:
  Node<T>* next;
  Node<T>* prev;
  Node(): next(nullptr), prev(nullptr) {}
  Node(T it): item(it), next(nullptr), prev(nullptr)  {}
  T getItem();
};


template<typename T>
T Node<T>::getItem() {
  return item;
}

template<typename T>
class Stack {
private:
    Node<T>* top;
    Node<T>* bottom;
    int numItems;
    
    
public:
    void create();
    void push(T item);
    void pop();
    T head();
    bool empty();
    int size();
};


template<typename T>
void Stack<T>::create(){
    bottom = new Node<T>{};
    bottom->next = nullptr;
    top = bottom;
    numItems = 0;
}

template<typename T>
bool Stack<T>::empty() {
    return numItems == 0 || top == bottom;;
}

template<typename T>
void Stack<T>::push(T item){
    Node<T>* aux = new Node<T>{item};
    aux->next = top;
    top = aux;
    numItems++;
}

template<typename T>
void Stack<T>::pop(){
    if (empty()) {
        cout << "Lista vazia" << endl;
    } else {
        Node<T>* aux = top;
        top = top->next;
        delete aux;
        numItems = numItems - 1;
    }
}

template<typename T>
T Stack<T>::head() {
    if (empty()) {
        cout << "Pilha vazia" << endl;
        return T();
    }
    return top->getItem();
}

template<typename T>
int Stack<T>::size() {
    return numItems;
}


template <typename T>
class ListNavigator {
private:
    Node<T>* current;
    int index = 0;

public:
    ListNavigator(Node<T>* node) : current(node) {}

    bool end() const { return current == nullptr; }

    void next() { 
    if (!end()) {
        current = current->next;
        index = getIndex() + 1;
        setIndex(index);
    }
}


    bool getCurrentItem(T& item) const {
        if (end()) return false;
        item = current->getItem();
        return true;
    }
    int getIndex() {
        return index;
    }
    void setIndex(int valor){
        this->index = valor;
    }
};


// list
template<typename T>
class List {
  private:
    Node<T>* pHead;
    Node<T>* pBack;
    int numItems;
    void succ(Node<T>*&);
    void pred(Node<T>*&);

  public:
    List();
    ~List();
    void insertFront(T);
    void insertBack(T);
    void removeFront();
    void removeBack();
    T getItemFront();
    T getItemBack();
    ListNavigator<T> getListNavigator() const;
    int size();
    bool empty();
};

// succ
template<typename T>
void List<T>::succ(Node<T>*& p) {
  p = p->next;
}

// pred
template<typename T>
void List<T>::pred(Node<T>*& p) {
  p = p->prev;
}

// list
template<typename T>
List<T>::List() {
  pHead = new Node<T>{}; // Nó cabeça
  pHead->next = nullptr;
  pBack = pHead;
  numItems = 0;
}

// list
template<typename T>
List<T>::~List() {
  Node<T>* node = pHead;
  while (node != nullptr) {
    Node<T>* temp = node;
    node = node->next;
    delete temp;
  }
  pHead = nullptr;
  pBack = nullptr;
  numItems = 0;
}

// insert front

template<typename T>
void List<T>::insertFront(T item) {
  Node<T>* node = new Node<T>{item};
  node->next = pHead->next;
  node->prev = pHead;

  if (pHead->next != nullptr){
    node->next->prev = node;
  } else {
    pBack = node;
  }

  pHead->next = node;

  numItems++;
}

// insert back

template<typename T>
void List<T>::insertBack(T item) {
  Node<T>* node = new Node<T>{item};
  node->prev = pBack;
  pBack->next = node;
  pBack = node;

  numItems++;
}

// remove front
template<typename T>
void List<T>::removeFront() {

  if (empty()) return;

  Node<T>* node = pHead->next;
  
  pHead->next = node->next;

  node->next->prev = pHead;

  delete node;

  numItems--;
}

// remove back
template<typename T>
void List<T>::removeBack() {

  if (empty()) return;

  Node<T>* node = pBack;

  pred(pBack);

  pBack->next = nullptr;

  delete node;

  numItems--;
}

// get item front

template<typename T>
T List<T>::getItemFront(){
  
  if (empty()) {
    cout<<"Lista vazia."<<endl;
    return T();
  }
  
  return pHead->next->getItem();
}

// get item back

template<typename T>
T List<T>::getItemBack(){
  
  if (empty()) {
    cout<<"Lista vazia."<<endl;
    return T();
  }
  
  return pBack->getItem();
}

//empty
template<typename T>
bool List<T>::empty() {
  return pHead == pBack;
}

//list navigator
template<typename T>
ListNavigator<T> List<T>::getListNavigator() const {
    return ListNavigator<T>{pHead->next};
}

 



#define TABLE_SIZE 1000
template <typename T>
struct HashTable {
    private:
    List<T> t[TABLE_SIZE];
    
    public:
    void insert(const std::string& key, T item);
    bool search(const std::string& key, T& item);
    int length();
    bool empty();
    int loadFactor();
    void print();
    unsigned long int hash(const std::string& key,unsigned long int m);
};

template <typename T>
void HashTable<T>::insert(const std::string& key, T item) {
    size_t index = hash(key, TABLE_SIZE);
    t[index].insertBack(item);
}

template <typename T>
bool HashTable<T>::search(const std::string& key, T& result) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        ListNavigator<T> nav = t[i].getListNavigator();
        T current;
        while (!nav.end()) {
            if (nav.getCurrentItem(current)) {
                if (current.value == key) {
                    result = current;
                    return true;
                }
            }
            nav.next();
        }
    }
    return false;
}



template <typename T>
int HashTable<T>::length() {
    return t.size();
}

template <typename T>
bool HashTable<T>::empty() {
    return t.empty();
}

template <typename T>
unsigned long int HashTable<T>::hash(const std::string& key, unsigned long int m) {
    unsigned long int hashValue = 0;
    unsigned long int n = key.length();
    for (size_t i = 0; i < n; ++i) {
        hashValue += key[i] * static_cast<unsigned long int>(std::pow(128, n - i - 1));
        hashValue %= m;
}
    return hashValue;
}

template <typename T>
void HashTable<T>::print() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (!t[i].empty()) {
            ListNavigator<T> nav = t[i].getListNavigator();
            T current;
            while (!nav.end()) {
                if (nav.getCurrentItem(current)) {
                    std::cout << current.value << ": " << current.key << std::endl;
                }
                nav.next();
            }
        }
    }
}

template <typename T>
string getSubstring(const std::string line, HashTable<T> &alfabeto){
    
    int div = line.length()/3;
    string substring, linhaTraduzida;
    Letter letra;
    int index = 0;
    
    for (int i = 0; i < div; i++){
        substring = line.substr(index, 3);
        if (alfabeto.search(substring, letra)) {
            linhaTraduzida += letra.key;
        }
        
        index += 3;
    }
    
    if (index < line.length()) {
        string restante = line.substr(index);
        linhaTraduzida += restante;
    }
    
    return linhaTraduzida;
}

template <typename T>
void alphabet(HashTable<T>& dictionary) {
    
    dictionary.insert("A", Letter("A", ":::"));
    dictionary.insert("B", Letter("B", ".::"));
    dictionary.insert("C", Letter("C", ":.:"));
    dictionary.insert("D", Letter("D", "::."));
    dictionary.insert("E", Letter("E", ":.."));
    dictionary.insert("F", Letter("F", ".:."));
    dictionary.insert("G", Letter("G", "..:"));
    dictionary.insert("H", Letter("H", "..."));
    dictionary.insert("I", Letter("I", "|::"));
    dictionary.insert("J", Letter("J", ":|:"));
    dictionary.insert("K", Letter("K", "::|"));
    dictionary.insert("L", Letter("L", "|.:"));
    dictionary.insert("M", Letter("M", ".|:"));
    dictionary.insert("N", Letter("N", ".:|"));
    dictionary.insert("O", Letter("O", "|:."));
    dictionary.insert("P", Letter("P", ":|."));
    dictionary.insert("Q", Letter("Q", ":.|"));
    dictionary.insert("R", Letter("R", "|.."));
    dictionary.insert("S", Letter("S", ".|."));
    dictionary.insert("T", Letter("T", "..|"));
    dictionary.insert("U", Letter("U", ".||"));
    dictionary.insert("V", Letter("V", "|.|"));
    dictionary.insert("W", Letter("W", "||."));
    dictionary.insert("X", Letter("X", "-.-"));
    dictionary.insert("Y", Letter("Y", ".--"));
    dictionary.insert("Z", Letter("Z", "--."));
    dictionary.insert(" ", Letter(" ", "---"));
    dictionary.insert("~", Letter("~", "~"));
    dictionary.insert(":", Letter(":", ":"));
};

void lerPrograma(List<string>& memoria) {
    string linha;

    while (getline(cin, linha)) {
        if (linha == "~") {
                memoria.insertBack(linha);
                break;
        }
        
        memoria.insertBack(linha);
    }
}

template <typename T>
void traduzirPrograma(List<string>& memoria, HashTable<T> &alfabeto, List<string>& traducao){
    
    ListNavigator<string> nav = memoria.getListNavigator();
    string linha;
    string linhaTraduzida;
    while (!nav.end()) {
        if (nav.getCurrentItem(linha)) {
            linhaTraduzida = getSubstring(linha, alfabeto);
            traducao.insertBack(linhaTraduzida);
        }
        nav.next();
    }
}

void imprimir(const List<string>& memoria) {
    ListNavigator<string> nav = memoria.getListNavigator();
    string linha;
    while (!nav.end()) {
        if (nav.getCurrentItem(linha)) {
            cout << linha << endl;
        }
        nav.next();
    }
}

bool validaNomeFuncao(const string& linha) {
    size_t primeiro_caracter = linha.find_first_not_of(" ");
    if (primeiro_caracter == string::npos) return false;

    string linha_sem_espacos = linha.substr(primeiro_caracter);

    return linha_sem_espacos.size() == 3 && isupper(linha_sem_espacos[0]) && linha_sem_espacos[1] == ' ' && linha_sem_espacos[2] == ':';
}

bool validaChamadaDeFuncao(const string& linha) {
    size_t primeiro_caracter = linha.find_first_not_of(" ");
    string linha_sem_espacos = (primeiro_caracter == string::npos) ? "" : linha.substr(primeiro_caracter);

    return linha_sem_espacos.size() == 1 && isupper(linha_sem_espacos[0]);
}

bool validaEnfileirar(const string& linha) {
    size_t primeiro_caracter = linha.find_first_not_of(" ");
    string linha_sem_espacos = (primeiro_caracter == string::npos) ? "" : linha.substr(primeiro_caracter);
    
    return linha_sem_espacos.find("ENFILEIRA") != string::npos;
}

bool validaDesenfileirar(const string& linha) {
    size_t primeiro_caracter = linha.find_first_not_of(" ");
    string linha_sem_espacos = (primeiro_caracter == string::npos) ? "" : linha.substr(primeiro_caracter);
    
    return linha_sem_espacos.find("DESENFILEIRA") != string::npos;

}

#define QUEUE_SIZE 100

template <typename T>
class Queue {
private:
    int frontIndex;
    int backIndex;
    int numItems;
    T items[QUEUE_SIZE];

public:
    Queue() {
        frontIndex = 0;
        backIndex = -1;
        numItems = 0;
    }

    void enqueue(T item) {
        if (numItems == QUEUE_SIZE) {
            return;
        }

        backIndex = (backIndex + 1) % QUEUE_SIZE;
        items[backIndex] = item;
        numItems++;
    }

    void dequeue() {
        if (empty()) {
            return;
        }

        frontIndex = (frontIndex + 1) % QUEUE_SIZE;
        numItems--;
    }

    T front() const {
        if (empty()) {
            return T(); 
        }

        return items[frontIndex];
    }

    bool empty() const {
        return numItems == 0;
    }

    int size() const {
        return numItems;
    }
};


void interpretarPrograma(Stack<string>& comandos, List<string>& memoria, Stack<int>& enderecos, string main = "Z :") {
    ListNavigator<string> nav = memoria.getListNavigator();
    Queue<string> fila;
    
    while(!nav.end()){
        string comando;
        if (nav.end()) break;
        nav.getCurrentItem(comando);
        
        if(validaNomeFuncao(comando) && comando == main) {
            nav.next();
            break;
        } else {
            nav.next();
        }
    }
    
    while(!nav.end()) {
        string comando;
        if (nav.end()) break;
        nav.getCurrentItem(comando);
        
        if (validaEnfileirar(comando)){
            string valor = comando.substr(10); 
            fila.enqueue(valor);
            nav.next();
        } else if (validaDesenfileirar(comando)){
            if (!fila.empty()) {
                fila.dequeue(); 
            }
            nav.next();
        }else {
            if (comando.empty()) {
                if (!enderecos.empty()) {
                    int retorno = enderecos.head();
                    enderecos.pop();

                    nav = memoria.getListNavigator();
                    
                    for (int i = 0; i < retorno; i++) {
                        nav.next();
                    }
        
                } else {
                    break;
                }
            } else if (validaChamadaDeFuncao(comando)) {
                enderecos.push(nav.getIndex() + 1);
                
                ListNavigator<string> nav2 = memoria.getListNavigator();
                while (!nav2.end()) {
                    string novoComando;
                    nav2.getCurrentItem(novoComando);
                    
                    if (validaNomeFuncao(novoComando) && novoComando[0] == comando[0]) {
                        nav = nav2;
                        nav.next();
                        break;
                    }
                    
                    nav2.next();
                }
            } else {
                nav.next();
            }
        }
    }
    
    while (!fila.empty()) {
        cout << fila.front() << " ";
        fila.dequeue();
    }
}


int main(int argc, const char * argv[]) {
    
    HashTable<Letter> dictionary;
    Stack<int> enderecos;
    Stack<string> comandos;
    
    List<string> memoria;
    List<string> traducao;

    alphabet(dictionary);

    lerPrograma(memoria);
    
    traduzirPrograma(memoria, dictionary, traducao);
    
    interpretarPrograma(comandos, traducao, enderecos);
    
}