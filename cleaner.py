import os
import re

# Carpetas de configuración
INPUT_DIR: str = 'code'       
OUTPUT_DIR: str = 'latex_src' 

# Expresiones regulares para C++
BOILERPLATE_REGEX: list[str] = [
    #r'^#include',
    r'^using namespace',
    r'^typedef',
    #r'^#define',
    r'^const int MOD',
    r'^//',           
    r'.*// hide.*'    
]

def read_file_safely(filepath: str) -> str:
    """Intenta leer en UTF-8. Si detecta caracteres especiales, usa latin-1."""
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            return f.read()
    except UnicodeDecodeError:
        with open(filepath, 'r', encoding='latin-1') as f:
            return f.read()

def remove_main_block(text: str) -> str:
    """Encuentra y elimina la función main completa en C++ usando una máquina de estados."""
    pattern = re.compile(r'^[ \t]*(?:inline[ \t]+)?(?:int|signed|void)[ \t]+main[ \t]*\([^)]*\)[ \t\n]*\{?', re.MULTILINE)
    match = pattern.search(text)
    
    if not match:
        return text
        
    start_idx: int = match.start()
    brace_idx: int = text.find('{', start_idx)
    if brace_idx == -1:
        return text
        
    depth: int = 0
    in_string: bool = False
    in_char: bool = False
    end_idx: int = -1
    
    i: int = brace_idx
    while i < len(text):
        c: str = text[i]
        
        if c == '\\': 
            i += 2
            continue
            
        if c == '"' and not in_char:
            in_string = not in_string
        elif c == "'" and not in_string:
            in_char = not in_char
            
        if not in_string and not in_char:
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
                if depth == 0:
                    end_idx = i
                    break
        i += 1
        
    if end_idx != -1:
        return text[:start_idx] + text[end_idx + 1:]
        
    return text

def remove_inline_c_comment(line: str) -> str:
    """Elimina comentarios // al final de una línea, respetando cadenas de texto y caracteres."""
    in_string = False
    in_char = False
    comment_idx = -1
    i = 0
    while i < len(line):
        c = line[i]
        if c == '\\':
            i += 2
            continue
        if c == '"' and not in_char:
            in_string = not in_string
        elif c == "'" and not in_string:
            in_char = not in_char
        elif c == '/' and i + 1 < len(line) and line[i+1] == '/' and not in_string and not in_char:
            comment_idx = i
            break
        i += 1
    
    if comment_idx != -1:
        return line[:comment_idx].rstrip()
    return line.rstrip()

def clean_template_file(filepath: str, outpath: str) -> None:
    """Reglas exclusivas para template.h"""
    raw_text: str = read_file_safely(filepath)

    no_block_comments: str = re.sub(r'/\*.*?\*/', '', raw_text, flags=re.DOTALL)
    
    lines: list[str] = no_block_comments.split('\n')
    dense_lines: list[str] = []

    for line in lines:
        line_no_comment = remove_inline_c_comment(line)
        if line_no_comment.strip():
            dense_lines.append(line_no_comment)

    text: str = "\n".join(dense_lines)

    os.makedirs(os.path.dirname(outpath), exist_ok=True)
    with open(outpath, 'w', encoding='utf-8') as f:
        f.write(text + '\n')

def clean_bash_file(filepath: str, outpath: str) -> None:
    """Reglas exclusivas para Bash (.sh)"""
    raw_text: str = read_file_safely(filepath)
    lines: list[str] = raw_text.split('\n')
    dense_lines: list[str] = []

    for i, line in enumerate(lines):
        stripped: str = line.strip()

        # 1. Conservar el shebang en la primera línea
        if i == 0 and stripped.startswith('#!'):
            dense_lines.append(line.rstrip())
            continue
            
        # 2. Etiqueta de ocultamiento específica para bash
        if '# hide' in stripped:
            continue
            
        # 3. Ignorar líneas que son solo comentarios
        if stripped.startswith('#'):
            continue
            
        # 4. Quitar comentarios en línea (asume un espacio antes del # para no romper rutas u otras cosas)
        line_no_inline: str = line.split(' #')[0]
        
        # 5. Guardar si la línea no quedó vacía
        if line_no_inline.strip():
            dense_lines.append(line_no_inline.rstrip())

    text: str = "\n".join(dense_lines)

    os.makedirs(os.path.dirname(outpath), exist_ok=True)
    with open(outpath, 'w', encoding='utf-8') as f:
        f.write(text + '\n')

def clean_cpp_file(filepath: str, outpath: str) -> None:
    """Reglas agresivas para los algoritmos en C++ (.cpp)"""
    raw_text: str = read_file_safely(filepath)

    no_block_comments: str = re.sub(r'/\*.*?\*/', '', raw_text, flags=re.DOTALL)
    no_main: str = remove_main_block(no_block_comments)
    
    lines: list[str] = no_main.split('\n')
    cleaned_lines: list[str] = []

    # Regex para ignorar importaciones locales, ej: #include "archivo.h"
    include_local_regex = re.compile(r'^[ \t]*#include[ \t]+"[^"]+"')

    for line in lines:
        stripped: str = line.strip()
        
        # 1. Ignorar boilerplate y marcas `// hide` (antes de quitar comentarios)
        is_boilerplate: bool = any(re.match(pattern, stripped) for pattern in BOILERPLATE_REGEX)
        if is_boilerplate:
            continue
            
        # 2. Ignorar importaciones de archivos locales (#include "archivo.h")
        if include_local_regex.match(stripped):
            continue
            
        # 3. Quitar comentarios al final de la línea respetando strings
        line_no_comment = remove_inline_c_comment(line)
        stripped_no_comment = line_no_comment.strip()
        
        if not stripped_no_comment:
            continue
            
        cleaned_lines.append(line_no_comment)

    text: str = "\n".join(cleaned_lines)

    os.makedirs(os.path.dirname(outpath), exist_ok=True)
    with open(outpath, 'w', encoding='utf-8') as f:
        f.write(text + '\n')

def main() -> None:
    if not os.path.exists(INPUT_DIR):
        print(f"Crea una carpeta llamada '{INPUT_DIR}' y pon tus códigos ahí.")
        return

    count: int = 0
    
    for root, _, files in os.walk(INPUT_DIR):
        for file in files:
            in_path: str = os.path.join(root, file)
            out_path: str = in_path.replace(INPUT_DIR, OUTPUT_DIR, 1)
            
            if file == 'template.h':
                clean_template_file(in_path, out_path)
                count += 1
            elif file.endswith('.sh'):
                clean_bash_file(in_path, out_path)
                count += 1
            elif file.endswith('.cpp'):
                clean_cpp_file(in_path, out_path)
                count += 1
                
    print(f"¡Listo! Se procesaron {count} archivos. Revisa la carpeta '{OUTPUT_DIR}'.")

if __name__ == '__main__':
    main()
