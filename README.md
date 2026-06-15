# ☩ Jogo de Exploração RPG (HTML5 & Canvas Lite)

An immersive retro, text-and-grid-based RPG exploration game built entirely in a single file with **HTML5, CSS3, and Vanilla JavaScript**. Navigate through mysterious fog-covered forests, engage in strategic turn-based combat, manage your pixelated inventory, and test your luck against procedural mimicry mechanisms!

---

## 🎮 Como Jogar

O jogo é inteiramente controlado pelo teclado, simulando a experiência clássica de consoles antigos e jogos de terminal.

### ⌨ Controles
* **📌 SETAS DO TECLADO (↑, ↓, ←, →):** Movimentação livre pelo mapa 8x8.
* **📌 TECLA [Y]:** Confirmar ação / Aceitar desafio / Atacar no combate / Ir para a próxima floresta.
* **📌 TECLA [N]:** Recusar ação / Fugir da luta / Permanecer na floresta atual.
* **📌 BARRA DE ESPAÇO:** Abrir o inventário de consumíveis durante o seu turno de combate (ou fechar/cancelar).
* **📌 SETAS ↑↓ + ENTER (No Inventário):** Navegar pelos itens e usar o consumível selecionado.

---

## 🛠 Mecânicas

### 1. Progressão Infinita
* **Sistema de Fim de Jogo:** O rastreamento de casas exploradas foi calibrado. Ao revelar todas as 64 casas do tabuleiro, o prompt de transição é ativado imediatamente.
* **Continuidade de Atributos:** Ao aceitar o avanço (**Y**), o tabuleiro reseta do zero com novos biomas escondidos, mas você **mantém todo o seu HP Máximo, ATK, DEF e Itens acumulados** da fase anterior.

### 2. Teto de Dificuldade dos Monstros
* Para evitar que os monstros escalem infinitamente além da capacidade humana na modalidade *Sistema de Fim de Jogo*, foi adicionado um limitador físico: os monstros da Floresta 2 em diante usam como referência os **status finais que você possuía no término da primeira floresta**. Eles continuam desafiadores, mas nunca ficam mais fortes do que os limites estipulados na fase base.

### 3. Sistema de Fuga Tática e Retorno (Casas Vermelhas)
* **Persistência de Ameaça:** Ao avistar um monstro e decidir fugir (usando **N** na aproximação ou acumulando **3 defesas consecutivas** em combate), a casa é dada como quase explorada e ganha um visual **Vermelho Escuro** com o marcador de demônio (`👺`).
* **Combate com Memória de Estado:** O monstro não desaparece e nem reseta! Você pode andar livremente pelo mapa, coletar baús para se fortalecer e, quando pisar na casa vermelha novamente, o combate é retomado **exatamente de onde você parou**, com o inimigo mantendo a mesma vida que tinha quando você recuou.

---

## 🗂 Estrutura Técnica do Código

O projeto foi arquitetado sob o conceito de *Single-File Application* (aplicação de arquivo único) para facilitar a portabilidade e hospedagem gratuita rápida (No caso, foi usado o Netlify).

* **Camada de Estilo (CSS3):** Utiliza variáveis nativas (`:root`) para controle de paleta escura neo-retro, animações suaves de transição de estado nas células e tipografia carregada via Google Fonts (*Press Start 2P* e *VT323*).
* **Matrizes de Lógica:**
  * `logicMatrix`: Controla o conteúdo real oculto de cada bloco (0 = Seguro, 1 = Criatura, 2 = Baú, 3 = Monstro em Fuga).
  * `visualMatrix`: Gerencia o estado de renderização visual no DOM (`unexplored`, `explored`, `fled`, `current`).
  * `savedMonsters`: Objeto chave-valor dinâmico baseado em coordenadas (`"r,c"`) que encapsula e salva a vida restante e atributos de criaturas pendentes.

---

## 🚀 Como Testar o Jogo

O jogo está hospedado no site Netlify. Segue o link do jogo:
https://jogoexploracaorpg.netlify.app/

---

## 📜 Licença

Este projeto é de código aberto. Sinta-se livre para clonar, modificar os atributos, adicionar novos itens nas tabelas de raridades (`ITEMS_COMMON`, `ITEMS_MEDIUM`, `ITEMS_RARE`) ou implementar novos monstros
