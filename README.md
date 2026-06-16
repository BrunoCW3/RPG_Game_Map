# 🗡️ Jogo de Exploração RPG — Terminal Edition

Um RPG de exploração em grade rodando no terminal, escrito em C puro. Inspirado em roguelikes clássicos, com combate por turnos, baús de tesouro, sistema de fuga e progressão infinita de florestas.

---

## 📸 Preview

```
     a  b  c  d  e  f  g  h
    -------------------------
 8 | .  .  .  .  .  .  .  .
 7 | .  .  .  .  .  .  .  .
 6 | .  .  .  .  .  .  .  .
 5 | .  .  .  .  .  .  .  .
 4 | .  .  .  .  .  .  .  .
 3 | .  .  .  .  .  .  .  .
 2 | .  .  .  .  .  .  .  .
 1 | @  .  .  .  .  .  .  .

  HP : 100/100   ATK: 2   DEF: 0   Casas: 0/64   Floresta: #1
  [setas] mover  [Enter] revelar  [f] fugir  [q] sair
```

---

## 🗂️ Estrutura do Projeto

```
.
├── main.c          # Ponto de entrada, tela inicial
├── matrizes.h      # Header compartilhado — tipos, macros, extern globals
├── matrizes.c      # Geração das matrizes lógica/visual e desenho do tabuleiro
├── revelador.c     # Lógica de revelação de casas, combate e baús
├── movimentacao.c  # Loop de input via termios (setas ANSI sem conio.h)
└── Makefile
```

---

## ⚙️ Compilação

### Linux / macOS

```bash
# Com Makefile
make

# Ou manualmente
gcc -Wall -std=c99 -o rpg main.c matrizes.c revelador.c movimentacao.c -lm
```

### Windows

O arquivo `movimentacao.c` usa `termios.h` (POSIX), que **não está disponível nativamente no Windows**. Alternativas:

- Compilar via **WSL** (Windows Subsystem for Linux) — recomendado
- Substituir `movimentacao.c` por uma versão com `conio.h` + `getch()` para MSVC/MinGW

---

## 🎮 Como Jogar

| Tecla | Ação |
|-------|------|
| `↑ ↓ ← →` | Mover o personagem pela grade |
| `Enter` | Revelar / interagir com a casa atual |
| `f` | Tentar fugir do combate atual |
| `q` | Sair do jogo |
| `y` / `n` | Confirmar / cancelar ações |

### Legenda do Tabuleiro

| Símbolo | Significado |
|---------|-------------|
| `@` | Você (jogador) |
| `.` | Casa inexplorada |
| `[ ]` | Casa segura explorada |
| `[G]` | Goblin derrotado |
| `[C]` | Baú aberto |
| `?` | Inimigo ativo — você fugiu desta casa |

---

## 🧩 Mecânicas

### Exploração

O mapa é uma grade 8×8 (64 casas) gerada deterministicamente via função `sin()` — sem `rand()`. A distribuição é:

- **70%** Caminho seguro
- **15%** Criatura
- **15%** Baú de tesouro

A casa inicial **A1** é sempre segura. Ao tentar entrar em uma casa com evento, aparece um aviso:

```
[!] Um ruido vem de e5! Prosseguir? [y/n]:
```

Há **50% de chance de mimetismo**: um baú pode virar inimigo e vice-versa ao confirmar a entrada.

### Combate

Combate por turnos. A cada turno você escolhe:

- **`y` — Atacar:** causa `ATK` de dano ao inimigo
- **`n` — Defender:** mitiga o próximo ataque com `DEF`; **3 defesas seguidas = fuga automática**
- **`f` — Fugir:** chance de fuga inversamente proporcional ao progresso no mapa

```
Chance de Fuga = 100% − (casas_exploradas / 64 × 100%)
```

Se a fuga falhar, o combate é forçado. O inimigo tem HP, ATK e DEF gerados com base nos atributos atuais do jogador (±5 de variação).

### Baús de Tesouro

| Raridade | Chance | Itens |
|----------|--------|-------|
| Comum | 60% | Espada de Madeira (+2 ATK), Armadura Velha (+5 DEF), Escudo de Madeira (+4 DEF) |
| Médio | 25% | Espada Velha (+7 ATK), Escudo de Soldado (+7 DEF), Espada Amaldiçoada (+10 ATK / −10 HP máx) |
| Raro | 15% | Espada do Anjo (+20 ATK), Armadura do Anjo (+20 DEF) |

Todos os bônus de equipamento são **permanentes e cumulativos**.

### Casas com `?` (Fuga)

Ao fugir de uma criatura, a casa fica marcada com `?` em vez de desaparecer. Isso significa:

- A casa **conta como visitada** no contador de progresso
- Você **pode retornar** e pressionar `Enter` para retomar o combate
- Ao derrotar a criatura depois, a casa vira `[G]` normalmente

### New Game Plus

Ao explorar as 64 casas, o jogo pergunta se você quer ir para uma nova floresta:

- **Todos os atributos e equipamentos** são mantidos
- O tabuleiro é **resetado** com nova geração de mapa
- Os inimigos são gerados com base nos seus **atributos atuais no início da nova floresta** — não ficam mais fortes a cada combate, apenas refletem o patamar que você chegou

---

## 🏗️ Arquitetura Interna

### Matrizes

O sistema opera com três matrizes `[8][8]`:

```c
int  mat_logic[ROWS][COLS];  // valor lógico: 0=seguro, 1=inimigo, 2=baú
int  mat_vis  [ROWS][COLS];  // estado visual: HIDDEN, EXPLORED, FLED
char mat_icon [ROWS][COLS];  // ícone renderizado: ' ', 'G', 'C'
```

### Geração Determinística

A matriz lógica usa `sin()` com seed composta por `(linha, coluna, geração)` para garantir mapas diferentes a cada floresta sem depender de `srand()`:

```c
double v = sin((r * 12.9898 + c * 78.233 + generation * 47.1) * 43758.5453);
int n = (int)fabs(floor(v * 10000)) % 100;
```

### Input sem conio.h

`movimentacao.c` usa `termios.h` para colocar o terminal em modo raw, capturando setas como sequências de escape ANSI (`ESC [ A/B/C/D`) sem precisar pressionar Enter a cada tecla.

---

## ❌ Funcionalidades não implementadas (vs. versão web)

Esta é uma versão simplificada. As seguintes features da versão HTML estão ausentes:

- Sistema de inventário com itens consumíveis (Pinga, Bandagens)
- Amuleto da Vida (cura passiva pós-combate)
- Inimigo com defesa tática real (na versão terminal ele "defende" mas não mitiga dano do player)
- Interface visual colorida / pixel art

---

## 📄 Licença

Projeto educacional de livre uso.
