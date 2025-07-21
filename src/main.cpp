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

namespace Constants {
    const float GRAVITY_X = 0.0f;       // Gravidade no eixo X
    const float GRAVITY_Y = 1000.0f;    // Gravidade no eixo Y (ajuste conforme a escala)

    const int SUB_STEPS = 8;            // Número de sub-passos para a integração de Verlet (mais = mais preciso, mais lento)
    const float FRICTION = 0.999f;      // Fricção para objetos (próximo de 1.0f para pouca fricção)

    const float COLLISION_DAMPING = 0.8f; // Amortecimento de colisão (0.0f = sem bounce, 1.0f = bounce perfeito)
    const float STICKY_THRESHOLD = 0.01f; // Limiar para evitar que objetos grudem nas restrições

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const char* WINDOW_TITLE = "Verlet Physics Simulation";
}
 */

int main() {
    Application app;
    app.run();
    return 0;
}