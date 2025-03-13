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

bool validarContraseña(const string& contraseña) {
    regex patron("^(.*[A-Z]{2,}.*)(.*[a-z]+.*)(.*\\d+.*)(.*[!@#$%^&*]+.*).{8,}$");
    return regex_match(contraseña, patron);
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

    cout << "Se ha enviado un correo con el código: " << usuario.resetToken << endl;
}

void restablecerContraseña() {
    string token, nuevaContraseña;
    cout << "Ingrese el token de restablecimiento: ";
    cin >> token;

    if (token != usuario.resetToken || time(0) > usuario.tokenExpiration) {
        cout << "Token inválido o expirado." << endl;
        return;
    }

    cout << "Ingrese su nueva contraseña: ";
    cin >> nuevaContraseña;

    if (!validarContraseña(nuevaContraseña)) {
        cout << "Contraseña insegura. Debe contener mínimo:\n"
             << "- 8 caracteres\n"
             << "- 2 mayúsculas seguidas\n"
             << "- 1 minúscula\n"
             << "- 1 número\n"
             << "- 1 símbolo especial (!@#$%^&*)\n";
        return;
    }

    usuario.password = nuevaContraseña;
    usuario.resetToken = "";
    cout << "Contraseña restablecida correctamente." << endl;
}

void menu() {
    int opcion;
    do {
        cout << "\n1. Solicitar restablecimiento de contraseña\n"
             << "2. Restablecer contraseña\n"
             << "3. Salir\n"
             << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                solicitarRestablecimiento();
                break;
            case 2:
                restablecerContraseña();
                break;
            case 3:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 3);
}

int main() {
    menu();
    return 0;
}

