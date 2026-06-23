#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Definição do nó da árvore
struct NO
{
    int matricula;
    string nome;
    string curso;
    NO *esq;
    NO *dir;
};

// ArvBin é um ponteiro para NO
typedef NO *ArvBin;

// Cria uma árvore vazia
ArvBin *cria_ArvBin()
{
    ArvBin *raiz = new ArvBin;

    if (raiz != nullptr)
        *raiz = nullptr;

    return raiz;
}

// Libera todos os nós da árvore
void libera_NO(NO *no)
{
    if (no == nullptr)
        return;

    libera_NO(no->esq);
    libera_NO(no->dir);

    delete no;
}

// Libera a estrutura da árvore
void libera_ArvBin(ArvBin *raiz)
{
    if (raiz == nullptr)
        return;

    libera_NO(*raiz);
    *raiz = nullptr;
}

// Insere um novo nó na árvore
bool insere_ArvBin(ArvBin *raiz, int matricula, string nome, string curso)
{
    if (raiz == nullptr)
        return false;

    NO *novo = new NO;
    novo->matricula = matricula;
    novo->nome = nome;
    novo->curso = curso;
    novo->esq = nullptr;
    novo->dir = nullptr;

    if (*raiz == nullptr){
        *raiz = novo;
        return true;
    }

    NO *atual = *raiz;

    while (true)
    {
        if (nome < atual->nome) // se o nome for menor, vai para a subárvore esquerda
        {
            if (atual->esq == nullptr) // se não houver nó à esquerda, insere o novo nó aqui
            {
                atual->esq = novo;
                return true;
            }
            atual = atual->esq;
        }
        else if (nome > atual->nome) // se o nome do novo nó for maior que o nome do nó atual, vai para a subárvore direita
        {
            if (atual->dir == nullptr)
            {
                atual->dir = novo;
                return true;
            }
            atual = atual->dir;
        }
        else
        {
            // matricula ja existente, não insere
            delete novo;
            cout << "Erro: Matrícula já cadastrada!\n";
            return false;
        }
    }
}

NO *busca_ArvBin(NO *no, string nome)
{
    if (no == nullptr)
        return nullptr;

    if (nome == no->nome){ // nó encontrado
        return no;
    }

    // Se o nome procurado for menor que o nome do nó atual
    if (nome < no->nome)
        return busca_ArvBin(no->esq, nome); // busca na subárvore esquerda
    else
        return busca_ArvBin(no->dir, nome); // busca na subárvore direita
}

int altArvBin(NO *no)
{

    if (no == nullptr)
        return 0;

    // 1 + a maior altura entre seus dois filhos
    return 1 + max(altArvBin(no->esq), altArvBin(no->dir));
}

int contaNos(NO *no)
{

    if (no == nullptr)
        return 0;

    // conta o nó atual (1) mais todos os nós das subárvores esquerda e direita
    return 1 + contaNos(no->esq) + contaNos(no->dir);
}

// Percurso em ordem
void emOrdem(NO *no)
{
    if (no == nullptr)
        return;

    emOrdem(no->esq);
    cout << no->nome
         << " - Matrícula: " << no->matricula
         << " - Curso: " << no->curso << endl;
    emOrdem(no->dir);
}

int main()
{

    int opcao;
    ArvBin *raiz = cria_ArvBin();

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Inserir aluno\n";
        cout << "2. Percorrer em ordem\n";
        cout << "3. Buscar aluno por nome\n";
        cout << "4. Altura da árvore\n";
        cout << "5. Contar número de alunos cadastrados\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao)
        {

        case 1:
        {
            int matricula;
            string nome, curso;

            cout << "Digite a matrícula: ";
            cin >> matricula;

            // Descarta tudo que sobrou no buffer até o '\n' (inclusive)
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Digite o nome: ";
            getline(cin, nome); // lê linha inteira

            cout << "Digite o curso: ";
            getline(cin, curso); // lê linha inteira, com espaços

            if (insere_ArvBin(raiz, matricula, nome, curso))
                cout << "Aluno inserido com sucesso!\n";
            else
                cout << "Erro: Matrícula já cadastrada!\n";

            break;
        }

        case 2:
            cout << "\n--- Alunos cadastrados ---\n";
            emOrdem(*raiz);
            break;

        case 3:
        {
            string nome;
            cout << "Digite o nome do aluno a ser buscado: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, nome);

            NO *aluno = busca_ArvBin(*raiz, nome);

            if (aluno != nullptr)
            {
                cout << "Aluno encontrado!\n";
                cout << "Matrícula: " << aluno->matricula
                     << " - Nome: " << aluno->nome
                     << " - Curso: " << aluno->curso << endl;
            }
            else
            {
                cout << "Aluno não encontrado!\n";
            }
            break;
        }
        case 4:
            cout << "Altura da árvore: " << altArvBin(*raiz) << endl;
            break;

        case 5:
            cout << "Número de alunos Cadastrados: " << contaNos(*raiz) << endl;
            break;

        case 0:
            cout << "Saindo...\n";
            break;

        default:
            cout << "Opção inválida!\n";
        }

    } while (opcao != 0);

    libera_ArvBin(raiz);  // destrói todos os nós
    delete raiz; // libera a estrutura da árvore

    return 0;
}
