#include <bits/stdc++.h>
#include "trie/trie_data_base.h"

using namespace std;

int main(int argc, char const *argv[])
{
    triedb tdb("/home/granzolino/TrieDB");


    //ENTIDADES

        //Preencher Produtore;
        element Produtor("Produtor");
        Produtor.push_attribute("nome");
        Produtor.push_attribute("telefone");
        tdb.insert_random_rows(Produtor);

        //Preencher Banda;
        element Banda("Banda");
        Banda.push_attribute("alcunha");
        tdb.insert_random_rows(Banda);

        //Preencher Endereco;
        element Endereco("Endereco");
        Endereco.push_attribute("telefone");
        Endereco.push_attribute("rua");
        Endereco.push_attribute("numero");
        tdb.insert_random_rows(Endereco);

        //Preencher Instrumento;
        element Instrumento("Instrumento");
        Instrumento.push_attribute("nome");
        tdb.insert_random_rows(Instrumento);

        //Preencher Musico;
        element Musico("Musico");
        Musico.push_attribute("nome");
        Musico.push_attribute("idade");
        Musico.push_attribute("sexo");
        Musico.push_attribute("funcao");
        tdb.insert_random_rows(Musico);

        //Preencher Artista;
        element Artista("Artista");
        Artista.push_attribute("eh_banda");
        tdb.insert_random_rows(Artista);

        //Preencher Disco;
        element Disco("Disco");
        Disco.push_attribute("data");
        Disco.push_attribute("formato");
        Disco.push_attribute("titulo");
        Disco.push_attribute("duracao");
        Disco.push_attribute("id_Produtor");
        Disco.push_attribute("id_Artista");
        tdb.insert_random_rows(Disco);

        //Preencher Musica;
        element Musica("Musica");
        Musica.push_attribute("genero");
        Musica.push_attribute("duracao");
        tdb.insert_random_rows(Musica);


    //Relações N:N

        //Preencher Repertorio
        element Repertorio("Repertorio");
        Repertorio.push_attribute("id_Musica");
        Repertorio.push_attribute("id_Disco");
        tdb.insert_random_rows(Repertorio);

        //Preencher Autoria
        element Autoria("Autoria");
        Autoria.push_attribute("id_Musica");
        Autoria.push_attribute("id_Artista");
        tdb.insert_random_rows(Autoria);

        //Preencher Participa
        element Participa("Participa");
        Participa.push_attribute("id_Artista_1");
        Participa.push_attribute("id_Artista_2");
        tdb.insert_random_rows(Participa);

        //Preencher Mora
        element Mora("Mora");
        Mora.push_attribute("id_Musico");
        Mora.push_attribute("id_Endereco");
        tdb.insert_random_rows(Mora);

        //Preencher Toca
        element Toca("Toca");
        Toca.push_attribute("id_Musico");
        Toca.push_attribute("id_Instrumento");
        tdb.insert_random_rows(Toca);


    return 0;
}
