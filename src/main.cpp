#include "application/Application.hpp"

/*
*VerletPhysicsEngine/
├── src/
│   ├── core/                  # Classes principais da física
│   │   ├── VerletObject.hpp
│   │   ├── VerletObject.cpp
│   │   ├── Engine.hpp
│   │   ├── Engine.cpp
│   │   └── Constants.hpp      # (Novo) Constantes globais (gravidade, iterações, etc.)
│   │
│   ├── constraints/           # Definições das restrições de ambiente (paredes, pinos)
│   │   ├── Constraint.hpp     # Classe base abstrata
│   │   ├── CircleConstraint.hpp
│   │   ├── CircleConstraint.cpp
│   │   ├── BoxConstraint.hpp
│   │   ├── BoxConstraint.cpp
│   │   └── PinConstraint.hpp
│   │   └── PinConstraint.cpp
│   │
│   ├── rendering/             # Componentes de desenho (usando SFML)
│   │   ├── Renderer.hpp
│   │   ├── Renderer.cpp
│   │
│   ├── application/           # Lógica de alto nível e interações do usuário
│   │   ├── Application.hpp
│   │   ├── Application.cpp
│   │   ├── Spawner.hpp        # Gerenciamento do "spawn" das bolinhas
│   │   ├── Spawner.cpp
│   │
│   └── main.cpp               # Ponto de entrada do programa
│
├── assets/                    # Para fontes, texturas (se for usar no futuro)
├── build/                     # Onde os arquivos de compilação serão gerados
├── CMakeLists.txt             # Arquivo de construção (altamente recomendado para C++ moderno)
└── README.md
 */

int main() {
    Application app;
    app.run();
    return 0;
}