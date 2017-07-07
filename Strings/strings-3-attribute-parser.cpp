/*
 *
 * Copyright <c> Manoel Vilela 2017
 *
 * Este problema se refere ao Attribute Parser RHTML do HackerRank C++
 *
 */
#include <cstdio>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <cstring>
using namespace std;

/*
 * Essa estrutura é usada para lidar com cada tag e suas filhas da puta
 * close_line é uma gambiarra pra saber em que linha o tag fecha
 * Isso é usado para poder fazer a leitura recursiva de modo obscuro
 */
typedef struct _Node {
    string name;
    map<string, string> attrs;
    vector<struct _Node> inner;
    int close_line;
} Node;

/*
 * Query é a estrutura básica para armazenar o caminho
 * e atributo de uma query.
 * path salva ordenamente a hierarquia da propriedade em relação
 * aos nomes de cada tag (Node.name)
 */
typedef struct _Query {
    vector<string> path;
    string attr;
} Query;

typedef vector<Node> AST;

/*
 * Essa função marota aqui é usada pra remover os primeiros espaços
 * que PODEM vir numa determinada linha (e.g.: indentação)
 */
string clean_initial_space(string str) {
    char c;
    stringstream ss(str);
    ss >> noskipws;
    do {
        ss >> c;
    } while (c == ' ');
    getline(ss, str);
    return c + str;
}

/*
 * Tokenize é uma função maluca pra devolver uma lista de tokens
 * Geralmente, primeiramente a tag e em seguida pares de key:value
 */
vector<string> tokenize(string str) {
    vector<string> v;
    string temp;
    char c;
    stringstream ss(str);
    ss >> noskipws;
    //cout << ss << endl;
    while (!ss.eof()) {
        ss >> c;
        switch (c) {
        case '\"':
            ss >> c;
            while(c != '\"') {
                temp = temp + c;
                ss >> c;
            }
            v.push_back(temp);
            temp = "";
            break;
        case '<':
        case '=':
        case '/':
            break;
        case ' ':
        case '>':
            if (!temp.empty()) {
                v.push_back(temp);
                temp = "";
            }
            break;
        default:
            temp = temp + c;
            break;
        }
    }
    return v;
}

/*
 * @create_node baseado numa linha tokenizada
 * cria um novo nó e armazena as informações nele.
 * No fim retorna esse nó.
 */
Node create_node(vector<string> parsed) {
    Node node = Node();
    node.name = parsed[0];
    // cout << ">>> " << node.name << endl;
    for(unsigned int i = 1; i < parsed.size() - 1; i+=2) {
        node.attrs[parsed[i]] = parsed[i + 1];
        // cout << ">> " << parsed[i] + "=" + parsed[i + 1] << endl;
    }
    return node;
}

/*
 * @parse_ast é onde acontece toda a desgraça desse código. Sinceramente
 * nem eu entendo direito como isso funciona. Além de estar horrível,
 * É uma função recursiva em múltiplas partes. 100% condenada.
 * Inicialmente AST era apenas um nó, mas depois que descobri que
 * nem sempre a entrada terá apenas uma tag de profundidade=0, então
 * Fiz a cagada de criar o tipo AST como vector<Node> e mudar tudo.
 */
AST parse_ast(vector<string> lines, int start = 0, bool root = true) {
    AST ast = AST();
    Node node = create_node(tokenize(clean_initial_space(lines[start])));
    ast.push_back(node);
    int i;
    // cout << "opening " << ast.name << " at " << start << endl;
    for (i = start + 1; i < (int) lines.size(); i++) {
        string line = clean_initial_space(lines[i]);
        if (line[1] != '/') { // a child node
            AST child = parse_ast(lines, i, false);
            i = child[0].close_line;
            ast[0].inner.push_back(child[0]);
        } else if (node.name.compare(tokenize(line)[0]) == 0) { // closing
            // cout << "closing " << ast.name << " at " << i << endl;
            break;
        }
    }

    if (root && i + 1 < (int) lines.size()) { //isso aqui é uma desgraça
        for(Node node : parse_ast(lines, i + 1, root)) {
            ast.push_back(node);
        }
    }

    ast[0].close_line = i;
    // cout << ast.name << " closes " << i << endl;

    return ast;
}

/*
 * Essa função é usada para imprimir todas as propriedades
 * em com uma sintaxe de pontos por atributo. Até onde chequei
 * é a parte mais correta desse código cagado.
 */
void print_ast(AST ast, string parent = "", int level = 0) {
    for (auto const &node: ast) {
        for(auto const &attr : node.attrs) {
            cout << level << " - " << parent + node.name  + "." + attr.first + " = " + attr.second << endl;
        }
        print_ast(node.inner, parent + node.name + ".", level + 1);
    }

}

/*
 * @parse_query recebe uma string com especificação de uma query
 * na forma <tag>.<tag>~<property> então retorna um struct Query
 * parseado e bonitinho
 */
Query parse_query(string str) {
    Query q = Query();
    stringstream ss(str);
    string temp;
    char c;
    q.attr = "";
    while(!ss.eof()) {
        ss >> c;
        switch (c) {
        case '.':
            q.path.push_back(temp);
            temp = "";
            break;
        case '~':
            q.path.push_back(temp);
            ss >> q.attr;
            temp = "";
            break;
        default:
            temp += c;
            break;
        }
    }
    return q;
}

/*
 * @search_ast baseado numa ast já parseada e a query tbm
 * Realiza uma busca em profunidade recursiva na árvore
 * Em procura da chave. Até onde vi o código é O(2^n): uma delícia.
 */
string search_ast(AST ast, Query q, int level = 0) {
    for (Node node : ast) {
        if (level < (int) q.path.size() - 1 && node.name.compare(q.path[level]) == 0) {
            string result = search_ast(node.inner, q, level + 1);
            // se a chave for "Not found!" eu tô é fudido
            if (result.compare("Not Found!") != 0) { // eita que a gamb rola mt
                return result;
            }
        } else if (node.name.compare(q.path[level]) == 0) {
            if (node.attrs.count(q.attr) > 0) {
                return node.attrs[q.attr];
            }
        }
    }

    return "Not Found!";
}


// apenas uma função auxiliar de teste
void test_query(AST ast, string raw_query) {
    Query query = parse_query(raw_query);
    cout << "== QUERY ==" << endl;
    for (auto const s: query.path) {
        cout << s << ".";
    };
    cout << "~" << query.attr;
    cout << " -> " << search_ast(ast, query) << endl;
}


// debug é apenas usada afim de... debugar.
void debug(){
    string test = "</tag1>";
    vector<string> test_lines = {
        "<tag1 v1 = \"123\" v2 = \"43.4\" v3 = \"hello\">",
        "</tag1>",
        "<tag2 v4 = \"v2\" name = \"Tag2\">",
        "<tag3 v1 = \"Hello\" v2 = \"World!\">",
        "</tag3>",
        "<tag4 v1 = \"Hello\" v2 = \"Universe!\">",
        "</tag4>",
        "</tag2>",
        "<tag5>",
        "<tag7 new_val = \"New\">",
        "</tag7>",
        "</tag5>",
        "<tag6>",
        "<tag8 intval = \"34\" floatval = \"9.845\">",
        "</tag8>",
        "</tag6>"
    };

    vector<string> query_lines = {
        "tag1~v1",
        "tag1.v1",
        "tag1~v2",
        "tag1~v3",
        "tag4~v2",
        "tag2.tag4~v1",
        "tag2.tag4~v2",
        "tag2.tag3~v2",
        "tag5.tag7~new_val",
        "tag5~new_val",
        "tag7~new_val",
        "tag6.tag8~intval",
        "tag6.tag8~floatval",
        "tag6.tag8~val",
        "tag8~intval"
    };
    AST ast = parse_ast(test_lines);
    string raw_query = "tag1.tag2.tag4.tag6~buzz";
    cout << "== AST PARSED ==" << endl;
    print_ast(ast);

    for(string query: query_lines) {
        test_query(ast, query);
    }

}


// e então a função desgraça
int main() {
    //debug();
    int n, q;
    vector<string> lines;
    vector<string> queries;
    string buffer;
    cin >> n;
    cin >> q;
    cin.ignore(); // ignorar newlines (drop \n)

    // recebe as linhas do RHTML
    for (; n > 0; n--) {
        getline(cin, buffer);
        lines.push_back(buffer);
    }

    // recebe as queries
    for (; q > 0; q--) {
        getline(cin, buffer);
        queries.push_back(buffer);
    }

    // parsear linhas
    AST ast = parse_ast(lines);
    for(string raw_query: queries) { // iterar queries
        Query q = parse_query(raw_query);
        // se não tiver atributo nada é encontrado
        if (q.attr.empty()) {
            cout << "Not Found!" << endl;
        } else {
            cout << search_ast(ast, q) << endl;
        }
    }

    return 0;
}
