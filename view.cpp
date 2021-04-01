#include <bits/stdc++.h>
#include "trie/trie_data_base.h"

using namespace std;

triedb tdb;

void in_table(string tag);
void remove(string tag);
void insert(string tag);
void see(string tag);
void see_all(string tag);
void update(string tag);


int main(int argc, char const *argv[])
{    
    unsigned op;
    do{
        cout << "\033[2J\033[1;1H";
        cout << "Qual tabela deseja consultar?" << endl;
        cout << "\t1 - Artista" << endl;
        cout << "\t2 - Autoria" << endl;
        cout << "\t3 - Banda" << endl;
        cout << "\t4 - Disco" << endl;
        cout << "\t5 - Endereco" << endl;
        cout << "\t6 - Instrumento" << endl;
        cout << "\t7 - Mora" << endl;
        cout << "\t8 - Musica" << endl;
        cout << "\t9 - Musico" << endl;
        cout << "\t10- Participa" << endl;
        cout << "\t11- Produtor" << endl;
        cout << "\t12- Repertorio" << endl;
        cout << "\t13- Toca" << endl;
        cout << "\t0 - SAIR" << endl;

        cin >> op;

        switch (op)
        {
        case 1:
            in_table("Artista");
            break;
        case 2:
            in_table("Autoria");
            break;
        case 3:
            in_table("Banda");
            break;
        case 4:
            in_table("Disco");
            break;
        case 5:
            in_table("Endereco");
            break;
        case 6:
            in_table("Instrumento");
            break;
        case 7:
            in_table("Mora");
            break;
        case 8:
            in_table("Musica");
            break;
        case 9:
            in_table("Musico");
            break;
        case 10:
            in_table("Participa");
            break;
        case 11:
            in_table("Produtor");
            break;
        case 12:
            in_table("Repertorio");
            break;
        case 13:
            in_table("Toca");
            break;
        default:
            op = 0;
            break;
        }

    }while(op);
    

    return 0;
}


void in_table(string tag){

    unsigned op;
    
    cout << "\033[2J\033[1;1H";
    cout << "O que deseja fazer com os elementos de \"" << tag << "\"?" << endl;
    cout << "\t1 - Ver todos os elementos" << endl;
    cout << "\t2 - Remover elemento por id" << endl;
    cout << "\t3 - Ver elemento por id" << endl;
    cout << "\t4 - Inserir novo elemento" << endl;
    cout << "\t5 - Atualizar elemento por id" << endl;
    cout << "\t0 - SAIR" << endl;

    cin >> op;
    getchar();
    
    switch (op)
    {
    case 1:
        see_all(tag);
        break;
    case 2:
        remove(tag);
        break;
    case 3:
        see(tag);
        break;
    case 4:
        insert(tag);
        break;
    case 5:
        update(tag);
        break;
    default:
        op = 0;
        break;
    }
    cout << "pressione ENTER para continuar" << endl;
    getchar();
}

void see_all(string tag){
    cout << "\033[2J\033[1;1H";
    vector<string> list = tdb.get_all_strings(tag);
    for(string s : list){
        cout << s << endl;
    }
}

void remove(string tag){
    cout << "\033[2J\033[1;1H";
    cout << "Insira o id:"<< endl;
    string id;
    getline(cin, id);
    tdb.remove_row(tag, id);
    cout << "**Removido!**" << endl;
}

void see(string tag){
    cout << "\033[2J\033[1;1H";
    cout << "Insira o id:"<< endl;
    string id;
    getline(cin, id);
    cout << tdb.get_string(tag, id) << endl;
}

void insert(string tag){
    element row = tdb.get_row(tag);
    cout << "\033[2J\033[1;1H";
    cout << "Insira o id:"<< endl;
    string id;
    getline(cin, id);
    row.set_id(id);
    for(auto& att: row.attributes)
    {
        cout << "Insira o valor de \"" << att.first << "\":"<< endl;
        getline(cin, id);
        row.set_attribute(att.first, id);
    }
    tdb.insert_row(row);
    cout << "**Inserido!**" << endl;
}

void update(string tag){
    element row = tdb.get_row(tag);
    cout << "\033[2J\033[1;1H";
    cout << "Insira o id:"<< endl;
    string id;
    getline(cin, id);
    row.set_id(id);
    for(auto& att: row.attributes)
    {
        cout << "Insira o valor de \"" << att.first << "\":"<< endl;
        getline(cin, id);
        row.set_attribute(att.first, id);
    }
    tdb.update_row(row);
    cout << "**Atualizado!**" << endl;
}
