#include <iostream>
#include <string>
#include <regex>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Usuario {
    string email;
    string password;
    string resetToken;
    time_t tokenExpiration;
};

Usuario usuario = {"usuario@example.com", "Clave123!"};

bool validarContrase�a(const string& contrase�a) {
    regex patron("^(.*[A-Z]{2,}.*)(.*[a-z]+.*)(.*\\d+.*)(.*[!@#$%^&*]+.*).{8,}$");
    return regex_match(contrase�a, patron);
}

string generarToken() {
    srand(time(0));
    string token = "";
    for (int i = 0; i < 10; i++) {
        token += 'A' + rand() % 26; 
    }
    return token;
}

void solicitarRestablecimiento() {
    string email;
    cout << "Ingrese su email registrado: ";
    cin >> email;

    if (email != usuario.email) {
        cout << "Correo no encontrado." << endl;
        return;
    }

    usuario.resetToken = generarToken();
    usuario.tokenExpiration = time(0) + 21600; 

    cout << "Se ha enviado un correo con el c�digo: " << usuario.resetToken << endl;
}

void restablecerContrase�a() {
    string token, nuevaContrase�a;
    cout << "Ingrese el token de restablecimiento: ";
    cin >> token;

    if (token != usuario.resetToken || time(0) > usuario.tokenExpiration) {
        cout << "Token inv�lido o expirado." << endl;
        return;
    }

    cout << "Ingrese su nueva contrase�a: ";
    cin >> nuevaContrase�a;

    if (!validarContrase�a(nuevaContrase�a)) {
        cout << "Contrase�a insegura. Debe contener m�nimo:\n"
             << "- 8 caracteres\n"
             << "- 2 may�sculas seguidas\n"
             << "- 1 min�scula\n"
             << "- 1 n�mero\n"
             << "- 1 s�mbolo especial (!@#$%^&*)\n";
        return;
    }

    usuario.password = nuevaContrase�a;
    usuario.resetToken = "";
    cout << "Contrase�a restablecida correctamente." << endl;
}

void menu() {
    int opcion;
    do {
        cout << "\n1. Solicitar restablecimiento de contrase�a\n"
             << "2. Restablecer contrase�a\n"
             << "3. Salir\n"
             << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                solicitarRestablecimiento();
                break;
            case 2:
                restablecerContrase�a();
                break;
            case 3:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opci�n no v�lida.\n";
        }
    } while (opcion != 3);
}

int main() {
    menu();
    return 0;
}

