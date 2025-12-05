#ifndef AUXI_ARVOREAVL_HPP
#define AUXI_ARVOREAVL_HPP

template <typename T, typename U>
struct No {
    T chave;
    U dado;
    int altura;

    No<T,U>* filhoEsq;
    No<T,U>* filhoDir;
    No<T,U>* pai;
};


template <typename T, typename U>
class ArvoreAVL {
    public:
        ArvoreAVL();
        ~ArvoreAVL();
        ArvoreAVL(const ArvoreAVL&) = delete;

        void inserir(T& chave, U& dado);
        void limpar();
        U* buscar(T& chave);
        int getQuantElementos();
        typedef void (*Callback)(T& chave, U& dado, void* contexto);
        void paraCadaNo(Callback c, void* contexto);
        ArvoreAVL<T,U>& operator = (const ArvoreAVL<T,U>& outra) = delete;

    private:
        No<T,U>* _raiz;
        int _tamanho;

        void _atualizarAltura(No<T,U>* no);
        void _balancear(No<T,U>* no);        
        void _deletarElementos(No<T,U>* no);
        int _fatorBalanceamento(No<T,U>* no);
        int _max(int a, int b);
        No<T,U>* _rotacaoDir(No<T,U>* desb);
        No<T,U>* _rotacaoEsq(No<T,U>* desb);
        void _iterar(No<T, U>* no, Callback c, void* contexto);
};

template <typename T, typename U>
ArvoreAVL<T,U>::ArvoreAVL() : _raiz(nullptr), _tamanho(0) {}

template <typename T, typename U>
ArvoreAVL<T,U>::~ArvoreAVL() { this->limpar(); }

template <typename T, typename U>
void ArvoreAVL<T,U>::inserir(T& chave, U& dado) { 
    No<T,U>* no = this->_raiz;
    No<T,U>* novo = nullptr;

    if (this->_raiz == nullptr) {
        novo = new No<T,U>{chave, dado, 1, nullptr, nullptr, nullptr};
        this->_raiz = novo;
        this->_tamanho++;
        return;
    }

    while (true) {
        if (chave > no->chave) {
            if (no->filhoDir == nullptr) {
                novo = new No<T,U>{chave, dado, 1, nullptr, nullptr, no};
                no->filhoDir = novo;
                break;
            }
            else no = no->filhoDir;
        }

        else if (chave < no->chave) {
            if (no->filhoEsq == nullptr) {
                novo = new No<T,U>{chave, dado, 1, nullptr, nullptr, no};
                no->filhoEsq = novo;
                break;
            }            
            else no = no->filhoEsq;
        }
        else return;
    }

    this->_tamanho++;
    this->_balancear(novo->pai);
}

template <typename T, typename U>
void ArvoreAVL<T,U>::limpar() {
    this->_deletarElementos(this->_raiz);
    this->_raiz = nullptr;
    this->_tamanho = 0;
}

template <typename T, typename U>
U* ArvoreAVL<T,U>::buscar(T& chave) {
    No<T,U>* no = this->_raiz;
    while (no != nullptr) {
        if (chave == no->chave) return &no->dado;
        if (chave < no->chave) no = no->filhoEsq;
        else no = no->filhoDir;
    }
    return nullptr;
}

template <typename T, typename U>
int ArvoreAVL<T,U>::getQuantElementos() { return this->_tamanho; }

template <typename T, typename U>
void ArvoreAVL<T,U>::paraCadaNo(Callback c, void* contexto) {
    this->_iterar(this->_raiz, c, contexto);
}  

template <typename T, typename U>
void ArvoreAVL<T,U>::_atualizarAltura(No<T,U>* no) {
    if (no == nullptr) return;

    int dir = (no->filhoDir != nullptr) 
            ? no->filhoDir->altura
            : 0;
    int esq = (no->filhoEsq != nullptr) 
            ? no->filhoEsq->altura
            : 0;

    no->altura = 1 + this->_max(esq, dir);
}

template <typename T, typename U>
void ArvoreAVL<T,U>::_balancear(No<T,U>* no) { 
    No<T,U>* atual = no;

    while (atual != nullptr) {
        this->_atualizarAltura(atual);
        int fb = this->_fatorBalanceamento(atual);

        if (fb > 1) {
            if (this->_fatorBalanceamento(atual->filhoDir) < 0)
                this->_rotacaoDir(atual->filhoDir);

            atual = this->_rotacaoEsq(atual);
        }
        else if (fb < -1) {
            if (this->_fatorBalanceamento(atual->filhoEsq) > 0)
                this->_rotacaoEsq(atual->filhoEsq);
            
            atual = this->_rotacaoDir(atual);
        }

        atual = atual->pai;
    }
}

template <typename T, typename U>
void ArvoreAVL<T,U>::_deletarElementos(No<T,U>* no) {
    if (no == nullptr) return;

    _deletarElementos(no->filhoEsq);
    _deletarElementos(no->filhoDir);

    delete no;
}

template <typename T, typename U>
int ArvoreAVL<T,U>::_fatorBalanceamento(No<T,U>* no) {
    if (no == nullptr) return 0;

    int dir = (no->filhoDir != nullptr) 
            ? no->filhoDir->altura
            : 0;
    int esq = (no->filhoEsq != nullptr) 
            ? no->filhoEsq->altura
            : 0;

    return dir - esq;
}

template <typename T, typename U>
int ArvoreAVL<T,U>::_max(int a, int b) {
    return (a > b) ? a : b;
}

template <typename T, typename U>
No<T,U>* ArvoreAVL<T,U>::_rotacaoDir(No<T,U>* desb) {
    No<T,U>* esq = desb->filhoEsq;
    No<T,U>* dir = esq->filhoDir;

    esq->filhoDir = desb;
    desb->filhoEsq = dir;

    esq->pai = desb->pai;

    if (dir != nullptr) dir->pai = desb;

    desb->pai = esq;

    if (desb == this->_raiz) this->_raiz = esq;
    else if (esq->pai->filhoDir == desb) esq->pai->filhoDir = esq;
    else esq->pai->filhoEsq = esq;

    this->_atualizarAltura(desb);
    this->_atualizarAltura(esq);

    return esq;
}

template <typename T, typename U>
No<T,U>* ArvoreAVL<T,U>::_rotacaoEsq(No<T,U>* desb) { 
    No<T,U>* dir = desb->filhoDir;
    No<T,U>* esq = dir->filhoEsq;

    dir->filhoEsq = desb;
    desb->filhoDir = esq;

    dir->pai = desb->pai;

    if (esq != nullptr) esq->pai = desb;

    desb->pai = dir;

    if (desb == this->_raiz) this->_raiz = dir;
    else if (dir->pai->filhoEsq == desb) dir->pai->filhoEsq = dir;
    else dir->pai->filhoDir = dir;

    this->_atualizarAltura(desb);
    this->_atualizarAltura(dir);

    return dir;
}

template <typename T, typename U>
void ArvoreAVL<T,U>::_iterar(No<T, U>* no, Callback c, void* contexto) {
    if (no == nullptr) return;

    _iterar(no->filhoEsq, c, contexto);
    c(no->chave, no->dado, contexto);
    _iterar(no->filhoDir, c, contexto);
}

#endif