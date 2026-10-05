# Data Structures and Algorithms — referencia ICPC

Referencia del equipo Mäthgic Crüe  contiene implementaciones, plantillas, fórmulas y notas para programación competitiva.



| Rol | Nombre | Usuario  |
| :--- | :--- | :--- |
| **Autor Principal** | Jorge Raúl Tzab López | `@SJMA11723` |
| **Coautor / Colaborador** | Ángel Manuel González López | `@angelmanuelgl` |
| **Coautor / Colaborador** | Rogelio Hernández Cruz | `@Rolexus934` |


El repo tiene dos objetivos:
1. conservar implementaciones C++ completas `code/`
2. producir `Referencia_ICPC.pdf`


NOTA IMPORTANTE: El proyecto **no es una biblioteca enlazable ni una sola aplicación**. No existe un ejecutable global: cada archivo C++ es una implementación o programa de ejemplo independiente. Lo que podriamos considerar como producto final es el documento LaTeX `Referencia_ICPC.pdf`.


## 1. Estructura del repositorio

```text
.
├── README.md                  # Esta documentación
├── Referencia_ICPC.tex        # Documento raíz y orden de las secciones
├── Referencia_ICPC.pdf        # <-- Referencia compilada y versionada
├── preambulo.tex              # Paquetes, formato, macros y estilo de código
├── ojo.tex                    # 
├── cleaner.py                 # Genera fuentes compactas para LaTeX de (*)
├── code/                      # Fuentes C++ y herramienta de stress testing
│   ├── template.h             # Includes, alias, macros y logger comunes
│   ├── stress.sh              # Comparación solución vs. fuerza bruta
│   ├── basics/
│   ├── complete_search/
│   ├── dp/
│   ├── fenwick_tree/
│   ├── graph/
│   ├── number_theory/
│   ├── segment_tree/
│   ├── sorting/
│   ├── sparse_table/
│   ├── sqrt_decomposition/
│   └── strings/
├── latex_src/                 # Copias compactas de `code/` para `minted` (*)
├── sections/                  # Capítulos LaTeX 
└── img/                       # Imágenes usadas
```


En general lo importante del pipeline es

- `code/` conserva programas y estructuras completas;
- `cleaner.py` transforma esos archivos en versiones densas dentro de `latex_src/`;
- `sections/*.tex` decide qué archivos compactados incluye y añade teoría o código en línea;
- `Referencia_ICPC.tex` decide el orden global;
- `preambulo.tex` define cómo se presentan fórmulas, títulos, código e imágenes;
- LaTeX ensambla todo en `Referencia_ICPC.pdf`.


### `code/`: fuente algorítmica

Contiene varios archivos procesables `.cpp`, `template.h` y `stress.sh`. Casi todos los `.cpp` tienen su propio `main()`, cada uno es independientes, no se compilan juntos.

`code/template.h` contiene:

- `<bits/stdc++.h>` y GNU Policy-Based Data Structures (`__gnu_pbds`);
- alias como `ll`, `vi`, `vll`, `vvi`, `pii` y `ordered_set`;
- macros de acceso y contenedores (`fi`, `se`, `pb`, `all`, `sz`);
- configuración de fast ios
- logger depuración (C++17).


Para si poder compilar cada uno:  Notar que alguno archivos incluyen esta plantilla mediante rutas relativas (`../template.h`, `../../template.h`, etc.); otros usan `#include "template.h"`. Segun con `-Icode` resuelve ambos estilos desde la raíz del repositorio.

### 1.1 `latex_src/`: vista generada para impresión

Misma jerarquía de `code/`, pero en una version compactada por  `cleaner.py`: como eliminar `main()` y comentarios  y etc, para que en el archivo `Referencia_ICPC` solo se muestre lo exclusivamente necesario.

NOTA: estos archivos no tienen equivalente en `code/`:

```text
number_theory/ecuaciones_diofantinas.cpp
number_theory/funcion_moebius.cpp
number_theory/funcion_phi_euler.cpp
number_theory/funcion_sigma0.cpp
number_theory/funcion_sigma1.cpp
number_theory/gcd_euclides_extendido.cpp
```

### 1.2 `sections/`: contenido de  `Referencia_ICPC.tex`



Cuando trabajamos en una archivo como `\sections\geometry` dos maneras de añadir código al manual 
1. `\inputcode{lenguaje}{ruta}{nombre}` carga un archivo compactado desde `latex_src/`;
2. los entornos `minted` contienen snippets escritos directamente en el `.tex`.



El macro `\inputcode` definido en `preambulo.tex` muestra el nombre del archivo y llama a `\inputminted` con numeración de líneas. 


**Uso de `//hide`:** Por ejemplo, archivos de teoría de números declaran con `// hide` funciones auxiliares que se explican o incorporan por separado, y varios algoritmos de grafos dependen de los alias/macros de `template.h`. La marca `// hide` permite que una dependencia necesaria para compilar la fuente completa no ocupe espacio en la versión impresa.

Las 19 secciones hasta ahora son:

| Archivo | Contenido principal |
| --- | --- |
| `temptesting.tex` | template, creación de archivos y stress testing |
| `ideas.tex` | recordatorios generales de resolución |
| `basics.tex` | min queue y heap actualizable |
| `number_theory.tex` | cribas, Euclides, diofánticas, funciones multiplicativas y Pollard Rho |
| `combi.tex` | Catalán, Narayana y particiones enteras |
| `calculus.tex` | FFT y multiplicación de polinomios |
| `formulazas.tex` | identidades de lógica, conjuntos, combinatoria y geometría |
| `numerical_methods.tex` | Gauss–Jordan y sistemas lineales, incluido módulo 2 |
| `sparse_table.tex` | consultas asociativas e idempotentes |
| `fenwick_tree.tex` | Binary Indexed Tree |
| `segment_tree.tex` | variantes puntual, lazy y dinámica |
| `sqrt_decomposition.tex` | algoritmo de Mo |
| `dsu.tex` | unión de conjuntos con rollback |
| `graph.tex` | caminos, árboles, MST, flujo, SCC y 2-SAT |
| `treap.tex` | treap por valor e implícito |
| `strings.tex` | hashing, KMP y estructuras de sufijos/múltiples patrones |
| `geometry.tex` | convex hull |
| `utils.tex` | subset sum, bitsets y operaciones bitwise |
| `li_chao_tree.tex` | máximo de funciones lineales |




## 3. Como funciona

### Pipeline 

```text
code/*.{cpp,h,sh}
        │
        │  python3 cleaner.py
        ▼
latex_src/                 sections/*.tex + img/*.png
        └──────────────┬───────────────┘
                       │  Referencia_ICPC.tex
                       │  + preambulo.tex
                       │  + pdflatex/minted
                       ▼
              Referencia_ICPC.pdf
```
1. La estrucutura de carpetas en `code/` se intenta mantener igual a la estructura de secciones y subsecciones de `Referencia_ICPC.pdf`
2. Se editan o agregan las implementaciones en `code/` y el contenido correspondiente en `sections/`.
3. `cleaner.py` recorre `code/` recursivamente y reproduce sus subdirectorios en `latex_src/`
4. `Referencia_ICPC.tex` carga `preambulo.tex`, crea el índice e incorpora todos los archivos de `sections/`.
5. Uso de `minted` resalta los bloques de codigo. Uso de  `graphicx` para incorpora los PNG de `img/`.

Recomendacion: LaTeX necesita varias pasadas para estabilizar el índice y las referencias. `latexmk` se ocupa de repetirlas y genera/actualiza `Referencia_ICPC.pdf`.

## 3 Compilación y ejecución

Todos los comandos siguientes deben ejecutarse desde la raíz del repositorio, salvo que se indique lo contrario.

### 3.0 Requisitos

#### Para C++
- compilador compatible con **GNU C++17** o posterior;
- biblioteca estándar de GNU que proporcione `<bits/stdc++.h>`;
- GNU PBDS (`<ext/pb_ds/assoc_container.hpp>` y `<ext/pb_ds/tree_policy.hpp>`) para los archivos que incluyen `template.h`.

C++17 es necesario, por la expresión del logger en `template.h`.

NOTA:
- Se recomienda GCC/g++ en Linux. 
- En macOS, el comando `/usr/bin/g++` suele ser Apple Clang y no suele inlcuir `<bits/stdc++.h>` ni PBDS. Una instalación de GCC mediante el gestor de paquetes del sistema es la opción más directa, yo le puse `g++-16` al binario.

#### Para generar fuentes LaTeX

- Python 3; el script usa únicamente la biblioteca estándar (`os` y `re`);
- no hay paquetes de Python que instalar para `cleaner.py`.

#### Para compilar el PDF

- una distribución LaTeX completa, por ejemplo TeX Live (por ejemplo mactex) o MiKTeX;
- `latexmk` y `pdflatex`;
- la clase `extarticle` y los paquetes declarados en `preambulo.tex` son: `hyperref`, `geometry`, `babel` con español, `xcolor`, `physics`, `amsthm`, `amssymb`, `amsmath`, `amsfonts`, `bbm`, `mathtools`, `minted`, `enumerate`, `enumitem`, `titling`, `lmodern`, `float`, `mathrsfs`, `wasysym`, `csquotes`, `dsfont`, `caption`, `graphicx`, `tocloft`, `multicol`, `parskip`, `fancyhdr`, `titlesec` y `chngcntr`;

Nota: `minted` ejecuta un resaltador externo. Por compatibilidad entre versiones, los comandos incluyen `-shell-escape`; este flag permite a LaTeX ejecutar comandos externos y solo debe usarse con fuentes de confianza.

### 3.1 Compilar y ejecutar C++ 

Ejemplo con la criba de Eratóstenes:

```bash
g++ -std=gnu++17 -O2 -pipe -Wall -Wextra -Icode \
  code/number_theory/sieve.cpp -o sieve
./sieve
```

Ejemplo con entrada redirigida:

```bash
g++ -std=gnu++17 -O2 -pipe -Wall -Wextra -Icode \
  code/graph/trees/mst/kruskal.cpp -o kruskal
./kruskal < input.txt
```

Flags:

- `-std=gnu++17`: estándar mínimo recomendado y extensiones GNU;
- `-O2`: optimización habitual para concurso;
- `-pipe`: usa tuberías durante la compilación; no cambia el ejecutable;
- `-Wall -Wextra`: activa diagnósticos útiles al adaptar una plantilla;
- `-Icode`: añade `code/` a la búsqueda de cabeceras y resuelve `#include "template.h"`.

**No intentar compilar todos los `.cpp` en un solo comando**, la mayoría define su propio `main()` y cada archivo representa un programa separado.

### Regenerar `latex_src/`

```bash
python3 cleaner.py
```

La ruta de entrada (`code`) y la de salida (`latex_src`) son relativas al directorio actual y están fijadas al principio del script. Ejecutarlo desde otra carpeta hará que no encuentre la entrada o escriba en una ubicación diferente.

### Compilar el manual completo

Pipeline recomendado:

```bash
python3 cleaner.py
```
luego
```bash
latexmk -pdf -shell-escape -interaction=nonstopmode -halt-on-error Referencia_ICPC.tex
```

`latexmk` repite `pdflatex` hasta estabilizar el índice. En una instalación moderna y completa, este comando produce `Referencia_ICPC.pdf`; el estado actual del documento compila a 15 páginas.

Alternativa manual, ejecutada suficientes veces para actualizar el índice:

```bash
pdflatex -shell-escape -interaction=nonstopmode -halt-on-error Referencia_ICPC.tex
pdflatex -shell-escape -interaction=nonstopmode -halt-on-error Referencia_ICPC.tex
pdflatex -shell-escape -interaction=nonstopmode -halt-on-error Referencia_ICPC.tex
```

Para borrar únicamente los auxiliares reconocidos por `latexmk`:

```bash
latexmk -c Referencia_ICPC.tex
```

`latexmk -c` conserva el PDF. `latexmk -C` también elimina la salida final, por lo que no debe usarse si se quiere conservar el PDF versionado.

## 4. Detalles de implementación

### 4.1 Diseño de las implementaciones C++

Las estructuras siguen el estilo de programación competitiva:

- tipos y macros breves compartidos por `template.h`;
- arreglos estáticos y límites de compilación en varias implementaciones;
- E/S por `stdin`/`stdout` en los ejemplos ejecutables;
- estructuras autocontenidas (`struct`) con construcción, actualización y consulta;
- complejidades y convenciones de indexación documentadas principalmente en `sections/`;
- implementaciones especializadas que deben parametrizarse, por ejemplo la función de combinación de Sparse Table/Segment Tree, el alfabeto de strings o los límites de vértices.
 

### 4.2 Consideraciones al reutilizar código

- Índices son base 0 o base 1. No todas las estructuras usan la misma convención.
- Ajustar `MAXN`, `LOGN`, `MAXV`, tamaño de bloque, módulo y elementos neutros antes de compilar una solución final.
- En `latex_src/` no hay un programa compilable porque el limpiador elimina `main()`, imports locales, alias y otras líneas. Es una version minima
- No hay sincronización bidireccional: cambiar `latex_src/` no actualiza `code/`, y regenerarlo puede sobrescribir esos cambios.
- El contenido escrito directamente en `sections/*.tex` no se genera desde `code/` y debe mantenerse por separado.
- `cleaner.py` reconoce `main()` mediante una expresión regular y balanceo de llaves; está diseñado para el estilo actual de los archivos, no como parser general de C++.
