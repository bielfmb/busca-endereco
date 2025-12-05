#ifndef AUXI_VETOR_HPP
#define AUXI_VETOR_HPP

template <typename T>
class Vetor {
    public:
        Vetor();
        ~Vetor();

        void inserir(T& elemento);
        void ordenar();
        void limpar();
        Vetor* mesclarIguais(Vetor<T>* outro);
        T* get(int pos);
        int getTamanho();

    private:
        T* _lista;
        int _capacidade;
        int _tamanho;

        void _quickSort(int esq, int dir);
        void _particao(int esq, int dir, int* i, int* j);
        int _calcularPivo(int a, int b, int c);
};

template <typename T>
Vetor<T>::Vetor() : _capacidade(4), _tamanho(0) {
    this->_lista = new T[this->_capacidade];
}

template <typename T>
Vetor<T>::~Vetor() { this->limpar(); }

template <typename T>
void Vetor<T>::inserir(T& elemento) { 
    if (this->_tamanho >= this->_capacidade) {
        this->_capacidade *= 2;
        T* nova = new T[this->_capacidade];

        for (int i = 0; i < this->_tamanho; i++)
            nova[i] = this->_lista[i];
        
        delete[] this->_lista;
        this->_lista = nova;
    }

    this->_lista[this->_tamanho] = elemento;
    this->_tamanho++;
}

template <typename T>
void Vetor<T>::ordenar() { this->_quickSort(0, this->_tamanho - 1); }

template <typename T>
void Vetor<T>::limpar() {
    delete[] this->_lista;
    
    this->_lista = nullptr;
    this->_capacidade = 4;
    this->_tamanho = 0;
}

template <typename T>
Vetor<T>* Vetor<T>::mesclarIguais(Vetor<T>* outro) {
    Vetor<T>* intersecao = new Vetor<T>();
    
    int i = 0, j = 0;

    while ((i < this->_tamanho) && (j < outro->_tamanho)) {
        if (this->_lista[i] == outro->_lista[j]) {
            intersecao->inserir(this->_lista[i]);
            i++; j++;
        }
        else if (this->_lista[i] < outro->_lista[j]) i++;
        else j++;
    }
    
}

template <typename T>
T* Vetor<T>::get(int pos) { 
    if (pos < 0 || pos > this->_tamanho) return nullptr;
    return &this->_lista[pos];
}

template <typename T>
int Vetor<T>::getTamanho() { return this->_tamanho; }

template <typename T>
void Vetor<T>::_quickSort(int esq, int dir) {
    int i, j;
    this->_particao(esq, dir, &i, &j);

    if (esq < j) this->_quickSort(esq, j);
    if (i < dir) this->_quickSort(i, dir);
}

template <typename T>
void Vetor<T>::_particao(int esq, int dir, int* i, int* j) {
    int pivo;

    *i = esq; 
    *j = dir;

    // NOTA: se há mais de 3 elementos na particao, escolhe o pivô como 
    // a mediana entre 3 objetos para evitar o pior caso do QuickSort
    if (dir - esq >= 3)
        pivo = this->_calcularPivo(*i, (*i + *j)/2, *j); 

    else pivo = *i; // se há menos, o pivô é o primeiro elemento

    do {
        while (this->_lista[pivo] > this->_lista[*i]) (*i)++;
        while (this->_lista[pivo] < this->_lista[*j]) (*j)--;

        if (*i <= *j) {
            T aux = this->_lista[*i];
            this->_lista[*i] = this->_lista[*j];
            this->_lista[*j] = aux;

            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}


template <typename T>
int Vetor<T>::_calcularPivo(int a, int b, int c) {
    T* x = &this->_lista[a];
    T* y = &this->_lista[b];
    T* z = &this->_lista[c];

    if ((x <= y && y <= z) || (z <= y && y <= x)) return b;
    if ((y <= x && x <= z) || (z <= x && x <= y)) return a;
    return c;
}

#endif