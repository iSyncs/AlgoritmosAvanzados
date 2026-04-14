// a00840096 - carlos baranda

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> construirLPS(const string& patron) {
    vector<int> lps(patron.length(), 0);
    int longitud = 0;
    int i = 1;

    // construye el arreglo lps para el patron
    while (i < static_cast<int>(patron.length())) {
        if (patron[i] == patron[longitud]) {
            longitud++;
            lps[i] = longitud;
            i++;
        } else {
            if (longitud != 0) {
                longitud = lps[longitud - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

vector<int> buscarKMP(const string& texto, const string& patron, const vector<int>& lps) {
    vector<int> indices;
    int i = 0;
    int j = 0;

    // busca todas las apariciones del patron en el texto
    while (i < static_cast<int>(texto.length())) {
        if (patron[j] == texto[i]) {
            i++;
            j++;
        }

        if (j == static_cast<int>(patron.length())) {
            indices.push_back(i - j);
            j = lps[j - 1];
        } else if (i < static_cast<int>(texto.length()) && patron[j] != texto[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return indices;
}

int main() {
    string texto;
    string patron;

    cout << "ingresa el texto: ";
    getline(cin, texto);

    cout << "ingresa el patron: ";
    getline(cin, patron);

    if (patron.empty()) {
        cout << "el patron no puede estar vacio" << endl;
        return 0;
    }

    vector<int> lps = construirLPS(patron);

    cout << "LPS: ";
    for (int valor : lps) {
        cout << valor << " ";
    }
    cout << endl;

    vector<int> coincidencias = buscarKMP(texto, patron, lps);

    if (coincidencias.empty()) {
        cout << "No se encontraron coincidencias" << endl;
    } else {
        for (int indice : coincidencias) {
            cout << "Patron encontrado en indice: " << indice << endl;
        }
    }

    return 0;
}
